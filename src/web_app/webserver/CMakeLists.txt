# Copyright (c) 2022，Horizon Robotics.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.5)
project(mywebsocket)

SET( CMAKE_BUILD_TYPE "Release")

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lprotobuf  -std=c++11  -lpthread ")
# #设置编译带的参数

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(PCL 1.9 REQUIRED)
find_package(RapidJSON)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)


MESSAGE(${PROJECT_SOURCE_DIR})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/uWSC/include
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/openssl
  include/
  include/server
  include/utils
  include/threads
  include/websocket
  ${PCL_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS})
  
file(GLOB_RECURSE ALL_SRCS "src/webTalk/[a-zA-Z]*.cpp" "src/webTalk/[a-zA-Z]*.cc"
                           "src/[a-zA-Z]*.cpp" "src/webTalk/[a-zA-Z]*.cpp"  )

add_executable(${PROJECT_NAME} ${ALL_SRCS})


ament_target_dependencies(mywebsocket rclcpp sensor_msgs std_msgs cv_bridge )


link_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/uWSC/
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/openssl/lib/
  ${PCL_LIBRARY_DIRS})

# SET(CMAKE_LIBRARY_PATH
# /home/ljy/ros2_ws/src/webserver/third_party/openssl/lib/
# ${CMAKE_CURRENT_SOURCE_DIR}/third_party/uWSC/
# )

add_definitions(${PCL_DEFINITIONS})

target_link_libraries(mywebsocket
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/openssl/lib/libssl.so.1.1
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/openssl/lib/libcrypto.so.1.1
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/uWSC/libuWS.so
  ${OpenCV_LIBS}
  ${PCL_LIBRARIES}
  z)


install(TARGETS
  mywebsocket
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  DESTINATION lib/${PROJECT_NAME})

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/uWSC/libuWS.so
  DESTINATION lib/)

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/openssl/lib/libssl.so.1.1
  DESTINATION lib/)  
install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/openssl/lib/libcrypto.so.1.1
  DESTINATION lib/)  



if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Install launch files.
install(DIRECTORY
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
