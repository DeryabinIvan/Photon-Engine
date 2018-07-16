// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef PHOTONENGINE_EXPORTS
#define PHOTONENGINE_API __declspec(dllexport)
#else
#define PHOTONENGINE_API __declspec(dllimport)
#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// TODO: reference additional headers your program requires here
//OpenGL
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

//matrixes, transformations...
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

//image loading
#include "SOIL/SOIL.h"

//models
#include "assimp/Importer.hpp"
