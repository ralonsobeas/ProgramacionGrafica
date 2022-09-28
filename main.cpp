#include <iostream>
#include "common.h"
#include <vector>
#include "mesh.h"
#include "render.h"
#include "object.h"
#include "scene.h"
#include "inputManager.h"
#include "system.h"

#include "cube.h"
#include "background.h"
#include "light.h"



bool renderfps(double framerate) 
{ 
	static double currentTime = 0; 
	static double lastTime=0;
	
	currentTime = glfwGetTime();
	if(currentTime - lastTime >= 1.0 / framerate) 
	{
		lastTime = currentTime;
		return true;
	}
	return false;
}


int main(int argc, char** argv)
{

	int glfwState=glfwInit();
	if (!glfwState)
		std::cout << "ERROR iniciando glfw\n";

	GLFWwindow* window = glfwCreateWindow(640,480,"Prueba 1 GLFW",nullptr,nullptr);
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	
	int glewState=glewInit();
	
	if (glewState!=GLEW_OK)
		std::cout << "ERROR iniciando glew\n";

	InputManager::init(window);
	Object* cube = new Cube("cube.trg");
	cube->scale = glm::vec3(0.5f, 0.5f, 0.5f);
	cube->position.z=3.0f;
	

	Render* render=new Render();
	Scene* scene=new Scene();
	System::scene=scene;
	//scene->setCamera(new Camera(glm::vec3(0,0,0.5),glm::vec3(0,0,0),perspective));
	scene->addLight(new Light(glm::vec4(-3.0, 0, 6.0, 1),glm::vec4(0, 0, 0, 1)));
	scene->addLight(new Light(glm::vec4(3.0, 0, 6.0, 1), glm::vec4(0, 0, 0, 1)));
	scene->setCamera(new Camera(glm::vec3(0, 0, 6.0), glm::vec3(0, 0, 0), perspective));
	scene->addObject(cube);
	
	render->setupObject(cube);

	while(!glfwWindowShouldClose(window))
	{	
	
		if(renderfps(60.0f)){
			scene->step(0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				render->drawScene(scene);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	
	//delete triangle;
	return 0;

}
