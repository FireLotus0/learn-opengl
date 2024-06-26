#include <iostream>
#include <string>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


const GLchar* vertexShaderSource =
"#version 330 core\n\
layout(location = 0) in vec3 position;\n\
layout(location = 1) in vec3 color;\n\
out vec3 ourColor;\n\
void main()\n\
{\n\
	gl_Position = vec4(position, 1.0f);\n\
	ourColor = color;\n\
}\n\0";
const GLchar* fragmentShaderSource =
"#version 330 core\n						\
	in vec3 ourColor;\n\
	out vec4 color;\n							\
	void main()\n								\
	{\n											\
	color = vec4(ourColor, 1.0f);\n		\
	}\n\0";

int main()
{
	//GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//顶点着色器
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//片元着色器
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//创建着色器程序
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//事件响应
	glfwSetKeyCallback(window, key_callback);


	GLfloat vertices[] = {
		// 顶点              //颜色
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};

	//创建顶点缓冲区对象
	GLuint VBO;
	glGenBuffers(1, &VBO);

	//创建顶点数组对象
	GLuint VAO;
	glGenVertexArrays(1, &VAO);


	// 1.t绑定顶点数据
	glBindVertexArray(VAO);
	// 2.绑定顶点缓冲区对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//将顶点数据传入缓冲区对象中（&传入缓冲区数据的类型&数据量大小以字节为单位&传入的数据&显卡管理传入数据的方式）
	/*
	*	GL_STATIC_DRAW: 这些数据基本上不会改变或者极少情况下会被改变。
		GL_DYNAMIC_DRAW: 这些数据可能会经常被改变。
		GL_STREAM_DRAW: 这些数据在每次绘制的时候都会被改变。
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//
	// 3.告知管线顶点数据的解析方式
	/*
	该属性在着色器程序中的属性索引。location 0
	该属性的分量个数（1-4）
	分量的数据类型
	是否规格化
	stride两个连续该属性之间的间隔
	该属性第一个分量距离数据起点的偏移量
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	//启用顶点属性数据0
	glEnableVertexAttribArray(0);
	//告知管线颜色数据的解析方式
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);//启用属性1.
	//4. Unbind the VAO解除VAO绑定
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		//事件处理
		glfwPollEvents();

		//清屏背景
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//渲染程序对象
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//交换前后缓存
		glfwSwapBuffers(window);
		glFlush();
	}
	glfwTerminate();
	cout << "Success!" << endl;
	system("pause");
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, 
	// closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}