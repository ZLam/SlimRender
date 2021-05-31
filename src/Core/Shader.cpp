#include "Shader.h"
#include "ShaderProgram.h"
#include "Attribute.h"

Shader::Shader(ShaderProgram* InProgram) :
Program(InProgram)
{
	
}

BlinnShader::BlinnShader(ShaderProgram* InProgram) :
Shader(InProgram)
{
	
}

void BlinnShader::VertexShader(const Vertex& InVertex)
{
	BlinnUniform* CurUniform = (BlinnUniform*)Program->CurUniform;
	BlinnAttribute* CurAttribute = (BlinnAttribute*)(Program->CurAttribArr[Program->CurAttribNum++]);
	Vec4f WorldPos = CurUniform->MatModel * InVertex.Position;
	CurAttribute->Colour = InVertex.Colour;
	CurAttribute->UV = InVertex.UV;
	CurAttribute->Clip_InCoord = CurUniform->MatCameraVP * WorldPos;

	CurAttribute->Clip_OutCoord = CurAttribute->Clip_InCoord;		//@TODO
}

Color BlinnShader::FragmentShader()
{
    BlinnUniform* CurUniform = (BlinnUniform*)Program->CurUniform;
	BlinnAttribute* InterpAttrib = (BlinnAttribute*)Program->CurInterpAttrib;
    BlinnMaterial* MyMaterial = (BlinnMaterial*)CurUniform->CurMaterial;
    Color OutColor = MyMaterial->Tex_Diffuse->Sample(InterpAttrib->UV) * InterpAttrib->Colour;
    
	return OutColor;
}
