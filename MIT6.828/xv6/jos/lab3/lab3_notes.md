# Lab3 :User Environments  
## Introduction  
在这一实验中你将完成基本的内核设施使得可以在受保护的用户模式环境下运行。你将增强JOS来设置数据结构来跟踪用户环境，创造一个单用户的环境，加载一个程序映像，并使他开始运行。你也将使得JOS内核可以处理任何的系统调用以及其他异常。  
**注意**:在这一实验中，单词环境和进程是可以交换的，都指代可以让你运行一个进程的抽象。我们使用环境而不是进程来强调JOS环境和UNIX进程提供不同的接口，不提供相同的机制。  
## PART A:用户环境和异常处理  
新包括的文件`inc/env.h`包含了基本的JOS中的用户环境的定义。阅读它。内核使用`ebv`数据结构来跟踪每个用户环境。在这一实验中你将初始的创建一个环境，但是你需要设计JOS内核来支持多环境。lab4将完成这一特征--通过fork调用。  
正如你在`kern/env.c`中看到的，内核维持三个主要的全局变量：  
```
struct Env *envs = NULL;		// All environments
struct Env *curenv = NULL;		// The current env
static struct Env *env_free_list;	// Free environment list
```

一旦JOS开启运行了，`envs`指向`env`结构的数组，代表了系统中所有的环境。在我们的设计中，JOS内核将支持最多`NENV`个同时有效的环境，虽然通常只有少数的环境在给定时间运行(`NENV`是一个常量定义在`inc/env.h`中)。一旦它被分配了，`envs`矩阵对于每个`NENV`可能的环境将包含一个`Env`数据结构的单例。  
JOS内核在`env_free_list`中保持所有的不活跃的`Env`结构。这一设计允许简单的环境的分配与回收，它们只需要从空闲链表中被加或者移除。  
内核使用`curenv`标志来跟踪正在执行的环境。在引导时，在第一个环境运行之前，`curenv`被初始化为NULL。  
### 环境状态  
`Env`结构在`inc/env.h`中被定义为如下：  
```
struct Env {
	struct Trapframe env_tf;	// Saved registers
	struct Env *env_link;		// Next free Env
	envid_t env_id;			// Unique environment identifier
	envid_t env_parent_id;		// env_id of this env's parent
	enum EnvType env_type;		// Indicates special system environments
	unsigned env_status;		// Status of the environment
	uint32_t env_runs;		// Number of times environment has run

	// Address space
	pde_t *env_pgdir;		// Kernel virtual address of page dir
};
```
这些是`Env`的域中是啥：  
**env_tf**:持有当环境不再运行时被保存的寄存器值：也就是，当内核或者不同的环境在运行时。内核保存这些当从用户态到内核态，所以环境接下来可以恢复从中断的地方开始。  
**env_link**:这是到在空闲链表`env_free_lsit`的下一个`Env`的链。`env_free_list`指向链表中的第一个自由的环境。  
**env_id**:内核在这里存储一个值，唯一的表示当前正在运行的环境(也就是，在`envs`矩阵中使用这一特殊的槽)。在一个用户环境终止后，内核可能重新分配相同的`env`结构给不同的环境 - 但是新的环境会有一个不同的`env_id`即使新的环境是重用`envs`矩阵中相同的槽。  
**env_parent_id**:内核在这里保存创建这个环境的`env_id`，用这种方法环境可以形成一个家族树，在决定每个环境可以允许对谁做什么这种安全决策时比较有效。  
**env_type**:被用来区分特殊的环境。对于大多数环境，它将是`ENV_TYPE_USE`。  
**env_status**:五种，自己看把。。  
**env_pgdir**:持有环境的页表目录的内核中的虚拟地址。  
就像一个UNIX进程一样，一个JOS环境将线程和地址空间的概念连在一起。线程被保存的寄存器(`env_tf`域)定义，地址空间被页表目录定义。为了运行一个环境，内核必须用保存的寄存器和合适的地址空间设置CPU。  
我们的`struct Env`和xv6的`proc`比较像。两个结构都有环境的用户模式寄存器状态在`trapframe`中。在JOS中，独立的环境没有它们自己的内核栈而xv6中有。一次只有一个JOS环境在内核中是活跃的，所以JOS只需要一个内核栈。  
### 分配环境矩阵  
在`mem_init`中分配一个矩阵给`Env`结构，叫做`envs`。  
Ex1. 修改`mem_init`，分配和映射`envs`矩阵。这一矩阵由`NENV`个`Env`结构组成。像`pages`矩阵一样，在`envs`的内存也应该被映射成用户只读在`UENVS`。
和pages的分配是一个套路的。。。直接再来一遍就行了。  
### 创造和运行环境  
你现在要写在`kern/env.c`中的代码来运行一个用户进程(下文将把环境变为进程)。因为我们现在还没有文件系统，我们将设置内核在加载一个静态的二进制的嵌入在内核中的映像。  
lab3的`GNUmakefile`生成了一系列的在二进制映像在`obj/usr`目录中。如果你看`kern/Makefrag`，你将注意到一些魔幻的直接链接到内核可执行文件好像它们是`.o`文件。`-b binary`的在链接器中的选项使得这些文件被链接好像原始的二进制文件而不是由编译器生成的`.o`文件。  
练习2：在文件`env.c`中，完成下列函数。  
`env_init`:在`envs`矩阵中初始化所有的`Env`结构体并将它们加到`env_free_list`中。也调用`env_init_percpu`,它配置了分段硬件。  
`env_setup_vm`:分配一个页表目录给新的进程并初始化地址空间中的内核部分  
`region_alloc`:分配以及映射一个进程的物理地址  
`load_icode`:你将需要解析一个ELF二进制文件的映像，很像bootloader已经做的，并且把它的内容加载到新进程的用户地址空间。  
`env_create`:使用`env_alloc`分配一个进程并且调用`load_icode`来加载一个ELF文件映像。  
`env_run`:开始一个给定的进程在用户模式下运行  
在你写这些函数的时候，`cprintf`的`%e`选项是有用的 -- 它打印一个对应错误代码的错误的描述，例如  
```
	r = -E_NO_MEM;
	panic("env_alloc: %e", r);
```

下面是一个调用图：  
``` 
    start (kern/entry.S)
    i386_init (kern/init.c)
        cons_init
        mem_init
        env_init
        trap_init (still incomplete at this point)
        env_create
        env_run
            env_pop_tf

```
如果一切正常，你的系统将会进入用户空间，并且执行`hello`二进制文件，直到它使用`int`指令进行系统调用。在当时JOS还没有设置硬件允许任何形式的从用户空间到内核空间的转换。当CPU发现还没有设置好处理系统调用，它生成一个通用的保护异常，发现不能处理，生成一个double fault异常，发现也不能处理，最后使用被叫作`triple fault`的机制放弃。通常你会看到CPU重置系统重启。虽然这对于合法的应用来说是重要的，对于内核的发展来说并不好，所以在6.828的QEMU中你将看到一个寄存器崩溃以及`Triple fault`信息。  
我们将短暂的address这个问题，但是现在我们可以使用调试器来检查我们已经进入用户模式了。使用`make qemu-gdb`并且在`env_pop_tf`中设置断电，这是在实际进入用户模式前的最后一个函数。使用`si`单步这一函数，处理器将会在`iret`之后进入用户模式。你然后会看到用户进程可执行文件的第一条指令，是`cmpl`指令在`lib/entry.S`中的标志`start`。现在使用`b *0x...`来设置断电在`int $0x30`在`hello`中的`sys_cputs`处。这个`int`是在终端打印一个字符的系统调用。如果你现在不能执行`int`，那么你的地址空间设置有问题，或者程序加载代码有问题。  

练习解答：不想骂自己了都，捣鼓了一天，其实明明是正确的，结果自己不仔细看课程的说明，反而相信博客上的东西，结果在正确的基础上浪费了n多时间，也是醉了。这里要特别注意，估计以前旧版的实验进行到这里时，会不断重启，但是新版的已经改了，上面也说的挺清楚了，因为没有设置中断，此时程序就是会崩，用gdb一步步调试到那里就行，结果这一天都因为没重启白调了。  
`env_init`:这部分是进程链表的初始化，将对应进程结构中的变量初始化就行，需要注意的是空闲进程链表的形成。  
`env_setup_vm`:这部分是给新的进程设置虚拟内存，新分配一页物理页用来当作页表，然后把内核的页表复制给该页表，并且把它赋值给进程页表即可。最后把该页表的物理地址和虚拟地址空间中的`UVPT`位置联系起来。  
`region_alloc`:主要是分配物理页给进程，并且把该物理页的物理地址和传入的虚拟地址对应起来。主要是调用`page_alloc`和`page_insert`  
`load_icode`:主要是把二进制映像加载到进程的地址空间中，主要方法是读取镜像文件的ELF头，然后根据该文件头的信息。调用`region_alloc`分配地址，调用`memmove`复制镜像中的东西。这里有一点没看懂的是中途使用了进程自己的页表，虽然看着很有道理，但是不知道会造成什么影响。。接着把进程中的`tf_eip`设置为程序的入口地址，因为最后是靠`tf_eip`返回的。最后，分配一页物理内存给程序的初始栈。  
`env_create`:相当简单，其实就是调用`env_alloc`和`load_icode`分配一个进程以及加载二进制映像到其中。  
`env_run`:切换进程，将当前进程状态改为`RUNNABLE`，将传入的进程参数改为当前进程，最后的`env_pop_tf`,其实就是切换到该进程运行，因为最后是靠进程的`tf`结构体来保存环境的。之前设置了eip，所以会返回到该处。

