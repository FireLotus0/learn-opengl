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

	//��������
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

	//������ɫ��
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
	//ƬԪ��ɫ��
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

	//������ɫ������
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

	//�¼���Ӧ
	glfwSetKeyCallback(window, key_callback);


	GLfloat vertices[] = {
		// ����              //��ɫ
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};

	//�������㻺��������
	GLuint VBO;
	glGenBuffers(1, &VBO);

	//���������������
	GLuint VAO;
	glGenVertexArrays(1, &VAO);


	// 1.t�󶨶�������
	glBindVertexArray(VAO);
	// 2.�󶨶��㻺��������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//���������ݴ��뻺���������У�&���뻺�������ݵ�����&��������С���ֽ�Ϊ��λ&���������&�Կ����������ݵķ�ʽ��
	/*
	*	GL_STATIC_DRAW: ��Щ���ݻ����ϲ���ı���߼�������»ᱻ�ı䡣
		GL_DYNAMIC_DRAW: ��Щ���ݿ��ܻᾭ�����ı䡣
		GL_STREAM_DRAW: ��Щ������ÿ�λ��Ƶ�ʱ�򶼻ᱻ�ı䡣
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//
	// 3.��֪���߶������ݵĽ�����ʽ
	/*
	����������ɫ�������е�����������location 0
	�����Եķ���������1-4��
	��������������
	�Ƿ���
	stride��������������֮��ļ��
	�����Ե�һ������������������ƫ����
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	//���ö�����������0
	glEnableVertexAttribArray(0);
	//��֪������ɫ���ݵĽ�����ʽ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);//��������1.
	//4. Unbind the VAO���VAO��
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		//�¼�����
		glfwPollEvents();

		//��������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//��Ⱦ�������
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//����ǰ�󻺴�
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