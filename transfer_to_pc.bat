@echo off
setlocal

rem Get the full path of the current directory
set "currentDirectory=%CD%"

echo Full Path: %currentDirectory%

rem Extract the current directory name only
for %%I in ("%currentDirectory%") do set "currentDirectoryName=%%~nI"

rem Transfer folder from Raspberry Pi to local machine
scp -r pi@raspberrypi:/home/pi/c_projects/%currentDirectoryName%/misure .

echo Folder %currentDirectoryName% transferred from Raspberry Pi to local machine.
