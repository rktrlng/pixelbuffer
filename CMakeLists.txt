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

if(UNIX)
	# install(
	# 	DIRECTORY pixelbuffer
	# 	DESTINATION /usr/local/lib
	# )
	install(
		FILES tools/img2pbf tools/pbf2img tools/pbf2imgbulk
		DESTINATION /usr/local/bin
		PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
	)
endif(UNIX)

########################################
add_executable(testpattern
	test/testpattern.cpp
)

add_executable(vec2test
	test/vec2test.cpp
)

add_executable(onebittest
	test/onebittest.cpp
)

add_executable(tgatest
	test/tgatest.cpp
)

add_executable(asciiart
	test/asciiart.cpp
)
