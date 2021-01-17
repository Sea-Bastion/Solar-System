#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include<ctime>
#include<thread>
#include<chrono>

#include<glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.inl>

#include<SOIL2.h>

struct Vertex {
	glm::vec3 position;
//	glm::vec3 color;
	glm::vec2 texcoord;
};