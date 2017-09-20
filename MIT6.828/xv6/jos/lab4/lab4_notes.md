# Lab4:抢占式多任务  
## Introduction  
在这个实验中你将在多个同时活动的用户模式的进程间完成抢占式多任务。  
在PART A你将给JOS添加一个多处理器的处理，完成轮询调度，以及添加基本的进程管理系统调用。  
在PART B你将完成一个像UNIX的fork，允许用户模式的进程创造一个自己的拷贝。  
最后，在PART C，你将给IPC添加支持，允许不同的用户模式进程互相通信并且互相显式的同步。你也将给硬件时钟中断添加支持。  
## PART A:多处理器支持和协同多任务  
在本实验的第一部分，你将首先扩展JOS来运行一个多任务系统，然后完成一些新的JOS内核系统调用来允许用户进程创建额外的新的进程。你也将完成协同轮询调度，允许内核从一个进程切换到另一个，当现在的进程自愿的放弃CPU时。然后在PART C，你将完成抢占式的调度，从而允许内核在一段时间之后从一个进程中重新控制CPU即使进程不合作。  
### 多处理器支持  
我们将使JOS支持对称的多任务`SMP`，一个多处理器的模型，在该模型中所有的CPU有同等的对系统资源例如内存和I/O总线的接触。当所有的CPU在SMP中是功能性的相同的，在引导过程中它们可以被分成两类：引导处理器(BSP)对初始化系统以及引导操作系统负责，应用处理器(AP)只有在操作系统启动并开始运行后被BSP激活。哪个处理器是BSP是由硬件和BIOS决定的。在这个点上，所有的存在的JOS代码都运行在BSP上。  
在一个SMP系统中，每个CPU有一个伴随的本地APIC(LAPIC)单元。LAPIC单元对在整个系统中生成中断负责。LAPIC也提供了一个与其连接的CPU的一个独一无二的id(不是CPU id。。特此注明)。在这个实验中，我们确保以下基本的LAPIC单元的功能：  
1. 阅读LAPIC ID来告诉我们的代码在哪个CPU上运行(cpunum()).  
2. 从BSP发送`STARTUP`跨处理器中断(IPI)到AP来启动其他CPU(`lapic_startap()`)  
3. 在PART C，我们编写一个LAPIC的内建定时器来生成时钟中断以支持抢占式多任务(`apic_init()`).  
一个处理器使用内存映射I/O接触它的LAPIC。在MMIO中，部分的物理内存是硬连接到一些I/O设备的寄存器的，所以相同的通常被使用来接触接触内存的加载/存储指令可以被使用来接触设备寄存器。你已经看到了一个I/O洞在物理地址`0xA0000`(我们使用它来写VGA显示器缓存)。LAPIC在一个从物理地址`0xFE000000`开始的洞，所以对于我们来说使用我们直接的在`KERNBASE`的映射太高了。JOS虚拟内存映射在`MMIOBASE`处留下了4M的沟，所以我们有一个地方映射设别。因为接下来的lab会介绍更多的MMIO的区域，你将写一个简单的函数来从这个区域分配空间以及映射设备内存。  
练习1：完成`kern/pmap.c`中的`mmio_map_region`.为了看它是怎么被使用的，看`kern/lapic.c`的`lapic_init`的开始处。  
`mmio_map_region`:比较简单，基本上就是调用`boot_map_region`.  
### 应用处理器的启动  
在启动AP之前，BSP应该首先收集关于多处理器系统的信息，例如CPU的总的数目，它们的APIC ID和LAPIC单元的MMIO地址。在`kern/mpconfig.c`中的`mp_init()`函数通过读在BIOS区域内存中的MP设置表来收集这些信息。  
`boot_aps()`函数(在`kern/init.c`)驱动AP的引导过程。AP在实模式下开启，很像bootloader在`boot/boot.S`中开始，所以`boot_aps()`复制了AP入口点代码(`kern/mpentry.S`)到在实模式下可以寻址的一个内存区域。不像bootloader，我们有一些AP开始执行代码的位置的控制。我们复制入口点代码到`0x7000`(`MPENTRY_PADDR`)，但是任何未被使用的，在640KB以下的页对齐的物理地址是可以的。  
在那之后，`boot_aps`一个一个的激活AP，通过发送`STARTUP`IPI给对应的AP的LAPIC 单元，一起发送的还有一个初始的`CS:IP`地址，在该地址AP应当开始运行它自己的入口点代码(在我们的例子中是`MPENTRY_PADDR`)。在`kern/mpentry.S`中的入口点代码是和`boot/boot.S`中的代码很像的。在一些简答的启动之后，它将AP放到保护模式下，此时分页被开启了，然后调用C设置的`mp_main()`.`boot_aps`等待AP发送一个`CPU_STARTED`标志到它的`struct CpuInfo`中的`cpu_status`状态，在唤醒其他的之前。  
练习2：阅读`boot_aps`和`mp_main`,以及`mpentry.S`.确保你明白在AP的引导期间的控制流转换。然后修改你的`pmap.c`中的`page_init`来避免在空闲链表中添加`MPENTRY_PADDR`添加页。这样我们可以安全的拷贝和运行AP引导代码在该物理地址。你的代码应当通过更新的`check_page_free_list`，但是可能会在`check_kern_pgdir`失败。
`pmap.c`:只要在`page_init`中添加当i等于`MPENTRY_PADDR/PGSIZE`时不要分配空闲页就行。  
### Per-CPU状态和初始化  
当写一个多处理器OS时，区分per-CPU的状态和全局的所有系统共享的状态是十分重要的。`kern/cpu.h`定义了大部分的per-CPU状态，包括`struct CpuInfo`，它保存了per-CPU变量。`cpunum()`总是返回调用它的CPU的ID，这样就可以通过`cpu`矩阵索引它了。自主的，宏`thiscpu`是当前CPU的`struct cpuinfo`。  
这里是一些你应当知道的per-CPU状态  
* per-CPU内核栈：因为多个CPU可以同时陷入到内核，我们需要一个分离的内核栈给每个处理器来防止它们影响各自的执行。矩阵`percpu_kstacks[NUCPU][KSTKSIZE]`为了NCP的内核栈保留空间  
* per-CPU TSS和TSS描述子：一个per-CPU TSS也是需要的，这是为了指出每个CPU的内核栈在哪里。为CPU i的TSS在`cpu[i].cpu_ts`中保存，对应的TSS描述子在GDT条目`gdt[(GD_TSS0 >> 3+i]`中定义。全局的`ts`变量将不再有用。  
* per-CPU的当前进程指针：因为每个CPU可以同时运行不同的用户进程，我们重新定义了标志`curenv`指代`cpus[cpunum()].cpu_env`，指向当前的CPU正在执行的当前的进程。  
* per-CPU系统寄存器：所有的寄存器，包括系统寄存器，对CPU来说都是私人的，因此，初始化这些寄存器的指令，例如`lcr3`，`ltr`，`lgdt`，`lidt`等，都应当在各自的CPU上进行。函数`env_init_percpu()`和`trap_init_percpu`是为这个目的定义的。  
练习3：修改`mem_init_mp()`来映射从`KSTACKSTOP`开始的per-CPU栈，正如在`inc/memlayout.h`中那样。每个栈的大小是`KSTKSIZE`大小加上`KSTKGAP`字节的未映射保护页。  
练习4：在`trap_init_percpu`中的代码为BSP初始化TSS和TSS描述子。它在lab3中是队的，但是在其他CPU上是不正确的，修改它。  
`mem_init_mp`:比较的简单把，其实就是对应的区域的映射，自己看看代码，看看提示很容易写。  
`trap_init_percpu`:大部分都还好，直接改成对应cpu的ts就行了，但是有个疑点就是段描述子到底是个啥，为啥要左移3位，为啥加载的时候又不用，这是个问题，以后必须搞清楚。再说，每个段不都是从0到0xffffffff吗。。。。

### 锁  
我们的现在的代码在初始化AP之后就开始自旋了。。。主要讲了大的内核锁，说了应该上锁和释放锁的位置。  
练习5：在上面说的适当的位置加锁和解锁。姑且先加了。。具体对不对得等下个练习。。  

问题：看起来使用大的锁只保证一次只有一个CPU可以运行在内核模式。为什么我们仍然需要为每个CPU分离内核栈？描述一个使用共享内核栈将会发生错误的场景，即使有大的内核锁的保护。  
答：这里不太知道。。查看了别人的，据说是因为不同的内核栈上有不同的信息，可能内核中会留下自己的CPU以后要用的数据。

### 轮询调度  
你的下一个任务是改变JOS内核这样它能自主的在轮询模式下的不同进程间切换。JOS的轮询像下面一样操作：  
1. 函数`sched_yield`负责选择一个新的进程运行。它循环并且顺序的搜寻`envs[]`数组，就在先前运行的进程之后开始(或者在之前没有运行进程的数组的开始)，选择第一个状态为`ENV_RUNNABLE`的进程，然后调用`env_run`来跳到该进程。  
2. `sched_yield`必须从不在两个CPU上运行相同的进程。它能够表明当前在一些CPU上运行的进程因为进程的状态是`ENV_RUNNING`。  
3. 我们为你完成了一个新的系统调用`sys_yield()`，这是我们的用户进程用来调用内核`sched_yield`函数的，并且会周期性的放弃CPU给一个不同的进程。  
练习6：在`sched_yield`中完成轮询调度。不要忘记修改`syscall`来解包`sys_yield`.确保在`mp_main`中接触`sched_yield`.  
修改`kern/init.c`来创造三个或者更多进程都运行着`user/yield.c`。
