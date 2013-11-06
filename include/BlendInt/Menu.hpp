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

#ifndef _BLENDINT_MENU_HPP_
#define _BLENDINT_MENU_HPP_

#include <BlendInt/Widget.hpp>

namespace BlendInt {

	/**
	 * @brief The menu widget for use in menu bars, context menus,
	 * and other popup menus.
	 */
	class Menu: public Widget
	{
		DISALLOW_COPY_AND_ASSIGN(Menu);

	public:

		Menu ();

		explicit Menu(AbstractForm* parent);

		Menu (const String& title, AbstractForm* parent = 0);

	};

}

#endif /* _BLENDINT_MENU_HPP_ */
