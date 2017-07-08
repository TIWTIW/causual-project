/*
YOUR NAME HERE
CSE 351 - Winter 2013
Lab 4 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 64bytes
    cache size = 262144bytes
    associativity = 1
mystery1:
    block size = 8 bytes
    cache size = 16384bytes
    associativity = 4
mystery2:
    block size = 16bytes
    cache size = 65536bytes
    associativity = 16
mystery3:
    block size = 2bytes
    cache size = 131072bytes
    associativity = 2
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */

  int i = 0;

  access_cache( (unsigned long long)( i ));
  ++i;
  for( ; ; i = i + 1 )
  {
      if( !access_cache( (unsigned long long)(i) ) )
          break;
  }

  return i;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
 
  flush_cache();

  const int bs = block_size;
  int i = 0;
  int result = 1;

  while( 1 )
  {
      flush_cache();
      for( i = 0; i < result; i = i + bs )
          access_cache( (unsigned long long)( i ) );

      if( !access_cache( (unsigned long long)( 0 ) ) )
          break;
      result = result << 1;
  }

  return result >> 1;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
  /* YOUR CODE GOES HERE */
  flush_cache();

  int i = 0;
  int j = 0;
  int time = 0;
  for( i = 0; ; i += cache_size )
  {
      access_cache( i );

      for( j = 0; j < i; j += cache_size )
        if( !access_cache( j ) )
            return time;
      time++;
  }
  return -1;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
