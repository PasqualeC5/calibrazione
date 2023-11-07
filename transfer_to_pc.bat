@echo off

rem Check if folder name is provided as a command-line argument
if "%~1"=="" (
    echo Error: Please provide the folder name to transfer from Raspberry Pi.
    exit /b 1
)

rem Transfer folder from Raspberry Pi to local machine
scp -r pi@raspberrypi:/home/pi/c_projects/%1 ./

echo Folder %1 transferred from Raspberry Pi to local machine.
