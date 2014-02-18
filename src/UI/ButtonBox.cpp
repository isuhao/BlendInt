/*
 * This file is part of BlendInt (a Blender-like Interface Library in
 * OpenGL).
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is free
 * software: you can redistribute it and/or modify it under the terms
 * of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is
 * distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with BlendInt.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Contributor(s): Freeman Zhang <zhanggyb@gmail.com>
 */

#include <BlendInt/UI/ButtonBox.hpp>
#include <BlendInt/UI/HorizontalLayout.hpp>

namespace BlendInt {

	ButtonBox::ButtonBox ()
	: BoxFrame(), m_active_button(0)
	{
		Init ();
	}

	ButtonBox::ButtonBox (AbstractWidget* parent)
	: BoxFrame(parent), m_active_button(0)
	{
		Init ();
	}

	ButtonBox::~ButtonBox ()
	{

	}

	void ButtonBox::Add (AbstractButton* button)
	{
		if(layout())
			layout()->Add(button);

		unsigned int width = layout()->preferred_size().width();
		unsigned int height = layout()->preferred_size().height();

		Resize(width + margin().left() + margin().right(), height + margin().top() + margin().bottom());
	}

	void ButtonBox::Init ()
	{
		// DEMO: use HLayout temporarily
		HorizontalLayout* layout = new HorizontalLayout;
		layout->SetMargin(1, 1, 1, 1);
		SetLayout(layout);
	}

}
