cmake_minimum_required(VERSION 3.5)
project(qt_viewer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -fdiagnostics-color=always)
endif()



#SET(CMAKE_BUILD_TYPE "Debug")

# set(CMAKE_PREFIX_PATH "DRIVER/CAMERA/lib/qt5/bin")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QRC_FILES ./UI/resource/images.qrc ./UI/resource/qss.qrc ./UI/resource/webSource.qrc)

file(GLOB OTHER_SOURCES  "UI/src/*.cpp"  "src/*.cpp" "Utility/*.cpp")

file(GLOB OTHER_INCLUDES  "UI/include/*.h*" "include/*.h*" "Utility/*.h")

file(GLOB ALL_INCLUDES  "UI/include" "include" "Utility")

##"DRIVER/CAMERA/include/libavcodec/" "DRIVER/CAMERA/include/libavformat" "DRIVER/CAMERA/include/libavutil"         

set(OTHER_SRCS ${OTHER_SOURCES} ${OTHER_INCLUDES})
set(Qt5_DIR /opt/Qt5.14.2)
find_package(Qt5 REQUIRED COMPONENTS Core WebEngineWidgets Widgets WebChannel WebEngineCore)

set(QT_LIBRARIES ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5WebEngineWidgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES})

set(UI_FILES ./UI/src/smsdialog.ui ./UI/src/aboutdialog.ui  ./UI/src/alarm.ui ./UI/src/diary.ui
        ./UI/src/addpolygon.ui ./UI/src/cameraviewer.ui ./UI/src/childtitlebar.ui
         ./UI/src/maintitlebar.ui ./UI/src/setroi.ui ./UI/src/webui.ui ./UI/src/addlidar.ui )

# find dependencies
 find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(sys_msgs REQUIRED)

# find_package(Qt5 COMPONENTS ${REQUIRED_LIBS} REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED NO_DEFAULT_PATH)
find_package(PCL 1.9 REQUIRED)
find_package(OpenCV 3.4.1 REQUIRED)
find_package(VTK REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PCL_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${VTK_INCLUDE_DIRS}
        ${JSONCPP_INCLUDE_DIRS}
        ${ALL_INCLUDES}
)

link_directories(
        ${PCL_LIBRARY_DIRS}
        ${OpenCV_LIB_DIR}
        ${VTK_LIBRARY_DIRS}
)

add_definitions(${PCL_DEFINITIONS})

add_executable(${PROJECT_NAME}_node
        ${UI_FILES}
        ${RC_FILES}
        ${QRC_FILES}
        ${QT_FORMS_H}
        ${SRC_LIST}
        ${OTHER_SRCS}
)

target_include_directories(${PROJECT_NAME}_node PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PCL_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${VTK_INCLUDE_DIRS}
  ${JSONCPP_INCLUDE_DIRS}
  ${ALL_INCLUDES}
  )

target_link_libraries(${PROJECT_NAME}_node
        ${QT_LIBRARIES}
        ${REQUIRED_LIBS_QUALIFIED}
        ${JSONCPP_LIBRARIES}
        ${PCL_LIBRARIES}
        ${OpenCV_LIBS}
        ${HK_LIBS}
        Qt5::Widgets
        )

ament_target_dependencies(${PROJECT_NAME}_node
        "ament_index_cpp"
        "rclcpp"
        "std_msgs"
        "sensor_msgs"
        "cv_bridge"
        "sys_msgs"
        )

 if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS ${PROJECT_NAME}_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME}/
)


ament_package()       
