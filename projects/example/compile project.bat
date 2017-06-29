@echo off
cd %~dp0
:start
echo SC-CL example.c
echo Press ENTER to launch
pause > nul
cls
"../../bin/SC-CL.exe" -platform=X360 -target=GTAV -out-dir="GTAV/X360/bin/" -vcx="example.vcxproj" -- -I "../../include/"
goto start
