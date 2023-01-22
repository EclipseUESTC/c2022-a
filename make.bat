@ echo off
if clean==%1 (goto CLEAN) 
call vcvars64.bat
cl /Zi /EHsc /Fe:main.exe *.c 
exit

:CLEAN
del *.exe
del *.obj
del *.pdb
del *.ilk