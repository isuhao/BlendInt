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

#ifndef _BLENDINT_GUI_PANEL_HPP_
#define _BLENDINT_GUI_PANEL_HPP_

/**
 * @defgroup widgets Widgets
 *
 * @ingroup gui
 */

#include <opengl/gl-buffer.hpp>
#include <opengl/gl-texture2d.hpp>

#include <gui/abstract-round-widget.hpp>
#include <gui/abstract-layout.hpp>

namespace BlendInt {

	/**
	 * @brief A widget usually contains other Form or widget in a box with padding
	 *
	 * @ingroup widgets
	 */
	class Panel: public AbstractRoundWidget
	{
		DISALLOW_COPY_AND_ASSIGN(Panel);

	public:

		Panel ();

		virtual ~Panel ();

		void SetLayout (AbstractLayout* layout);

		void AddWidget (AbstractWidget* widget);

		void InsertWidget (int index, AbstractWidget* widget);

		virtual bool IsExpandX () const;

		virtual bool IsExpandY () const;

		virtual Size GetPreferredSize () const;

	protected:

		virtual void PerformSizeUpdate (const SizeUpdateRequest& request);

		virtual void PerformRoundTypeUpdate (int round_type);

		virtual void PerformRoundRadiusUpdate (float radius);

		virtual Response Draw (AbstractWindow* context);

	private:

		void InitializePanelOnce ();

		void OnLayoutDestroyed (AbstractWidget* layout);

		AbstractLayout* layout_;

		GLuint vao_[3];

		GLBuffer<ARRAY_BUFFER, 3> buffer_;

        GLTexture2D texture_buffer_;

	};

} /* namespace BlendInt */

#endif /* _BLENDINT_GUI_PANEL_HPP_ */
