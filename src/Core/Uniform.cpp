#include "Uniform.h"
#include "Material.h"

Uniform::~Uniform()
{
	if (CurMaterial)
	{
		delete CurMaterial;
		CurMaterial = nullptr;
	}
}

BlinnUniform::BlinnUniform()
{
	CurMaterial = new BlinnMaterial();
}
