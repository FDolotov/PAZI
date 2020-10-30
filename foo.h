#ifndef FOO_H
#define FOO_H

#include "params.h"

struct point
{
    gcry_mpi_t x;
    gcry_mpi_t y;
    gcry_mpi_t z;
};

struct point convert(struct point);
struct point doubling(struct point);
struct point summ(struct point, struct point);
struct point binary(struct point, gcry_mpi_t);
void check_if_on_curve(struct point);
void check_identity(struct point);
void check_neighbors(struct point);
void check_lineary(struct point, gcry_mpi_t, gcry_mpi_t);

#endif
