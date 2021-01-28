#include <stdio.h>
#include <gcrypt.h>
#include <sys/types.h>
#include "foo.h"

gcry_mpi_t p;
gcry_mpi_t a;
gcry_mpi_t d;
gcry_mpi_t q;
gcry_mpi_t u;
gcry_mpi_t v;

gcry_mpi_t zero;
gcry_mpi_t one;
gcry_mpi_t two;

int main()
{
    params_set1(); //256 - bit param set
    printf("\n256 - bit test start\n\n");
   
    gcry_mpi_t rand1 = gcry_mpi_new(0);
    gcry_mpi_randomize(rand1, 256, GCRY_STRONG_RANDOM);
    
    gcry_mpi_t rand2 = gcry_mpi_new(0);
    gcry_mpi_randomize(rand2, 256, GCRY_STRONG_RANDOM);
    
    struct point f;
    init_point(&f);

    f.x = u;
    f.y = v;
    f.z = one;
    
    struct point k;
    init_point(&k);
    k = binary(&f, &rand1); // Random values for better accuracy
    
    check_if_on_curve(&k); //Test 1: k is on curve
    
    f = binary(&f, &q); 
    check_identity(&f); // Test 2: if [q]P = 0 
    
    check_neighbors(&k); // Tests 3.1 & 3.2: [q+1]P == P && [q-1]P == -P
    
    check_lineary(&f, &rand1, &rand2); // Test 4: [k1]P + [k2]P == [k1 + k2]P 
    
    
    
    params_set2(); //512 - bit param set
    printf("\n512 - bit test start\n\n");
   
    gcry_mpi_randomize(rand1, 512, GCRY_STRONG_RANDOM);
    
    gcry_mpi_randomize(rand2, 512, GCRY_STRONG_RANDOM);

    f.x = u;
    f.y = v;
    f.z = one;
   
    
    k = binary(&f, &rand1); // Random values for better accuracy
    
    check_if_on_curve(&k); // Test 1
    
    f = binary(&f, &q); 
    check_identity(&f); // Test 2
    
    check_neighbors(&k); // Test 3.1 & 3.2
    
    check_lineary(&f, &rand1, &rand2); // Test 4

    gcry_mpi_release(rand1); // Free memory
    gcry_mpi_release(rand2);
    release_memory();
}
