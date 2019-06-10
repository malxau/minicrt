/*
 * ENV.C
 *
 * Implementations for environment library functions.
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


#ifdef UNICODE
#define mini_tsearchenvex_s mini_wsearchenvex_s
#else
#define mini_tsearchenvex_s mini_searchenvex_s
#endif

void
MCRT_FN
mini_tsearchenvex_s(const TCHAR * filename, const TCHAR * envvar, TCHAR * out, unsigned int outlen, int * component)
{
    DWORD envlen, newenvlen;
    TCHAR * envvardata;
    TCHAR * begin;
    TCHAR * end;
    TCHAR search;
    TCHAR * scratch;
    DWORD filenamelen = mini_tcslen(filename);
    HANDLE hFind;
    WIN32_FIND_DATA FindData;

    *component = -1;

    //
    //  If we can't possibly do anything, stop.
    //

    if (outlen == 0) {
        return;
    }

    //
    //  This function is documented to check the current directory first
    //  (for some reason.)
    //

    hFind = FindFirstFile(filename, &FindData);

    if (hFind != INVALID_HANDLE_VALUE) {
        FindClose(hFind);
        mini_stprintf_s(out, outlen, _T("%s"), FindData.cFileName);
        return;
    }

    *out = '\0';

    scratch = malloc(outlen * sizeof(TCHAR));
    if (scratch == NULL) {
        return;
    }

retry:

    envlen = GetEnvironmentVariable(envvar, NULL, 0);

    //
    //  If the variable the caller wants doesn't exist, stop.
    //

    if (envlen == 0) {
        free(scratch);
        return;
    }

    envvardata = malloc(envlen * sizeof(TCHAR));
    if (envvardata == NULL) {
        free(scratch);
        return;
    }

    newenvlen = GetEnvironmentVariable(envvar, envvardata, envlen);
    
    //
    //  The variable grew while we were looking at it.  Try again.
    //

    if (newenvlen > envlen) {
        free(envvardata);
        goto retry;
    }

    begin = envvardata;

    while (*begin == ';') begin++;

    *component = 0;

    while (*begin) {

        DWORD componentlen;

        (*component)++;

        search = ';';

        if (*begin == '"') {
            begin++;
            search = '"';
        }

        end = mini_tcschr(begin, search);

        if (end == NULL) {

            end = begin + mini_tcslen(begin);
        }

        componentlen = (DWORD)(end - begin);

        if (componentlen != 0 && componentlen + 1 + filenamelen < outlen) {

            mini_memcpy(scratch, begin, componentlen * sizeof(TCHAR));
            mini_memcpy(scratch + componentlen, _T("\\"), sizeof(TCHAR));
            mini_stprintf(scratch + componentlen + 1, _T("%s"), filename);

            hFind = FindFirstFile(scratch, &FindData);

            if (hFind != INVALID_HANDLE_VALUE) {
                LPTSTR fn;
                FindClose(hFind);
                GetFullPathName(scratch, outlen, out, &fn);
                mini_stprintf_s(fn, outlen - (unsigned int)(fn-out), _T("%s"), FindData.cFileName);
                free(scratch);
                free(envvardata);
                return;
            }
        }

        begin = end;
        if (search == '"') {
            while (*begin == '"') begin++;
        }

        while (*begin == ';') begin++;
    }

    free(scratch);
    free(envvardata);
}

#ifdef UNICODE
#define mini_tsearchenv_s mini_wsearchenv_s
#else
#define mini_tsearchenv_s mini_searchenv_s
#endif

void
MCRT_FN
mini_tsearchenv_s(const TCHAR * filename, const TCHAR * envvar, TCHAR * out, unsigned int outlen)
{
    int component;
    mini_tsearchenvex_s(filename, envvar, out, outlen, &component);
}

#ifdef UNICODE
#define mini_tsearchenv mini_wsearchenv
#else
#define mini_tsearchenv mini_searchenv
#endif

void
MCRT_FN
mini_tsearchenv(const TCHAR * filename, const TCHAR * envvar, TCHAR * out)
{
    //
    //  If the caller hasn't specified a buffer size, assume MAX_PATH since it's
    //  likely what they intended
    //

    mini_tsearchenv_s(filename, envvar, out, MAX_PATH);
}

// vim:sw=4:ts=4:et:
