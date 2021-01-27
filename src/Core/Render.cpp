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
		/**
		 * [2]，优化，根据斜率，因为处理过线段，斜率在(0-1]
		 * 所以实际上x+1并不一定y也会+1，也就是不用每次都要算y，y可能保持当前的值
		 */
		float k = std::abs(dY / dX);
		uint32 y = InY1;
		float sumK = 0;
		//
		//
		// [1]，直接用公式算出x，y（效率会比较低）
		// float k = dY / dX;
		//

		for (uint32 x = InX1; x <= InX2; x++)
		{
			// [1]
			// uint32 y = (x - InX1) * k + InY1;
			//
			
			if (bSteep)
			{
				DrawPixel(y, x, InColor);
			}
			else
			{
				DrawPixel(x, y, InColor);
			}

			/**
			 * [2]，这里的处理其实就是做了优化，不用每次都算y
			 * 那为什么是 sumK > 0.5f 呢？为什么是 sumK -= 1.0f 呢？
			 * 这些问题用y=x/6的线段模拟下会容易理解些
			 * 首先x每增加一格，sumK都会累加斜率k，而斜率范围在(0-1]，所以其实x每增加一格，
			 * sumK就累计倾斜了多少，但又不一定倾斜到y要增加一格的层度
			 * 第一个问题，为什么是 sumK > 0.5f
			 * 一般会想不应该sumK累计倾斜到1.0f，y就增加一格吗，
			 * 可以是可以但不好看。比如这里y=x/6，用0.5f判断，y增加一格发生在x==3的时候。
			 * 用1.0f判断，y增加一格要在x==6的时候。
			 * 那么如果线条越倾斜趋向于平，前面就会有一大段平的线条，要到靠后点y才会增加一格，线条倾斜出来的样子就不好看。
			 * 而0.5f判断就会在超过一半的时候y就增加一格，前面平的线段跟后面平的线段看上去一样的，这样就比较好看。
			 * 第二个问题，为什么是 sumK -= 1.0f
			 * 前面累计用0.5f判断，这里为什么不是sumK -= 0.5f呢。
			 * 分别用sumK -= 1.0f和sumK -= 0.5f计算，x从0到6的y值就会理解了。
			 * 用0.5f的话x=6时y=2，但实际y不可能增加了2格，y应该还是1才对，所以明显错了
			 * 用1.0f的话，整条线条是正常的倾斜的。那为什么是1.0f呢。
			 * 可以理解成，因为sumK累计够0.5f以上y就会增加一格，但其实是因为视觉好看才会在累计够一半y就增加一格的，
			 * 实际y增加一格的地方确实应该在sumK累计到1的时候。既然y提前加了一格，那么y应该保持当前值到实际增加一格的时候，
			 * 所以sumK -= 1.0f，就意味sumK离1.0f还有多少，需要补回来的那段就是y保持当前值的情况，
			 * 当sumK把那段补回后，其实就又重新开始累计。
			 */
			sumK += k;
			if (sumK > 0.5f)
			{
				sumK -= 1.0f;
				InY2 > InY1 ? y++ : y--;
			}
			//
		}
	}
}
