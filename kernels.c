/********************************************************
 * Kernels to be optimized for the OS&C prflab.
 * Acknowledgment: This lab is an extended version of the
 * CS:APP Performance Lab
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "defs.h"
#include "smooth.h" // helper functions for naive_smooth
#include "blend.h"  // helper functions for naive_blend
#include <immintrin.h>

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

char more_writes_pr_inner_loopdescr[] = "more_writes_pr_inner_loop";
void more_writes_pr_inner_loop(int dim, pixel *src, pixel *dst)
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

char more_writes_pr_inner_loop2descr[] = "more_writes_pr_inner_loop and no call to RIDX";
void more_writes_pr_inner_loop2(int dim, pixel *src, pixel *dst)
{
    int i, j;

    int dim_minus_one = dim-1;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j = j + 32) {
            dst[(dim_minus_one-j-0) * dim + i] = src[i * dim + (j+0)];
            dst[(dim_minus_one-j-1) * dim + i] = src[i * dim + (j+1)];
            dst[(dim_minus_one-j-2) * dim + i] = src[i * dim + (j+2)];
            dst[(dim_minus_one-j-3) * dim + i] = src[i * dim + (j+3)];
            dst[(dim_minus_one-j-4) * dim + i] = src[i * dim + (j+4)];
            dst[(dim_minus_one-j-5) * dim + i] = src[i * dim + (j+5)];
            dst[(dim_minus_one-j-6) * dim + i] = src[i * dim + (j+6)];
            dst[(dim_minus_one-j-7) * dim + i] = src[i * dim + (j+7)];
            dst[(dim_minus_one-j-8) * dim + i] = src[i * dim + (j+8)];
            dst[(dim_minus_one-j-9) * dim + i] = src[i * dim + (j+9)];
            dst[(dim_minus_one-j-10) * dim + i] = src[i * dim + (j+10)];
            dst[(dim_minus_one-j-11) * dim + i] = src[i * dim + (j+11)];
            dst[(dim_minus_one-j-12) * dim + i] = src[i * dim + (j+12)];
            dst[(dim_minus_one-j-13) * dim + i] = src[i * dim + (j+13)];
            dst[(dim_minus_one-j-14) * dim + i] = src[i * dim + (j+14)];
            dst[(dim_minus_one-j-15) * dim + i] = src[i * dim + (j+15)];
            dst[(dim_minus_one-j-16) * dim + i] = src[i * dim + (j+16)];
            dst[(dim_minus_one-j-17) * dim + i] = src[i * dim + (j+17)];
            dst[(dim_minus_one-j-18) * dim + i] = src[i * dim + (j+18)];
            dst[(dim_minus_one-j-19) * dim + i] = src[i * dim + (j+19)];
            dst[(dim_minus_one-j-20) * dim + i] = src[i * dim + (j+20)];
            dst[(dim_minus_one-j-21) * dim + i] = src[i * dim + (j+21)];
            dst[(dim_minus_one-j-22) * dim + i] = src[i * dim + (j+22)];
            dst[(dim_minus_one-j-23) * dim + i] = src[i * dim + (j+23)];
            dst[(dim_minus_one-j-24) * dim + i] = src[i * dim + (j+24)];
            dst[(dim_minus_one-j-25) * dim + i] = src[i * dim + (j+25)];
            dst[(dim_minus_one-j-26) * dim + i] = src[i * dim + (j+26)];
            dst[(dim_minus_one-j-27) * dim + i] = src[i * dim + (j+27)];
            dst[(dim_minus_one-j-28) * dim + i] = src[i * dim + (j+28)];
            dst[(dim_minus_one-j-29) * dim + i] = src[i * dim + (j+29)];
            dst[(dim_minus_one-j-30) * dim + i] = src[i * dim + (j+30)];
            dst[(dim_minus_one-j-31) * dim + i] = src[i * dim + (j+31)];
        }
}

char more_writes_pr_inner_loop3descr[] = "more_writes_pr_inner_loop and software-prefetching";
void more_writes_pr_inner_loop3(int dim, pixel *src, pixel *dst)
{
    int i, j;

    int dim_minus_one = dim-1;

    for (i = 0; i < dim; i++) {
        __builtin_prefetch(&src[i * dim], 0, 3);
        //__builtin_prefetch(&dst[(dim_minus_one) * dim], 0, 3);
        for (j = 0; j < dim; j = j + 32) {
            dst[(dim_minus_one-j-0) * dim + i] = src[i * dim + (j+0)];
            dst[(dim_minus_one-j-1) * dim + i] = src[i * dim + (j+1)];
            dst[(dim_minus_one-j-2) * dim + i] = src[i * dim + (j+2)];
            dst[(dim_minus_one-j-3) * dim + i] = src[i * dim + (j+3)];
            dst[(dim_minus_one-j-4) * dim + i] = src[i * dim + (j+4)];
            dst[(dim_minus_one-j-5) * dim + i] = src[i * dim + (j+5)];
            dst[(dim_minus_one-j-6) * dim + i] = src[i * dim + (j+6)];
            dst[(dim_minus_one-j-7) * dim + i] = src[i * dim + (j+7)];
            dst[(dim_minus_one-j-8) * dim + i] = src[i * dim + (j+8)];
            dst[(dim_minus_one-j-9) * dim + i] = src[i * dim + (j+9)];
            dst[(dim_minus_one-j-10) * dim + i] = src[i * dim + (j+10)];
            dst[(dim_minus_one-j-11) * dim + i] = src[i * dim + (j+11)];
            dst[(dim_minus_one-j-12) * dim + i] = src[i * dim + (j+12)];
            dst[(dim_minus_one-j-13) * dim + i] = src[i * dim + (j+13)];
            dst[(dim_minus_one-j-14) * dim + i] = src[i * dim + (j+14)];
            dst[(dim_minus_one-j-15) * dim + i] = src[i * dim + (j+15)];
            dst[(dim_minus_one-j-16) * dim + i] = src[i * dim + (j+16)];
            dst[(dim_minus_one-j-17) * dim + i] = src[i * dim + (j+17)];
            dst[(dim_minus_one-j-18) * dim + i] = src[i * dim + (j+18)];
            dst[(dim_minus_one-j-19) * dim + i] = src[i * dim + (j+19)];
            dst[(dim_minus_one-j-20) * dim + i] = src[i * dim + (j+20)];
            dst[(dim_minus_one-j-21) * dim + i] = src[i * dim + (j+21)];
            dst[(dim_minus_one-j-22) * dim + i] = src[i * dim + (j+22)];
            dst[(dim_minus_one-j-23) * dim + i] = src[i * dim + (j+23)];
            dst[(dim_minus_one-j-24) * dim + i] = src[i * dim + (j+24)];
            dst[(dim_minus_one-j-25) * dim + i] = src[i * dim + (j+25)];
            dst[(dim_minus_one-j-26) * dim + i] = src[i * dim + (j+26)];
            dst[(dim_minus_one-j-27) * dim + i] = src[i * dim + (j+27)];
            dst[(dim_minus_one-j-28) * dim + i] = src[i * dim + (j+28)];
            dst[(dim_minus_one-j-29) * dim + i] = src[i * dim + (j+29)];
            dst[(dim_minus_one-j-30) * dim + i] = src[i * dim + (j+30)];
            dst[(dim_minus_one-j-31) * dim + i] = src[i * dim + (j+31)];
        }
    }
}

char more_writes_pr_inner_loop4descr[] = "more_writes_pr_inner_loop4 and no extra multiplication";
void more_writes_pr_inner_loop4(int dim, pixel *src, pixel *dst)
{
    int i, j;

    int dim_minus_one = dim-1;

    for (i = 0; i < dim; i++) {
        int idim = i * dim;
        for (j = 0; j < dim; j = j + 32) {
            dst[(dim_minus_one-j-0) * dim + i] = src[idim + (j+0)];
            dst[(dim_minus_one-j-1) * dim + i] = src[idim + (j+1)];
            dst[(dim_minus_one-j-2) * dim + i] = src[idim + (j+2)];
            dst[(dim_minus_one-j-3) * dim + i] = src[idim + (j+3)];
            dst[(dim_minus_one-j-4) * dim + i] = src[idim + (j+4)];
            dst[(dim_minus_one-j-5) * dim + i] = src[idim + (j+5)];
            dst[(dim_minus_one-j-6) * dim + i] = src[idim + (j+6)];
            dst[(dim_minus_one-j-7) * dim + i] = src[idim + (j+7)];
            dst[(dim_minus_one-j-8) * dim + i] = src[idim + (j+8)];
            dst[(dim_minus_one-j-9) * dim + i] = src[idim + (j+9)];
            dst[(dim_minus_one-j-10) * dim + i] = src[idim + (j+10)];
            dst[(dim_minus_one-j-11) * dim + i] = src[idim + (j+11)];
            dst[(dim_minus_one-j-12) * dim + i] = src[idim + (j+12)];
            dst[(dim_minus_one-j-13) * dim + i] = src[idim + (j+13)];
            dst[(dim_minus_one-j-14) * dim + i] = src[idim + (j+14)];
            dst[(dim_minus_one-j-15) * dim + i] = src[idim + (j+15)];
            dst[(dim_minus_one-j-16) * dim + i] = src[idim + (j+16)];
            dst[(dim_minus_one-j-17) * dim + i] = src[idim + (j+17)];
            dst[(dim_minus_one-j-18) * dim + i] = src[idim + (j+18)];
            dst[(dim_minus_one-j-19) * dim + i] = src[idim + (j+19)];
            dst[(dim_minus_one-j-20) * dim + i] = src[idim + (j+20)];
            dst[(dim_minus_one-j-21) * dim + i] = src[idim + (j+21)];
            dst[(dim_minus_one-j-22) * dim + i] = src[idim + (j+22)];
            dst[(dim_minus_one-j-23) * dim + i] = src[idim + (j+23)];
            dst[(dim_minus_one-j-24) * dim + i] = src[idim + (j+24)];
            dst[(dim_minus_one-j-25) * dim + i] = src[idim + (j+25)];
            dst[(dim_minus_one-j-26) * dim + i] = src[idim + (j+26)];
            dst[(dim_minus_one-j-27) * dim + i] = src[idim + (j+27)];
            dst[(dim_minus_one-j-28) * dim + i] = src[idim + (j+28)];
            dst[(dim_minus_one-j-29) * dim + i] = src[idim + (j+29)];
            dst[(dim_minus_one-j-30) * dim + i] = src[idim + (j+30)];
            dst[(dim_minus_one-j-31) * dim + i] = src[idim + (j+31)];
        }
    }
}

char more_writes_pr_inner_loop5descr[] = "more_writes_pr_inner_loop5 16 times";
void more_writes_pr_inner_loop5(int dim, pixel *src, pixel *dst)
{
    int i, j;

    int dim_minus_one = dim-1;

    for (i = 0; i < dim; i++) {
        int idim = i * dim;
        for (j = 0; j < dim; j = j + 16) {
            dst[(dim_minus_one-j-0) * dim + i] = src[idim + (j+0)];
            dst[(dim_minus_one-j-1) * dim + i] = src[idim + (j+1)];
            dst[(dim_minus_one-j-2) * dim + i] = src[idim + (j+2)];
            dst[(dim_minus_one-j-3) * dim + i] = src[idim + (j+3)];
            dst[(dim_minus_one-j-4) * dim + i] = src[idim + (j+4)];
            dst[(dim_minus_one-j-5) * dim + i] = src[idim + (j+5)];
            dst[(dim_minus_one-j-6) * dim + i] = src[idim + (j+6)];
            dst[(dim_minus_one-j-7) * dim + i] = src[idim + (j+7)];
            dst[(dim_minus_one-j-8) * dim + i] = src[idim + (j+8)];
            dst[(dim_minus_one-j-9) * dim + i] = src[idim + (j+9)];
            dst[(dim_minus_one-j-10) * dim + i] = src[idim + (j+10)];
            dst[(dim_minus_one-j-11) * dim + i] = src[idim + (j+11)];
            dst[(dim_minus_one-j-12) * dim + i] = src[idim + (j+12)];
            dst[(dim_minus_one-j-13) * dim + i] = src[idim + (j+13)];
            dst[(dim_minus_one-j-14) * dim + i] = src[idim + (j+14)];
            dst[(dim_minus_one-j-15) * dim + i] = src[idim + (j+15)];
        }
    }
}

char more_writes_pr_inner_loop6descr[] = "more_writes_pr_inner_loop5 16 times even less multiply";
void more_writes_pr_inner_loop6(int dim, pixel *src, pixel *dst)
{
    int i, j;

    int dim_minus_one = dim-1;

    for (i = 0; i < dim; i++) {
        int idim = i * dim;
        for (j = 0; j < dim; j = j + 16) {
            int idimj = idim + j;
            int acc = (dim_minus_one-j) * dim + i;

            dst[acc] = src[idimj + 0];
            acc -= dim;
            dst[acc] = src[idimj + 1];
            acc -= dim;
            dst[acc] = src[idimj + 2];
            acc -= dim;
            dst[acc] = src[idimj + 3];
            acc -= dim;
            dst[acc] = src[idimj + 4];
            acc -= dim;
            dst[acc] = src[idimj + 5];
            acc -= dim;
            dst[acc] = src[idimj + 6];
            acc -= dim;
            dst[acc] = src[idimj + 7];
            acc -= dim;
            dst[acc] = src[idimj + 8];
            acc -= dim;
            dst[acc] = src[idimj + 9];
            acc -= dim;
            dst[acc] = src[idimj + 10];
            acc -= dim;
            dst[acc] = src[idimj + 11];
            acc -= dim;
            dst[acc] = src[idimj + 12];
            acc -= dim;
            dst[acc] = src[idimj + 13];
            acc -= dim;
            dst[acc] = src[idimj + 14];
            acc -= dim;
            dst[acc] = src[idimj + 15];
        }
    }
}

/*char transpose_then_exchange_rows_descr[] = "transpose_then_exchange_rows";
void transpose_then_exchange_rows(int dim, pixel *src, pixel *dst)
{
    int i, j;

    pixel aux[dim*dim];

    // Transpose
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            aux[j * dim + i] = src[i * dim + j];

    // Exchange rows
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            dst[dim - 1 - i * dim + j] = aux[i * dim + j];
        }
    }
}*/

char four_writes_pr_inner_loopdescr[] = "four_writes_pr_inner_loop";
void four_writes_pr_inner_loop(int dim, pixel *src, pixel *dst)
{
    int i, j;

    int dim_minus_one = dim-1;

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j = j + 4) {
            dst[(dim_minus_one-j-0) * dim + i] = src[i * dim + (j+0)];
            dst[(dim_minus_one-j-1) * dim + i] = src[i * dim + (j+1)];
            dst[(dim_minus_one-j-2) * dim + i] = src[i * dim + (j+2)];
            dst[(dim_minus_one-j-3) * dim + i] = src[i * dim + (j+3)];
        }
    }
}

char four_writes_pr_inner_loop2descr[] = "four_writes_pr_inner_loop and i*dim pre-calc";
void four_writes_pr_inner_loop2(int dim, pixel *src, pixel *dst)
{
    int i, j;

    int dim_minus_one = dim-1;

    for (i = 0; i < dim; i++) {
        int idim = i * dim;
        for (j = 0; j < dim; j = j + 4) {
            int j0 = j+0;
            int j1 = j+1;
            int j2 = j+2;
            int j3 = j+3;
            dst[(dim_minus_one-j0) * dim + i] = src[idim + (j0)];
            dst[(dim_minus_one-j1) * dim + i] = src[idim + (j1)];
            dst[(dim_minus_one-j2) * dim + i] = src[idim + (j2)];
            dst[(dim_minus_one-j3) * dim + i] = src[idim + (j3)];
        }
    }
}

char xor_first_descr[] = "Swap using xor";

void xor(pixel *px1, pixel *px2);


void print_corners(pixel *src, int dim);

void xor_first(int dim, pixel *src, pixel *dst)
{
    int dim_m_one = dim-1;
/*
    printf("SRC:\n\n");
    pixel px = src[RIDX(0,0,dim)];
    printf("up left Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);

    px = src[RIDX(dim_m_one,0,dim)];
    printf("down left Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);

    px = src[RIDX(dim_m_one,dim_m_one,dim)];
    printf("down right Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);

    px = src[RIDX(0,dim_m_one,dim)];
    printf("up right Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);
*/
    int i, j;

    // Flip on y|axis
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim; j++){
            dst[RIDX(i, j, dim)] = src[RIDX(i, dim_m_one - j, dim)];
        }
    }

    // Transpose \ using xor
    for (i = 0; i < dim; i++){
        for (j = i + 1; j < dim; j++){
            pixel *px1 = &dst[RIDX(i, j, dim)];
            pixel *px2 = &dst[RIDX(j, i, dim)];
            xor(px1, px2);
            xor(px2, px1);
            xor(px1, px2);
        }
    }
/*
    printf("DST:\n\n");
    px = dst[RIDX(0,0,dim)];
    printf("up left Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);

    px = dst[RIDX(dim_m_one,0,dim)];
    printf("down left Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);

    px = dst[RIDX(dim_m_one,dim_m_one,dim)];
    printf("down right Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);

    px = dst[RIDX(0,dim_m_one,dim)];
    printf("up right Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);
*/
}

void xor(pixel *px1, pixel *px2) {
    /* pixel temp = *px1; // Create a temporary copy of px1
    *px1 = *px2;      // Copy px2 into px1
    *px2 = temp;      // Copy the temporary value (original px1) into px2
    return;
     */

    px1->red ^= px2->red;
    px1->green ^= px2->green;
    px1->blue ^= px2->blue;
    px1->alpha ^= px2->alpha;
}

char xor2desc[] = "Xor x-flip and / transpose";
void xor2(int dim, pixel *src, pixel *dst) {
    int dim_m_one = dim-1;
    int i, j;

    // Flip on x-axis
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim; j++){
            dst[RIDX(i, j, dim)] = src[RIDX(dim_m_one - i, j, dim)];
        }
    }

    // Transpose / using xor
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim - i - 1; j++){
            pixel *px1 = &dst[RIDX(i, j, dim)];
            pixel *px2 = &dst[RIDX(dim_m_one - j, dim_m_one - i, dim)];
            xor(px1, px2);
            xor(px2, px1);
            xor(px1, px2);
        }
    }

}

char xor3desc[] = "xor with memcpy";
void xor3(int dim, pixel *src, pixel *dst){
    int dim_m_one = dim-1;
    int i, j;
    size_t row_size = sizeof(pixel) * dim;

    // Flip on x-axis
    for (i = 0; i < dim; i++){
        memcpy(&dst[RIDX(i, 0, dim)], &src[RIDX(dim_m_one - i, 0, dim)], row_size);
    }

    // Transpose diagonal / using xor
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim - i - 1; j++){
            pixel *px1 = &dst[RIDX(i, j, dim)];
            pixel *px2 = &dst[RIDX(dim_m_one - j, dim_m_one - i, dim)];
            xor(px1, px2);
            xor(px2, px1);
            xor(px1, px2);
        }
    }
}

char xor4desc[] = "xor with temp variable";
void xor4(int dim, pixel *src, pixel *dst){
    int dim_m_one = dim-1;
    int i, j;
    size_t row_size = sizeof(pixel) * dim;

    // Flip on x-axis
    for (i = 0; i < dim; i++){
        memcpy(&dst[RIDX(i, 0, dim)], &src[RIDX(dim_m_one - i, 0, dim)], row_size);
    }

    // Transpose diagonal / using temp
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim - i - 1; j++){
            pixel temp = dst[RIDX(i, j, dim)];
            dst[RIDX(i, j, dim)] = dst[RIDX(dim_m_one - j, dim_m_one - i, dim)];
            dst[RIDX(dim_m_one - j, dim_m_one - i, dim)] = temp;
        }
    }
}

char xor5desc[] = "flip then transpose with pre-computation";
void xor5(int dim, pixel *src, pixel *dst){
    int dim_m_one = dim-1;
    int i, j;
    size_t row_size = sizeof(pixel) * dim;

    // Flip on x-axis
    int dimdim = dim * dim;
    int dimdim_minus_dim = dimdim - dim;
    int idx;
    for (idx = 0; idx < dimdim; idx += dim){
        memcpy(&dst[idx], &src[dimdim_minus_dim - idx], row_size);
    }

    // Transpose diagonal / using temp
    pixel temp;
    for (i = 0; i < dim; i++){
        int a = dim * i;
        int b = dim_m_one * dim + dim_m_one - i;
        for (j = 0; j < dim - i - 1; j++){
            temp = dst[a];
            dst[a] = dst[b];
            dst[b] = temp;
            a += 1;
            b -= dim;
        }
    }
}

char xor6desc[] = "flip then transpose also loop unrolling";
void xor6(int dim, pixel *src, pixel *dst){
    int dim_m_one = dim-1;
    int i, j;
    size_t row_size = sizeof(pixel) * dim;

    // Flip on x-axis
    int dimdim = dim * dim;
    int dimdim_minus_dim = dimdim - dim;
    int idx;
    for (idx = 0; idx < dimdim; idx += dim){
        memcpy(&dst[idx], &src[dimdim_minus_dim - idx], row_size);
    }

    // Transpose diagonal / using temp
    pixel temp;
    int a = 0;
    for (i = 0; i < dim; i++){
        int b = dim_m_one * dim + dim_m_one - i;
        int diagonal_index = dim - i - 1;
        for (j = 0; j < diagonal_index - 4; j += 4){

            temp = dst[a];
            dst[a] = dst[b];
            dst[b] = temp;

            temp = dst[a+1];
            dst[a+1] = dst[b-dim];
            dst[b-dim] = temp;

            temp = dst[a+2];
            dst[a+2] = dst[b-dim-dim];
            dst[b-dim-dim] = temp;

            temp = dst[a+3];
            dst[a+3] = dst[b-dim-dim-dim];
            dst[b-dim-dim-dim] = temp;

            a += 4;
            b -= dim * 4;
        }

        while (j < diagonal_index) {
            temp = dst[a];
            dst[a] = dst[b];
            dst[b] = temp;

            j++;
            a++;
            b -= dim;
        }

        a += dim-diagonal_index;
    }
}


char a_desc[] = "j in outer loop";
void a(int dim, pixel *src, pixel *dst) {
    int i, j;
    int d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15;
    int d_precalc, s_precalc;
    d1 = dim;
    d2 = d1 + dim;
    d3 = d2 + dim;
    d4 = d3 + dim;
    d5 = d4 + dim;
    d6 = d5 + dim;
    d7 = d6 + dim;
    d8 = d7 + dim;
    d9 = d8 + dim;
    d10 = d9 + dim;
    d11 = d10 + dim;
    d12 = d11 + dim;
    d13 = d12 + dim;
    d14 = d13 + dim;
    d15 = d14 + dim;

    int dim_minus_one = dim - 1;

    for (j = 0; j < dim; j++){
        int d_pre = (dim_minus_one - j) * dim;

        for (i = 0; i < dim; i += 16){
            s_precalc = i * dim + j;
            d_precalc = d_pre + i;
            dst[d_precalc] = src[s_precalc];
            dst[d_precalc + 1] = src[s_precalc + d1];
            dst[d_precalc + 2] = src[s_precalc + d2];
            dst[d_precalc + 3] = src[s_precalc + d3];
            dst[d_precalc + 4] = src[s_precalc + d4];
            dst[d_precalc + 5] = src[s_precalc + d5];
            dst[d_precalc + 6] = src[s_precalc + d6];
            dst[d_precalc + 7] = src[s_precalc + d7];
            dst[d_precalc + 8] = src[s_precalc + d8];
            dst[d_precalc + 9] = src[s_precalc + d9];
            dst[d_precalc + 10] = src[s_precalc + d10];
            dst[d_precalc + 11] = src[s_precalc + d11];
            dst[d_precalc + 12] = src[s_precalc + d12];
            dst[d_precalc + 13] = src[s_precalc + d13];
            dst[d_precalc + 14] = src[s_precalc + d14];
            dst[d_precalc + 15] = src[s_precalc + d15];
        }
    }
}

char b_desc[] = "dst in rows, src in columns";
void b(int dim, pixel *src, pixel *dst) {
    int dimdim = dim * dim;
    int a_jump = dimdim + 1;
    int a = dim * (dim - 1);
    int b = 0;
    int a1, a2, a3, a4, a5, a6, a7;
    while (b < dimdim) {
        a1 = a - dim;
        a2 = a1 - dim;
        a3 = a2 - dim;
        a4 = a3 - dim;
        a5 = a4 - dim;
        a6 = a5 - dim;
        a7 = a6 - dim;
        for (int i = 0; i < dim; i += 8) {
            dst[a] = src[b];
            dst[a1] = src[b+1];
            dst[a2] = src[b+2];
            dst[a3] = src[b+3];
            dst[a4] = src[b+4];
            dst[a5] = src[b+5];
            dst[a6] = src[b+6];
            dst[a7] = src[b+7];
            a -= 8 * dim;
            b += 8;
            a1 = a - dim;
            a2 = a1 - dim;
            a3 = a2 - dim;
            a4 = a3 - dim;
            a5 = a4 - dim;
            a6 = a5 - dim;
            a7 = a6 - dim;
        }
        a += a_jump;
    }
}

char c_desc[] = "src in rows, dst in columns";
void c(int dim, pixel *src, pixel *dst) {
    int dimdim = dim * dim;
    int b = dim - 1;
    int a = 0;
    while (a < dimdim) {
        for (int i = 0; i < dim; i += 8) {
            dst[a] = src[b];
            dst[a+1] = src[b+dim];
            dst[a+2] = src[b+dim+dim];
            dst[a+3] = src[b+dim+dim+dim];
            dst[a+4] = src[b+dim+dim+dim+dim];
            dst[a+5] = src[b+dim+dim+dim+dim+dim];
            dst[a+6] = src[b+dim+dim+dim+dim+dim+dim];
            dst[a+7] = src[b+dim+dim+dim+dim+dim+dim+dim];
            b += 8 * dim;
            a += 8;
        }
        b -= dimdim + 1;
    }
}

char d_desc[] = "local variables";
void d(int dim, pixel *src, pixel *dst) {
    int i, j;
    for (j = 0; j < dim; j += 8) {
        int tmp1 = dim*(dim-1-j);
        int tmp2 = tmp1 - dim;
        int tmp3 = tmp2 - dim;
        int tmp4 = tmp3 - dim;
        int tmp5 = tmp4 - dim;
        int tmp6 = tmp5 - dim;
        int tmp7 = tmp6 - dim;
        int tmp8 = tmp7 - dim;
        for (i = 0; i < dim; i++) {
            int dimx = dim*i+j;

            dst[tmp1+i] = src[dimx];
            dst[tmp2+i] = src[dimx+1];
            dst[tmp3+i] = src[dimx+2];
            dst[tmp4+i] = src[dimx+3];
            dst[tmp5+i] = src[dimx+4];
            dst[tmp6+i] = src[dimx+5];
            dst[tmp7+i] = src[dimx+6];
            dst[tmp8+i] = src[dimx+7];
        }
    }
}

void print_corners(pixel *src, int dim) {
    printf("\n");
    pixel px = src[RIDX(0,0,dim)];
    printf("up left Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);

    px = src[RIDX(dim - 1,0,dim)];
    printf("down left Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);

    px = src[RIDX(dim - 1, dim - 1,dim)];
    printf("down right Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);

    px = src[RIDX(0, dim - 1,dim)];
    printf("up right Red=%hu, Green=%hu, Blue=%hu, Alpha=%hu\n", px.red, px.green, px.blue, px.alpha);
};

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst)
{
    a(dim, src, dst);
}

/*
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function.
 */
void register_rotate_functions() 
{
    /*
    add_rotate_function(&xor_first, xor_first_descr);
    add_rotate_function(&xor2, xor2desc);
    add_rotate_function(&xor3, xor3desc);
    add_rotate_function(&xor4, xor4desc);
    add_rotate_function(&xor5, xor5desc);
    add_rotate_function(&xor6, xor6desc);
    */
    add_rotate_function(&a, a_desc);
    add_rotate_function(&b, b_desc);
    add_rotate_function(&c, c_desc);
    add_rotate_function(&d, d_desc);
    /*
    add_rotate_function(&rotate, rotate_descr);
    add_rotate_function(&more_writes_pr_inner_loop, more_writes_pr_inner_loopdescr);
    add_rotate_function(&more_writes_pr_inner_loop2, more_writes_pr_inner_loop2descr);
    add_rotate_function(&more_writes_pr_inner_loop3, more_writes_pr_inner_loop3descr);
    add_rotate_function(&four_writes_pr_inner_loop, four_writes_pr_inner_loopdescr);
    add_rotate_function(&four_writes_pr_inner_loop2, four_writes_pr_inner_loop2descr);
    add_rotate_function(&more_writes_pr_inner_loop4, more_writes_pr_inner_loop4descr);
    add_rotate_function(&more_writes_pr_inner_loop5, more_writes_pr_inner_loop5descr);
    add_rotate_function(&more_writes_pr_inner_loop6, more_writes_pr_inner_loop6descr);
     */
}

/******************************************************************************
 * ROTATE_T KERNEL
 *****************************************************************************/

// Your different versions of the rotate_t kernel go here
// (i.e. rotate with multi-threading)

pixel *global_src;
pixel *global_dst;
int global_dim;

void* thread_function(void *arg){
    int idx = *(int*)arg;
    int s, d;
    int block_start = 16 * idx;
    int next_block_start = 16 * (idx + 1);

    for (int j = 0; j < global_dim; ++j) {
        for (int i = block_start; i < next_block_start; ++i) {
            s = RIDX(i, j, global_dim);
            d = RIDX(global_dim-1-j, i, global_dim);
            global_dst[d] = global_src[s];
        }
    }

    return NULL;
}

char rotate_t_a_descr[] = "First attempt";

void rotate_t_a(int dim, pixel *src, pixel *dst){

    if (dim <= 512) {
        rotate(dim, src, dst);
        return;
    }

    global_src = src;
    global_dst = dst;
    global_dim = dim;

    int i;
    int chunk_count = dim / 16;
    pthread_t threads[chunk_count];
    int thread_args[chunk_count];
    for (i = 0; i < chunk_count; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, (void *) &thread_args[i]);
    }

    for (i = 0; i < chunk_count; ++i) {
        pthread_join(threads[i], NULL);
    }
}



/* 
 * rotate_t - Your current working version of rotate_t
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_t_descr[] = "rotate_t: Current working version";
void rotate_t(int dim, pixel *src, pixel *dst)
{
    rotate_t_a(dim, src, dst);
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
    add_rotate_t_function(&rotate_t_a, rotate_t_a_descr);
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

char blend_one_descr[] = "Only a single loop";
void blend_one(int dim, register pixel *src, register pixel *dst) {
    register int i;
    register int dimdim = dim * dim;
    for (i = 0; i < dimdim; i++){
        blend_pixel(&src[i], &dst[i], &bgc); // `blend_pixel` defined in blend.c
    }
}

char blend_descr[] = "blend: Current working version";
void blend(int dim, pixel *src, pixel *dst)
{
    blend_one(dim, src, dst);
}

/*
 * register_blend_functions - Register all of your different versions
 *     of the blend kernel with the driver by calling the
 *     add_blend_function() for each test function.
 */
void register_blend_functions() {
    add_blend_function(&blend, blend_descr);
    add_blend_function(&blend_one, blend_one_descr);
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

void* blend_thread_function(void *arg) {
    int idx = *(int*)arg;
    int limit = idx + global_dim;

    for (int i = idx; i < limit; ++i) {
        blend_pixel(&global_src[i], &global_dst[i], &bgc); // `blend_pixel` defined in blend.c
    }

    return NULL;
}


char blend_v_one_descr[] = "Blend multithread without C intrinsics";
void blend_v_one(int dim, pixel *src, pixel *dst) {
    global_dim = dim;
    global_src = src;
    global_dst = dst;
    int dimdim = dim * dim;

    pthread_t threads[dim];
    int thread_args[dim];
    int i;

    int arg = 0;
    for (i = 0; i < dimdim; i += dim) {
        thread_args[arg] = i;
        pthread_create(&threads[arg], NULL, blend_thread_function, (void *) &thread_args[arg]);
        arg += 1;
    }

    arg = 0;
    for (i = 0; i < dimdim; i += dim) {
        pthread_join(threads[arg], NULL);
        arg += 1;
    }
}

/*
char blend_v_intrinsics_one_descr[] = "First attempt using intrinsics";
void blend_v_intrinsics_one(int dim, pixel *src, pixel *dst) {
    int pixel_count = dim * dim;
    const float one_over_255 = 1.0F / 255.0F;
    __m256 _1_over_255 = _mm256_set1_ps(one_over_255);

    // start for loop for each section of size 256i. Each struct is 64 bits, which means 4 pixels will take up 256 bits.
    for (int i = 0; i < pixel_count; i += 4) {
        // fill a vector with alpha values of each pixel. src[i].alpha / 255 = src[i].alpha * 1 / 255 = src[i].alpha * constant_float. A float between 0-1. Name it "alpha"
        __m256i alpha = _mm256_set_epi16(
                (short) src[i+0].alpha, (short) src[0].alpha, (short) src[0].alpha, (short) src[0].alpha,
                (short) src[1].alpha, (short) src[1].alpha, (short) src[1].alpha, (short) src[1].alpha,
                (short) src[2].alpha, (short) src[2].alpha, (short) src[2].alpha, (short) src[2].alpha,
                (short) src[3].alpha, (short) src[3].alpha, (short) src[3].alpha, (short) src[3].alpha
        );

        __m256 alpha_floats = _mm256_cvtepi32_ps(alpha);
        __m256 alpha_fraction = _mm256_mul_ps(alpha_floats, _1_over_255);
        __m256i img = _mm256_load_si256((__m256i*) &src[i]); // Maybe src with / without ambersand?
        __m256 adjusted_src = _mm256_mul_ps(img, alpha_fraction);

        // fill a vector with the background color. Name it "background"
        //__m256i background = _mm256_set_epi64x(
        //        *(long*) src,
        //        *(long*) &src[1],
        //        *(long*) &src[2],
        //        *(long*) &src[3]); //__m256i background = _mm256_set1_epi16((short) src->red);

        // fill a vector with the remainder. 1-alpha[i]. Name it "remainder".
        unsigned short remainder_alpha_0 = 1 - src[0+i].alpha;
        unsigned short remainder_alpha_1 = 1 - src[1+i].alpha;
        unsigned short remainder_alpha_2 = 1 - src[2+i].alpha;
        unsigned short remainder_alpha_3 = 1 - src[3+i].alpha;

        __m256i remainder_alpha = _mm256_set_epi16(
                (short) remainder_alpha_0, (short) remainder_alpha_0, (short) remainder_alpha_0, (short) remainder_alpha_0,
                (short) remainder_alpha_1, (short) remainder_alpha_1, (short) remainder_alpha_1, (short) remainder_alpha_1,
                (short) remainder_alpha_2, (short) remainder_alpha_2, (short) remainder_alpha_2, (short) remainder_alpha_2,
                (short) remainder_alpha_3, (short) remainder_alpha_3, (short) remainder_alpha_3, (short) remainder_alpha_3
        );

        __m256 remainder_floats = _mm256_cvtepi32_ps(remainder_alpha);
        __m256 remainder_fraction = _mm256_mul_ps(remainder_floats, _1_over_255);
        __m256i background = _mm256_load_si256((__m256i*) &bgc);
        __m256 adjusted_background = _mm256_mul_ps(img, alpha_fraction);

        // Modify the img such that each rgb value is multiplied by "alpha".


        // Modify the background such that each rgb value is multiplied by "remainder".

        // Add together img and background

        // store img in the dst array
        _mm256_store_si256((__m256i*)dst, img);
    }

}

char blend_v_2_descr[] = "Second attempt";
void blend_v_2(int dim, pixel *src, pixel *dst) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; j += 4) {
            // Load 8 source pixels into a 256-bit vector
            __m256i src_pixels = _mm256_load_si256((__m256i*)&src[RIDX(i, j, dim)]);

            // Convert 16-bit unsigned shorts to 32-bit floats
            __m256 src_floats = _mm256_cvtepi32_ps(_mm256_unpacklo_epi16(src_pixels, _mm256_setzero_si256()));

            // Load 8 destination pixels into a 256-bit vector
            __m256i dst_pixels = _mm256_load_si256((__m256i*)&dst[RIDX(i, j, dim)]);

            // Convert 16-bit unsigned shorts to 32-bit floats
            __m256 dst_floats = _mm256_cvtepi32_ps(_mm256_unpacklo_epi16(dst_pixels, _mm256_setzero_si256()));

            // Extract alpha and convert to 32-bit floats
            __m256 alpha = _mm256_cvtepi32_ps(_mm256_and_si256(src_pixels, _mm256_set1_epi32(0xFFFF)));

            // Compute (1 - alpha) for each color channel
            __m256 one_minus_alpha = _mm256_sub_ps(_mm256_set1_ps(1.0F), alpha);

            // Compute blended color channels
            __m256 blended_colors = _mm256_blendv_ps(dst_floats, src_floats, alpha);

            // Convert back to integer and store the result
            __m256i result_pixels = _mm256_cvtps_epi32(blended_colors);
            _mm256_store_si256((__m256i*)&dst[RIDX(i, j, dim)], result_pixels);
        }
    }
}

*/
//int i, j;
//for (i = 0; i < dim; i++)
//for (j = 0; j < dim; j++)
//blend_pixel(&src[RIDX(i, j, dim)], &dst[RIDX(i, j, dim)], &bgc); // `blend_pixel` defined in blend.c



/*
 * register_blend_v_functions - Register all of your different versions
 *     of the blend_v kernel with the driver by calling the
 *     add_blend_function() for each test function.
 */
void register_blend_v_functions() {
    add_blend_v_function(&blend_v, blend_v_descr);
    add_blend_v_function(&blend_v_one, blend_v_one_descr);
    //add_blend_v_function(&blend_v_intrinsics_one, blend_v_intrinsics_one_descr);
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

void* blend_smooth_function(void *arg) {
    int idx = *(int*)arg;
    int s, d;
    int block_start = 16 * idx;
    int next_block_start = 16 * (idx + 1);

    for (int j = 0; j < global_dim; ++j) {
        for (int i = block_start; i < next_block_start; ++i) {
            global_dst[RIDX(i, j, global_dim)] = avg(global_dim, i, j, global_src);
        }
    }

    return NULL;
}

char first_smooth_descr[] = "First attempt";
void first_smooth(int dim, pixel *src, pixel *dst)
{
    global_src = src;
    global_dst = dst;
    global_dim = dim;

    int i;
    int chunk_count = dim / 16;
    pthread_t threads[chunk_count];
    int thread_args[chunk_count];
    for (i = 0; i < chunk_count; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, blend_smooth_function, (void *) &thread_args[i]);
    }

    for (i = 0; i < chunk_count; ++i) {
        pthread_join(threads[i], NULL);
    }
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
    add_smooth_function(&first_smooth, first_smooth_descr);
    /* ... Register additional test functions here */
}
