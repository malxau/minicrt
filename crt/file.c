/*
 * FILE.C
 *
 * Implementations for f* file library functions.
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

#ifndef FILE_SHARE_DELETE
#define FILE_SHARE_DELETE 4
#endif

#define MINICRT_BUILD
#include "minicrt.h"


#ifdef UNICODE
#define mini_ftopen mini_wfopen
#else
#define mini_ftopen mini_fopen
#endif

FILE *
MCRT_FN
mini_ftopen(TCHAR * filename, TCHAR * mode)
{
    FILE * RetVal;
    DWORD DesiredAccess;
    DWORD CreateDisposition;

    if (mini_tcscmp(mode,_T("r"))==0 ||
        mini_tcscmp(mode,_T("rb"))==0) {

        DesiredAccess = GENERIC_READ;
        CreateDisposition = OPEN_EXISTING;

    } else if (mini_tcscmp(mode,_T("w"))==0 ||
               mini_tcscmp(mode,_T("wb"))==0) {

        DesiredAccess = GENERIC_WRITE;
        CreateDisposition = CREATE_ALWAYS;

    } else {
        return NULL;
    }

    RetVal = malloc(sizeof(FILE));
    if (RetVal == NULL) {
        return NULL;
    }

    RetVal->hFile = CreateFile(filename,
                               DesiredAccess,
                               FILE_SHARE_READ|FILE_SHARE_DELETE,
                               NULL,
                               CreateDisposition,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);

    if (RetVal->hFile != INVALID_HANDLE_VALUE) {
        return RetVal;
    } else {
        free(RetVal);
    }

    return NULL;
}

#ifdef UNICODE
#define mini_ftgets mini_fgetws
#else
#define mini_ftgets mini_fgets
#endif

TCHAR *
MCRT_FN
mini_ftgets(TCHAR * str,int n,FILE * fp)
{
    int count = 0;
    CHAR ch;
    DWORD bytesread;

    while ((count + 1) < n && ReadFile(fp->hFile,&ch,sizeof(ch),&bytesread,NULL) && bytesread == sizeof(ch)) {
        str[count] = ch;
        count++;
        if (ch == '\n' || ch == '\r') {
            break;
        }
    }
    str[count] = '\0';
    if (count == 0) {
        return NULL;
    }
    return str;
}

#ifndef UNICODE

int
MCRT_FN
mini_fclose(FILE * fp)
{
    if (fp==NULL) {
        return 0;
    }

    if (fp->hFile != NULL && fp->hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(fp->hFile);
    }

    free(fp);
    return 0;
}

#endif

// vim:sw=4:ts=4:et:
