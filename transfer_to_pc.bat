@echo off



rem Transfer folder from Raspberry Pi to local machine
scp -r pi@raspberrypi:/home/pi/c_projects/calibrazione/misure .


echo Folder %1 transferred from Raspberry Pi to local machine.
