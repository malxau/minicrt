/*
 * EP_CONS.C
 *
 * Entrypoint code for console applications
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
#define mini_tcmdlinetoargs mini_wcmdlinetoargs
#else
#define mini_tcmdlinetoargs mini_cmdlinetoargs
#endif


LPTSTR *
MCRT_FN
mini_tcmdlinetoargs(LPTSTR szCmdLine, int * argc)
{
    int arg_count = 0;
    int char_count = 0;
    TCHAR break_char = ' ';
    TCHAR * c;
    LPTSTR * ret;
    LPTSTR ret_str;

    //
    //  Consume all spaces.  After this, we're either at
    //  the end of string, or we have an arg, and it
    //  might start with a quote
    //

    c = szCmdLine;
    while (*c == ' ') c++;
    if (*c == '"') {
        break_char = '"';
        c++;
    }

    while (*c != '\0') {
        if (*c == break_char) {
            break_char = ' ';
            c++;
            while (*c == break_char) c++;
            if (*c == '"') {
                break_char = '"';
                c++;
            }
                arg_count++;
        } else {
            char_count++;

            //
            //  If we hit a break char, we count the argument then.
            //  If we hit end of string, count it here; note we're
            //  only counting it if we counted a character before it
            //  (ie., trailing whitespace is not an arg.)
            //

            c++;

            if (*c == '\0') {
                arg_count++;
            }
        }
    }

    *argc = arg_count;

    ret = HeapAlloc( GetProcessHeap(), 0, (arg_count * sizeof(LPTSTR)) + (char_count + arg_count) * sizeof(TCHAR));

    ret_str = (LPTSTR)(ret + arg_count);

    arg_count = 0;
    ret[arg_count] = ret_str;

    //
    //  Consume all spaces.  After this, we're either at
    //  the end of string, or we have an arg, and it
    //  might start with a quote
    //

    c = szCmdLine;
    while (*c == ' ') c++;
    break_char = ' ';
    if (*c == '"') {
        break_char = '"';
        c++;
    }

    while (*c != '\0') {
        if (*c == break_char) {
            *ret_str = '\0';
            ret_str++;

            break_char = ' ';
            c++;
            while (*c == break_char) c++;
            if (*c == '"') {
                break_char = '"';
                c++;
            }
            if (*c != '\0') {
                arg_count++;
                ret[arg_count] = ret_str;
            }
        } else {
            *ret_str = *c;
            ret_str++;

            //
            //  If we hit a break char, we count the argument then.
            //  If we hit end of string, count it here; note we're
            //  only counting it if we counted a character before it
            //  (ie., trailing whitespace is not an arg.)
            //

            c++;

            if (*c == '\0') {
                *ret_str = '\0';
            }
        }
    }

    return ret;
}


#ifdef UNICODE
#define CONSOLE_USER_ENTRYPOINT wmain
#define CONSOLE_CRT_ENTRYPOINT  wmainCRTStartup
#else
#define CONSOLE_USER_ENTRYPOINT main
#define CONSOLE_CRT_ENTRYPOINT  mainCRTStartup
#endif

int __cdecl CONSOLE_USER_ENTRYPOINT(int argc, LPTSTR argv[]);

VOID __cdecl CONSOLE_CRT_ENTRYPOINT()
{
    TCHAR ** argv;
    int argc;
    int ret;

    argv = mini_tcmdlinetoargs(GetCommandLine(), &argc);
    ret = CONSOLE_USER_ENTRYPOINT(argc, argv);

    ExitProcess(ret);
}


// vim:sw=4:ts=4:et:
