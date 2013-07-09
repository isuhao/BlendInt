/*
 * RollingTriangle.cpp
 *
 *  Created on: 2013年7月4日
 *      Author: zhanggyb
 */

#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <iostream>

#include "RollingTriangle.h"

namespace BIL {

	RollingTriangle::RollingTriangle (BasicObject *parent)
			: Drawable(parent)
	{
		// TODO Auto-generated constructor stub
		resize(400, 400);
	}

	RollingTriangle::~RollingTriangle ()
	{
		// TODO Auto-generated destructor stub
	}

	void RollingTriangle::render (void)
	{
		float ratio;

		ratio = getSize().getWidth() / (float) getSize().getHeight();

		glViewport(0, 0, getSize().getWidth(), getSize().getHeight());

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		glBegin(GL_TRIANGLES);
		{
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(-0.6f, -0.4f, 0.f);
			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(0.6f, -0.4f, 0.f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(0.f, 0.6f, 0.f);
		}
		glEnd();
	}

} /* namespace BIL */