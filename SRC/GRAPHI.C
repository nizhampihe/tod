#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include <windowsx.h>
#include "hdr/graphics.h"
#include "hdr/application.h"

BYTE *bdp ;
int hy, wx ;

BOOL tarop (int a, int b, int c)
{
	bdp [(a + (hy - b - 1) * wx) * 3 + 0] = c % 0x100 ; c /= 0x100 ;
	bdp [(a + (hy - b - 1) * wx) * 3 + 1] = c % 0x100 ; c /= 0x100 ;
	bdp [(a + (hy - b - 1) * wx) * 3 + 2] = c ;
	return TRUE ;
}

BOOL resetl (GAMBAR gb)
{
    for (int y = gb.size.top ; y < gb.size.bottom ; y++)
    for (int x = gb.size.left ; x < gb.size.right ; x++)
    if (bdp [(x + (hy - y - 1) * wx) * 3 + 2] * 0x10000 +
    bdp [(x + (hy - y - 1) * wx) * 3 + 1] * 0x100 +
    bdp [(x + (hy - y - 1) * wx) * 3 + 0] != BACKRON)
    tarop (x, y, BACKRON) ;
    return TRUE ;
}

BOOL
grphcinit (HWND ly,
           HWND st)
{
    RECT rc, rs ;
    GetClientRect (ly, &rc) ;
    GetWindowRect (st, &rs) ;
    wx = rc.right ;
    hy = rc.bottom - rc.top - (rs.bottom - rs.top) ;
    GetWindowRect (ly, &rc) ;
    bdp = (BYTE *) malloc (wx * hy * 3) ;
    for (int y = 0 ; y < hy ; y++)
    for (int x = 0 ; x < wx ; x++)
    tarop (x, y, BACKRON) ;
    return TRUE ;
}

HWND
BuatStatusBar (HWND      hwnd,
               int       id,
               HINSTANCE hinst)
{
    HWND    hstatus ;
    RECT    rc ;
    
    hstatus = CreateWindowEx (
        0,
        STATUSCLASSNAME,
        (PCTSTR) NULL,
        SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        hwnd, (HMENU) IntToPtr (id), hinst, NULL) ;
    GetClientRect (hwnd, &rc) ;
    int pap[4] = {100, 200, 300, -1} ;
    SendMessage (hstatus, SB_SETPARTS, (WPARAM) sizeof (pap) / sizeof (int), (LPARAM) pap) ;
    return hstatus ;
}

HBITMAP
BuatLayar (HDC hdc)
{
    BITMAPINFOHEADER bmih ;
    memset (&bmih, 0, sizeof (BITMAPINFOHEADER)) ;
    
    bmih.biWidth = wx ;
    bmih.biHeight = hy;
    bmih.biBitCount = 24 ;
    bmih.biCompression = BI_RGB ;
    bmih.biSize = sizeof (BITMAPINFOHEADER) ;
    bmih.biPlanes = 1 ;
    
    BITMAPINFO *bmi = (BITMAPINFO *) &bmih ;
    return CreateDIBitmap (hdc, &bmih, CBM_INIT, bdp, bmi, DIB_RGB_COLORS) ;
}

BOOL
tampil (HDC hdc)
{
    HBITMAP gb = BuatLayar (hdc) ;
    HDC mem = CreateCompatibleDC (NULL) ;
    HBITMAP bmem = SelectBitmap(mem, gb) ;
    //BITMAP bm ;
    //GetObject (gb, sizeof (bm), &bm) ;
    BitBlt (hdc, 0, 0, wx, hy, mem, 0, 0, SRCCOPY);
    SelectBitmap (mem, bmem) ;
    DeleteObject (bmem) ;
    DeleteObject (gb) ;
    DeleteDC (mem) ;
    return TRUE ;
}

GAMBAR
GetGambar (HBITMAP gb)
{
    BITMAPINFO bmi ;
    GAMBAR ret ;
    ret.next = NULL ;
    HDC hdc = CreateCompatibleDC (NULL) ;
    memset (&bmi, 0, sizeof (BITMAPINFOHEADER)) ;
    bmi.bmiHeader.biSize = sizeof (BITMAPINFOHEADER) ;
    GetDIBits (hdc, gb, 0, 0, NULL, &bmi, DIB_RGB_COLORS) ;
    bmi.bmiHeader.biBitCount = 24 ;
    bmi.bmiHeader.biCompression = BI_RGB ;
    BYTE *data = (BYTE *) malloc (bmi.bmiHeader.biHeight * bmi.bmiHeader.biWidth * 3) ;
    ret.data = (int *) malloc (bmi.bmiHeader.biHeight * bmi.bmiHeader.biWidth * 4) ;
    ret.size = (RECT) {0, 0, (SHORT)bmi.bmiHeader.biHeight, (SHORT)bmi.bmiHeader.biWidth} ;
    GetDIBits (hdc, gb, 0, bmi.bmiHeader.biHeight, data, &bmi, DIB_RGB_COLORS) ;
    for (int y = 0 ; y < bmi.bmiHeader.biHeight ; y++)
    for (int x = 0 ; x < bmi.bmiHeader.biWidth ; x++)
    ret.data [x + y * (bmi.bmiHeader.biWidth)] = 
    data [(x + y * (bmi.bmiHeader.biWidth)) * 3 + 2] * 0x10000 +
    data [(x + y * (bmi.bmiHeader.biWidth)) * 3 + 1] * 0x100 +
    data [(x + y * (bmi.bmiHeader.biWidth)) * 3 + 0] ;
    free (data) ;
    return ret ;
}

BOOL
taroi (GAMBAR gb)
{
    for (int y = gb.size.top ; y < gb.size.bottom ; y++)
    for (int x = gb.size.left ; x < gb.size.right ; x++) 
    if (gb.data [x - gb.size.left + ((gb.size.bottom - y - 1) * (gb.size.right - gb.size.left))] != 0xffffff)
    tarop (x, y, gb.data [x - gb.size.left + ((gb.size.bottom - y - 1) * (gb.size.right - gb.size.left))]) ;
    return TRUE ;
}