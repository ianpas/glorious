@echo off

cd /d "%~dp0"

set FLAG=/Zpc /nologo /O3 /WX /Ges
set COMPILE=fxc %FLAG%


rem =======================================================================
rem  glorious
rem =======================================================================
set INPUT=glorious
set OUTPUT=glorious

%COMPILE% /T vs_5_0 /E VSMain /Fo "%OUTPUT%\PashaShader.pashavs" "%INPUT%\PashaShader.hlsl"
%COMPILE% /T ps_5_0 /E PSMain /Fo "%OUTPUT%\PashaShader.pashaps" "%INPUT%\PashaShader.hlsl"


pause
