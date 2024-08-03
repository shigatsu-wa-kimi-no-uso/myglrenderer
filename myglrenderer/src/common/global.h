#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "defs.h"
#include <memory>
#include <map>
#include <unordered_map>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;
using glm::mat3;
using glm::mat4;
using glm::translate;
using glm::rotate;
using glm::perspective;
using glm::radians;
using glm::lookAt;
using glm::normalize;
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::vector;
using std::pair;
template<class K, class T, class Pr = std::less<K>>
using sortedmap = std::map<K,T,Pr>;
template<typename K,typename V>
using hashmap = std::unordered_map<K,V>;

enum class GLSLType {
	INT = GL_INT,
	FLOAT = GL_FLOAT,
	VEC2 = GL_FLOAT_VEC2,
	VEC3 = GL_FLOAT_VEC3,
	VEC4 = GL_FLOAT_VEC4,
	IVEC2 = GL_INT_VEC2,
	IVEC3 = GL_INT_VEC3,
	IVEC4 = GL_INT_VEC4,
	MAT3 = GL_FLOAT_MAT3,
	MAT4 = GL_FLOAT_MAT4
};


#endif // !GLOBAL_H