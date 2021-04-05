#include "ShaderProgram.h"

ShaderProgram::~ShaderProgram()
{
	if (CurShader)
	{
		delete CurShader;
		CurShader = nullptr;
	}
	if (CurUniform)
	{
		delete CurUniform;
		CurUniform = nullptr;
	}
}

BlinnShaderProgram::BlinnShaderProgram()
{
	for (int32 i = 0; i < MAX_ATTRIBUTE_NUM; i++)
	{
		memset(CurAttributeArr[i], 0, sizeof(BlinnAttribute));
	}
	
	CurShader = new BlinnShader(this);
	CurUniform = new Uniform();
}
