#result for lab4 part I
1. Test System        
My computer in my lab in USTC(western campus, avtivity center), Linux ubuntu16.04, 64bit. CPU:P    entium(R) Dual-Core  CPU      E5700  @ 3.00GH  
2. Test Result  

| Array Size | Performing src assignment? | App | Time with i then j | Time with j then i  |
| ---------- |----------------------------|-----|------------------  |---------------------|
|  2048      |              No            |  C  |       0.16         |     2.79            |
|  2048      |              No            | C O |       0.11         |     2.77            |
|  2048      |              No            |  J  |       1.51         |     8.25            |
|  2048      |              No            | J I |       1.75         |     8.38            |
|  2048      |              Yes           |  C  |       0.23         |     3.26            |
|  2048      |              Yes           | C O |       0.17         |     2.95            |
|  2048      |              Yes           |  J  |       2.33         |     12.23           |
|  2048      |              Yes           | J I |       8.63         |     20.72           |
|  4096      |              No            |  C  |       0.63         |     11.83           |
|  4096      |              No            | C O |       0.46         |     12.06           |
|  4096      |              No            |  J  |       5.86         |     33.32           |
|  4096      |              No            | J I |       6.91         |     48.27           |
|  4096      |              Yes           |  C  |       1.31         |     14.31           |
|  4096      |              Yes           | C O |       0.71         |     14.06           |
|  4096      |              Yes           |  J  |       9.12         |     34.16           |
|  4096      |              Yes           | J I |  7.06 outofmemory? | 18.94 outofmemory?  |
  
3. Q&A  
    1. The difference is that the type of one's is Integer while the other is typical. I'm not in java so I don't quite understand the difference. 
    2. The pair that surprised me most is the one that in the 10 and 11 line of the table, and Time with j then i. In my opinion, the time of the one which is optimizaed shouldn't be slower than the other. 
    3. change before: without optimizaed: too long...I give up with: 0 second   
       change after: without : so long... with : also so long...
