@echo off
setlocal

rem Get the full path of the current directory
set "currentDirectory=%CD%"

echo Full Path: %currentDirectory%

rem Extract the current directory name only
for %%I in ("%currentDirectory%") do set "currentDirectoryName=%%~nI"

rem Transfer folder to Raspberry Pi
scp -r ../%currentDirectoryName% pi@raspberrypi:/home/pi/c_projects/

echo Folder %currentDirectoryName% transferred to Raspberry Pi.
