#ifndef __MyHeader_H_
#define __MyHeader_H_

#include    <sys/types.h>   /* basic system data types */
#include    <sys/time.h>    /* timeval{} for select() */
#include    <time.h>        /* timespec{} for pselect() */
#include    <errno.h>
#include    <fcntl.h>       /* for nonblocking */
#include    <limits.h>      /* PIPE_BUF */
#include    <signal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string>
#include    <math.h>
#include    <sys/stat.h>    /* for S_xxx file mode constants */
#include    <unistd.h>
#include    <sys/wait.h>
#include    <semaphore.h>
#include    <mqueue.h>      /* Posix message queues */
#include    <pthread.h>
#include    <semaphore.h>   /* Posix semaphores */
#include    <sys/mman.h>    /* Posix shared memory */

//#define MAP_FAILED  ((void *)(-1))

#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
                    /* default permissions for new files */
/* $$.ix [FILE_MODE]~constant,~definition~of$$ */
#define DIR_MODE    (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

//#define min(a,b)    ((a) < (b) ? (a) : (b))
//#define max(a,b)    ((a) > (b) ? (a) : (b))

#endif // __MyHeader_H_