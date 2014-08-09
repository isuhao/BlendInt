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

#include <BlendInt/Gui/HBlock.hpp>

namespace BlendInt {

	HBlock::HBlock ()
	: AbstractContainer()
	{
		set_size(100, 20);
		set_margin(0, 0, 0, 0);
	}
	
	HBlock::~HBlock ()
	{
	}
	
	void HBlock::PushBack (AbstractWidget* widget)
	{
		AbstractWidget* orig_last = last();

		if(PushBackSubWidget(widget)) {

			widget->SetEmboss(true);
			FillInHBlock(position(), size(), margin());

			if(orig_last) {
				orig_last->SetRoundCornerType(orig_last->round_type() & ~(RoundTopRight | RoundBottomRight));
				widget->SetRoundCornerType(RoundTopRight | RoundBottomRight);
			} else {
				widget->SetRoundCornerType(RoundAll);
			}

		}
	}
	
	bool HBlock::IsExpandX () const
	{
		bool expand = false;

		for(AbstractWidget* p = first(); p; p = p->next())
		{
			if(p->IsExpandX()) {
				expand = true;
				break;
			}
		}

		return expand;
	}

	bool HBlock::IsExpandY () const
	{
		bool expand = false;

		for(AbstractWidget* p = first(); p; p = p->next())
		{
			if(p->IsExpandY()) {
				expand = true;
				break;
			}
		}

		return expand;
	}
	
	Size HBlock::GetPreferredSize () const
	{
		Size preferred_size;

		if(first() == 0) {

			preferred_size.set_width(100);
			preferred_size.set_height(20);

		} else {

			Size tmp;
			int max_width = 0;
			int max_height = 0;
			int sum = 0;

			for(AbstractWidget* p = first(); p; p = p->next())
			{
				if(p->visiable()) {
					tmp = p->GetPreferredSize();

					sum++;
					max_width = std::max(max_width, tmp.width());
					max_height = std::max(max_height, tmp.height());
				}
			}
			preferred_size.set_width(sum * (max_width - 1));
			preferred_size.set_height(max_height);

			preferred_size.add_width(margin().hsum());
			preferred_size.add_height(margin().vsum());
		}

		return preferred_size;
	}
	
	void HBlock::PerformMarginUpdate(const Margin& request)
	{
		FillInHBlock(position(), size(), request);
	}

	bool HBlock::SizeUpdateTest (const SizeUpdateRequest& request)
	{
		// Do not allow sub widget changing its size
		if(request.source()->container() == this) {
			return false;
		}

		return true;
	}

	bool HBlock::PositionUpdateTest (const PositionUpdateRequest& request)
	{
		// Do not allow sub widget changing its position
		if(request.source()->container() == this) {
			return false;
		}

		return true;
	}

	void HBlock::PerformSizeUpdate(const SizeUpdateRequest& request)
	{
		if(request.target() == this) {
			set_size(*request.size());
			FillInHBlock(position(), *request.size(), margin());
		}

		ReportSizeUpdate(request);
	}
	
	void HBlock::PerformPositionUpdate(const PositionUpdateRequest& request)
	{
		if (request.target() == this) {
			int x = request.position()->x() - position().x();
			int y = request.position()->y() - position().y();

			set_position(*request.position());

			MoveSubWidgets(x, y);
		}

		ReportPositionUpdate(request);
	}

	ResponseType HBlock::Draw (const Profile& profile)
	{
		return Ignore;
	}
	
	ResponseType HBlock::CursorEnterEvent (bool entered)
	{
		return Ignore;
	}
	
	ResponseType HBlock::KeyPressEvent (const KeyEvent& event)
	{
		return Ignore;
	}
	
	ResponseType HBlock::ContextMenuPressEvent (const ContextMenuEvent& event)
	{
		return Ignore;
	}
	
	ResponseType HBlock::ContextMenuReleaseEvent (const ContextMenuEvent& event)
	{
		return Ignore;
	}
	
	ResponseType HBlock::MousePressEvent (const MouseEvent& event)
	{
		return Ignore;
	}
	
	ResponseType HBlock::MouseReleaseEvent (const MouseEvent& event)
	{
		return Ignore;
	}
	
	ResponseType HBlock::MouseMoveEvent (const MouseEvent& event)
	{
		return Ignore;
	}

	void HBlock::FillInHBlock (const Point& out_pos, const Size& out_size,
					const Margin& margin)
	{
		int x = out_pos.x() + margin.left();
		int y = out_pos.y() + margin.bottom();
		int w = out_size.width() - margin.hsum();
		int h = out_size.height() - margin.vsum();

		FillInHBlock(x, y, w, h);
	}

	void HBlock::FillInHBlock (int x, int y, int w, int h)
	{
		int count = widget_count();
		if(count == 0) return;
		int average_width = w / count + 1;

		for(AbstractWidget* p = first(); p; p = p->next())
		{
			ResizeSubWidget(p, average_width, h);
			SetSubWidgetPosition(p, x, y);
			x = x + average_width - 1;
		}
	}

}
