/*
 * MEM.C
 *
 * Implementations for mem* library functions.
 *
 * Copyright (c) 2014 Malcolm J. Smith
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif

#include <windows.h>
#include <tchar.h>

#define MINICRT_BUILD
#include "minicrt.h"

int _fltused = 0;

void *
MCRT_FN
mini_memcpy(void * dest, void * src, unsigned int len)
{
    unsigned int i;
    char * char_src = (char *)src;
    char * char_dest = (char *)dest;
    for (i = 0; i < len; i++) {
        char_dest[i] = char_src[i];
    }
    return dest;
}

void *
MCRT_FN
mini_memmove(void * dest, void * src, unsigned int len)
{
    unsigned int i;
    char * char_src = (char *)src;
    char * char_dest = (char *)dest;
    if (char_dest > char_src) {
        if (len == 0) {
            return dest;
        }
        for (i = len - 1; ; i--) {
            char_dest[i] = char_src[i];
            if (i==0) break;
        }
    } else {
        for (i = 0; i < len; i++) {
            char_dest[i] = char_src[i];
        }
    }
    return dest;
}

void *
MCRT_FN
mini_memset(void * dest, char c, unsigned int len)
{
    unsigned int i;
    unsigned int fill;
    unsigned int chunks = len / sizeof(fill);
    char * char_dest = (char *)dest;
    unsigned int * uint_dest = (unsigned int *)dest;

    //
    //  Note we go from the back to the front.  This is to 
    //  prevent newer compilers from noticing what we're doing
    //  and trying to invoke the built-in memset instead of us.
    //

    fill = (c<<24) + (c<<16) + (c<<8) + c;

    for (i = len; i > chunks * sizeof(fill); i--) {
        char_dest[i - 1] = c;
    }

    for (i = chunks; i > 0; i--) {
        uint_dest[i - 1] = fill;
    }

    return dest;
}

int
MCRT_FN
mini_memcmp(const void * buf1, const void * buf2, unsigned int len)
{
    unsigned int i = 0;
    unsigned char * char_buf1 = (unsigned char *)buf1;
    unsigned char * char_buf2 = (unsigned char *)buf2;
    for (i = 0; i < len; i++) {
        if (char_buf1[i] < char_buf2[i]) {
            return -1;
        } else if (char_buf1[i] > char_buf2[i]) {
            return 1;
        }
    }
    return 0;
}

// vim:sw=4:ts=4:et:
