
# cmake_minimum_required(VERSION 3.15)

# Set the project name and version
# project(${UPPER_PROJECT_NAME} VERSION 1.0)

# add_library(${UPPER_PROJECT_NAME} MODULE)

set(UPPER_PROJECT_NAME ${CMAKE_PROJECT_NAME})


# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_policy(SET CMP0076 NEW)

option(STMEPIC_BARD_ID "Enable BoardID" ON)
option(STMEPIC_CAN_CONTROLER "Enable CAN Controler" ON)
option(STMEPIC_ENCODERS "Enable Encoders module" ON)
option(STMEPIC_LOGGER "Enable LOGGER module" ON)
option(STMEPIC_MOVEMENT "Enable Movement controler module" ON)
option(STMEPIC_SENSORS "Enable Sensors module" ON)
option(STMEPIC_DFU_PROGRAMING "Enable Usb programing module" ON)


# Add the core modules
add_subdirectory(src/Containers)
add_subdirectory(src/Timing)
add_subdirectory(src/Gpio)
add_subdirectory(src/Filters)
add_subdirectory(src/config)
add_subdirectory(src/Status)
add_subdirectory(src/Device)
add_subdirectory(etl)


# Add the extra modules
if(STMEPIC_BARD_ID)
  add_subdirectory(src/BoardId)
endif()

if(STMEPIC_CAN_CONTROLER)
  add_subdirectory(src/CanControl)
endif()


if(STMEPIC_ENCODERS)
  add_subdirectory(src/Encoders)
endif()

if(STMEPIC_LOGGER)
  add_subdirectory(src/Logger)
endif()

if(STMEPIC_MOVEMENT)
  add_subdirectory(src/Movement)
  add_subdirectory(src/Motor)
endif()

if(STMEPIC_SENSORS)
  add_subdirectory(src/Sensors)
endif()

if(STMEPIC_DFU_PROGRAMING)
  add_subdirectory(src/DFU)
endif()





