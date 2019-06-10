/*
 * RAND.C
 *
 * Implementations for random library functions.
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

unsigned int bit_recycler = 0;
unsigned int rand_seed = 0;

int
MCRT_VARARGFN
mini_rand()
{
    unsigned int oldbits = bit_recycler>>23;
    bit_recycler = (bit_recycler<<7) + (rand_seed>>23);
    rand_seed = (rand_seed * 83 + 13) ^ (rand_seed>>17) ^ (oldbits);
    return rand_seed % RAND_MAX;
}

void
MCRT_FN
mini_srand(unsigned int seed)
{
    rand_seed = seed;
    bit_recycler = 0;
}

// vim:sw=4:ts=4:et:
