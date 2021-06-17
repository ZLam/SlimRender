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

	/**
	 * 首先要理解点解三维空间下顶点的属性直接在屏幕空间下线性插值系唔啱嘅
	 * 然后尝试理解和推导出，点解顶点属性除以W可以在屏幕空间下线性插值
	 * 上一步操作完后，再乘以W恢复出来的属性就是正确透视投影下的属性
	 * 一句话概括就是，三维空间的平面上本来线性的东西投影到二维空间下就不再是线性的了
	 */
	virtual void HandleInterpAttrib(Attribute* InAttribArr[3], float RecipW[3], const float& InAlpha, const float& InBeta, const float& InGamma) = 0;
	
	Shader* CurShader = nullptr;
	Uniform* CurUniform = nullptr;
	std::vector<Attribute*> CurAttribArr{ MAX_ATTRIBUTE_NUM, nullptr };		// 暂时默认10 @TODO handle clip
	int32 CurAttribNum = 0;
	Attribute* CurInterpAttrib = nullptr;
};

class BlinnShaderProgram : public ShaderProgram
{
public:
	BlinnShaderProgram();
	virtual ~BlinnShaderProgram() = default;

	void HandleInterpAttrib(Attribute* InAttribArr[3], float RecipW[3], const float& InAlpha, const float& InBeta, const float& InGamma) override;
};
