cmake_minimum_required(VERSION 3.10)

# Define the project name and specify the programming language
project(hdRaiden LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(HOUDINI_ROOT "C:/Program Files/Side Effects Software/Houdini 20.5.278")
set(USD_ROOT "D:/dev/dependencies/usd")

# Define output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# Build against Houdini or vanilla USD
option(TARGET_DCC "DCC application to build for, eg HOUDINI." NONE)

# Odin build ------------------------------------------------------
file(GLOB ODINSOURCES "src/*.odin")

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/hdRdn_odin.lib
    COMMAND odin build ../src -build-mode:static -strict-style -out:hdRdn_odin.lib
    DEPENDS ${ODINSOURCES}
)

# Add a custom target for hdRdn_odin.lib
add_custom_target(GenerateOdinLib ALL DEPENDS ${CMAKE_BINARY_DIR}/hdRdn_odin.lib)


# C++ build ------------------------------------------------------
if(TARGET_DCC STREQUAL Houdini)
    include_directories(
        ${HOUDINI_ROOT}/toolkit/include
        ${HOUDINI_ROOT}/python311/include
    )
else()
    include_directories(
        ${USD_ROOT}/include
        ${USD_ROOT}/include/boost-1_78
        ${USD_ROOT}/python/include
    )
endif()


# Find all .cpp files in the src directory and store them in SOURCES variable
file(GLOB CPPSOURCES "src/cpp/*.cpp")

# Add the executable target and specify the source files
add_library(hdRaiden SHARED ${CPPSOURCES})

add_dependencies(hdRaiden GenerateOdinLib)

if(TARGET_DCC STREQUAL Houdini)
    target_link_libraries(hdRaiden PRIVATE
        ${HOUDINI_ROOT}/python311/libs/python311.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/hboost_python311-mt-x64.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/tbb.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/libpxr_tf.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/libpxr_sdf.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/libpxr_hd.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/libpxr_hf.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/libpxr_arch.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/libpxr_gf.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/libpxr_cameraUtil.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/libpxr_vt.lib
        ${HOUDINI_ROOT}/custom/houdini/dsolib/libpxr_usdRender.lib
        ${CMAKE_BINARY_DIR}/hdRdn_odin.lib
    )
    # From hcustom
    add_definitions(-nologo -TP -Zc:forScope -Zc:rvalueCast -Zc:inline- -Zc:strictStrings -std:c++17 -Zc:referenceBinding -Zc:ternary -Zc:throwingNew -permissive- -Zc:__cplusplus -DAMD64 -DSIZEOF_VOID_P=8 -DI386 -DWIN32 -DSWAP_BITFIELDS -D_WIN32_WINNT=0x0600 -DNOMINMAX -DSTRICT -DWIN32_LEAN_AND_MEAN -D_USE_MATH_DEFINES -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS -DSESI_LITTLE_ENDIAN -DHBOOST_ALL_NO_LIB -DHBOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT=1 -DHBOOST_BIND_GLOBAL_PLACEHOLDERS=1 -DEIGEN_MALLOC_ALREADY_ALIGNED=0 -DFBX_ENABLED=1 -DOPENCL_ENABLED=1 -DOPENVDB_ENABLED=1 -DUSE_VULKAN=1 -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS=1-wd4384 -wd4355 -w14996 -O2 -DNDEBUG -DH_PYTHON_VERSION=3.11 -MD -EHsc -GR -bigobj -DMAKING_DSO -LD)
else()
    target_link_libraries(hdRaiden PRIVATE
        ${USD_ROOT}/python/libs/python310.lib
        ${USD_ROOT}/lib/boost_python310-vc142-mt-x64-1_78.lib
        ${USD_ROOT}/lib/tbb.lib
        ${USD_ROOT}/lib/usd_tf.lib
        ${USD_ROOT}/lib/usd_sdf.lib
        ${USD_ROOT}/lib/usd_hd.lib
        ${USD_ROOT}/lib/usd_hf.lib
        ${USD_ROOT}/lib/usd_arch.lib
        ${USD_ROOT}/lib/usd_gf.lib
        ${USD_ROOT}/lib/usd_cameraUtil.lib
        ${USD_ROOT}/lib/usd_vt.lib
        ${USD_ROOT}/lib/usd_usdRender.lib
        ${CMAKE_BINARY_DIR}/hdRdn_odin.lib
    )
    add_definitions(/EHsc /LD /MD /DNOMINMAX)
endif()

# Set compiler options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd /Zi /Ob0 /Od /RTC1")
endif()

# Disable manifest generation
if(MSVC)
    target_link_options(hdRaiden PRIVATE /MANIFEST:NO)
endif()