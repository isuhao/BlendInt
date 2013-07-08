/*
 * Application.cpp
 *
 *  Created on: 2013年7月3日
 *      Author: zhanggyb
 */

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>

#include <iostream>
#include <string>

#include <BIL/Application.h>


namespace BIL {

	std::string Application::glStrVersion;
	GLfloat Application::glVersion = 1.0;

	Application::Application ()
			: _mainWindow(NULL)
	{
		// TODO Auto-generated constructor stub

	}

	int Application::init (void)
	{
		int ret = glfwInit();

		if (ret == GL_TRUE)
			glfwSetErrorCallback(&Application::cbError);

			return ret;
	}

	GLFWVersion Application::getVersion (void)
	{
		GLFWVersion version;

		glfwGetVersion(&version.major, &version.minor, &version.rev);

		return version;
	}

	std::string Application::getVersionString (void)
	{
		std::string version;

		version = glfwGetVersionString();

		return version;
	}

	// FIXME: run in bummblebee cause crash if the window is closed
	void Application::run (void)
	{
		if (_mainWindow == NULL) {
			std::cerr << "No Main Window" << std::endl;
			return;
		}

		_mainWindow->MakeContextCurrent();

		// check OpenGL version
		glStrVersion = (const char*)glGetString(GL_VERSION);
		glVersion = std::atof(glStrVersion.c_str());	// C++ 98
		// glVersion = std::stof (glStrVersion);	// C++ 11

		// Initialize GLEW
		glewExperimental = true; // Needed in core profile
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initilize GLEW" << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		while (!glfwWindowShouldClose(_mainWindow->getWindow())) {

			_mainWindow->refresh();

			glfwSwapBuffers(_mainWindow->getWindow());
			glfwPollEvents();
		}

		return;
	}

	Application::~Application ()
	{
		// TODO Auto-generated destructor stub

		// TODO: the following lines will cause crash
		/*
		if (_mainWindow != NULL) {
			delete _mainWindow;
			_mainWindow = NULL;
		}
		*/

		glfwTerminate();
	}

	void Application::cbError (int error, const char* description)
	{
		std::cerr << error << ' ' << description << std::endl;

		return;
	}

} /* namespace BIL */
