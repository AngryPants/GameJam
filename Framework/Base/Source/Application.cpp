#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

//#include Systems
#include "AudioManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"

#include "RenderSystem.h"
#include "IDGenerator.h"
#include "GameData.h"

//Include Controller(s)
#include "Controller_Keyboard.h"
#include "Controller_Mouse.h"
#include "Controller_Gamepad.h"

//Include Scene(s)
#include "SceneTest.h"
#include "SceneEmpty.h"
#include "SceneGJ.h"
#include "SceneMainMenu.h"

GLFWwindow* m_window;
const unsigned char maxFPS = 60; //Maximum FPS of this game.
const unsigned int frameTime = 1000 / maxFPS; //Minimum time for each frame.

//Define an error callback
static void error_callback(int error, const char* description) {
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void resize_callback(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);
}

int Application::GetWindowWidth() {
	return this->m_window_width;
}

int Application::GetWindowHeight() {
	return this->m_window_height;
}

Application::Application() {
	m_window_height = 900;
	m_window_width = 1600;
}

Application::~Application() {
}

void Application::InitScenes() {
	//Add Scenes Here!
	SceneManager::GetInstance().CreateScene<SceneEmpty>("Empty Scene");
	SceneManager::GetInstance().CreateScene<SceneTest>("Test Scene");
 	SceneManager::GetInstance().CreateScene<SceneGJ>("Level 1");
	SceneManager::GetInstance().CreateScene<SceneMainMenu>("Main Menu");
	SceneManager::GetInstance().SetActiveScene("Main Menu");
	//SceneManager::GetInstance().SetActiveScene("Level 1");
}

void Application::Init() {
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	
	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(m_window_width, m_window_height, "A_Framework", NULL, NULL); //Windowed
	//m_window = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "A_Framework", glfwGetPrimaryMonitor(), NULL);

	//If the window couldn't be created
	if (!m_window) {
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	//Hide the cursor
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
	//Initialise Threads
	elapsedTime = 0.0;
	for (unsigned int t = 0; t < NUM_THREAD; ++t) {
		accumulatedTime[t] = 0.0;
	}

	controller::Mouse::GetInstance().SetWindow(m_window);
	controller::Keyboard::GetInstance().SetWindow(m_window);
	controller::GamepadManager::GetInstance().SetWindow(m_window);

	quit = false;
}

void Application::ExitSystems() {
	//Close the systems, starting from the highest level to the lowest level.
	SceneManager::Destroy();
	
	//GameObjectManager MUST be destroyed BEFORE ComponentManager.
	GameObjectManager::Destroy();
	ComponentManager::Destroy();

	MeshBuilder::Destroy();
	TextureManager::Destroy();
	
	RenderHelper::Destroy();
	GraphicsManager::Destroy();

	AudioManager::Destroy();
	InputManager::GetInstance().Destroy();

	//Now the rest of the systems that have no dependacy.
	RenderSystem::Destroy();

	//Destroy this last, just in case another other Systems are still relying on IDs generated by this.
	IDGenerator::Destroy();
}

void Application::RunThreads() {
	
	if (accumulatedTime[THREAD_UPDATE_WINDOW_SIZE] >= 3.0) {
		glfwGetWindowSize(m_window, &m_window_width, &m_window_height);
		resize_callback(m_window, m_window_width, m_window_height);
		accumulatedTime[THREAD_UPDATE_WINDOW_SIZE] = 0.0;
	}

}

void Application::Run() {

	//Main Loop
	InitScenes();
	//Update anything created in the scene's Init();
	GameObjectManager::GetInstance().Update();
	ComponentManager::GetInstance().Update();
	m_timer.startTimer(); //Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !quit) {
		elapsedTime = m_timer.getElapsedTime();
		
		//Update
		InputManager::GetInstance().Update();
		SceneManager::GetInstance().Update(elapsedTime);
		GameObjectManager::GetInstance().Update();
		ComponentManager::GetInstance().Update();
		AudioManager::GetInstance().Update();

		//Render
		SceneManager::GetInstance().Render();
		glfwSwapBuffers(m_window); //Swap buffers

		//Threads
		RunThreads();
		for (unsigned int t = 0; t < NUM_THREAD; ++t) {
			accumulatedTime[t] += elapsedTime;
		}

		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime); // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed		
}

void Application::Exit() {
	//Delete all our systems(Managers etc.)
	ExitSystems();
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

void Application::Quit() {
	quit = true;
}