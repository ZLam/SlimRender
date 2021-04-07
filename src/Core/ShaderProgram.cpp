#include "ShaderProgram.h"

ShaderProgram::~ShaderProgram()
{
	if (CurShader)
	{
		delete CurShader;
		CurShader = nullptr;
	}
	if (CurInterpAttrib)
	{
		delete CurInterpAttrib;
		CurInterpAttrib = nullptr;
	}
	if (CurUniform)
	{
		delete CurUniform;
		CurUniform = nullptr;
	}
	for (auto Value : CurAttribArr)
	{
		if (Value)
		{
			delete Value;
			Value = nullptr;
		}
	}
	CurAttribArr.clear();
}

void ShaderProgram::Resume()
{
	CurAttribNum = 0;
}

BlinnShaderProgram::BlinnShaderProgram()
{
	for (int32 i = 0; i < MAX_ATTRIBUTE_NUM; i++)
	{
		CurAttribArr[i] = new BlinnAttribute();
	}
	CurUniform = new BlinnUniform();
	CurInterpAttrib = new BlinnAttribute();
	CurShader = new BlinnShader(this);
}

void BlinnShaderProgram::HandleInterpAttrib(Attribute* InAttribArr[3], const float& InAlpha, const float& InBeta, const float& InGamma)
{
	BlinnAttribute* InterpAttrib = (BlinnAttribute*)CurInterpAttrib;
	BlinnAttribute* Attrib00 = (BlinnAttribute*)InAttribArr[0];
	BlinnAttribute* Attrib01 = (BlinnAttribute*)InAttribArr[1];
	BlinnAttribute* Attrib02 = (BlinnAttribute*)InAttribArr[2];
	InterpAttrib->Colour = Attrib00->Colour * InAlpha + Attrib01->Colour * InBeta + Attrib02->Colour * InGamma;
}
