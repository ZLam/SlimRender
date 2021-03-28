#pragma once

#include <string>
#include <vector>

#include "Vector.h"
#include "Color.h"

class Texture
{
private:
	int32 Width = 0;
	int32 Height = 0;
	int32 NumChannels = 0;
	std::vector<Color> Data;
	
public:
	Texture(const std::string& InFilePath);

	bool LoadFromFile(const std::string& InFilePath);

	Color Sample(const Vec2f& InUV);
    
    int32 GetWidth() const
    {
        return Width;
    }
    
    int32 GetHeight() const
    {
        return Height;
    }
};
