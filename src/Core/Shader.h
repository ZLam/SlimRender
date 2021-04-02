#pragma once

class Shader
{
public:
	virtual ~Shader() = default;
	virtual void VertexShader() = 0;
	virtual void FragmentShader() = 0;
};
