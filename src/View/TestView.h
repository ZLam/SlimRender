#pragma once

#include <vector>

#include "Core/BaseView.h"
#include "SDL.h"
#include "imgui.h"
#include "Core/Render.h"
#include "Core/Camera.h"
#include "Core/Vertex.h"
#include "Core/ShaderProgram.h"
#include "Core/Mesh.h"

class TestView : public BaseView
{
private:
	// SDL_Texture* Tex;
	// ImVec2 TexSize = ImVec2(100.0f, 100.0f);

	SDL_Texture* Tex_Try;
	Render* Render_Try;
	Vec2i Size_Try = Vec2i(500, 500);
	Camera* Cam_Try;
	ShaderProgram* ShaderProgram_Try;

	std::vector<Vertex> CubeVertexArr = {
		Vertex(Vec3f(1.0f, 1.0f, 1.0f), Color::Red),			//1
		Vertex(Vec3f(-1.0f, -1.0f, 1.0f), Color::Green),		//2
		Vertex(Vec3f(1.0f, -1.0f, 1.0f), Color::Blue),		//3

		Vertex(Vec3f(1.0f, 1.0f, 1.0f), Color::Red),			//1
		Vertex(Vec3f(-1.0f, 1.0f, 1.0f), Color::Blue),		//4
		Vertex(Vec3f(-1.0f, -1.0f, 1.0f), Color::Green),		//2

		Vertex(Vec3f(1.0f, 1.0f, -1.0f), Color::Blue),		//5
		Vertex(Vec3f(1.0f, -1.0f, -1.0f), Color::Green),		//7
		Vertex(Vec3f(-1.0f, -1.0f, -1.0f), Color::Red),		//6

		Vertex(Vec3f(1.0f, 1.0f, -1.0f), Color::Blue),		//5
		Vertex(Vec3f(-1.0f, -1.0f, -1.0f), Color::Red),		//6
		Vertex(Vec3f(-1.0f, 1.0f, -1.0f), Color::Green),		//8

		Vertex(Vec3f(1.0f, 1.0f, -1.0f), Color::Blue),		//5
		Vertex(Vec3f(-1.0f, 1.0f, 1.0f), Color::Blue),		//4
		Vertex(Vec3f(1.0f, 1.0f, 1.0f), Color::Red),			//1

		Vertex(Vec3f(1.0f, 1.0f, -1.0f), Color::Blue),		//5
		Vertex(Vec3f(-1.0f, 1.0f, -1.0f), Color::Green),		//8
		Vertex(Vec3f(-1.0f, 1.0f, 1.0f), Color::Blue),		//4

		Vertex(Vec3f(1.0f, -1.0f, -1.0f), Color::Green),		//7
		Vertex(Vec3f(1.0f, -1.0f, 1.0f), Color::Blue),		//3
		Vertex(Vec3f(-1.0f, -1.0f, 1.0f), Color::Green),		//2

		Vertex(Vec3f(1.0f, -1.0f, -1.0f), Color::Green),		//7
		Vertex(Vec3f(-1.0f, -1.0f, 1.0f), Color::Green),		//2
		Vertex(Vec3f(-1.0f, -1.0f, -1.0f), Color::Red),		//6

		Vertex(Vec3f(1.0f, 1.0f, -1.0f), Color::Blue),		//5
		Vertex(Vec3f(1.0f, -1.0f, 1.0f), Color::Blue),		//3
		Vertex(Vec3f(1.0f, -1.0f, -1.0f), Color::Green),		//7

		Vertex(Vec3f(1.0f, 1.0f, -1.0f), Color::Blue),		//5
		Vertex(Vec3f(1.0f, 1.0f, 1.0f), Color::Red),			//1
		Vertex(Vec3f(1.0f, -1.0f, 1.0f), Color::Blue),		//3

		Vertex(Vec3f(-1.0f, 1.0f, -1.0f), Color::Green),		//8
		Vertex(Vec3f(-1.0f, -1.0f, -1.0f), Color::Red),		//6
		Vertex(Vec3f(-1.0f, -1.0f, 1.0f), Color::Green),		//2

		Vertex(Vec3f(-1.0f, 1.0f, -1.0f), Color::Green),		//8
		Vertex(Vec3f(-1.0f, -1.0f, 1.0f), Color::Green),		//2
		Vertex(Vec3f(-1.0f, 1.0f, 1.0f), Color::Blue),		//4
	};
	Matrix4 CubeModelMat;
	Matrix4 CubeScaleMat;
	Matrix4 CubeRotateMat;

	std::vector<Vertex> PlaneVertexArr = {
		Vertex(Vec3f(1.0f, 1.0f, 0.0f), Color::White, Vec2f(1.0f, 1.0f)),			//1
		Vertex(Vec3f(-1.0f, -1.0f, 0.0f), Color::White, Vec2f(0.0f, 0.0f)),		//2
		Vertex(Vec3f(1.0f, -1.0f, 0.0f), Color::White, Vec2f(1.0f, 0.0f)),		//3

		Vertex(Vec3f(1.0f, 1.0f, 0.0f), Color::White, Vec2f(1.0f, 1.0f)),			//1
		Vertex(Vec3f(-1.0f, 1.0f, 0.0f), Color::White, Vec2f(0.0f, 1.0f)),		//4
		Vertex(Vec3f(-1.0f, -1.0f, 0.0f), Color::White, Vec2f(0.0f, 0.0f)),		//2
	};
	Matrix4 PlaneModelMat;
	Matrix4 PlaneScaleMat;
	Matrix4 PlaneRotateMat;
	float SumRotateX_Plane = 0.0f;
    

    Mesh* TestMesh;
    Matrix4 TestMeshModelMat;
    Matrix4 TestMeshScaleMat;
    Matrix4 TestMeshRotateMat;
    float SumRotateX_TestMesh = 0.0f;
	
    
	
public:
	TestView(const std::string& InName);
	virtual ~TestView() override;

	bool Init() override;
	void Draw() override;
};
