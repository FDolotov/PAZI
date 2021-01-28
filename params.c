#include "params.h"

// 256 - bit param set
//id-tc26-gost-3410-2012-256-paramSetA

void params_set1()
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

    zero = gcry_mpi_new(0);
    gcry_mpi_scan(&zero, GCRYMPI_FMT_HEX, "0", 0, &scanned);
}


//512 - bit param set
//id-tc26-gost-3410-2012-512-paramSetC

void params_set2()
{
    size_t scanned;

    p = gcry_mpi_new(0);
    gcry_mpi_scan(&p, GCRYMPI_FMT_HEX, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDC7", 0, &scanned);

    a = gcry_mpi_new(0);
    gcry_mpi_scan(&a, GCRYMPI_FMT_HEX, "1", 0, &scanned);    

    d = gcry_mpi_new(0);
    gcry_mpi_scan(&d, GCRYMPI_FMT_HEX, "9E4F5D8C017D8D9F13A5CF3CDF5BFE4DAB402D54198E31EBDE28A0621050439CA6B39E0A515C06B304E2CE43E79E369E91A0CFC2BC2A22B4CA302DBB33EE7550", 0, &scanned);    
    
    q = gcry_mpi_new(0);
    gcry_mpi_scan(&q, GCRYMPI_FMT_HEX, "3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC98CDBA46506AB004C33A9FF5147502CC8EDA9E7A769A12694623CEF47F023ED", 0, &scanned);    
    
    u = gcry_mpi_new(0);
    gcry_mpi_scan(&u, GCRYMPI_FMT_HEX, "12", 0, &scanned);    
    
    v = gcry_mpi_new(0);
    gcry_mpi_scan(&v, GCRYMPI_FMT_HEX, "469AF79D1FB1F5E16B99592B77A01E2A0FDFB0D01794368D9A56117F7B38669522DD4B650CF789EEBF068C5D139732F0905622C04B2BAAE7600303EE73001A3D", 0, &scanned);

    two = gcry_mpi_new(0);
    gcry_mpi_scan(&two, GCRYMPI_FMT_HEX, "2", 0, &scanned);

    one = gcry_mpi_new(0);
    gcry_mpi_scan(&one, GCRYMPI_FMT_HEX, "1", 0, &scanned);

    zero = gcry_mpi_new(0);
    gcry_mpi_scan(&zero, GCRYMPI_FMT_HEX, "0", 0, &scanned);
}


//Function for clear memory allocated for params
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
