#ifndef PARAMS_H
#define PARAMS_H

#include <gcrypt.h>
#include <sys/types.h>

gcry_mpi_t p;
gcry_mpi_t a;
gcry_mpi_t d;
gcry_mpi_t q;
gcry_mpi_t u;
gcry_mpi_t v;

gcry_mpi_t zero;
gcry_mpi_t one;
gcry_mpi_t two;

extern void set_params();
extern void release_memory();

#endif
