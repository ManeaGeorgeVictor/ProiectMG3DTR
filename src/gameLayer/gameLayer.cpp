#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include <platformTools.h>
#include <shader.h>
#include "mesh.h"
#include <camera.h>
#include <imfilebrowser.h>

Mesh model;
Shader shader;
Camera camera;

GLint viewProj;

ImGui::FileBrowser fileBrowser;

bool initGame()
{
	float data[] =
	{
		0, 1, 0,
		-1, -1, 0,
		1, -1, 0
	};

	model.loadFromData(data, sizeof(data));

	shader.loadShaderProgramFromFile(
		RESOURCES_PATH "shader.vert",
		RESOURCES_PATH "shader.frag"
	);

	viewProj = shader.getUniform("viewProj");

	camera.position.z = 2;

	fileBrowser.SetTitle("test");
	fileBrowser.SetTypeFilters({".gltf", ".fbx", ".pbj", ".glb"});
	fileBrowser.Open();

	return true;
}



bool gameLogic(float deltaTime)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h

	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen

	camera.aspectRatio = (float)w / h;

#pragma endregion

#pragma region input

	static auto lastMousePos = platform::getRelMousePosition();
	auto newMousePos = platform::getRelMousePosition();
	glm::vec2 mouseDelta = (lastMousePos - newMousePos);
	mouseDelta *= 0.01;
	lastMousePos = newMousePos;

	if (platform::isRMouseHeld())
	{


		camera.rotateCamera(mouseDelta);

		glm::vec3 deplasare = {};
		float speed = deltaTime * 5;

		if (platform::isButtonHeld(platform::Button::A))
		{
			deplasare.x -= speed;
		}

		if (platform::isButtonHeld(platform::Button::D))
		{
			deplasare.x += speed;
		}

		if (platform::isButtonHeld(platform::Button::W))
		{
			deplasare.z -= speed;
		}

		if (platform::isButtonHeld(platform::Button::S))
		{
			deplasare.z += speed;
		}
		
		if (platform::isButtonHeld(platform::Button::Q))
		{
			deplasare.y -= speed;
		}

		if (platform::isButtonHeld(platform::Button::E))
		{
			deplasare.y += speed;
		}

		camera.moveFps(deplasare);
	}


#pragma endregion

	fileBrowser.Display();
	
	if (fileBrowser.HasSelected())
	{
		std::cout << fileBrowser.GetSelected();
		fileBrowser.ClearSelected();
	}


	shader.bind();

	glUniformMatrix4fv(viewProj, 1,
		0, glm::value_ptr(camera.getViewProjectionMatrix()));
	
	glBindVertexArray(model.vao);

	glDrawArrays(GL_TRIANGLES, 0, model.vertexCount);

	return true;
#pragma endregion

}



void closeGame()
{


}
