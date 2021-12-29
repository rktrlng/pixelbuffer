cmake_minimum_required (VERSION 2.8.12)
project (PixelBuffer)

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -O2")
endif(UNIX)

if(WIN32)
	add_definitions( "/W1 /D_CRT_SECURE_NO_WARNINGS /wd4514 /nologo" )
endif(WIN32)

include_directories(
	.
)

########################################
add_executable(testpattern
	demo/testpattern.cpp
)
