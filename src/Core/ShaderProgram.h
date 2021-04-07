#pragma once

#include <vector>
#include "Shader.h"
#include "Uniform.h"
#include "Attribute.h"

constexpr int MAX_ATTRIBUTE_NUM = 10;

class ShaderProgram
{
public:
	ShaderProgram() = default;
	virtual ~ShaderProgram();

	void Resume();

	virtual void HandleInterpAttrib(Attribute* InAttribArr[3], const float& InAlpha, const float& InBeta, const float& InGamma) = 0;
	
	Shader* CurShader = nullptr;
	Uniform* CurUniform = nullptr;
	std::vector<Attribute*> CurAttribArr{ MAX_ATTRIBUTE_NUM, nullptr };		// 暂时默认10 @TODO
	int32 CurAttribNum = 0;
	Attribute* CurInterpAttrib = nullptr;
};

class BlinnShaderProgram : public ShaderProgram
{
public:
	BlinnShaderProgram();
	virtual ~BlinnShaderProgram() = default;

	void HandleInterpAttrib(Attribute* InAttribArr[3], const float& InAlpha, const float& InBeta, const float& InGamma) override;
};
