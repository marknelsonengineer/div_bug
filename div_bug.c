#include <stdio.h>
#include <stdint.h>

int main() {
   printf( "div_bug\n" );

   uint8_t rval;

   // rdrand sets CF on success... I've tried this with and without this 
   // check and the program still throws an exception

   // This works as expected
   asm volatile (
//     "try_again_1:"
       "rdrand ax;"           // If CF==0, then the rdrand failed... try again
//     "jnc    try_again_1;"
       "mov    ax, 42;"       // This works... as expected
       "mov    cl, 4;"
       "div    cl;"
       "mov    %0, ah;"
      :"=r" ( rval )          // Output
      :                       // Input
      :"ax", "cl", "cc"   );  // Clobbers

   printf( "The first return value is %u\n", rval );


   // This throws a `Floating point exception (core dumped)`
   asm volatile (
//     "try_again_2:"
       "rdrand ax;"           // If CF==0, then the rdrand failed... try again
//     "jnc    try_again_2;"
//     "mov    ax, 42;"       // <---- Remove this and it breaks
       "mov    cl, 4;"
       "div    cl;"
       "mov    %0, ah;"
      :"=r" ( rval )          // Output
      :                       // Input
      :"ax", "cl", "cc"   );  // Clobbers

   printf( "The second return value is %u\n", rval );

}