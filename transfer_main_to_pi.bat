@echo off


rem Transfer folder to Raspberry Pi
scp  main.cpp pi@raspberrypi:/home/pi/c_projects/%CD%/

echo main.cpp transferred to Raspberry Pi.
