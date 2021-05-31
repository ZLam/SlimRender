#include "TestView.h"

#include <iostream>
#include <thread>
#include <filesystem>
#include "Core/Math.h"
#include "Core/Functions.h"
#include "Core/RandomHelper.h"
#include "Core/Vector.h"
#include "Core/App.h"
#include "Core/Matrix.h"
#include "Core/Texture.h"

// #define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"

TestView::TestView(const std::string& InName) :
BaseView(InName)
{
	
}

TestView::~TestView()
{
	// if (Tex)
	// {
	// 	SDL_DestroyTexture(Tex);
	// 	Tex = nullptr;
	// }
	if (Tex_Try)
	{
		SDL_DestroyTexture(Tex_Try);
		Tex_Try = nullptr;
	}
	if (Render_Try)
	{
		delete Render_Try;
		Render_Try = nullptr;
	}
	if (Cam_Try)
	{
		delete Cam_Try;
		Cam_Try = nullptr;
	}
	if (ShaderProgram_Try)
	{
		delete ShaderProgram_Try;
		ShaderProgram_Try = nullptr;
	}
}

bool TestView::Init()
{
	auto Renderer = App::GetInstance().Get_SDL_Renderer();
	
	// Tex = SDL_CreateTexture(
	// 	Renderer,
	// 	SDL_PIXELFORMAT_RGBA32,
	// 	SDL_TEXTUREACCESS_TARGET,
	// 	static_cast<int>(TexSize.x),
	// 	static_cast<int>(TexSize.y)
	// );

	Render_Try = new Render(Size_Try.X, Size_Try.Y);
	
    Cam_Try = new Camera(Vec3f(0.0f, 0.0f, 5.0f), Vec3f(0.0f, 0.0f, 0.0f));
	Cam_Try->SetupProjection(ANGLE_TO_RADIAN(60.0f), (float)(Size_Try.X) / (float)(Size_Try.Y), 0.1f, 10000.0f);

	ShaderProgram_Try = new BlinnShaderProgram();
	BlinnMaterial* CurMaterial = (BlinnMaterial*)ShaderProgram_Try->CurUniform->CurMaterial;
	CurMaterial->Tex_Diffuse = new Texture(ResFullPath("/test2.png"));

	Tex_Try = SDL_CreateTexture(
		Renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		Size_Try.X,
		Size_Try.Y
	);

	return true;
}

void TestView::Draw()
{
	auto Renderer = App::GetInstance().Get_SDL_Renderer();
	
	// SDL_SetRenderTarget(Renderer, Tex);
	// SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	// SDL_RenderClear(Renderer);
	// SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
	// SDL_RenderDrawLine(Renderer, 10, 10, 90, 90);
	// SDL_SetRenderTarget(Renderer, nullptr);
	
	Render_Try->CleanColorBuffer();
	Render_Try->CleanDepthBuffer();


	float DeltaTime = App::GetInstance().GetDeltaTime();
	
	
	// pixels begin
	// Render_Try->DrawPixel(0, 0, Color::Red);
	// Render_Try->DrawPixel(Render_Try->GetWidth() / 2, Render_Try->GetHeight() / 2, Color::Green);
	// Render_Try->DrawPixel(Render_Try->GetWidth() - 1, Render_Try->GetHeight() - 1, Color::Blue);
	// pixels end
	
	// lines begin
	// Render_Try->DrawLine(50, 50, 200, 100, Color::Red);
	// Render_Try->DrawLine(50, 50, 200, 200, Color::Red);
	// Render_Try->DrawLine(50, 50, 200, 300, Color::Red);
	// Render_Try->DrawLine(50, 50, 200, 400, Color::Red);
	// Render_Try->DrawLine(50, 50, 100, 400, Color::Red);
	// Render_Try->DrawLine(150, 150, 50, 250, Color::Red);
	// Render_Try->DrawLine(150, 150, 79, 220, Color::Red);
	// uint32 OriginX = 150;
	// uint32 OriginY = 150;
	// float r = 100;
	// float a = 0;
	// while (a < 360)
	// {
	// 	// std::cout << ANGLE_TO_RADIAN(a) << std::endl;
	// 	auto ToX = static_cast<uint32>(OriginX + cos(ANGLE_TO_RADIAN(a)) * r);
	// 	auto ToY = static_cast<uint32>(OriginY + sin(ANGLE_TO_RADIAN(a)) * r);
	// 	// std::cout << OriginX << " " << OriginY << " " << ToX << " " << ToY << std::endl;
	// 	Render_Try->DrawLine(OriginX, OriginY, ToX, ToY, Color::Red);
	// 	a += 10;
	// }
	// lines end

	// triangles begin
	// Render_Try->DrawTriangle_OldSchool(Vec2i(200, 100), Vec2i(250, 500), Vec2i(350, 300));
	// Render_Try->DrawTriangle_OldSchool(Vec2i(200, 100), Vec2i(300, 300), Vec2i(350, 150));
	// Render_Try->DrawTriangle_OldSchool(Vec2i(200, 200), Vec2i(400, 100), Vec2i(300, 400));
	// Render_Try->DrawTriangle_OldSchool(Vec2i(250, 200), Vec2i(250, 250), Vec2i(250, 300));
	// Render_Try->DrawTriangle(Vec3f(200, 200, 0), Vec3f(400, 100, 0), Vec3f(300, 400, 0));
	// static float MaxTime = 1.0f;
	// static float SumTime = MaxTime;
	// static float CurAngle = 0.0f;
	// static float PreAngle = 30.0f;
	// static float R = 200.0f;
	// static uint32 Index_A = 0;
	// static Vec2f Center(250, 250);
	// // static Vec2i A1(250, 200);
	// static Vec3f A2(250, 250, 0);
	// // static Vec2i A3(250, 300);
	// static std::vector<Vec3f> A1Arr = {
	// 	Vec3f(250, 200, 0),
	// 	Vec3f(300, 200, 0),
	// 	Vec3f(300, 250, 0),
	// 	Vec3f(300, 300, 0),
	// 	Vec3f(250, 300, 0),
	// };
	// static std::vector<Vec3f> A3Arr = {
	// 	Vec3f(250, 300, 0),
	// 	Vec3f(200, 300, 0),
	// 	Vec3f(200, 250, 0),
	// 	Vec3f(200, 200, 0),
	// 	Vec3f(250, 200, 0),
	// };
	// // Render_Try->DrawTriangle_OldSchool(A1Arr[Index_A], A2, A3Arr[Index_A], Color::Green);
	// Render_Try->DrawTriangle(A1Arr[Index_A], A2, A3Arr[Index_A]);
	// SumTime += App::GetInstance().GetDeltaTime();
	// if (SumTime >= MaxTime)
	// {
	// 	// std::cout << SumTime << std::endl;
	// 	SumTime -= MaxTime;
	// 	A2.X = Center.X + cos(ANGLE_TO_RADIAN(CurAngle)) * R;
	// 	A2.Y = Center.Y + sin(ANGLE_TO_RADIAN(CurAngle)) * R;
	// 	CurAngle += PreAngle;
	// 	if (CurAngle >= 360.0f)
	// 	{
	// 		CurAngle -= 360.0f;
	// 		Index_A++;
	// 		Index_A %= 5;
	// 	}
	// }
	// triangles end



	// std::cout << "===test mvp begin===" << std::endl;
	// static float SumTime = 0;
	// std::vector<Vec3f> VexArr{
	// 	Vec3f(2.0f, 0.0f, 0.0f),
	// 	Vec3f(0.0f, 2.0f, 0.0f),
	// 	Vec3f(-2.0f, 0.0f, 0.0f),
	// };
	// std::vector<Vec3f> VexArr_TestZ{
	// 	Vec3f(2.0f, 0.0f, -1.0f),
	// 	Vec3f(0.0f, 2.0f, -1.0f),
	// 	Vec3f(-2.0f, 0.0f, -1.0f),
	// 	// Vec3f(3.5f, -1.0f, -3.0f),
	// 	// Vec3f(2.5f, 1.5f, -3.0f),
	// 	// Vec3f(-1.0f, 0.5f, -3.0f),
	// 	// Vec3f(-1.0f, 0.0f, 0.1f),
	// 	// Vec3f(-2.0f, 2.0f, -2.0f),
	// 	// Vec3f(-3.0f, 0.0f, 0.0f),
	// 	Vec3f(0.0f, -2.5f, -1.1f),
	// 	Vec3f(1.8f, 1.8f, -1.1f),
	// 	Vec3f(-1.0f, 1.0f, 0.0f),
	// };
	// std::vector<uint32> IndiceArr{ 0, 1, 2 };
	// std::vector<uint32> IndiceArr_TestZ{ 0, 1, 2, 3, 4, 5,  };
	// std::vector<Vec4f> ResultArr;
	// std::vector<Vec3f>* CurVexArr = &VexArr_TestZ;
	// std::vector<uint32>* CurIndicArr = &IndiceArr_TestZ;
	// static Matrix4 ModelMat;
	// Matrix4 MatMVP = Cam_Try->GetProjMat() * Cam_Try->GetViewMat() * ModelMat;
	// // std::cout << Cam_Try->GetViewMat() << std::endl;
	// // std::cout << Cam_Try->GetProjMat() << std::endl;
	// // std::cout << MatMVP << std::endl;
	// for (auto& i : *CurIndicArr)
	// {
	// 	auto& V = (*CurVexArr)[i];
	// 	auto P = MatMVP * Vec4f(V, 1.0f);		// MVP变换
	// 	// std::cout << P << std::endl;
	// 	/**
	// 	 * Homogeneous division
	// 	 * @TODO
	// 	 * 做完MVP变换后W并不是等于1的，这里本质的意义是什么？
	// 	 * 因为用了齐次坐标，这里要用W=1来表示一个点？
	// 	 * 除以W后，才表示在NDC空间中？
	// 	 */
	// 	P *= (1.0f / P.W);
	// 	// std::cout << P << std::endl;
	// 	P = ViewPort_Try->GetViewportMat() * P;		// 视口变换
	// 	ResultArr.push_back(P);
	// }
	// // for (auto& i : *CurIndicArr)
	// // {
	// // 	// std::cout << ResultArr[i] << std::endl;
	// // 	auto& P1 = ResultArr[i];
	// // 	auto& P2 = ResultArr[(i + 1) % 3];
	// // 	Render_Try->DrawLine(P1.X, P1.Y, P2.X, P2.Y);
	// // }
	// // SumTime += App::GetInstance().GetDeltaTime();
	// // if (SumTime >= 0.2f)
	// // {
	// // 	ModelMat.RotateZ(10.0f);
	// // 	// ModelMat.RotateY(10.0f);
	// // 	SumTime = 0.0f;
	// // }
	// for (uint32 i = 0; i < CurIndicArr->size(); i+=3)
	// {
	// 	auto& P1 = ResultArr[(*CurIndicArr)[i]];
	// 	auto& P2 = ResultArr[(*CurIndicArr)[i + 1]];
	// 	auto& P3 = ResultArr[(*CurIndicArr)[i + 2]];
	// 	Render_Try->DrawTriangle(
	// 		Vec3f(P1.X, P1.Y, P1.Z),
	// 		Vec3f(P2.X, P2.Y, P2.Z),
	// 		Vec3f(P3.X, P3.Y, P3.Z)
	// 	);
	// }
	// std::cout << "===test mvp end===" << std::endl;


	
	// std::cout << "===test draw cube begin===" << std::endl;
	// CubeScaleMat.Scale(1.0f);
	// CubeRotateMat.RotateX(2.0f * DeltaTime);
	// CubeRotateMat.RotateY(6.0f * DeltaTime);
	// CubeRotateMat.RotateZ(10.0f * DeltaTime);
	// // CubeModelMat.Identity();
	// CubeModelMat = CubeRotateMat * CubeScaleMat;
	// ShaderProgram_Try->CurUniform->MatCameraVP = Cam_Try->GetProjMat() * Cam_Try->GetViewMat();
	// ShaderProgram_Try->CurUniform->MatModel = CubeModelMat;
	// int faceNum = CubeVertexArr.size() / 3;
	// for (int i = 0; i < faceNum; i++)
	// {
	// 	Vertex* CurVertexArr[3];
	// 	for (int j = 0; j < 3; j++)
	// 	{
	// 		CurVertexArr[j] = &CubeVertexArr[i * 3 + j];
	// 	}
	// 	Render_Try->DrawTriangle(CurVertexArr, ShaderProgram_Try);
	// }
	// std::cout << "===test draw cube end===" << std::endl;




	// std::cout << "===test draw plane begin===" << std::endl;
	PlaneScaleMat.Scale(1.0f);
	// PlaneRotateMat.RotateX(30.0f * DeltaTime);
	// PlaneRotateMat.RotateY(30.0f * DeltaTime);
	SumRotateX += 50.0f * DeltaTime;
	float ToAngle = 60.0f * std::sin(ANGLE_TO_RADIAN(SumRotateX));
	PlaneRotateMat.Identity();
	PlaneRotateMat.RotateX(ToAngle);
	PlaneModelMat = PlaneRotateMat * PlaneScaleMat;
	ShaderProgram_Try->CurUniform->MatCameraVP = Cam_Try->GetProjMat() * Cam_Try->GetViewMat();
	ShaderProgram_Try->CurUniform->MatModel = PlaneModelMat;
	int FaceNum = PlaneVertexArr.size() / 3;
	for (int i = 0; i < FaceNum; i++)
	{
		Vertex* CurVertexArr[3];
		for (int j = 0; j < 3; j++)
		{
			CurVertexArr[j] = &PlaneVertexArr[i * 3 + j];
		}
		Render_Try->DrawTriangle(CurVertexArr, ShaderProgram_Try);
	}
	// std::cout << "===test draw plane end===" << std::endl;



	
	void* Pixels = nullptr;
	int Pitch;
	SDL_LockTexture(Tex_Try, nullptr, &Pixels, &Pitch);
	memcpy(Pixels, Render_Try->GetColorBuffer(), Render_Try->GetColorBufferSize());
	SDL_UnlockTexture(Tex_Try);



	
	if (ImGui::Begin(Name.c_str()))
	{
		// ImGui::Image(Tex, TexSize);
		if (ImGui::Button("Test"))
		{
			std::cout << "===test random begin===" << std::endl;
			std::cout << Random(0u, 10u) << std::endl;
			std::cout << Random(0.0f, 10.0f) << std::endl;
			auto c1 = Color::RandomColor();
			std::cout << c1 << std::endl;
			std::cout << "===test random end===" << std::endl;
	
			
	
			std::cout << "===test load obj begin===" << std::endl;
			tinyobj::attrib_t ObjAttrib;
			std::vector<tinyobj::shape_t> ObjShapeArr;
			std::vector<tinyobj::material_t> ObjMatArr;
			std::string StrWarn;
			std::string StrErr;
			std::string ObjFilePath = ResFullPath("/cube.obj");
			bool bLoadObj = tinyobj::LoadObj(&ObjAttrib, &ObjShapeArr, &ObjMatArr, &StrWarn, &StrErr, ObjFilePath.c_str());
			if (!StrWarn.empty())
			{
				std::cout << "[WARN] : " << StrWarn << std::endl;
			}
			if (!StrErr.empty())
			{
				std::cout << "[ERR] : " << StrErr << std::endl;
			}
			if (bLoadObj)
			{
				std::cout << "vertices num : " << ObjAttrib.vertices.size() << std::endl;
				// for (auto Vertex : ObjAttrib.vertices)
				// {
				// 	std::cout << Vertex << std::endl;
				// }
				std::cout << "ObjShapeArr num : " << ObjShapeArr.size() << std::endl;
				for (auto& Shape : ObjShapeArr)
				{
					size_t Offset = 0;
					std::cout << "shape name : " << Shape.name << std::endl;
					std::cout << "num_face_vertices num : " << Shape.mesh.num_face_vertices.size() << std::endl;
					std::cout << "indices num : " << Shape.mesh.indices.size() << std::endl;
					for (size_t i = 0; i < Shape.mesh.num_face_vertices.size(); i++)
					{
						size_t Num_FV = Shape.mesh.num_face_vertices[i];	// 当前面的顶点数量
						for (size_t j = 0; j < Num_FV; j++)
						{
							auto& IndexInfo = Shape.mesh.indices[Offset + j];
							std::cout << ObjAttrib.vertices[IndexInfo.vertex_index * 3] << ", " << ObjAttrib.vertices[IndexInfo.vertex_index * 3 + 1] << ", " << ObjAttrib.vertices[IndexInfo.vertex_index * 3 + 2] << " ";
						}
						std::cout << std::endl;
						Offset += Num_FV;
					}
				}
			}
			std::cout << "===test load obj end===" << std::endl;



			std::cout << "===test load img begin===" << std::endl;
			std::string ImgFilePath = ResFullPath("/test.png");
			int ImgWidth = 0;
			int ImgHeight = 0;
			int NumChannels = 0;
			uint8* ImgData = stbi_load(ImgFilePath.c_str(), &ImgWidth, &ImgHeight, &NumChannels, 0);
			if (ImgData)
			{
				std::vector<int> PixelIndexArr = {
					0,
					ImgWidth / 2 * NumChannels,
					ImgWidth * (ImgHeight / 2) * NumChannels,
					(ImgWidth * ImgHeight - 1) * NumChannels,
				};
				std::cout << ImgWidth << ", " << ImgHeight << ", " << NumChannels << std::endl;
				for (const auto& PixelIndex : PixelIndexArr)
				{
					uint8 r, g, b, a = 255;
					r = ImgData[PixelIndex];
					g = ImgData[PixelIndex + 1];
					b = ImgData[PixelIndex + 2];
					a = NumChannels >= 4 ? ImgData[PixelIndex + 3] : 255;
					std::cout << PixelIndex << ", " << (int32)r << ", " << (int32)g << ", " << (int32)b << ", " << (int32)a << std::endl;
				}
				stbi_image_free(ImgData);
				ImgData = nullptr;
			}
			std::cout << "===test load img end===" << std::endl;



			std::cout << "===test filesystem begin===" << std::endl;
			auto p = std::filesystem::current_path();
            auto p2 = std::filesystem::current_path().root_directory();
            auto p3 = std::filesystem::current_path().root_path();
			std::cout << p << std::endl;
            std::cout << p2 << std::endl;
            std::cout << p3 << std::endl;
			std::cout << p.string() << std::endl;
			std::cout << p.generic_string() << std::endl;
			std::cout << GetProjectDir() << std::endl;
			std::cout << GetResDir() << std::endl;
			std::cout << ResFullPath("/test.png") << std::endl;
			std::cout << "===test filesystem end===" << std::endl;



			std::cout << "===test texture begin===" << std::endl;
			std::string TexFilePath = ResFullPath("/test.png");
			auto Tex01 = Texture(TexFilePath);
			auto C1 = Tex01.Sample(Vec2f(0.0f, 0.0f));
			auto C2 = Tex01.Sample(Vec2f(0.51f, 0.0f));
			auto C3 = Tex01.Sample(Vec2f(0.0f, 0.51f));
			auto C4 = Tex01.Sample(Vec2f(0.51f, 0.51f));
			auto C5 = Tex01.Sample(Vec2f(1.0f, 1.0f));
			std::cout << C1 << std::endl;
			std::cout << C2 << std::endl;
			std::cout << C3 << std::endl;
			std::cout << C4 << std::endl;
			std::cout << C5 << std::endl;
			std::cout << "===test texture end===" << std::endl;
			

			
			std::cout << "===test misc begin===" << std::endl;
			Vec2f v1;
			std::cout << static_cast<void*>(&v1) << std::endl;
			v1 += Vec2f(1.0f, 5.0f);
			std::cout << static_cast<void*>(&v1) << std::endl;
			std::cout << v1 << std::endl;
			std::cout << static_cast<int32>(1.2f) << std::endl;
			std::cout << static_cast<int32>(1.7f) << std::endl;
			// Render_Try->DrawTriangle_OldSchool(Vec2i(1, 1), Vec2i(1, 2), Vec2i(1, 3));
			// Render_Try->DrawTriangle_OldSchool(Vec2i(1, 1), Vec2i(1, 3), Vec2i(1, 2));
			// Render_Try->DrawTriangle_OldSchool(Vec2i(1, 2), Vec2i(1, 1), Vec2i(1, 3));
			// Render_Try->DrawTriangle_OldSchool(Vec2i(1, 2), Vec2i(1, 3), Vec2i(1, 1));
			// Render_Try->DrawTriangle_OldSchool(Vec2i(1, 3), Vec2i(1, 1), Vec2i(1, 2));
			// Render_Try->DrawTriangle_OldSchool(Vec2i(1, 3), Vec2i(1, 2), Vec2i(1, 1));
			// auto a = std::chrono::steady_clock::now();
			// std::this_thread::sleep_for(std::chrono::microseconds(3000000));
			// auto b = std::chrono::steady_clock::now() - a;
			// auto c = std::chrono::duration_cast<std::chrono::microseconds>(b);
			// std::cout << b.count() << std::endl;
			// std::cout << c.count() << std::endl;
			std::cout << std::numeric_limits<float>::infinity() << std::endl;
			std::cout << (0.1f > (std::numeric_limits<float>::infinity())) << std::endl;
			std::cout << std::tan(45) << std::endl;
			std::cout << "===test misc end===" << std::endl;
		}
	}
	ImGui::End();
	
	if (ImGui::Begin("Test Soft Render", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::Image(Tex_Try, ImVec2(Size_Try.X, Size_Try.Y));
	}
	ImGui::End();

	// for (long i = 0; i < 50000000; i++)
	// {
	// 	
	// }
}
