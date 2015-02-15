/*
 * This file is part of BlendInt (a Blender-like Interface Library in
 * OpenGL).
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is free software:
 * you can redistribute it and/or modify it under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is distributed in
 * the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with BlendInt.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Contributor(s): Freeman Zhang <zhanggyb@gmail.com>
 */

#ifndef _BLENDINT_GUI_STRINGLISTMODEL_HPP_
#define _BLENDINT_GUI_STRINGLISTMODEL_HPP_

#include <gui/abstract-list-model.hpp>

namespace BlendInt {

	class StringListModel: public AbstractListModel
	{
	public:

		StringListModel();

		virtual ~StringListModel ();

		virtual int GetRowCount (const ModelIndex& superview = ModelIndex()) const;

		virtual int GetColumnCount (const ModelIndex& superview = ModelIndex()) const;

		virtual bool InsertRows (int row, int count, const ModelIndex& superview = ModelIndex());

		virtual bool RemoveRows (int row, int count, const ModelIndex& superview = ModelIndex());

#ifdef DEBUG

		void Print ();

#endif

	private:

		int rows_;

	};

}

#endif /* _BLENDINT_GUI_STRINGLISTMODEL_HPP_ */
