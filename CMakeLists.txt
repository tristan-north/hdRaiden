# Compile with Visual Studio 2022 compiler. Run cmake from x64 Native Tools Command Prompt for VS 2022.

# cd D:\dev\hdRaiden\buildHoudini
# cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ..
# ninja


cmake_minimum_required(VERSION 3.10)

# Define the project name and specify the programming language
project(hdRaiden LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HFS "C:/Program Files/Side Effects Software/Houdini 20.5.278")

# Define output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../binHoudini)

include_directories(
	${HFS}/toolkit/include
	${HFS}/python311/include
)


# Find all .cpp files in the src directory and store them in SOURCES variable
file(GLOB SOURCES "src/*.cpp")

# Add the executable target and specify the source files
add_library(hdRaiden SHARED ${SOURCES})

target_link_libraries(hdRaiden PRIVATE
    ${HFS}/python311/libs/python311.lib
    ${HFS}/custom/houdini/dsolib/hboost_python311-mt-x64.lib
    ${HFS}/custom/houdini/dsolib/tbb.lib
    ${HFS}/custom/houdini/dsolib/libpxr_tf.lib
    ${HFS}/custom/houdini/dsolib/libpxr_sdf.lib
    ${HFS}/custom/houdini/dsolib/libpxr_hd.lib
    ${HFS}/custom/houdini/dsolib/libpxr_hf.lib
    ${HFS}/custom/houdini/dsolib/libpxr_arch.lib
    ${HFS}/custom/houdini/dsolib/libpxr_gf.lib
    ${HFS}/custom/houdini/dsolib/libpxr_cameraUtil.lib
    ${HFS}/custom/houdini/dsolib/libpxr_vt.lib
    ${HFS}/custom/houdini/dsolib/libpxr_usdRender.lib
)

# From hcustom
add_definitions(-nologo -TP -Zc:forScope -Zc:rvalueCast -Zc:inline- -Zc:strictStrings -std:c++17 -Zc:referenceBinding -Zc:ternary -Zc:throwingNew -permissive- -Zc:__cplusplus -DAMD64 -DSIZEOF_VOID_P=8 -DI386 -DWIN32 -DSWAP_BITFIELDS -D_WIN32_WINNT=0x0600 -DNOMINMAX -DSTRICT -DWIN32_LEAN_AND_MEAN -D_USE_MATH_DEFINES -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS -DSESI_LITTLE_ENDIAN -DHBOOST_ALL_NO_LIB -DHBOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT=1 -DHBOOST_BIND_GLOBAL_PLACEHOLDERS=1 -DEIGEN_MALLOC_ALREADY_ALIGNED=0 -DFBX_ENABLED=1 -DOPENCL_ENABLED=1 -DOPENVDB_ENABLED=1 -DUSE_VULKAN=1 -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS=1-wd4384 -wd4355 -w14996 -O2 -DNDEBUG -DH_PYTHON_VERSION=3.11 -MD -EHsc -GR -bigobj -DMAKING_DSO -LD)

# Set compiler options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd /Zi /Ob0 /Od /RTC1")
endif()

# Set the linker options to not generate manifest files
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
