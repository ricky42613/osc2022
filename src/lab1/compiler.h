#ifndef _COMPILER_H
#define _COMPILER_H

#define uint unsigned int
#define uchar unsigned char
#define likely(x) __builtin_expect(!!(x), 1)    // x很可能為真
#define unlikely(x) __builtin_expect(!!(x), 0)  // x很可能為假

#endif