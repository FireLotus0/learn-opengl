#### 环境配置
1. 更新系统，安装开发工具
```cpp
sudo yum update -y
sudo yum groupinstall -y "Development Tools"
```

2. 安装OpenGL开发库
```cpp
sudo yum install -y epel-release
sudo yum install -y mesa-libGL-devel mesa-libGLU-devel
```

3. 源码编译GLEW
```cpp
# 下载最新版本的 GLEW
wget http://downloads.sourceforge.net/project/glew/glew/2.2.0/glew-2.2.0.tgz

# 解压缩下载的文件
tar -xvf glew-2.2.0.tgz
cd glew-2.2.0

# 编译和安装 GLEW
make
sudo make install
```

4. 源码编译GLFW
```cpp
# 安装依赖
sudo yum install -y cmake

# 下载最新版本的 GLFW
wget https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.zip

# 解压缩下载的文件
unzip glfw-3.3.8.zip
cd glfw-3.3.8

# 创建构建目录并使用 CMake 构建
mkdir build
cd build
cmake ..
make
sudo make install
```

5. 配置环境变量，将库路径添加到系统库路径:可以通过编辑 /etc/ld.so.conf.d/ 文件夹中的配置文件来添加这些路径：
```cpp
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/local-lib.conf'
sudo ldconfig
```

6. 测试程序
```cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);#### 环境配置
1. 更新系统，安装开发工具
```cpp
sudo yum update -y
sudo yum groupinstall -y "Development Tools"
```

2. 安装OpenGL开发库
```cpp
sudo yum install -y epel-release
sudo yum install -y mesa-libGL-devel mesa-libGLU-devel
```

3. 源码编译GLEW
```cpp
# 下载最新版本的 GLEW
wget http://downloads.sourceforge.net/project/glew/glew/2.2.0/glew-2.2.0.tgz

# 解压缩下载的文件
tar -xvf glew-2.2.0.tgz
cd glew-2.2.0

# 编译和安装 GLEW
make
sudo make install
```

4. 源码编译GLFW
```cpp
# 安装依赖
sudo yum install -y cmake

# 下载最新版本的 GLFW
wget https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.zip

# 解压缩下载的文件
unzip glfw-3.3.8.zip
cd glfw-3.3.8

# 创建构建目录并使用 CMake 构建
mkdir build
cd build
cmake ..
make
sudo make install
```

5. 配置环境变量，将库路径添加到系统库路径:可以通过编辑 /etc/ld.so.conf.d/ 文件夹中的配置文件来添加这些路径：
```cpp
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/local-lib.conf'
sudo ldconfig
```

6. 测试程序
```cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 这里可以添加 OpenGL 渲染代码

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
```

7. 常见的安装目录位置
```cpp
OpenGL (Mesa)：头文件在 /usr/include/GL，库文件在 /usr/lib64 或 /usr/lib。
GLEW：头文件在 /usr/local/include/GL（如果从源代码编译安装），库文件在 /usr/local/lib。
GLFW：头文件在 /usr/local/include/GLFW（如果从源代码编译安装），库文件在 /usr/local/lib。
```

8. 编译链接
```cpp
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
```

