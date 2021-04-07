#pragma once

#include "Vector.h"
#include "Vertex.h"
#include "Color.h"

class ShaderProgram;

class Shader
{
protected:
	ShaderProgram* Program;
	
public:
	Shader(ShaderProgram* InProgram);
	virtual ~Shader() = default;
	
	virtual void VertexShader(const Vertex& InVertex) = 0;
	virtual Color FragmentShader() = 0;
};

class BlinnShader : public Shader
{
public:
	BlinnShader(ShaderProgram* InProgram);
	virtual ~BlinnShader() = default;

	void VertexShader(const Vertex& InVertex) override;
	Color FragmentShader() override;
};
