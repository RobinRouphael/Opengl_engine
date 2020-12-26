project(Engine)

############################################
# Configure CMake and GCC flags
cmake_minimum_required(VERSION 2.8.9) # Minimal version compatible QT5
CMAKE_POLICY(SET CMP0043 NEW) # This will silence the Cmake Warning "Policy CMP0043 is not set"

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic -Wextra")
set(CMAKE_CXX_STANDARD 17)
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
        ${folder_ui} src/widgets/metaballWidget.cpp src/widgets/metaballWidget.h src/models/metaball.cpp src/models/metaball.h src/widgets/singleMeshModelWidget.cpp src/widgets/singleMeshModelWidget.h src/core/bone.cpp src/core/bone.h src/core/transform.cpp src/core/transform.h src/models/cylinder.cpp src/models/cylinder.h src/widgets/boneWidget.cpp src/widgets/boneWidget.h)

set(EXT_LIBS Qt5::OpenGL ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${EXT_LIBS})
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})
