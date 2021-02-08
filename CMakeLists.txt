
cmake_minimum_required(VERSION 3.5.1)


if(MSVC)
add_compile_options("/bigobj")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(CMAKE_CXX_STANDARD 17)
PROJECT(LPReditor_ANPR)

#************************
#OPENCV
#************************
if (MSVC)
#if necessary change the path ../opencv-master/build/ to the path where you build opencv
find_path(OPENCV4_ROOT OpenCV.sln ../opencv-master/build/)
set(OpenCV_DIR OPENCV4_ROOT)
if(NOT OpenCV_FOUND)
find_path(OpenCV_DIR OpenCV.sln ../opencv-master/build/)
endif(OpenCV_FOUND)
else (MSVC)
endif (MSVC) 
#if necessary change the path ../opencv-master/build/ to the path where you build opencv
FIND_PACKAGE( OpenCV REQUIRED PATHS "../opencv-master/build/")
set(OpenCV_DIR ../opencv-master/build)
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


#************************
#EXECUTABLE
#************************
find_path(LPReditor_ANPR_ROOT Open_LPReditor.cpp ../LPReditor_ANPR/ )
find_path(LPReditor_ANPR_INC utils_anpr_detect.h ${LPReditor_ANPR_ROOT}/include/ )
find_path(LPReditor_ANPR_SOURCE utils_anpr_detect.cpp ${LPReditor_ANPR_ROOT}/src/ )
FILE(GLOB LPReditor_ANPRSources ${LPReditor_ANPR_ROOT}/*.cpp ${LPReditor_ANPR_ROOT}/*.h ${LPReditor_ANPR_SOURCE}/*.cpp ${LPReditor_ANPR_INC}/*.h )
# Create a target for the library
ADD_EXECUTABLE( ${CMAKE_PROJECT_NAME} ${LPReditor_ANPRSources} )
#************************
#INC DIRS
#************************
include_directories(${LPReditor_ANPR_INC})
#************************
#PREPROCESSOR
#************************
add_definitions(
-DLPREDITOR_DEMO_NO_ARGS
-DLPREDITOR_DEMO_PRINT_STATS_IN_TXT_FILE
)

#************************
#LINKING
#************************
if(MSVC)
foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
   if(${flag_var} MATCHES "/MT")
      string(REGEX REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
   endif(${flag_var} MATCHES "/MT")
endforeach(flag_var)
endif(MSVC)
target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})
#************************
##onnxruntime
#************************
if (MSVC)
#if necessary, in the lines below, change ../onnxruntime-win-x64-1.4.0/ to point to the  actual path of the onnxruntime-win-x64-1.4.0 directory
find_library(onnxruntime-win-x64-1.4.0_RELEASE
 NAMES onnxruntime
 PATHS 
../onnxruntime-win-x64-1.4.0/lib
 )
SET(onnxruntime-win-x64-1.4.0_LIBRARY
  debug ${onnxruntime-win-x64-1.4.0_RELEASE}
  optimized ${onnxruntime-win-x64-1.4.0_RELEASE})
 find_path(onnxruntime-win-x64-1.4.0_LIB_PATH onnxruntime.lib ../onnxruntime-win-x64-1.4.0/lib)
 find_path(onnxruntime-win-x64-1.4.0_INCLUDE onnxruntime_cxx_api.h ../onnxruntime-win-x64-1.4.0/include)
  MESSAGE( STATUS )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "onnxruntime-win-x64-1.4.0_LIBRARY =${onnxruntime-win-x64-1.4.0_LIBRARY}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "onnxruntime-win-x64-1.4.0_INCLUDE =${onnxruntime-win-x64-1.4.0_INCLUDE}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS )
find_library(onnxruntime-win-x64-gpu-1.6.0_RELEASE
 NAMES onnxruntime
 PATHS 
../onnxruntime-win-x64-gpu-1.6.0/lib
 )
SET(onnxruntime-win-x64-gpu-1.6.0_LIBRARY
  debug ${onnxruntime-win-x64-gpu-1.6.0_RELEASE}
  optimized ${onnxruntime-win-x64-gpu-1.6.0_RELEASE})
 find_path(onnxruntime-win-x64-gpu-1.6.0_LIB_PATH onnxruntime.lib ../onnxruntime-win-x64-gpu-1.6.0/lib)
 find_path(onnxruntime-win-x64-gpu-1.6.0_INCLUDE onnxruntime_cxx_api.h ../onnxruntime-win-x64-gpu-1.6.0/include)
MESSAGE( STATUS )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "onnxruntime-win-x64-gpu-1.6.0_LIBRARY =${onnxruntime-win-x64-gpu-1.6.0_LIBRARY}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "onnxruntime-win-x64-gpu-1.6.0_INCLUDE =${onnxruntime-win-x64-gpu-1.6.0_INCLUDE}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS )
include_directories(${onnxruntime-win-x64-1.4.0_INCLUDE})
target_link_libraries(${CMAKE_PROJECT_NAME} ${onnxruntime-win-x64-1.4.0_LIBRARY})
#include_directories(${onnxruntime-win-x64-gpu-1.6.0_INCLUDE})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${onnxruntime-win-x64-gpu-1.6.0_LIBRARY})
file(GLOB ONNXRUNTIME_DLLS "${onnxruntime-win-x64-1.4.0_LIB_PATH}/*.dll")
file(GLOB ONNXRUNTIME_LIBS "${onnxruntime-win-x64-1.4.0_LIB_PATH}/*.lib")
#file(GLOB ONNXRUNTIME_DLLS "${onnxruntime-win-x64-gpu-1.6.0_LIB_PATH}/*.dll")
#file(GLOB ONNXRUNTIME_LIBS "${onnxruntime-win-x64-gpu-1.6.0_LIB_PATH}/*.lib")
else (MSVC)
#if necessary, in the lines below, change ../onnxruntime-linux-x64-1.6.0/ to point to the  actual path of the onnxruntime-linux-x64-1.6.0 directory
find_library(onnxruntime-linux-x64-1.6.0_RELEASE
 NAMES libonnxruntime.so
 PATHS 
../onnxruntime-linux-x64-1.6.0/lib
 )
SET(onnxruntime-linux-x64-1.6.0_LIBRARY
  debug ${onnxruntime-linux-x64-1.6.0_RELEASE}
  optimized ${onnxruntime-linux-x64-1.6.0_RELEASE}) 
 find_path(onnxruntime-linux-x64-1.6.0_LIB_PATH libonnxruntime.so ../onnxruntime-linux-x64-1.6.0/lib)
 find_path(onnxruntime-linux-x64-1.6.0_INCLUDE onnxruntime_cxx_api.h ../onnxruntime-linux-x64-1.6.0/include)
  MESSAGE( STATUS )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "onnxruntime-linux-x64-1.6.0_LIBRARY =${onnxruntime-linux-x64-1.6.0_LIBRARY}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "onnxruntime-linux-x64-1.6.0_INCLUDE =${onnxruntime-linux-x64-1.6.0_INCLUDE}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS )
find_library(onnxruntime-linux-x64-gpu-1.6.0_RELEASE
 NAMES libonnxruntime.so
 PATHS 
../onnxruntime-linux-x64-gpu-1.6.0/lib
 )
SET(onnxruntime-linux-x64-gpu-1.6.0_LIBRARY
  debug ${onnxruntime-linux-x64-gpu-1.6.0_RELEASE}
  optimized ${onnxruntime-linux-x64-gpu-1.6.0_RELEASE})
 find_path(onnxruntime-linux-x64-gpu-1.6.0_LIB_PATH libonnxruntime.so ../onnxruntime-linux-x64-gpu-1.6.0/lib)
 find_path(onnxruntime-linux-x64-gpu-1.6.0_INCLUDE onnxruntime_cxx_api.h ../onnxruntime-linux-x64-gpu-1.6.0/include)
  MESSAGE( STATUS )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "onnxruntime-linux-x64-gpu-1.6.0_LIBRARY =${onnxruntime-linux-x64-gpu-1.6.0_LIBRARY}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "onnxruntime-linux-x64-gpu-1.6.0_INCLUDE =${onnxruntime-linux-x64-gpu-1.6.0_INCLUDE}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS )
include_directories(${onnxruntime-linux-x64-1.6.0_INCLUDE})
target_link_libraries(${CMAKE_PROJECT_NAME} ${onnxruntime-linux-x64-1.6.0_LIBRARY})
#include_directories(${onnxruntime-linux-x64-gpu-1.6.0_INCLUDE})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${onnxruntime-linux-x64-gpu-1.6.0_LIBRARY})
file(GLOB ONNXRUNTIME_DLLS "${onnxruntime-linux-x64-1.6.0_LIB_PATH}/*.so")
file(GLOB ONNXRUNTIME_LIBS "${onnxruntime-linux-x64-1.6.0_LIB_PATH}/*.so")
#file(GLOB ONNXRUNTIME_DLLS "${onnxruntime-linux-x64-gpu-1.6.0_LIB_PATH}/*.so")
#file(GLOB ONNXRUNTIME_LIBS "${onnxruntime-linux-x64-gpu-1.6.0_LIB_PATH}/*.so")
endif (MSVC) 
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "ONNXRUNTIME_DLLS =${ONNXRUNTIME_DLLS}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "ONNXRUNTIME_LIBS =${ONNXRUNTIME_LIBS}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS )

#************************
#CUSTOM POST BUILD COMMAND
#************************
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
${ONNXRUNTIME_DLLS} ${ONNXRUNTIME_LIBS}
$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)
