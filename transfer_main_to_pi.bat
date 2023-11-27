@echo off


rem Transfer folder to Raspberry Pi
rem Get the full path of the current directory
set "currentDirectory=%CD%"

echo Full Path: %currentDirectory%

rem Extract the current directory name only
for %%I in ("%currentDirectory%") do set "currentDirectoryName=%%~nI"

echo Directory name: %currentDirectoryName%

scp  main.cpp pi@raspberrypi:/home/pi/c_projects/%currentDirectoryName%/

echo main.cpp transferred to Raspberry Pi.
