cmake_minimum_required(VERSION 3.10)

project(orcquestion)
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/package")
#set(PACKVERSION 2.0.0.1)
######################################################################
#全局编译标志
######################################################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

######################################################################
#全局链接和包含
######################################################################

include_directories(${PROJECT_SOURCE_DIR})
#include_directories(${CMAKE_SOURCE_DIR}/3rdParty/mysql_connector/include/jdbc)
#include_directories(${CMAKE_SOURCE_DIR}/3rdParty/ali_oss/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdParty)
#include_directories(${CMAKE_SOURCE_DIR}/common)
#include_directories(${CMAKE_SOURCE_DIR}/3rdParty/redis_sds/include)
include_directories(${CMAKE_SOURCE_DIR}/ai_model/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdParty/opencv3.4.5/include)
include_directories(${CMAKE_SOURCE_DIR}/alg/include/caffe/gflags/include)
include_directories(${CMAKE_SOURCE_DIR}/alg/include/)
include_directories(${CMAKE_SOURCE_DIR}/3rdParty/eureka/)

link_directories(${CMAKE_SOURCE_DIR}/3rdParty/eureka/lib)
#link_directories(${CMAKE_SOURCE_DIR}/3rdParty/librdkafka/lib)
#link_directories(${CMAKE_SOURCE_DIR}/3rdParty/mysql_connector/lib)
#link_directories(${CMAKE_SOURCE_DIR}/3rdParty/ali_oss/lib)
#link_directories(${CMAKE_SOURCE_DIR}/3rdParty/redis_sds/lib)
link_directories(${CMAKE_SOURCE_DIR}/ai_model/libs/linux/gpu)
link_directories(${CMAKE_SOURCE_DIR}/3rdParty/opencv3.4.5/lib)
link_directories(${CMAKE_SOURCE_DIR}/alg/lib)

find_package(Boost REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(CUDA REQUIRED)
if (CUDA_FOUND)
    include_directories(${CUDA_INCLUDE_DIRS})
endif()

#find_package(OpenCV REQUIRED)
#if (OpenCV_FOUND)
#    include_directories(${OpenCV_INCLUDE_DIRS})
#endif()

#################################################################L#####
#全局编译输出指定
######################################################################

#IF(CMAKE_BUILD_TYPE MATCHES Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
#ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${BUILD_TYPE})


######################################################################
#子工程目录
######################################################################
#add_subdirectory(base/third_party/dynamic_annotations)
#add_subdirectory(base/third_party/symbolize)
#add_subdirectory(base/third_party/xdg_mime)
#add_subdirectory(base/third_party/libevent)
#add_subdirectory(third_party)


#add_subdirectory(base)
#add_subdirectory(3rdParty/eureka)
#add_subdirectory(breakpad)
#add_subdirectory(3rdParty/hiredis)

######################################################################
#common目录 获取所有源文件
######################################################################
#aux_source_directory(${CMAKE_SOURCE_DIR}/common DIR_COMMON_SRCS)
######################################################################
#编译对象
######################################################################
add_executable(orcquestion
    demo.cpp
    ${DIR_COMMON_SRCS}
)

if(Boost_FOUND)
    target_link_libraries(orcquestion ${Boost_LIBRARIES})
endif()

if(CUDA_FOUND)
    target_link_libraries(orcquestion ${CUDA_LIBRARIES})
endif()

if(OpenCV_FOUND)
    target_link_libraries(orcquestion ${OpenCV_LIBRARIES})
endif()

target_include_directories(orcquestion PRIVATE
    ${PROJECT_SOURCE_DIR}/alg/include
    ${PROJECT_SOURCE_DIR}/opencv3.4.5/include
    ${PROJECT_SOURCE_DIR}/3rdParty/eureka/json
    ${PROJECT_SOURCE_DIR}/alg/include/caffe/gflags/include 
    )

target_link_libraries(orcquestion
    crypto
    boost_system
    opencv_core
    opencv_imgcodecs
    
    #ocritem
    #ProblemClass
    #glog
    #gflags
    
    )

######################################################################
#程序发布设置
######################################################################

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ DESTINATION bin)
install(DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ DESTINATION lib)
#install(DIRECTORY 3rdParty/librdkafka/lib DESTINATION .)
install(DIRECTORY 3rdParty/eureka/lib DESTINATION .)
install(DIRECTORY alg/lib DESTINATION .)
install(DIRECTORY config/ DESTINATION bin/config)
install(DIRECTORY opencv3.4.5/lib DESTINATION .)
#install(FILES scripts/requirments.sh DESTINATION .)
#install(FILES scripts/install.sh DESTINATION .)
#install(FILES scripts/ReadMe.txt DESTINATION .)
#install(DIRECTORY 3rdParty/mysql_connector/lib DESTINATION .)
#install(DIRECTORY 3rdParty/ali_oss/lib DESTINATION .)
#install(DIRECTORY 3rdParty/redis_sds/lib DESTINATION .)
install(DIRECTORY ai_model/ DESTINATION bin/mod)
