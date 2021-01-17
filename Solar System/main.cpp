#include "libs.h"

const Vertex Vertices[] = {
	glm::vec3(-50.f, 50.f, 0.0f),		glm::vec2(0.f, 1.f),
	glm::vec3(-50.f,-50.f, 0.0f),		glm::vec2(0.f, 0.f),
	glm::vec3( 50.f,-50.f, 0.0f),		glm::vec2(1.f, 0.f),
	glm::vec3( 50.f, 50.f, 0.0f),		glm::vec2(1.f, 1.f)
};
unsigned VertexCount = sizeof(Vertices) / sizeof(Vertex);

GLuint Indices[] = {
	0, 1, 2, 0, 2, 3
};
unsigned IndiceCount = sizeof(Indices) / sizeof(GLuint);

const int DELTA = 1 / 60;

void frame_buffer_resize_callback(GLFWwindow* window, int framebufferWidth, int framebufferHight)
{
	glViewport(0, 0, framebufferWidth, framebufferHight);

	//set update to shader
	float screen_size[] = { framebufferWidth, framebufferHight };
	glUniform2fv(4, 1, screen_size);

}

bool loadShaders(GLint &program)
{
	//function vars-------------------------
	bool returnVal = true;
	char infoLog[512];
	GLint success;

	std::string tmp = "";
	std::string src = "";

	std::ifstream in_file;


	//vertex shader--------------------------
	//read shader code
	in_file.open("Shaders/VertexShader.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, tmp))
			src += tmp + "\n";
	}
	else
	{
		std::cout << "ERROR FAILED TO LOAD VERTEX SHADER" << std::endl;
		returnVal = false;
	}

	in_file.close();

	//load in shader
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* VertSrc = src.c_str();
	glShaderSource(VertexShader, 1, &VertSrc, NULL);
	glCompileShader(VertexShader);

	//check for compile errors
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
		std::cout << "FAILED TO COMPILE VERTEX SHADER:" << std::endl;
		std::cout << infoLog << std::endl;
		returnVal = false;
	}



	//fragment shader------------------------------
	tmp = "";
	src = "";


	in_file.open("Shaders/FragmentShader.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, tmp))
			src += tmp + "\n";
	}
	else
	{
		std::cout << "ERROR FAILED TO LOAD FRAGMENT SHADER" << std::endl;
		returnVal = false;
	}

	in_file.close();

	//load in shader
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* FragSrc = src.c_str();
	glShaderSource(FragmentShader, 1, &FragSrc, NULL);
	glCompileShader(FragmentShader);

	//check for compile errors
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
		std::cout << "FAILED TO COMPILE FRAGMENT SHADER:" << std::endl;
		std::cout << infoLog << std::endl;
		returnVal = false;
	}


	//create program-------------------------
	program = glCreateProgram();
	
	glAttachShader(program, VertexShader);
	glAttachShader(program, FragmentShader);
	
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "FAILED TO LINK SHADERS TO PROGRAM" << std::endl;
		std::cout << infoLog << std::endl;
		returnVal = false;
	}

	//clean up------------------------------
	glUseProgram(0);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);


	return returnVal;
}

void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() 
{
	//--------------------PROGRAM INIT---------------------

	//init glft
	glfwInit();

	//make window
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HIGHT = 480;
	//int framebufferWidth = 0;
	//int framebufferHight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HIGHT, "Solar System", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, frame_buffer_resize_callback);

	//make context
	glfwMakeContextCurrent(window);


	//init glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) 
	{
		std::cout << "FAILED TO INIT GLEW" << std::endl;
		glfwTerminate();
		return 1;
	}

	//enable options
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//normal
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//------------------SHADERS-------------------------
	GLint core_program;
	if (!loadShaders(core_program))
	{
		std::cout << "FAILED TO LOAD IN SHADERS" << std::endl;
		glfwTerminate();
		return 1;
	}


	//-----------------VERTICIES------------------------
	//make VAO
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//make VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	//make EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);


	//describe data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(1);

	//unbind
	glBindVertexArray(0);


	//----------------------TEXTURES----------------------------
	//load in texture
	int image_width = 0;
	int image_height = 0;
	unsigned char* image = SOIL_load_image("Textures/Sun.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

	GLuint texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
	}

	//clean up
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);


	//-------------free--------------
	glm::vec4 translation = glm::vec4(0.0f);
	glm::mat4 rotation = glm::rotate(glm::mat4(1.f), 0.f, glm::vec3(0.0f, 0.0f, 1.0f));


	//--------------------MAIN LOOP------------------------
	bool loop = true;
	while (!glfwWindowShouldClose(window))
	{
		int endTime = std::clock() + DELTA;


		//UPDATE INPUT-----------
		glfwPollEvents();
		updateInput(window);


		//------------------------------UPDATE OBJ-----------------------------
		if (false) {
			//do things later
		}


		//DRAW-------------------
		//clear buffers
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//enable shader
		glUseProgram(core_program);

		//load up textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);


		//bind draw data
		glBindVertexArray(VAO);

		//draw
		glUniform3fv(2, 1, glm::value_ptr(translation));
		glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(rotation));
		
		//glDrawArrays(GL_TRIANGLES, 0, VertexCount);
		glDrawElements(GL_TRIANGLES, IndiceCount, GL_UNSIGNED_INT, 0);

		//end draw
		glfwSwapBuffers(window);
		glFlush();

	}
	
	//cleanup
	glfwDestroyWindow(window);
	glfwTerminate();
	glDeleteProgram(core_program);


	return 0;
}