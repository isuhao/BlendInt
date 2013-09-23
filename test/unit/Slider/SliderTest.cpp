// cpp

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <stdio.h>

#include "SliderTest.h"

#include <BILO/Interface.hpp>
#include <BILO/Slider.hpp>

#include <stdlib.h>

using namespace BILO;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(SliderTest);

myLabel::myLabel(const String& label)
: BILO::Label(label)
{

}

myLabel::~myLabel()
{

}

void myLabel::print_value(int value)
{
	char c[10];
	sprintf(c, "%d", value);
	String str = c;

	set_text (str);
}

SliderTest::SliderTest ()
{

}

SliderTest::~SliderTest ()
{

}

void SliderTest::setUp ()
{
}

void SliderTest::tearDown ()
{
#ifdef DEBUG
	int mapsize = Drawable::map_size();

	if(mapsize > 0) {
		map<uint64_t, Drawable*>::const_iterator it;
		for (it = Drawable::get_map().begin(); it != Drawable::get_map().end(); it++)
		{
			cout << "id: " << it->first << " was not deleted!" << endl;
		}
	}

	CPPUNIT_ASSERT(mapsize == 0);
#endif
}

void SliderTest::slider_move_test01()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	glfwSetErrorCallback(&cbError);

	GLFWwindow* window = glfwCreateWindow(1200, 800, "Demo Window for BILO", NULL, NULL);
	if (!window) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	glfwSetWindowSizeCallback(window, &cbWindowSize);
	glfwSetKeyCallback(window, &cbKey);
	glfwSetMouseButtonCallback(window, &cbMouseButton);
	glfwSetCursorPosCallback(window, &cbCursorPos);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* initialize BILO after OpenGL content is created */
	if (!Interface::initialize()) {
		glfwTerminate();
		CPPUNIT_ASSERT(false);
		return;
	}

	Cpp::ConnectionScope scope_;

	Interface* app = Interface::instance();
	app->resize(1200, 800);

	Slider * hslider = new Slider;
	hslider->set_pos (200, 200);

	myLabel* label = new myLabel;
	label->set_pos (200, 250);

	scope_.connect(hslider->slider_moved(), label, &myLabel::print_value);

	app->bind(hslider);
	app->bind(label);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		app->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	/* release BILO */
	Interface::release();

	glfwTerminate();
	CPPUNIT_ASSERT(true);
}

void SliderTest::cbError (int error, const char* description)
{
	std::cerr << "Error: " << description
			<< " (error code: " << error << ")"
			<< std::endl;
}

void SliderTest::cbWindowSize (GLFWwindow* window, int w, int h)
{
	BILO::Interface::instance()->resizeEvent(w, h);
}

void SliderTest::cbKey (GLFWwindow* window, int key, int scancode, int action,
        int mods)
{
	BILO::Interface::instance()->keyEvent(key, scancode, action, mods);
}

void SliderTest::cbMouseButton (GLFWwindow* window, int button, int action,
        int mods)
{
	BILO::Interface::instance()->mouseButtonEvent(button, action, mods);
}

void SliderTest::cbCursorPos (GLFWwindow* window, double xpos, double ypos)
{
	BILO::Interface::instance()->cursorPosEvent(xpos, ypos);
}
