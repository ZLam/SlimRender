#pragma once

#include "Shader.h"
#include "Uniform.h"
#include "Attribute.h"

constexpr int MAX_ATTRIBUTE_NUM = 10;

class ShaderProgram
{
public:
	ShaderProgram() = default;
	virtual ~ShaderProgram();
	
	Shader* CurShader = nullptr;
	Uniform* CurUniform = nullptr;
	Attribute* CurAttributeArr[MAX_ATTRIBUTE_NUM]{ nullptr };		// ��ʱĬ��10 @TODO
	int32 CurAttribNum = 0;
};

class BlinnShaderProgram : public ShaderProgram
{
public:
	BlinnShaderProgram();
	virtual ~BlinnShaderProgram() = default;
};
