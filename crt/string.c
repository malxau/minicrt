/*
 * STRING.C
 *
 * Implementations of the str* library functions.
 *
 * Copyright (c) 2014-2017 Malcolm J. Smith
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
#define mini_ttoi mini_wtoi
#else
#define mini_ttoi mini_atoi
#endif

int
MCRT_FN
mini_ttoi (TCHAR * str)
{
    int ret = 0;
    while (*str >= '0' && *str <= '9') {
        ret *= 10;
        ret += *str - '0';
        str++;
    }
    return ret;
}

#ifdef UNICODE
#define mini_tcscat_s mini_wcscat_s
#else
#define mini_tcscat_s mini_strcat_s
#endif

TCHAR *
MCRT_FN
mini_tcscat_s(TCHAR * dest, unsigned int len, const TCHAR * src)
{
    unsigned int i,j;
    for (i = 0; dest[i] != '\0' && i < len; i++);
    for (j = 0; src[j] != '\0' && i < len - 1; ) {
        dest[i++] = src[j++];
    }
    dest[i++] = '\0';
    return dest;
}

#ifdef UNICODE
#define mini_tcsncat mini_wcsncat
#else
#define mini_tcsncat mini_strncat
#endif

TCHAR *
MCRT_FN
mini_tcsncat(TCHAR * dest, const TCHAR * src, unsigned int len)
{
    unsigned int i,j;
    for (i = 0; dest[i] != '\0'; i++);
    for (j = 0; src[j] != '\0' && j < len; ) {
        dest[i++] = src[j++];
    }
    dest[i++] = '\0';
    return dest;
}

#ifdef UNICODE
#define mini_tcschr mini_wcschr
#else
#define mini_tcschr mini_strchr
#endif

TCHAR *
MCRT_FN
mini_tcschr(const TCHAR * str, TCHAR ch)
{
    const TCHAR * ptr = str;
    while (*ptr != '\0' && *ptr != ch) ptr++;
    if (*ptr == ch) return (TCHAR *)ptr;
    return NULL;
}

#ifdef UNICODE
#define mini_tcsrchr mini_wcsrchr
#else
#define mini_tcsrchr mini_strrchr
#endif

TCHAR *
MCRT_FN
mini_tcsrchr(const TCHAR * str, TCHAR ch)
{
    const TCHAR * ptr = str;
    while (*ptr != '\0') ptr++;
    while (*ptr != ch && ptr > str) ptr--;
    if (*ptr == ch) return (TCHAR *)ptr;
    return NULL;
}

#ifdef UNICODE
#define mini_tcslen mini_wcslen
#else
#define mini_tcslen mini_strlen
#endif

int
MCRT_FN
mini_tcslen(const TCHAR * str)
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

#ifdef UNICODE
#define mini_tcsstr mini_wcsstr
#else
#define mini_tcsstr mini_strstr
#endif

TCHAR *
MCRT_FN
mini_tcsstr(const TCHAR * str, TCHAR * search)
{
    const TCHAR * ptr = str;
    int i;
    while (*ptr != '\0') {
        for (i=0;ptr[i]==search[i]&&search[i]!='\0'&&ptr[i]!='\0';i++);
        if (search[i]=='\0') return (TCHAR*)ptr;
        ptr++;
    }
    return NULL;
}

#ifdef UNICODE
#define mini_ttoupper mini_towupper
#else
#define mini_ttoupper mini_toupper
#endif

int
MCRT_FN
mini_ttoupper(int c)
{
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}

#ifdef UNICODE
#define mini_ttolower mini_towlower
#else
#define mini_ttolower mini_tolower
#endif

int
MCRT_FN
mini_ttolower(int c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

#ifdef UNICODE
#define mini_tcsupr mini_wcsupr
#else
#define mini_tcsupr mini_strupr
#endif

TCHAR *
MCRT_FN
mini_tcsupr(TCHAR * str)
{
    TCHAR * ptr = str;

    while (*ptr != '\0') {
        *ptr = (TCHAR)mini_ttoupper(*ptr);
        ptr++;
    }
    return str;
}

#ifdef UNICODE
#define mini_tcslwr mini_wcslwr
#else
#define mini_tcslwr mini_strlwr
#endif

TCHAR *
MCRT_FN
mini_tcslwr(TCHAR * str)
{
    TCHAR * ptr = str;

    while (*ptr != '\0') {
        *ptr = (TCHAR)mini_ttolower(*ptr);
        ptr++;
    }
    return str;
}

#ifdef UNICODE
#define mini_tcsncmp mini_wcsncmp
#else
#define mini_tcsncmp mini_strncmp
#endif

int
MCRT_FN
mini_tcsncmp(const TCHAR * str1, const TCHAR * str2, unsigned int count)
{
    const TCHAR * ptr1 = str1;
    const TCHAR * ptr2 = str2;
    unsigned int remaining = count;

    while(TRUE) {
        if (*ptr1 < *ptr2) {
            return -1;
        } else if (*ptr1 > *ptr2) {
            return 1;
        } else if (*ptr1 == '\0') {
            return 0;
        }

        ptr1++;
        ptr2++;
        remaining--;

        if (remaining == 0) {
            return 0;
        }
    }
    return 0;
}

#ifdef UNICODE
#define mini_tcscmp mini_wcscmp
#else
#define mini_tcscmp mini_strcmp
#endif

int
MCRT_FN
mini_tcscmp(const TCHAR * str1, const TCHAR * str2)
{
    return mini_tcsncmp(str1, str2, (unsigned int)-1);
}

#ifdef UNICODE
#define mini_tcsnicmp mini_wcsnicmp
#else
#define mini_tcsnicmp mini_strnicmp
#endif

int
MCRT_FN
mini_tcsnicmp(const TCHAR * str1, const TCHAR * str2, unsigned int count)
{
    const TCHAR * ptr1 = str1;
    const TCHAR * ptr2 = str2;
    unsigned int remaining = count;

    while(TRUE) {
        if (mini_ttoupper(*ptr1) < mini_ttoupper(*ptr2)) {
            return -1;
        } else if (mini_ttoupper(*ptr1) > mini_ttoupper(*ptr2)) {
            return 1;
        } else if (*ptr1 == '\0') {
            return 0;
        }
        ptr1++;
        ptr2++;
        remaining--;

        if (remaining == 0) {
            return 0;
        }
    }
    return 0;
}

#ifdef UNICODE
#define mini_tcsicmp mini_wcsicmp
#else
#define mini_tcsicmp mini_stricmp
#endif

int
MCRT_FN
mini_tcsicmp(const TCHAR * str1, const TCHAR * str2)
{
    return mini_tcsnicmp(str1, str2, (unsigned int)-1);
}

#ifdef UNICODE
#define mini_tcstok_s mini_wcstok_s
#else
#define mini_tcstok_s mini_strtok_s
#endif

TCHAR *
MCRT_FN
mini_tcstok_s(TCHAR * str, TCHAR * match, TCHAR ** context)
{
    TCHAR * next;
    if (str != NULL) {
        *context = str;
    }

    next = *context;
    if (next == NULL) {
        return NULL;
    }

    while (*next != match[0] && *next != '\0') next++;

    if (*next == match[0]) {
        TCHAR * ret = *context;
        *next = '\0';
        *context = ++next;
        return ret;
    } else {
        TCHAR * ret = *context;
        *context = NULL;
        return ret;
    }
}

#ifdef UNICODE
#define mini_tcstok mini_wcstok
#define STRTOK_CTX  wcstok_context
#else
#define mini_tcstok mini_strtok
#define STRTOK_CTX  strtok_context
#endif

TCHAR * STRTOK_CTX;
TCHAR *
MCRT_FN
mini_tcstok(TCHAR * str, TCHAR * match)
{
    return mini_tcstok_s(str, match, &STRTOK_CTX);
}

#ifdef UNICODE
#define mini_tcsspn mini_wcsspn
#else
#define mini_tcsspn mini_strspn
#endif

int
MCRT_FN
mini_tcsspn(TCHAR * str, TCHAR * chars)
{
    DWORD len = 0;
    DWORD i;

    for (len = 0; str[len] != '\0'; len++) {
        for (i = 0; chars[i] != '\0'; i++) {
            if (str[len] == chars[i]) {
                break;
            }
        }
        if (chars[i] == '\0') {
            return len;
        }
    }

    return len;
}

#ifdef UNICODE
#define mini_tcscspn mini_wcscspn
#else
#define mini_tcscspn mini_strcspn
#endif

int
MCRT_FN
mini_tcscspn(TCHAR * str, TCHAR * match)
{
    DWORD len = 0;
    DWORD i;

    for (len = 0; str[len] != '\0'; len++) {
        for (i = 0; match[i] != '\0'; i++) {
            if (str[len] == match[i]) {
                return len;
            }
        }
    }

    return len;
}

#ifdef UNICODE
#define mini_stprintf_s mini_swprintf_s
#else
#define mini_stprintf_s mini_sprintf_s
#endif

int
MCRT_VARARGFN
mini_stprintf_s(LPTSTR szDest, unsigned int len, LPCTSTR szFmt, ...)
{
    va_list marker;
    int out_len;

    va_start( marker, szFmt );
    out_len = mini_vstprintf_s(szDest, len, szFmt, marker);
    va_end( marker );
    return out_len;
}

#ifdef UNICODE
#define mini_stprintf_s mini_swprintf_s
#else
#define mini_stprintf_s mini_sprintf_s
#endif

int
MCRT_VARARGFN
mini_stprintf(LPTSTR szDest, LPCTSTR szFmt, ...)
{
    va_list marker;
    int out_len;

    va_start( marker, szFmt );
    out_len = mini_vstprintf_s(szDest, (DWORD)-1, szFmt, marker);
    va_end( marker );
    return out_len;
}


#ifdef UNICODE
#define mini_vftprintf mini_vfwprintf
#else
#define mini_vftprintf mini_vfprintf
#endif

int
MCRT_VARARGFN
mini_vftprintf(FILE * fp, LPCTSTR szFmt, va_list marker)
{
    va_list savedmarker = marker;
    int len;
    TCHAR stack_buf[20];
    HANDLE hOut;
    DWORD written;
    TCHAR * buf;

    if (fp==stdin) {
        return 0;
    } else if (fp==stdout) {
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    } else if (fp==stderr) {
        hOut = GetStdHandle(STD_ERROR_HANDLE);
    } else {
        hOut = fp->hFile;
    }

    len = mini_vstprintf_size(szFmt, marker);

    if (len>(int)(sizeof(stack_buf)/sizeof(stack_buf[0]))) {
        buf = HeapAlloc(GetProcessHeap(), 0, len * sizeof(TCHAR));
        if (buf == NULL) {
            return 0;
        }
    } else {
        buf = stack_buf;
    }

    marker = savedmarker;
    len = mini_vstprintf_s(buf, len, szFmt, marker);
#ifdef UNICODE
    {
        CHAR ansi_stack_buf[64 + 1];
        LPSTR ansi_buf;
    
        if (len >= (int)sizeof(ansi_stack_buf)) {

            ansi_buf = HeapAlloc(GetProcessHeap(), 0, len + 1);
        } else {

            ansi_buf = ansi_stack_buf;
        }

        if (ansi_buf != NULL) {
            WideCharToMultiByte(CP_ACP,
                                0,
                                buf,
                                len,
                                ansi_buf,
                                len + 1,
                                NULL,
                                NULL);

            WriteFile(hOut, ansi_buf, len, &written, NULL);

            if (ansi_buf != ansi_stack_buf) {
                HeapFree(GetProcessHeap(), 0, ansi_buf);
            }
        } else {
            len = 0;
        }
    }
#else
    WriteFile(hOut,buf,len*sizeof(TCHAR),&written,NULL);
#endif

    if (buf != stack_buf) {
        HeapFree(GetProcessHeap(), 0, buf);
    }
    return len;
}

#ifdef UNICODE
#define mini_ftprintf mini_fwprintf
#else
#define mini_ftprintf mini_fprintf
#endif

int
MCRT_VARARGFN
mini_ftprintf(FILE * fp, LPCTSTR szFmt, ...)
{
    va_list marker;
    int out_len;

    va_start( marker, szFmt );
    out_len = mini_vftprintf(fp, szFmt, marker);
    va_end( marker );
    return out_len;
}

#ifdef UNICODE
#define mini_tprintf mini_wprintf
#else
#define mini_tprintf mini_printf
#endif

int
MCRT_VARARGFN
mini_tprintf(LPCTSTR szFmt, ...)
{
    va_list marker;
    int out_len;

    va_start( marker, szFmt );
    out_len = mini_vftprintf(stdout, szFmt, marker);
    va_end( marker );
    return out_len;
}


// vim:sw=4:ts=4:et:
