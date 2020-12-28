#ifndef PARAMS_H
#define PARAMS_H

#include <gcrypt.h>
#include <sys/types.h>

extern gcry_mpi_t p;
extern gcry_mpi_t a;
extern gcry_mpi_t d;
extern gcry_mpi_t q;
extern gcry_mpi_t u;
extern gcry_mpi_t v;

extern gcry_mpi_t zero;
extern gcry_mpi_t one;
extern gcry_mpi_t two;

extern void set_params();
extern void release_memory();

#endif
