::------------------------------------::
:: BUILD.BAT                          ::
::                (c) 2018 NizhamPihe ::
::   Hanya Program untuk mengcompile  ::
:: agar lebih mudah                   ::
::------------------------------------::

::----------[Initialization]----------::
@ECHO OFF
IF NOT EXIST OBJ MKDIR OBJ
FOR %%I IN (%PATH%) DO (
IF EXIST %%I\GCC.EXE (
SET TEMU=1
)
)
IF NOT DEFINED TEMU (
SET PATH=..\MINGW64\BIN;%PATH%
)
IF "%~1"=="" GOTO all
IF /I "%~1"=="all" GOTO all
IF EXIST SRC/%~1.C GOTO src
IF EXIST RES/%~1.RC GOTO res
ECHO usage: build [FileName]
GOTO exit

::----------[Source File]-------------::
:src
SET FILE=SRC\%~1.C
FOR %%C IN (%FILE%) DO (
ECHO Compiling %%~nC . . .
GCC -o OBJ\%%~nC.O -c SRC\%%~nC.C
)
GOTO fin

::----------[Resource File]-----------::
:res
SET FILE=RES\%~1.RC
FOR %%F IN (%FILE%) DO (
ECHO Compiling %%~nF . . .
WINDRES -o OBJ\%%~nF.O -i RES\%%~nF.RC
)
GOTO fin

::----------[Compile All]-------------::
:all
FOR /R %%S IN (SRC\*.C) DO (
ECHO Compiling %%~nS . . .
GCC -o OBJ\%%~nS.O -c SRC\%%~nS.C
)
FOR /R %%R IN (RES\*.RC) DO (
ECHO Compiling %%~nR . . .
WINDRES -o OBJ\%%~nR.O -i RES\%%~nR.RC
)
GOTO fin

::----------[Linking]-----------------::
:fin
SET FILE=TOD.EXE
ECHO Linking . . .
GCC -o %FILE% OBJ\*.O -mwindows -mconsole
IF NOT EXIST %FILE% (
ECHO Program Gagal Dibuat
GOTO exit
)
FOR %%F IN (%FILE%) DO (
ECHO Program Berhasil Dibuat
ECHO Ukuran = %%~zF byte
)
CHOICE /c:ny /n /m "Play ? (y/n)"
IF %errorlevel% == 1 GOTO exit
%FILE%

:exit