cmake_minimum_required(VERSION 3.1)
project(opengl-test)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 OpenGL 库
find_package(OpenGL REQUIRED)

# 设置 GLEW 的包含路径和库文件路径
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# 查找 GLFW 库
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h PATHS /usr/local/include /usr/include)
find_library(GLFW_LIBRARY glfw3 PATHS /usr/local/lib /usr/lib64 /usr/lib)
include_directories(${GLFW_INCLUDE_DIR})

# 包含源文件
set(SOURCES main.cc)

# 添加可执行文件
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# 设置可执行文件生成路径
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 链接库
target_link_libraries(${CMAKE_PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    GLEW
    ${GLFW_LIBRARIES}
)
