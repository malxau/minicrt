/*
 * EP_GUI.C
 *
 * Entrypoint code for GUI applications.
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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);

#ifdef UNICODE
#define GUI_USER_ENTRYPOINT wWinMain
#define GUI_CRT_ENTRYPOINT  wWinMainCRTStartup
#else
#define GUI_USER_ENTRYPOINT WinMain
#define GUI_CRT_ENTRYPOINT  WinMainCRTStartup
#endif

VOID GUI_CRT_ENTRYPOINT()
{
    LPTSTR szCmdLine = GetCommandLine();
    TCHAR  cTerminate = ' ';

    if (*szCmdLine == '"') {
        cTerminate = '"';
        szCmdLine++;
    }

    while (*szCmdLine && *szCmdLine != cTerminate) {
        szCmdLine++;
    }

    if (*szCmdLine == '"') {
        szCmdLine++;
    }

    while (*szCmdLine && *szCmdLine == ' ') {
        szCmdLine++;
    }


    GUI_USER_ENTRYPOINT(GetModuleHandle(NULL), NULL, szCmdLine, SW_SHOW);

    ExitProcess(0);
}

// vim:sw=4:ts=4:et:
