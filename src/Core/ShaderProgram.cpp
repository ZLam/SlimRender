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

void BlinnShaderProgram::HandleInterpAttrib(Attribute* InAttribArr[3], float RecipW[3], const float& InAlpha, const float& InBeta, const float& InGamma)
{
	BlinnAttribute* InterpAttrib = (BlinnAttribute*)CurInterpAttrib;
	BlinnAttribute* Attrib00 = (BlinnAttribute*)InAttribArr[0];
	BlinnAttribute* Attrib01 = (BlinnAttribute*)InAttribArr[1];
	BlinnAttribute* Attrib02 = (BlinnAttribute*)InAttribArr[2];
	BlinnUniform* MyUniform = (BlinnUniform*)CurUniform;
	BlinnMaterial* MyMaterial = (BlinnMaterial*)MyUniform->CurMaterial;
	float Weight00 = RecipW[0] * InAlpha;
	float Weight01 = RecipW[1] * InBeta;
	float Weight02 = RecipW[2] * InGamma;
	float Normalizer = 1.0f / (Weight00 + Weight01 + Weight02);
	
    // 透视正确
    InterpAttrib->Colour = (Attrib00->Colour * Weight00 + Attrib01->Colour * Weight01 + Attrib02->Colour * Weight02) * Normalizer;
    InterpAttrib->UV = (Attrib00->UV * Weight00 + Attrib01->UV * Weight01 + Attrib02->UV * Weight02) * Normalizer;
	InterpAttrib->Normal = (Attrib00->Normal * Weight00 + Attrib01->Normal * Weight01 + Attrib02->Normal * Weight02) * Normalizer;
	InterpAttrib->WorldPos = (Attrib00->WorldPos * Weight00 + Attrib01->WorldPos * Weight01 + Attrib02->WorldPos * Weight02) * Normalizer;
	// InterpAttrib->Colour = MyMaterial->Tex_Diffuse->Sample(InterpAttrib->UV);

    // 透视错误
	// InterpAttrib->Colour = Attrib00->Colour * InAlpha + Attrib01->Colour * InBeta + Attrib02->Colour * InGamma;
	// InterpAttrib->UV = Attrib00->UV * InAlpha + Attrib01->UV * InBeta + Attrib02->UV * InGamma;
	// InterpAttrib->Colour = MyMaterial->Tex_Diffuse->Sample(InterpAttrib->UV);
}
