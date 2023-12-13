# Install script for directory: /home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/SOEM/libsoem.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/soem/cmake/soemConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/soem/cmake/soemConfig.cmake"
         "/home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/SOEM/CMakeFiles/Export/share/soem/cmake/soemConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/soem/cmake/soemConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/soem/cmake/soemConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/soem/cmake" TYPE FILE FILES "/home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/SOEM/CMakeFiles/Export/share/soem/cmake/soemConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/soem/cmake" TYPE FILE FILES "/home/pi/Desktop/c_projects/calibrazione/build/meca500_ethercat_cpp/sun_etherCAT/SOEM/CMakeFiles/Export/share/soem/cmake/soemConfig-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/soem" TYPE FILE FILES
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercat.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercatbase.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercatcoe.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercatconfig.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercatconfiglist.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercatdc.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercateoe.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercatfoe.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercatmain.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercatprint.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercatsoe.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/soem/ethercattype.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/osal/linux/osal_defs.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/osal/osal.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/oshw/linux/nicdrv.h"
    "/home/pi/Desktop/c_projects/calibrazione/meca500_ethercat_cpp/sun_etherCAT/SOEM/oshw/linux/oshw.h"
    )
endif()

