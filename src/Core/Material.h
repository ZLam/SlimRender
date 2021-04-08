#pragma once

#include "Texture.h"

struct Material
{
	virtual ~Material() = default;
};

struct BlinnMaterial : Material
{
	virtual ~BlinnMaterial()
	{
		if (Tex_Diffuse)
		{
			delete Tex_Diffuse;
			Tex_Diffuse = nullptr;
		}
	}
	
	Texture* Tex_Diffuse = nullptr;
};
