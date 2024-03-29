cmake_minimum_required (VERSION 3.12)
project (PIXELBUFFER)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(DEFAULT_BUILD_TYPE "Release")

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -O2")
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

add_executable(utiltest
	tests/utiltest.cpp
)

add_executable(vec2test
	tests/vec2test.cpp
)

add_executable(vec3test
	tests/vec3test.cpp
)

add_executable(vec4test
	tests/vec4test.cpp
)

add_executable(mat4test
	tests/mat4test.cpp
)

add_executable(mat3test
	tests/mat3test.cpp
)

add_executable(mat2test
	tests/mat2test.cpp
)

add_executable(geomtest
	tests/geomtest.cpp
)

add_executable(colortest
	tests/colortest.cpp
)

add_executable(pixelbuffertest
	tests/pixelbuffertest.cpp
)
