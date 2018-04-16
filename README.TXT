+---------------------------------+
| TOD.EXE - TURBO OF DOOM         |
|               TOD v1.0.0 x86 64 |
|             (c) 2018 NizhamPihe |
+---------------------------------+

DESCRIPTION
===========
  sebuah game petualangan arcade
  endless space shooter yang sangat
  menyenangkan

FEATURES
========
  - Endless Run
  - Save HighScore
  - Power Ups

PREREQUISITES
=============
  - CPU Architecture x86
  - OS Windows 7 64 bit
  - MinGW-w64

INSTALATION
===========
  $ git clone https://github.com/nizhampihe/tutpotr.git
  $ cd tod
  $ for /r %f in (src\*.c) do gcc -o %~nf.o -c src\%~nxf
  $ for /r %f in (res\*.rc) do windres -o %~nf.o -i res\%~nxf
  $ gcc -o tod.exe *.o
  $ tod.exe