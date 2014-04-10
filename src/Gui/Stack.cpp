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

#include <BlendInt/Gui/Stack.hpp>
#include <algorithm>

namespace BlendInt {

	Stack::Stack()
	: AbstractContainer(), m_index(0)
	{
		set_preferred_size(400, 300);
		set_size(400, 300);
	}

	Stack::~Stack()
	{

	}

	void Stack::Add (AbstractWidget* widget)
	{
		if(AppendSubWidget(widget)) {
			// TODO: lock widget's geometry

			unsigned int w = size().width() - margin().left() - margin().right();
			unsigned int h = size().height() - margin().top() - margin().bottom();

			Resize(widget, w, h);
			SetPosition(widget, position().x() + margin().left(), position().y() + margin().bottom());

			if((sub_widget_size() - 1) != m_index) {
				widget->SetVisible(false);
			}
		}
	}

	void Stack::Insert (size_t index, AbstractWidget* widget)
	{
		if(InsertSubWidget(index, widget)) {
			// TODO: lock widget's geometry

			unsigned int w = size().width() - margin().left() - margin().right();
			unsigned int h = size().height() - margin().top() - margin().bottom();

			Resize(widget, w, h);
			SetPosition(widget, position().x() + margin().left(), position().y() + margin().bottom());
		}
	}

	void Stack::Remove (AbstractWidget* widget)
	{
		if(RemoveSubWidget(widget)) {
			m_index--;
		}
	}

	void Stack::SetIndex (size_t index)
	{
		size_t size = sub_widget_size();

		if(index > (size - 1)) return;

		if(size) {
			sub_widgets()->at(m_index)->SetVisible(false);

			m_index = index;
			sub_widgets()->at(m_index)->SetVisible(true);
		}
	}

	AbstractWidget* Stack::GetActiveWidget () const
	{
		return 0;
	}

	AbstractWidget* Stack::GetWidget (size_t index)
	{

		return 0;
	}

	void Stack::HideSubWidget(size_t index)
	{
		size_t size = sub_widget_size();

		if(size && index < (size - 1)) {
			AbstractWidget* p = sub_widgets()->at(index);
			p->SetVisible(false);
		}
	}

	bool Stack::Update (const UpdateRequest& request)
	{
		if(request.source() == Predefined) {

			switch (request.type()) {

				case FormPosition: {
					const Point* pos_p = static_cast<const Point*>(request.data());

					int x = pos_p->x() - position().x();
					int y = pos_p->y() - position().y();

					MoveSubWidgets(x, y);

					return true;
				}

				case FormSize: {
					const Size* new_size = static_cast<const Size*>(request.data());

					unsigned int w = new_size->width() - margin().left() - margin().right();
					unsigned int h = new_size->height() - margin().top() - margin().bottom();

					ResizeSubWidgets(w, h);

					return true;
				}

				case ContainerMargin: {

					const Margin* margin_p = static_cast<const Margin*>(request.data());

					unsigned int w = size().width() - margin_p->left() - margin_p->right();
					unsigned int h = size().height() - margin_p->top() - margin_p->bottom();

					ResizeSubWidgets(w, h);

					return true;
				}

				default:
					return true;
			}

		} else {
			return false;
		}
	}

	ResponseType Stack::Draw (const RedrawEvent& event)
	{
		return IgnoreAndContinue;
	}

	ResponseType Stack::CursorEnterEvent(bool entered)
	{
		return Ignore;
	}

	ResponseType Stack::KeyPressEvent(const KeyEvent& event)
	{
		return Ignore;
	}

	ResponseType Stack::ContextMenuPressEvent(const ContextMenuEvent& event)
	{
		return Ignore;
	}

	ResponseType Stack::ContextMenuReleaseEvent(const ContextMenuEvent& event)
	{
		return Ignore;
	}

	ResponseType Stack::MousePressEvent(const MouseEvent& event)
	{
		return Ignore;
	}

	ResponseType Stack::MouseReleaseEvent(const MouseEvent& event)
	{
		return Ignore;
	}

	ResponseType Stack::MouseMoveEvent(const MouseEvent& event)
	{
		return IgnoreAndContinue;
	}

}