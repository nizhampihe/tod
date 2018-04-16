#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include <windowsx.h>
#include "hdr/game.h"
#include "hdr/resource.h"
#include "hdr/application.h"

LRESULT
CALLBACK
WndProc (HWND   hwnd,
         UINT   msg,
         WPARAM wParam,
         LPARAM lParam)
{
    PAINTSTRUCT ps ;
    HDC         hdc ;
    POINTS      pt ;
    
    switch (msg)
    {
        case WM_CLOSE :
            DestroyWindow (hwnd) ;
            break ;
        case WM_DESTROY :
            PostQuitMessage (0) ;
            break ;
        default :
            return DefWindowProc (hwnd, msg, wParam, lParam) ;
    }
    return 0 ;
}