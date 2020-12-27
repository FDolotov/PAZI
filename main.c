#include <stdio.h>
#include <gcrypt.h>
#include <sys/types.h>
#include "foo.h"

int main()
{
    size_t scanned;
    gcry_mpi_t H = gcry_mpi_new(0);
    gcry_mpi_scan(&H, GCRYMPI_FMT_HEX, "F", 0, &scanned);
    gcry_mpi_t J = gcry_mpi_new(0);
    gcry_mpi_scan(&J, GCRYMPI_FMT_HEX, "4", 0, &scanned);

    set_params();

    struct point f; 
    struct point j = {u, v, J};

    f = binary(j, q);
    check_if_on_curve(f);
    check_identity(f);
    check_neighbors(f);
    check_lineary(j, H, J);

    gcry_mpi_release(J);
    gcry_mpi_release(H);


    release_memory();
}
