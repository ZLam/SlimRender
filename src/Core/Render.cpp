#include "Render.h"

#include <iostream>
#include "App.h"
#include "Math.h"

Render::Render(const int32& InWidth, const int32& InHeight) :
Width(InWidth),
Height(InHeight)
{
	ColorBuffer = new uint32[Width * Height];
	ColorBufferSize = Width * Height * sizeof(uint32);
	DepthBuffer = new float[Width * Height];
	CurViewport = new Viewport(Width, Height);
}

Render::~Render()
{
	if (ColorBuffer)
	{
		delete[] ColorBuffer;
		ColorBuffer = nullptr;
	}
	if (DepthBuffer)
	{
		delete[] DepthBuffer;
		DepthBuffer = nullptr;
	}
	if (CurViewport)
	{
		delete CurViewport;
		CurViewport = nullptr;
	}
}

void Render::CleanColorBuffer()
{
	// std::memset(ColorBuffer, InColor.GetRGBA32(), ColorBufferSize);		//不可以这样用，memset实际是一个个字节那样写进去的，而不能四个四个字节那样写进去
	// std::fill(ColorBuffer, ColorBuffer + (Width * Height), Color::Red.GetRGBA32());
	std::memset(ColorBuffer, 0, ColorBufferSize);		//暂时默认强制设为黑色背景
}

void Render::CleanDepthBuffer()
{
	std::fill(DepthBuffer, DepthBuffer + Width * Height, std::numeric_limits<float>::infinity());
}

void Render::DrawPixel(const int32& InX, const int32& InY, const Color& InColor)
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
void Render::DrawTriangle(Vertex** VertexArr, ShaderProgram* InShaderProgram)
{
	InShaderProgram->Resume();
	
	// vertex shader
	for (int32 i = 0; i < 3; i++)
	{
		InShaderProgram->CurShader->VertexShader((*VertexArr)[i]);
	}
	
	// clipping @TODO

	// assembly
	int32 CurAttribNum = InShaderProgram->CurAttribNum;
	auto& CurAttribArr = InShaderProgram->CurAttribArr;
	for (int32 i = 0; i < CurAttribNum - 2; i++)
	{
		Attribute* TriangleAttribArr[3];
		Vec4f NDC_Coord[3];
		Vec4f Screen_Coord[3];
		float RecipW[3];
		TriangleAttribArr[0] = CurAttribArr[i];
		TriangleAttribArr[1] = CurAttribArr[i + 1];
		TriangleAttribArr[2] = CurAttribArr[i + 2];

		// perspective division
		for (int32 j = 0; j < 3; j++)
		{
			NDC_Coord[j] = TriangleAttribArr[j]->Clip_OutCoord / TriangleAttribArr[j]->Clip_OutCoord.W;
		}
		
		// culling
		if (IsCull(NDC_Coord))
		{
			return;
		}

		// reciprocals of w
		for (int32 j = 0; j < 3; j++)
		{
			RecipW[j] = 1.0f / TriangleAttribArr[j]->Clip_OutCoord.W;
		}

		// viewport
		for (int32 j = 0; j < 3; j++)
		{
			Screen_Coord[j] = CurViewport->GetViewportMat() * NDC_Coord[j];
		}
        
        if (bWireframeMode)
        {
            // wireframe
            for (int32 j = 0; j < 3; j++)
            {
                int32 Next = (j + 1) % 3;
                DrawLine(Screen_Coord[j].X, Screen_Coord[j].Y, Screen_Coord[Next].X, Screen_Coord[Next].Y);
            }
        }
        else
        {
            // raster
            BoundingBox TriangleBBox;
            GetTriangleAABB(Screen_Coord[0], Screen_Coord[1], Screen_Coord[2], TriangleBBox);
            int32 PixelMinX = std::max((int32)std::floor(TriangleBBox.MinX), 0);
            int32 PixelMinY = std::max((int32)std::floor(TriangleBBox.MinY), 0);
            int32 PixelMaxX = std::min((int32)std::ceil(TriangleBBox.MaxX), Width - 1);
            int32 PixelMaxY = std::min((int32)std::ceil(TriangleBBox.MaxY), Height - 1);
            for (int32 CurY = PixelMinY; CurY <= PixelMaxY; CurY++)
            {
                for (int32 CurX = PixelMinX; CurX <= PixelMaxX; CurX++)
                {
                    float Alpha, Beta, Gamma;
                    GetBarycentric2D(		// 计算重心坐标
                        Screen_Coord[0].X, Screen_Coord[0].Y,
                        Screen_Coord[1].X, Screen_Coord[1].Y,
                        Screen_Coord[2].X, Screen_Coord[2].Y,
                        CurX + 0.5f, CurY + 0.5f,
                        Alpha, Beta, Gamma
                    );
                    if (Alpha > -EPSILON_EX && Beta > -EPSILON_EX && Gamma > -EPSILON_EX)		// 判断是否在三角形内
                    {
                        float Depth = Screen_Coord[0].Z * Alpha + Screen_Coord[1].Z * Beta + Screen_Coord[2].Z * Gamma;		// z-buffer
                        int32 Index = CurY * Width + CurX;
                        if (Depth < DepthBuffer[Index])
                        {
                            // perspective correct interpolation
                            InShaderProgram->HandleInterpAttrib(TriangleAttribArr, RecipW, Alpha, Beta, Gamma);

                            // fragment shader
                            Color OutColor = InShaderProgram->CurShader->FragmentShader();

                            ColorBuffer[Index] = OutColor.GetRGBA32();
                            DepthBuffer[Index] = Depth;
                        }
                    }
                }
            }
        }
	}
}

void Render::GetTriangleAABB(const Vec4f& A, const Vec4f& B, const Vec4f& C, BoundingBox& InBoundingBox)
{
	InBoundingBox.MinX = std::min(A.X, std::min(B.X, C.X));
	InBoundingBox.MinY = std::min(A.Y, std::min(B.Y, C.Y));
	InBoundingBox.MaxX = std::max(A.X, std::max(B.X, C.X));
	InBoundingBox.MaxY = std::max(A.Y, std::max(B.Y, C.Y));
}

/**
 * 计算重心坐标
 * 目前只知道用面积比例怎么求，下面的是一个优化版本，但不太理解原理。。
 * https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
 */
Vec3f Render::GetBarycentric2D(const Vec2f& A, const Vec2f& B, const Vec2f& C, const Vec2f& P)
{
	Vec2f V0 = B - A, V1 = C - A, V2 = P - A;
	float D00 = Vec2f::DotProduct(V0, V0);
	float D01 = Vec2f::DotProduct(V0, V1);
	float D11 = Vec2f::DotProduct(V1, V1);
	float D20 = Vec2f::DotProduct(V2, V0);
	float D21 = Vec2f::DotProduct(V2, V1);
	float Denom = D00 * D11 - D01 * D01;
	float Beta = (D11 * D20 - D01 * D21) / Denom;
	float Gamma = (D00 * D21 - D01 * D20) / Denom;
	float Alpha = 1.0f - Beta - Gamma;
	return Vec3f(Alpha, Beta, Gamma);
}

void Render::GetBarycentric2D(const float& XA, const float& YA, const float& XB, const float& YB, const float& XC, const float& YC,
	const float& XP, const float& YP, float& Alpha, float& Beta, float& Gamma)
{
	float AB_X = XB - XA;
	float AB_Y = YB - YA;
	float AC_X = XC - XA;
	float AC_Y = YC - YA;
	float AP_X = XP - XA;
	float AP_Y = YP - YA;
	float D00 = AB_X * AB_X + AB_Y * AB_Y;
	float D01 = AB_X * AC_X + AB_Y * AC_Y;
	float D11 = AC_X * AC_X + AC_Y * AC_Y;
	float D20 = AP_X * AB_X + AP_Y * AB_Y;
	float D21 = AP_X * AC_X + AP_Y * AC_Y;
	float Denom = D00 * D11 - D01 * D01;
	Beta = (D11 * D20 - D01 * D21) / Denom;
	Gamma = (D00 * D21 - D01 * D20) / Denom;
	Alpha = 1.0f - Beta - Gamma;
}

/**
 * this is the same as (but more efficient than)
 *     vec3_t ab = vec3_sub(b, a);
 *     vec3_t ac = vec3_sub(c, a);
 *     return vec3_cross(ab, ac).z <= 0;
 */
bool Render::IsCull(Vec4f InNDC_Coord[3])
{
	return InNDC_Coord[0].X * InNDC_Coord[1].Y - InNDC_Coord[0].Y * InNDC_Coord[1].X +
		InNDC_Coord[1].X * InNDC_Coord[2].Y - InNDC_Coord[1].Y * InNDC_Coord[2].X +
		InNDC_Coord[2].X * InNDC_Coord[0].Y - InNDC_Coord[2].Y * InNDC_Coord[0].X <= 0;
}
