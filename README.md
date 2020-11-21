# RavEngine
A C++ cross-platform game library, with emphasis on performance and ease of use. Notable features:
1. Automatic multithreaded object evaluation 
   - ECS data-oriented and Scripting-style object-oriented supported simultaneously
   - the OOP scripting system is powered by ECS and automatically threaded
2. CPU-multithreaded physics simulation (Nvidia PhysX 4.1)
3. Easy memory management handled via automatic reference counting 
4. Supports native platform rendering APIs (Metal, DirectX)
5. Easy integration with CMake
6. Quality-of-life features like automatic shader compilation

Note: RavEngine does not have a GUI editor.

## This is early alpha
Expect bugs and frequent breaking changes. Do not use in serious projects. 

## Integrating and building
Integrating this library with CMake is easy. 
```cmake
cmake_minimum_required(VERSION 3.17)

# require C++17
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

PROJECT(Example_RavEngine_Game)

add_subdirectory("RavEngine") # configure the engine library

# configure your executable like normal
file(GLOB SOURCES "src/*.cpp" "src/*.hpp" "src/*.h")
add_executable("${PROJECT_NAME}" ${SOURCES})
target_link_libraries("${APPNAME}" PUBLIC "RavEngine" )  # also adds header includes

# inform engine about your different assets
file(GLOB meshes "$meshes/*.obj")
file(GLOB textures "textures/*")
file(GLOB shaders "shaders/*.cmake")
pack_resources(TARGET "${PROJECT_NAME}" 
   MESHES ${meshes}
   SHADERS ${shaders}
   TEXTURES ${textures}
)

# fixup mac bundle
INSTALL(CODE 
   "include(BundleUtilities)
   fixup_bundle(\"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${PROJECT_NAME}.app\" \"\" \"\")
   " 
   COMPONENT Runtime
)
```
You need to declare your shaders, so that RavEngine can automatically compile them to the correct backend. Simply create a `.cmake` file and invoke RavEngine's macro:
```cmake
declare_shader("shaderName" "${CMAKE_CURRENT_LIST_DIR}/vertexshader.glsl" "${CMAKE_CURRENT_LIST_DIR}/fragmentshader.glsl" "${CMAKE_CURRENT_LIST_DIR}/varying.def.hlsl")
```
When you load a shader, RavEngine will use the name you specify as the first parameter. To learn how to write BGFX shaders, see documentation at [https://github.com/bkaradzic/bgfx](https://github.com/bkaradzic/bgfx)

Then simply build with CMake as normal. On Windows, you will need to run your initial configure twice before building. Example scripts are provided. 

## Supported platforms
| Platform | Architecture | Compiler | CMake Generator | Rendering API |
| --- | --- | --- | --- | --- |
| macOS 10.15+ | Intel | Apple Clang | Xcode | Metal |
| Windows 10 | x64 | MSVC++ | Visual Studio | DirectX 11 |
| Linux | x64 | Clang++ | Ninja | Vulkan |

Note for Linux users: You must have the following shared libaries installed on your system:
- libatomic
- x11-dev

You will also need to use the clang++ compiler, g++ is currently not supported. To do this, simply execute the following command:
```
export CC=/usr/bin/clang; export CXX=/usr/bin/clang++; ./build-linux.sh
```

## Example programs
View a respository with code samples here: [https://github.com/ravbug/ravengine-samples](https://github.com/ravbug/ravengine-samples)
