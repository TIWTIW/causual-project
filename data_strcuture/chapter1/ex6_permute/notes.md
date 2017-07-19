# Permute
&emsp;&emsp;全排列算法也算是比较经典的问题了，之前已经做过一遍，但是当时其实也是一知半解，这回自己写一下，希望能彻底搞懂

## 一、经典全排列
&emsp;&emsp;全排列问题的定义其实很简单，就是给一个数组，要输出它所有排列的可能性，例如，给了"abc",得出的答案应该有"abc"、"acb"、"bac"、"bca"、"cab"、"cba",这就是所有可能的排列了。  
&emsp;&emsp;全排列算法最先想到的应当是递归的解法，因为要知道n位的排列，可以固定第1位不动，获取后面n-1位的全排列，然后固定第2位。。。直到最后一位，接着依次交换第1位和其他位，这样就可以得到所有的全排列。值得注意的是，每次获取后面的全排列都应当保持数组原有位置不变，否则就可能陷入重复。  
&emsp;&emsp;话虽然是这么说，真正写起程序来还是很捉急。程序的设计思路其实很简单，核心的代码如下
```
for( int i = low; i <= high; ++i )
{
   swap( str[low], str[i] );
   permute( str, low + 1, high );
   swap( str[low], str[i] );
}
```
&emsp;&emsp;其中`permute`就是递归函数名称了。这里的思想其实就是从低位到高位，交换低位和第i位，然后获取以低位之后一位的全排列，接着再将低位和第i位换回来，保持数组原样不变，再推进i，重复上述过程。  
&emsp;&emsp;还是举个例子把，以`"abc"`为例，首先交换`a`和`a`不变，接着获取`“bc”`的全排列，而`“bc”`中首先交换`b`和`b`，接着进入`c`的全排列，显然只有`c`，于是返回，于是交换回`b`和`b`，推进一步，交换`b`和`c`，进入`b`的全排列，显然只有`b`，于是再返回，交换回`b`和`c`。这样排列仍然为`abc`，这里又是返回，回到了`abc`，交换回`a`和`a`，并且推进，交换`a`和`b`，得到`bac`，重复上述步骤。

## 二、字典序排列
&emsp;&emsp;全排列是一个博大精深的问题。。。除了上述经典的全排列之外，由全排列又引出了一些其它的问题，我写着试试。  
&emsp;&emsp;首先是字典序排列问题，这个问题以前刷LeetCode的时候貌似也见过。那么什么是字典序排列呢，其实就是从小到大的排列，也即顺序排列。刚刚的全排列算法输出的排列毋庸置疑是不是顺序的，举个例子的话，`123`的字典序排列如下：  
```
123
132
213
231
312
321
```
&emsp;&emsp;那么如何才能得到字典序输出的排列呢？在那之前，还是先看一下有了一个已知的序列之后，如何得到它的下一个字典序，具体方法的证明貌似比较复杂，我直接给出方法：  
&emsp;&emsp;令数组为a，大小为n，从序列的最后一个元素往前回溯，直到找到某个m,使得a[m+1] > a[m],在a[m+1]在a[n-1]间找到最大的元素，和a[m]交换，然后对a[m+1]和a[n-1]之间的元素进行排序，得到的就是该序列的下一个字典序排列。  
&emsp;&emsp;好了，那么在可以知道某个序列的下一个字典序之后，想要得到按序输出的字典序，只要先对输入序列排序，得到最小的字典序输出，接着不断得到序列的下一个字典序，直到最大的字典序输出即可。  

# 三、去重全排列
&emsp;&emsp;上述第一种方法对于出现重复数字的情况是不行的，因为当出现重复数字时，会输出重复的排列，那么应该怎么去重呢？
&emsp;&emsp;关于这一块，我也找了很久，不过大多没有给出很详细的说明，基本上是举了个例子，然后得出的结论是待交换元素与第1个元素之间不应当出现和待交换元素相同的元素，也就是在[i,j)中不出现和j相同的元素即可以完成全排列，暂时还真不明白，姑且先记着把。  
P.S.目前的理解只能是如果出现了相同的元素，那么说明之前已经生成过全排列了，所以就不用再次重复。
P.P.S. 还可以用DFS生成全排列。。。

---
&emsp;&emsp;其实还有全排列的一些比较冷门的东西，例如什么中介数之类的，以后有机会用到再看把。。。