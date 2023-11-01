/********************************************************
 * Kernels to be optimized for the OS&C prflab.
 * Acknowledgment: This lab is an extended version of the
 * CS:APP Performance Lab
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "smooth.h" // helper functions for naive_smooth
#include "blend.h"  // helper functions for naive_blend

/* 
 * Please fill in the following struct
 */
student_t student = {
    "wihe",             /* ITU alias */
    "William Skou Heidemann",    /* Full name */
    "wihe@itu.dk", /* Email address */
};

/******************************************************************************
 * ROTATE KERNEL
 *****************************************************************************/

// Your different versions of the rotate kernel go here

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
/* stride pattern, visualization (we recommend that you draw this for your functions):
    dst         src
    3 7 B F     0 1 2 3
    2 6 A E     4 5 6 7
    1 5 9 D     8 9 A B
    0 4 8 C     C D E F
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

char first_attempt_rotate_descr[] = "First attempt";
void first_attempt_rotate(int dim, pixel *src, pixel *dst)
{
    int i, j;

    int dim_minus_one = dim-1;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j = j + 32) {
            dst[RIDX(dim_minus_one-j-0, i, dim)] = src[RIDX(i, j+0, dim)];
            dst[RIDX(dim_minus_one-j-1, i, dim)] = src[RIDX(i, j+1, dim)];
            dst[RIDX(dim_minus_one-j-2, i, dim)] = src[RIDX(i, j+2, dim)];
            dst[RIDX(dim_minus_one-j-3, i, dim)] = src[RIDX(i, j+3, dim)];
            dst[RIDX(dim_minus_one-j-4, i, dim)] = src[RIDX(i, j+4, dim)];
            dst[RIDX(dim_minus_one-j-5, i, dim)] = src[RIDX(i, j+5, dim)];
            dst[RIDX(dim_minus_one-j-6, i, dim)] = src[RIDX(i, j+6, dim)];
            dst[RIDX(dim_minus_one-j-7, i, dim)] = src[RIDX(i, j+7, dim)];
            dst[RIDX(dim_minus_one-j-8, i, dim)] = src[RIDX(i, j+8, dim)];
            dst[RIDX(dim_minus_one-j-9, i, dim)] = src[RIDX(i, j+9, dim)];
            dst[RIDX(dim_minus_one-j-10, i, dim)] = src[RIDX(i, j+10, dim)];
            dst[RIDX(dim_minus_one-j-11, i, dim)] = src[RIDX(i, j+11, dim)];
            dst[RIDX(dim_minus_one-j-12, i, dim)] = src[RIDX(i, j+12, dim)];
            dst[RIDX(dim_minus_one-j-13, i, dim)] = src[RIDX(i, j+13, dim)];
            dst[RIDX(dim_minus_one-j-14, i, dim)] = src[RIDX(i, j+14, dim)];
            dst[RIDX(dim_minus_one-j-15, i, dim)] = src[RIDX(i, j+15, dim)];
            dst[RIDX(dim_minus_one-j-16, i, dim)] = src[RIDX(i, j+16, dim)];
            dst[RIDX(dim_minus_one-j-17, i, dim)] = src[RIDX(i, j+17, dim)];
            dst[RIDX(dim_minus_one-j-18, i, dim)] = src[RIDX(i, j+18, dim)];
            dst[RIDX(dim_minus_one-j-19, i, dim)] = src[RIDX(i, j+19, dim)];
            dst[RIDX(dim_minus_one-j-20, i, dim)] = src[RIDX(i, j+20, dim)];
            dst[RIDX(dim_minus_one-j-21, i, dim)] = src[RIDX(i, j+21, dim)];
            dst[RIDX(dim_minus_one-j-22, i, dim)] = src[RIDX(i, j+22, dim)];
            dst[RIDX(dim_minus_one-j-23, i, dim)] = src[RIDX(i, j+23, dim)];
            dst[RIDX(dim_minus_one-j-24, i, dim)] = src[RIDX(i, j+24, dim)];
            dst[RIDX(dim_minus_one-j-25, i, dim)] = src[RIDX(i, j+25, dim)];
            dst[RIDX(dim_minus_one-j-26, i, dim)] = src[RIDX(i, j+26, dim)];
            dst[RIDX(dim_minus_one-j-27, i, dim)] = src[RIDX(i, j+27, dim)];
            dst[RIDX(dim_minus_one-j-28, i, dim)] = src[RIDX(i, j+28, dim)];
            dst[RIDX(dim_minus_one-j-29, i, dim)] = src[RIDX(i, j+29, dim)];
            dst[RIDX(dim_minus_one-j-30, i, dim)] = src[RIDX(i, j+30, dim)];
            dst[RIDX(dim_minus_one-j-31, i, dim)] = src[RIDX(i, j+31, dim)];
        }

}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst)
{
    naive_rotate(dim, src, dst);
}

/*
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function.
 */
void register_rotate_functions() 
{
    add_rotate_function(&rotate, rotate_descr);
    add_rotate_function(&first_attempt_rotate, first_attempt_rotate_descr);
    /* ... Register additional test functions here */
}

/******************************************************************************
 * ROTATE_T KERNEL
 *****************************************************************************/

// Your different versions of the rotate_t kernel go here
// (i.e. rotate with multi-threading)

/* 
 * rotate_t - Your current working version of rotate_t
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_t_descr[] = "rotate_t: Current working version";
void rotate_t(int dim, pixel *src, pixel *dst)
{
    naive_rotate(dim, src, dst);
}

/*********************************************************************
 * register_rotate_t_functions - Register all of your different versions
 *     of the rotate_t kernel with the driver by calling the
 *     add_rotate_t_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_t_functions() 
{
    add_rotate_t_function(&rotate_t, rotate_t_descr);
    /* ... Register additional test functions here */
}

/******************************************************************************
 * BLEND KERNEL
 *****************************************************************************/

// Your different versions of the blend kernel go here.

char naive_blend_descr[] = "naive_blend: Naive baseline implementation";
void naive_blend(int dim, pixel *src, pixel *dst) // reads global variable `pixel bgc`
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    blend_pixel(&src[RIDX(i, j, dim)], &dst[RIDX(i, j, dim)], &bgc); // `blend_pixel` defined in blend.c
}

char blend_descr[] = "blend: Current working version";
void blend(int dim, pixel *src, pixel *dst)
{
    naive_blend(dim, src, dst);
}

/*
 * register_blend_functions - Register all of your different versions
 *     of the blend kernel with the driver by calling the
 *     add_blend_function() for each test function.
 */
void register_blend_functions() {
    add_blend_function(&blend, blend_descr);
    /* ... Register additional test functions here */
}

/******************************************************************************
 * BLEND_V KERNEL
 *****************************************************************************/

// Your different versions of the blend_v kernel go here
// (i.e. with vectorization, aka. SIMD).

char blend_v_descr[] = "blend_v: Current working version";
void blend_v(int dim, pixel *src, pixel *dst)
{
    naive_blend(dim, src, dst);
}

/*
 * register_blend_v_functions - Register all of your different versions
 *     of the blend_v kernel with the driver by calling the
 *     add_blend_function() for each test function.
 */
void register_blend_v_functions() {
    add_blend_v_function(&blend_v, blend_v_descr);
    /* ... Register additional test functions here */
}

/******************************************************************************
 * SMOOTH KERNEL
 *****************************************************************************/

// Your different versions of the smooth kernel go here

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src); // `avg` defined in smooth.c
}

char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst)
{
  naive_smooth(dim, src, dst);
}

/*
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.
 */

void register_smooth_functions() {
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}
