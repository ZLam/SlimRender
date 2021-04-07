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
	CurAttribute->Clip_InCoord = CurUniform->MatCameraVP * WorldPos;

	CurAttribute->Clip_OutCoord = CurAttribute->Clip_InCoord;		//@TODO
}

Color BlinnShader::FragmentShader()
{
	BlinnAttribute* InterpAttrib = (BlinnAttribute*)Program->CurInterpAttrib;
	return InterpAttrib->Colour;
}
