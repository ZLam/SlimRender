#include "Render.h"

#include <iostream>
#include "App.h"

Render::Render(const uint32& InWidth, const uint32& InHeight) :
Width(InWidth),
Height(InHeight)
{
	ColorBuffer = new uint32[Width * Height];
	ColorBufferSize = Width * Height * sizeof(uint32);
}

Render::~Render()
{
	if (ColorBuffer)
	{
		delete[] ColorBuffer;
		ColorBuffer = nullptr;
	}
}

void Render::CleanColorBuffer()
{
	// std::memset(ColorBuffer, InColor.GetRGBA32(), ColorBufferSize);		//不可以这样用，memset实际是一个个字节那样写进去的，而不能四个四个字节那样写进去
	// std::fill(ColorBuffer, ColorBuffer + (Width * Height), Color::Red.GetRGBA32());
	std::memset(ColorBuffer, 0, ColorBufferSize);		//暂时默认强制设为黑色背景
}

void Render::DrawPixel(const uint32& InX, const uint32& InY, const Color& InColor)
{
	ColorBuffer[InY * Width + InX] = InColor.GetRGBA32();
}

void Render::DrawLine(uint32 InX1, uint32 InY1, uint32 InX2, uint32 InY2,
	const Color& InColor)
{
	if (InX1 == InX2 && InY1 == InY2)
	{
		DrawPixel(InX1, InY1, InColor);
	}
	else if (InX1 == InX2)
	{
		if (InY1 > InY2)
		{
			std::swap(InY1, InY2);
		}
		for (auto y = InY1; y <= InY2; y++)
		{
			DrawPixel(InX1, y, InColor);
		}
	}
	else if (InY1 == InY2)
	{
		if (InX1 > InX2)
		{
			std::swap(InX1, InX2);
		}
		for (auto x = InX1; x <= InX2; x++)
		{
			DrawPixel(x, InY1, InColor);
		}
	}
	else
	{
		bool bSteep = false;
		float dX = static_cast<float>(InX1) - static_cast<float>(InX2);
		float dY = static_cast<float>(InY1) - static_cast<float>(InY2);
		
		if (std::abs(dX) < std::abs(dY))
		{
			/**
			 * 这一步的作用是，因为当斜率大于1的线段直接用公式算出x，y渲染出来会由于斜率大所以点与点之间会有空洞。
			 * 但斜率小于1的线段就不会有这种问题
			 * 目前处理是，从（x1, y1）到（x2, y2）的线段转为从（y1，x1）到（y2，x2）的线段
			 * 转换前斜率k1：（y1 - y2）/（x1 - x2），转换后斜率k2（x1 - x2）/（y1 - y2）
			 * k1 = 1 / k2，画下图就知道2条线段基于y=x对称的
			 * 所以用转换后的线段公式算出的x，y要以（y，x）渲染
			 */
			std::swap(InX1, InY1);
			std::swap(InX2, InY2);
			bSteep = true;
		}

		if (InX1 > InX2)
		{
			/**
			 * 这一步的作用是，无论point1和point2传咩数据进来，都处理成point1靠左，point2靠右，从point1画向point2，这样方便循环处理而已
			 */
			std::swap(InX1, InX2);
			std::swap(InY1, InY2);
		}

		dX = static_cast<float>(InX1) - static_cast<float>(InX2);
		dY = static_cast<float>(InY1) - static_cast<float>(InY2);
		float k = dY / dX;
		// std::cout << k << std::endl;

		for (uint32 x = InX1; x <= InX2; x++)
		{
			uint32 y = (x - InX1) * k + InY1;
			// float t = (x - InX1) / (float)(InX2 - InX1);
			// uint32 y = InY1 * (1. - t) + InY2 * t;
			if (bSteep)
			{
				DrawPixel(y, x, InColor);
			}
			else
			{
				DrawPixel(x, y, InColor);
			}
		}
	}
}
