/*
 * This file is part of BIL (Blender Interface Library).
 *
 * BIL (Blender Interface Library) is free software: you can
 * redistribute it and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * BIL (Blender Interface Library) is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with BIL.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Contributor(s): Freeman Zhang <zhanggyb@gmail.com>
 */
#include <GL/glew.h>

#include <BIL/ScrollWidget.hpp>

namespace BIL {

	ScrollBar::ScrollBar(Drawable* parent)
	: Widget(parent)
	{

	}

	ScrollBar::~ScrollBar()
	{

	}

	void ScrollBar::render ()
	{

	}

	ScrollWidget::ScrollWidget(Drawable* parent)
	: Widget(parent)
	{

	}

	ScrollWidget::~ScrollWidget ()
	{

	}

	void ScrollWidget::add_widget(Widget* widget)
	{
		// TODO: more code needed here
		add_child(widget);
	}

	void ScrollWidget::render ()
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glTranslatef(pos_.x(),
					 pos_.y(),
					 z());

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glScissor (100, 100, 200, 200);
		glEnable (GL_SCISSOR_TEST);

		glColor3f(0.6f, 1.0f, 0.2f);
		glBegin(GL_POLYGON);
			glVertex2d(50,50);
			glVertex2d(600,50);
			glVertex2d(600,500);
			glVertex2d(50,500);
		glEnd();

		glDisable(GL_SCISSOR_TEST);

		glDisable(GL_BLEND);

		glPopMatrix();
	}

}