#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct sgambar {
    int            *data ;
    RECT            size ;
    struct sgambar *next ;
} GAMBAR ;

extern int hy, wx ;

HWND BuatStatusBar (HWND, int, HINSTANCE) ;
BOOL grphcinit (HWND, HWND) ;
BOOL tampil (HDC) ;
GAMBAR GetGambar (HBITMAP) ;
BOOL taroi (GAMBAR) ;
BOOL tarop (int, int, int) ;
BOOL resetl (GAMBAR) ;
//HBITMAP layar (HWND, HWND, HBITMAP) ;
//void drawin (HDC, POINTS, HBITMAP) ;
//POINTS
//GetGambar (HBITMAP gb) ;

#endif