#ifndef APPLICATION_H
#define APPLICATION_H

#define SCR_HEIGHT 459
#define SCR_WIDTH  522
#define BACKRON    0x000000
#define TBACKRON   301

#define IntToPtr(i) ((VOID *)(INT_PTR)((int)i))

extern const char NamaGame [] ;
extern const char NamaApp [] ;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
#endif