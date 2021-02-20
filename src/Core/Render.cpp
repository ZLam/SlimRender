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

/**
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void Render::DrawLine(int32 InX1, int32 InY1, int32 InX2, int32 InY2, const Color& InColor)
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
		for (auto Y = InY1; Y <= InY2; Y++)
		{
			DrawPixel(InX1, Y, InColor);
		}
	}
	else if (InY1 == InY2)
	{
		if (InX1 > InX2)
		{
			std::swap(InX1, InX2);
		}
		for (auto X = InX1; X <= InX2; X++)
		{
			DrawPixel(X, InY1, InColor);
		}
	}
	else
	{
		bool bSteep = false;
		
		if (std::abs(InX1 - InX2) < std::abs(InY1 - InY2))
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
		
		float DiffX = static_cast<float>(InX1 - InX2);
		float DiffY = static_cast<float>(InY1 - InY2);
		/**
		 * [2]，优化，根据斜率，因为处理过线段，斜率在(0-1]
		 * 所以实际上x+1并不一定y也会+1，也就是不用每次都要算y，y可能保持当前的值
		 */
		float K = std::abs(DiffY / DiffX);
		int32 Y = InY1;
		float SumK = 0;
		//
		//
		// [1]，直接用公式算出x，y（效率会比较低）
		// float k = dY / dX;
		//

		for (int32 X = InX1; X <= InX2; X++)
		{
			// [1]
			// int32 y = (x - InX1) * k + InY1;
			//
			
			if (bSteep)
			{
				DrawPixel(Y, X, InColor);
			}
			else
			{
				DrawPixel(X, Y, InColor);
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
			SumK += K;
			if (SumK > 0.5f)
			{
				SumK -= 1.0f;
				InY2 > InY1 ? Y++ : Y--;
			}
			//
		}
	}
}

/**
 * 旧式的渲染三角形方法
 * 主要就是以行扫描（scanline）的方式绘制
 * 把一个三角形打横切开上下2半，然后根据斜率一行一行填满一个三角形
 */
void Render::DrawTriangle_OldSchool(Vec2i V1, Vec2i V2, Vec2i V3, const Color& InColor)
{
	if ((V1.Y == V2.Y && V1.Y == V3.Y) || (V1.X == V2.X && V1.X == V3.X))
	{
		return;
	}
	
	if (V1.Y > V2.Y)
	{
		std::swap(V1, V2);
	}
	if (V2.Y > V3.Y)
	{
		std::swap(V2, V3);
	}
	if (V1.Y > V2.Y)
	{
		std::swap(V1, V2);
	}

	float CurX1 = 0.0f;
	float CurX2 = 0.0f;
	float K1 = 0.0f;
	float K2 = 0.0f;
	
	if (V2.Y - V1.Y == 0)
	{
		CurX1 = static_cast<float>(V3.X);
		CurX2 = static_cast<float>(V3.X);
		K1 = -static_cast<float>(V1.X - V3.X) / static_cast<float>(V1.Y - V3.Y);
		K2 = -static_cast<float>(V2.X - V3.X) / static_cast<float>(V2.Y - V3.Y);
		for (int32 CurY = V3.Y; CurY >= V2.Y; CurY--)
		{
			DrawLine(
				static_cast<int32>(std::round(CurX1)),
				CurY,
				static_cast<int32>(std::round(CurX2)),
				CurY,
				InColor
			);
			CurX1 += K1;
			CurX2 += K2;
		}
	}
	else if (V2.Y - V3.Y == 0)
	{
		CurX1 = static_cast<float>(V1.X);
		CurX2 = static_cast<float>(V1.X);
		K1 = static_cast<float>(V3.X - V1.X) / static_cast<float>(V3.Y - V1.Y);
		K2 = static_cast<float>(V2.X - V1.X) / static_cast<float>(V2.Y - V1.Y);
		for (int32 CurY = V1.Y; CurY <= V2.Y; CurY++)
		{
			DrawLine(
				static_cast<int32>(std::round(CurX1)),
				CurY,
				static_cast<int32>(std::round(CurX2)),
				CurY,
				InColor
			);
			CurX1 += K1;
			CurX2 += K2;
		}
	}
	else
	{
		CurX1 = static_cast<float>(V1.X);
		CurX2 = static_cast<float>(V1.X);
		K1 = static_cast<float>(V3.X - V1.X) / static_cast<float>(V3.Y - V1.Y);
		K2 = static_cast<float>(V2.X - V1.X) / static_cast<float>(V2.Y - V1.Y);

		for (int32 CurY = V1.Y; CurY <= V2.Y; CurY++)
		{
			DrawLine(
				static_cast<int32>(std::round(CurX1)),
				CurY,
				static_cast<int32>(std::round(CurX2)),
				CurY,
				InColor
			);
			CurX1 += K1;
			CurX2 += K2;
		}

		CurX1 = static_cast<float>(V3.X);
		CurX2 = static_cast<float>(V3.X);
		K1 = -static_cast<float>(V1.X - V3.X) / static_cast<float>(V1.Y - V3.Y);
		K2 = -static_cast<float>(V2.X - V3.X) / static_cast<float>(V2.Y - V3.Y);
		for (int32 CurY = V3.Y; CurY > V2.Y; CurY--)
		{
			DrawLine(
				static_cast<int32>(std::round(CurX1)),
				CurY,
				static_cast<int32>(std::round(CurX2)),
				CurY,
				InColor
			);
			CurX1 += K1;
			CurX2 += K2;
		}
	}
}

/**
 * 现代GPU渲染三角形的方式
 * 先求一个三角形的包围盒（bounding box），然后基于重心坐标的方法插值填满三角形区域
 */
void Render::DrawTriangle(const Vec2i& V1, const Vec2i& V2, const Vec2i& V3)
{
	if ((V1.Y == V2.Y && V1.Y == V3.Y) || (V1.X == V2.X && V1.X == V3.X))
	{
		return;
	}

	Vec2i BoxMin, BoxMax;
	GetTriangleAABB(V1, V2, V3, BoxMin, BoxMax);

	for (int32 Y = BoxMin.Y; Y <= BoxMax.Y; Y++)
	{
		for (int32 X = BoxMin.X; X <= BoxMax.X; X++)
		{
			Vec2i CurPoint(X, Y);
			Vec3f BarycentricCoord = GetBarycentric(V1, V2, V3, CurPoint);
			if (BarycentricCoord.X < 0 || BarycentricCoord.Y < 0 || BarycentricCoord.Z < 0)
			{
				continue;
			}
			Color TmpColor(BarycentricCoord.X, BarycentricCoord.Y, BarycentricCoord.Z);
			DrawPixel(X, Y, TmpColor);
		}
	}
}

void Render::GetTriangleAABB(const Vec2i& A, const Vec2i& B, const Vec2i& C, Vec2i& BoxMin, Vec2i& BoxMax)
{
	int32 minX = A.X, minY = A.Y, maxX = A.X, maxY = A.Y;
	if (B.X < minX)
		minX = B.X;
	if (B.Y < minY)
		minY = B.Y;
	if (B.X > maxX)
		maxX = B.X;
	if (B.Y > maxY)
		maxY = B.Y;
	if (C.X < minX)
		minX = C.X;
	if (C.Y < minY)
		minY = C.Y;
	if (C.X > maxX)
		maxX = C.X;
	if (C.Y > maxY)
		maxY = C.Y;
	BoxMin.X = minX;
	BoxMin.Y = minY;
	BoxMax.X = maxX;
	BoxMax.Y = maxY;
}

/**
 * 计算重心坐标
 * 目前只知道用面积比例怎么求，下面的是一个优化版本，但不太理解原理。。
 * https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
 */
Vec3f Render::GetBarycentric(const Vec2i& A, const Vec2i& B, const Vec2i& C, const Vec2i& P)
{
	Vec2i V0 = B - A, V1 = C - A, V2 = P - A;
	float D00 = Vec2i::DotProduct(V0, V0);
	float D01 = Vec2i::DotProduct(V0, V1);
	float D11 = Vec2i::DotProduct(V1, V1);
	float D20 = Vec2i::DotProduct(V2, V0);
	float D21 = Vec2i::DotProduct(V2, V1);
	float Denom = D00 * D11 - D01 * D01;
	float V = (D11 * D20 - D01 * D21) / Denom;
	float W = (D00 * D21 - D01 * D20) / Denom;
	float U = 1.0f - V - W;
	return Vec3f(U, V, W);
}
