@echo off

rem Check if folder name is provided as a command-line argument
if "%~1"=="" (
    echo Error: Please provide the folder name to transfer.
    exit /b 1
)

rem Transfer folder to Raspberry Pi
scp -r %1 pi@raspberrypi:/home/pi/c_projects/

echo Folder %1 transferred to Raspberry Pi.
