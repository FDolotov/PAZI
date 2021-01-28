#ifndef FOO_H
#define FOO_H

#include "params.h"

struct point
{
    gcry_mpi_t x;
    gcry_mpi_t y;
    gcry_mpi_t z;
};

void init_point(struct point* p);
void release_point(struct point* p1);
void print_point(struct point* p);
void convert(struct point*);

struct point doubling(struct point*);
struct point summ(struct point*, struct point*);
struct point binary(struct point*, gcry_mpi_t*);

void check_if_on_curve(struct point*); // Test 1
void check_identity(struct point*); // Test 2
void check_neighbors(struct point*); // Test 3.1 & 3.2
void check_lineary(struct point*, gcry_mpi_t*, gcry_mpi_t*); // Test 4

#endif
