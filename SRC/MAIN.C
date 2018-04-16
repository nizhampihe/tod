/*------------------------------------*
 * MAIN.C                             *
 *                (c) 2018 NizhamPihe *
 *------------------------------------*/
#include <windows.h>
#include "hdr/resource.h"
#include "hdr/application.h"

const char NamaGame [] = "Turbo of Doom" ;
const char NamaApp [] = "TOD.EXE" ;

int
WINAPI
WinMain (HINSTANCE hInstance,
         HINSTANCE hPrevInstance,
         LPSTR     lpCmdLine,
         int       nShowCmd)
{
  WNDCLASSEX wc ;

  wc.cbSize        = sizeof (WNDCLASSEX) ;
  wc.style         = CS_HREDRAW | 
                     CS_VREDRAW ;
  wc.lpfnWndProc   = WndProc ;
  wc.cbClsExtra    = 0 ;
  wc.cbWndExtra    = 0 ;
  wc.hInstance     = hInstance ;
  wc.hIcon         = LoadIcon  (NULL,
                     IDI_APPLICATION) ;
  wc.hCursor       = LoadCursor (NULL,
                     IDC_ARROW) ;
  wc.hbrBackground = (HBRUSH) 
                     (COLOR_WINDOW+1) ;
  wc.lpszMenuName  = MAKEINTRESOURCE
                     (IDM_MYMENU) ;
  wc.lpszClassName = NamaApp ;
  wc.hIconSm       = LoadIcon (NULL,
                     DI_APPLICATION) ;

  RegisterClassEx (&wc) ;

  HWND hwnd = CreateWindowEx (
    WS_EX_CLIENTEDGE,
    NamaApp,
    NamaGame,
    WS_SYSMENU | WS_MINIMIZEBOX,
    CW_USEDEFAULT, CW_USEDEFAULT,
    SCR_WIDTH, SCR_HEIGHT,
    NULL, NULL, hInstance, NULL) ;

  ShowWindow (hwnd, nShowCmd) ;
  UpdateWindow (hwnd) ;

  MSG Msg ;
  while (GetMessage (&Msg, 
         NULL, 0, 0) > 0)
  {
    TranslateMessage (&Msg) ;
    DispatchMessage (&Msg) ;
  }
  return Msg.wParam ;
}