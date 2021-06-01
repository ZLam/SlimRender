#include "Texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "Math.h"

Texture::Texture(const std::string& InFilePath)
{
	LoadFromFile(InFilePath);
}

bool Texture::LoadFromFile(const std::string& InFilePath)
{
	uint8* ImgData = stbi_load(InFilePath.c_str(), &Width, &Height, &NumChannels, 0);
	if (!ImgData)
	{
		std::cout << "load img fail!" << "(" << InFilePath << ")" << std::endl;
		return false;
	}
    Data.reserve(Width * Height);
    //for (int Row = 0; Row < Height; Row++)
    for (int Row = Height - 1; Row >= 0; Row--)     // (0, 0) start in left down
	{
		for (int Col = 0; Col < Width; Col++)
		{
			int Index = (Row * Width + Col) * NumChannels;
			uint8 Red = 255, Green = 255, Blue = 255, Alpha = 255;
			if (NumChannels == 1)
			{
				Red = Green = Blue = ImgData[Index];
			}
			else if (NumChannels == 3)
			{
				Red = ImgData[Index];
				Green = ImgData[Index + 1];
				Blue = ImgData[Index + 2];
			}
			else if (NumChannels == 4)
			{
				Red = ImgData[Index];
				Green = ImgData[Index + 1];
				Blue = ImgData[Index + 2];
				Alpha = ImgData[Index + 3];
			}
			Data.emplace_back(Red, Green, Blue, Alpha);
		}
	}
	std::cout << "load img done." << "(" << InFilePath << ", " << Width << ", " << Height << ", " << NumChannels << ")" << std::endl;
	stbi_image_free(ImgData);
	return true;
}

Color Texture::Sample(const Vec2f& InUV)
{
	// clamp
	// float U = InUV.X < 0.0f ? 0.0f : (InUV.X > 1.0f ? 1.0f : InUV.X);
	// float V = InUV.Y < 0.0f ? 0.0f : (InUV.Y > 1.0f ? 1.0f : InUV.Y);
	//
	
	// repeat
	float U = InUV.X - std::floor(InUV.X);
	float V = InUV.Y - std::floor(InUV.Y);
	//

	int Col = (int)((Width - 1) * U);
	int Row = (int)((Height - 1) * V);
	int Index = Row * Width + Col;
	
	return Data[Index];
}
