#ifndef LSTD_TYPES_H
#define LSTD_TYPES_H



typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;
typedef float f32;
typedef double f64;
typedef int size_t;

#ifdef NULL
#undef NULL
#endif

#define NULL ((void*)0)
#endif /**/
