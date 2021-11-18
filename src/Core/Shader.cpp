#include "Shader.h"
#include "Math.h"
#include "Vector.h"
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
	CurAttribute->Normal = (CurUniform->MatNormal * InVertex.Normal).GetNormal();
	CurAttribute->WorldPos = WorldPos;
	CurAttribute->Clip_InCoord = CurUniform->MatCameraVP * WorldPos;

	CurAttribute->Clip_OutCoord = CurAttribute->Clip_InCoord;		//@TODO handle clip
}

Color BlinnShader::FragmentShader()
{
    BlinnUniform* CurUniform = (BlinnUniform*)Program->CurUniform;
	BlinnAttribute* InterpAttrib = (BlinnAttribute*)Program->CurInterpAttrib;
    BlinnMaterial* MyMaterial = (BlinnMaterial*)CurUniform->CurMaterial;

	// 显示diffuse texture
    // Color OutColor = MyMaterial->Tex_Diffuse->Sample(InterpAttrib->UV) * InterpAttrib->Colour;
	//

	// 显示normal
	// Color OutColor = Color((InterpAttrib->Normal.X + 1.0f) / 2.0f, (InterpAttrib->Normal.Y + 1.0f) / 2.0f, (InterpAttrib->Normal.Z + 1.0f) / 2.0f);
	//

	// 显示光照
	Vec3f Result;
//	Vec3f TexDiffuse(1.0f, 0.5f, 0.0f);
    Color TexDiffuseColor = MyMaterial->Tex_Diffuse->Sample(InterpAttrib->UV);
    Vec3f TexDiffuse(TexDiffuseColor.R, TexDiffuseColor.G, TexDiffuseColor.B);
	Vec3f CameraDir = (CurUniform->CameraPos - InterpAttrib->WorldPos).GetNormal();
	for (auto& CurLight : CurUniform->LightArr)
	{
		Vec3f LightDir = (CurLight.Position - InterpAttrib->WorldPos).GetNormal();
		
		// ambient
		Vec3f CurAmbient = TexDiffuse * CurLight.Ambient;
	
		// diffuse
		float fReceive = std::max(Vec3f::DotProduct(InterpAttrib->Normal, LightDir), 0.0f);
		Vec3f CurDiffuse = TexDiffuse * fReceive * CurLight.Diffuse;
	
		// specular
		Vec3f HalfDir = (LightDir + CameraDir).GetNormal();
		float Spec = std::pow(std::max(Vec3f::DotProduct(InterpAttrib->Normal, HalfDir), 0.0f), 64.0f);
		Vec3f CurSpecular = TexDiffuse * Spec * CurLight.Specular;
		
	
		Result += CurAmbient + CurDiffuse + CurSpecular;
		Result.X *= InterpAttrib->Colour.R;
		Result.Y *= InterpAttrib->Colour.G;
		Result.Z *= InterpAttrib->Colour.B;
	}
	Color OutColor(Result.X, Result.Y, Result.Z, 1.0f);
	//
	
    
	return OutColor;
}
