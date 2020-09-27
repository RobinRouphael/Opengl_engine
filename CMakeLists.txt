project(Engine)

############################################
# Configure CMake and GCC flags
cmake_minimum_required(VERSION 2.8.9) # Minimal version compatible QT5
CMAKE_POLICY(SET CMP0043 NEW) # This will silence the Cmake Warning "Policy CMP0043 is not set"

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic -Wextra")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

find_package(Qt5 COMPONENTS OpenGL REQUIRED)
if (Qt5OpenGL_FOUND)
    message(STATUS "Found Qt ${Qt5OpenGL_VERSION}")
else (Qt5OpenGL_FOUND)
    message(EROR "Unable to find QTOpenGL library")
endif(Qt5OpenGL_FOUND)
find_package(OpenGL REQUIRED) # define OPENGL_LIBRARIES

#OpenGL deprecated on MacosX : remove compilation warning
add_definitions(-DGL_SILENCE_DEPRECATION)


#ASSIMP
find_package(ASSIMP REQUIRED)
if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif()


################################################################################
# Define project private sources and headers
#
# the variable "folder_source" contains all .cpp files of this project
FILE(GLOB_RECURSE
        folder_source
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        )

FILE(GLOB_RECURSE
        folder_header
        ${CMAKE_SOURCE_DIR}/src/*.h

        )

FILE(GLOB_RECURSE
        folder_ui
        ${CMAKE_SOURCE_DIR}/src/*.ui
        )

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/glm
        ${CMAKE_SOURCE_DIR}/textures
)

SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})
SOURCE_GROUP("Shader Files" FILES ${folder_shader})

################################################################################
# Configure QT

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON )


################################################################################
# Build target application

add_executable(${PROJECT_NAME}
        ${folder_source}
        ${folder_header}
        ${folder_ui}
        src/models/sphere.cpp src/models/sphere.h src/core/model.cpp src/core/model.h src/core/mesh.cpp src/core/mesh.h src/core/geometry.cpp src/core/geometry.h src/core/shader.cpp src/core/shader.h src/core/texture.cpp src/core/texture.h src/core/light.cpp src/core/light.h src/models/icosphere.cpp src/models/icosphere.h src/modelWidget/sphereWidget.cpp src/modelWidget/sphereWidget.h src/core/modelInterface.cpp src/core/modelInterface.h src/core/lightInterface.cpp src/core/lightInterface.h src/core/material.cpp src/core/material.h src/models/assimpmodel.cpp src/models/assimpmodel.h src/modelWidget/importedModelWidget.cpp src/modelWidget/importedModelWidget.h src/modelWidget/icoSphereWidget.cpp src/modelWidget/icoSphereWidget.h src/models/cube.cpp src/models/cube.h)

set(EXT_LIBS Qt5::OpenGL ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${EXT_LIBS} )
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})
