#pragma once

#include "Matrix.h"

struct Uniform
{
	
};

struct BlinnUniform : Uniform
{
	Matrix4 MatModel;
	Matrix4 MatCameraVP;
};
