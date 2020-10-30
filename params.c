#include "params.h"

void set_params()
{
    size_t scanned;
    p = gcry_mpi_new(0);
    gcry_mpi_scan(&p, GCRYMPI_FMT_HEX, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD97", 0, &scanned);

    a = gcry_mpi_new(0);
    gcry_mpi_scan(&a, GCRYMPI_FMT_HEX, "1", 0, &scanned);    

    d = gcry_mpi_new(0);
    gcry_mpi_scan(&d, GCRYMPI_FMT_HEX, "605F6B7C183FA81578BC39CFAD518132B9DF62897009AF7E522C32D6DC7BFFB", 0, &scanned);    
    
    q = gcry_mpi_new(0);
    gcry_mpi_scan(&q, GCRYMPI_FMT_HEX, "400000000000000000000000000000000FD8CDDFC87B6635C115AF556C360C67", 0, &scanned);    
    
    u = gcry_mpi_new(0);
    gcry_mpi_scan(&u, GCRYMPI_FMT_HEX, "D", 0, &scanned);    
    
    v = gcry_mpi_new(0);
    gcry_mpi_scan(&v, GCRYMPI_FMT_HEX, "60CA1E32AA475B348488C38FAB07649CE7EF8DBE87F22E81F92B2592DBA300E7", 0, &scanned);

    two = gcry_mpi_new(0);
    gcry_mpi_scan(&two, GCRYMPI_FMT_HEX, "2", 0, &scanned);

    one = gcry_mpi_new(0);
    gcry_mpi_scan(&one, GCRYMPI_FMT_HEX, "1", 0, &scanned);

    gcry_mpi_t zero = gcry_mpi_new(0);
    gcry_mpi_scan(&zero, GCRYMPI_FMT_HEX, "0", 0, &scanned);
}

void release_memory()
{
    gcry_mpi_release(p);
    gcry_mpi_release(a);
    gcry_mpi_release(d);
    gcry_mpi_release(q);
    gcry_mpi_release(u);
    gcry_mpi_release(v);
    gcry_mpi_release(zero);
    gcry_mpi_release(one);
    gcry_mpi_release(two);
}
