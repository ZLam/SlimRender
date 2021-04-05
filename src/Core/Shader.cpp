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

Vec4f BlinnShader::VertexShader(const Vertex& InVertex)
{
	BlinnUniform* CurUniform = (BlinnUniform*)Program->CurUniform;
	BlinnAttribute* CurAttribute = (BlinnAttribute*)(Program->CurAttributeArr[Program->CurAttribNum++]);
	Vec4f WorldPos = CurUniform->MatModel * InVertex.Position;
	CurAttribute->Colour = InVertex.Colour;
	return CurUniform->MatCameraVP * WorldPos;
}

Color BlinnShader::FragmentShader()
{
	return Color::White;
}
