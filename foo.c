#include "foo.h"

//allocate memory for point
void init_point(struct point* p)
{
	p->x = gcry_mpi_new(0);
	p->y = gcry_mpi_new(0);
	p->z = gcry_mpi_new(0);
}


//release allocated memory for point
void release_point(struct point* p1)
{
	gcry_mpi_release(p1->x);
	gcry_mpi_release(p1->y);
	gcry_mpi_release(p1->z);
}

//return value of coordinates of point
void print_point(struct point* p)
{
	gcry_mpi_dump(p->x);
	printf("\n");
	gcry_mpi_dump(p->y);
	printf("\n");
	gcry_mpi_dump(p->z);
	printf("\n\n");
}


//Projective coordinates for twisted Edwards curve
//http://www.hyperelliptic.org/EFD/g1p/auto-twisted-projective.html
void convert(struct point* f)
{
    gcry_mpi_t buff = gcry_mpi_new(0);
    
    gcry_mpi_invm(buff, f->z, p); //z^-1
    gcry_mpi_mulm(f->x, buff, f->x, p); // x/z
    gcry_mpi_mulm(f->y, buff, f->y, p); // y/z
    f->z = one;
  
    
    gcry_mpi_release(buff);
}


//mmadd-2008-bbjlp
struct point summ(struct point* f, struct point* s)
{
    gcry_mpi_t x1 = gcry_mpi_new(0);
    gcry_mpi_t y1 = gcry_mpi_new(0);
    gcry_mpi_t x2 = gcry_mpi_new(0);
    gcry_mpi_t y2 = gcry_mpi_new(0);
    gcry_mpi_t buff = gcry_mpi_new(0);
    gcry_mpi_t buff2 = gcry_mpi_new(0);

    x1 = f->x;
    y1 = f->y;
    x2 = s->x;
    y2 = s->y;

    gcry_mpi_t C = gcry_mpi_new(0);
    gcry_mpi_mulm(C, x1, x2, p); //x1*x2

    gcry_mpi_t D = gcry_mpi_new(0);
    gcry_mpi_mulm(D, y1, y2, p); //y1*y2
    
    gcry_mpi_t E = gcry_mpi_new(0);
    gcry_mpi_mulm(buff, d, C, p); //d*C
    gcry_mpi_mulm(E, buff, D, p); // d*C*D

    struct point newpoint;
    init_point(&newpoint);
    
    
    //newpoint.x
    gcry_mpi_addm(buff, x1, y1, p);
    gcry_mpi_addm(buff2, x2, y2, p);
    gcry_mpi_mulm(buff, buff, buff2, p);
    gcry_mpi_subm(buff, buff, C, p);
    gcry_mpi_subm(buff, buff, D, p);
    gcry_mpi_subm(buff2, one, E, p);
    gcry_mpi_mulm(newpoint.x, buff2, buff, p);
    
    
    //newpoint.y
    gcry_mpi_addm(buff, one, E, p);
    gcry_mpi_mulm(buff2, a, C, p);
    gcry_mpi_subm(buff2, D, buff2, p);
    gcry_mpi_mulm(newpoint.y, buff, buff2, p);
    
    
    //newpoint.z
    gcry_mpi_powm(buff, E, two, p);
    gcry_mpi_subm(newpoint.z, one, buff, p);

    convert(&newpoint);
    return newpoint;

    release_point(&newpoint);
    
    gcry_mpi_release(x1);
    gcry_mpi_release(y1);
    gcry_mpi_release(x2);
    gcry_mpi_release(y2);
    gcry_mpi_release(buff);
    gcry_mpi_release(buff2);
    gcry_mpi_release(C);
    gcry_mpi_release(D);
    gcry_mpi_release(E);
}


//dbl-2008-bbjlp
struct point doubling(struct point* f)
{
    gcry_mpi_t x1 = gcry_mpi_new(0);
    gcry_mpi_t y1 = gcry_mpi_new(0);
    gcry_mpi_t z1 = gcry_mpi_new(0);
    gcry_mpi_t buff = gcry_mpi_new(0);

    x1 = f->x;
    y1 = f->y;
    z1 = f->z;

    gcry_mpi_t B = gcry_mpi_new(0);
    gcry_mpi_addm(buff, x1, y1, p); //x1 + y1
    gcry_mpi_powm(B, buff, two, p); //(x1 + y1)^2
    
    gcry_mpi_t C = gcry_mpi_new(0);
    gcry_mpi_powm(C, x1, two, p); //x1^2
    
    gcry_mpi_t D = gcry_mpi_new(0);
    gcry_mpi_powm(D, y1, two, p); //y1^2

    gcry_mpi_t E = gcry_mpi_new(0);
    gcry_mpi_mulm(E, a, C, p); //a*C 
    
    gcry_mpi_t F = gcry_mpi_new(0);
    gcry_mpi_addm(F, E, D, p); //E + D
    
    gcry_mpi_t H = gcry_mpi_new(0);
    gcry_mpi_powm(H, z1, two, p); //z1^2
    
    gcry_mpi_t J = gcry_mpi_new(0);
    gcry_mpi_mulm(buff, two, H, p); //2*H
    gcry_mpi_subm(J, F, buff, p); //F - 2*H

    struct point newpoint;
    init_point(&newpoint);

    
    //newpoint.x
    gcry_mpi_subm(buff, B, C, p); //C - D
    gcry_mpi_subm(buff, buff, D, p); //B - C - D
    gcry_mpi_mulm(newpoint.x, buff, J, p); //(B - C - D)*J
    
    
    //newpoint.y
    gcry_mpi_subm(buff, E, D, p); // E - D
    gcry_mpi_mulm(newpoint.y, F, buff, p); //F*(E - D)  
    
    
    //newpoint.z
    gcry_mpi_mulm(newpoint.z, F, J, p); //F*J
    
    convert(&newpoint);
    return newpoint;

    release_point(&newpoint);
    gcry_mpi_release(x1);
    gcry_mpi_release(y1);
    gcry_mpi_release(z1);

   
    gcry_mpi_release(buff);
    gcry_mpi_release(B);
    gcry_mpi_release(C);
    gcry_mpi_release(D);
    gcry_mpi_release(E);
    gcry_mpi_release(F);
    gcry_mpi_release(H);
    gcry_mpi_release(J);
}


struct point binary(struct point* f, gcry_mpi_t* seed)
{
    struct point newpoint;
    init_point(&newpoint);


    newpoint.x = zero;
    newpoint.y = one;
    newpoint.z = one;

    unsigned long int i;
    unsigned long int iterator = gcry_mpi_get_nbits(*seed) - 1;

    for(i = iterator; i > 0; --i)
    {
        newpoint = doubling(&newpoint);
        if(gcry_mpi_test_bit(*seed, i) == 1)
        {
            newpoint = summ(&newpoint, f);
        }
        
        if(i == 1)
        {
            newpoint = doubling(&newpoint);
            if(gcry_mpi_test_bit(*seed, i-1) == 1)
            {
                newpoint = summ(&newpoint, f);
            }    
        }
    }
    return newpoint;

    release_point(&newpoint);
}


void check_if_on_curve(struct point* f)
{
    gcry_mpi_t buff = gcry_mpi_new(0);
    gcry_mpi_t buff2 = gcry_mpi_new(0);
    gcry_mpi_t buff3 = gcry_mpi_new(0);
    

    gcry_mpi_powm(buff, f->x, two, p); //x^2
    gcry_mpi_powm(buff2, f->y, two, p); //y^2    
    gcry_mpi_mulm(buff, buff, a, p); //a*x^2
    gcry_mpi_mulm(buff3, buff, buff2, p); //y^2*x^2
    gcry_mpi_mulm(buff3, buff3, d, p); //y^2*x^2*b
    gcry_mpi_addm(buff, buff, buff2, p); //a*x^2 + y^2
    gcry_mpi_addm(buff3, buff3, one, p); //1 + y^2*x^2*b


    if (!gcry_mpi_cmp(buff, buff3)) //if buff == buff3 !cmp == true
    {
        printf("\e[38;5;82mTest 1 passed\n\033[0m");
    	/*printf("\n");
	gcry_mpi_dump(buff);
	printf("\n");
	gcry_mpi_dump(buff3);
	printf("\n\n");*/	
    }
    else
    {
        printf("\e[38;5;198mTest 1 failed\n\033[0m");
      	/*printf("\n");
	gcry_mpi_dump(buff);
	printf("\n");
	gcry_mpi_dump(buff3);
	printf("\n\n");*/
    }

    gcry_mpi_release(buff);
    gcry_mpi_release(buff2);
    gcry_mpi_release(buff3);
}


void check_identity (struct point* P) //[q]P == (0, 1, 1)
{
    gcry_mpi_t x = gcry_mpi_new(0);
    gcry_mpi_t y = gcry_mpi_new(0);
    gcry_mpi_t z = gcry_mpi_new(0);
    
    x = P->x;
    y = P->y;
    z = P->z;
    
    if ((gcry_mpi_cmp_ui(x, 0) == 0) && (gcry_mpi_cmp_ui(y, 1) == 0) && (gcry_mpi_cmp_ui(z, 1) == 0))
    {
        printf("\e[38;5;82mTest 2 passed\n\033[0m");    
    }
    else
    {
        printf("\e[38;5;198mTest 2 failed\n\033[0m");
    }
}


void check_neighbors(struct point* P)
{
    gcry_mpi_t x = gcry_mpi_new(0);
    gcry_mpi_t y = gcry_mpi_new(0);
    
    x = P->x;
    y = P->y;

    struct point r;
    init_point(&r);

    gcry_mpi_t buff = gcry_mpi_new(0);
    buff = gcry_mpi_copy(q);
    gcry_mpi_addm(buff, buff, one, p); // q + 1
    

    r = binary(P, &buff);

    
    if (gcry_mpi_cmp(x, r.x) == 0 && gcry_mpi_cmp(y, r.y) == 0) // [q + 1]P == P
    {
        printf("\e[38;5;82mTest 3.1 passed\n\033[0m");    
    }
    else
    {
        printf("\e[38;5;198mTest 3.1 failed\n\033[0m");
    }

    gcry_mpi_release(buff);

    struct point l;
    init_point(&l);

    gcry_mpi_t buff2 = gcry_mpi_new(0);
    buff2 = gcry_mpi_copy(q);
    gcry_mpi_subm(buff2, buff2, one, p); // q - 1


    l = binary(P, &buff2);

    gcry_mpi_subm(x, zero, x, p); // Turns P into -P
    
    if (gcry_mpi_cmp(x, l.x) == 0 && gcry_mpi_cmp(y, l.y) == 0) // [q - 1]P == -P
    {
        printf("\e[38;5;82mTest 3.2 passed\n\033[0m");    
    }
    else
    {
        printf("\e[38;5;198mTest 3.2 failed\n\033[0m");
    }

    gcry_mpi_release(buff2);
}


void check_lineary(struct point* P, gcry_mpi_t* k1, gcry_mpi_t* k2)
{
    struct point f, s;
    init_point(&f);
    init_point(&s);
    

    if(gcry_mpi_cmp(*k1, *k2) < 0) // k1 should be greater, than k2
    {
	gcry_mpi_swap(*k1,*k2);
    }


    gcry_mpi_t buff = gcry_mpi_new(0);
    gcry_mpi_addm(buff, *k1, *k2, p); // k1 + k2

    f = binary(P, k1); // [k1]P
    s = binary(P, k2); // [k2]P
    
    f = summ(&f, &s); // [k1]P + [k2]P
    s = binary(P, &buff); // [k1 + k2]P

    if (!gcry_mpi_cmp(f.x, s.x) && !gcry_mpi_cmp(f.y, s.y) && !gcry_mpi_cmp(f.z, s.z))
    {
        printf("\e[38;5;82mTest 4 passed\n\033[0m");    
    }
    else
    {
        printf("\e[38;5;198mTest 4 failed\n\033[0m");
    }

    gcry_mpi_release(buff);
}
