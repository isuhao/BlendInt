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

#include <GL/glew.h>

#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>

#include <BlendInt/AbstractWidget.hpp>
#include <BlendInt/ContextManager.hpp>
#include <BlendInt/AbstractLayout.hpp>

namespace BlendInt {

	using namespace std;

	AbstractWidget::AbstractWidget ()
		: m_z(0),
		  m_in_layout(false),
		  m_expand_x(false),
		  m_expand_y(false),
		  m_fire_events(true),
		  m_visible(true)
#ifdef DEBUG
		  ,m_id(0)
#endif

	{
#ifdef DEBUG
		// generate a unique id
		uint64_t temp = id_last;

		while (AbstractWidget::obj_map.count(id_last) == 1) {
			id_last++;
			if (temp == id_last)
				throw std::out_of_range("Cannot assign unique id for object");
		}

		m_id = id_last;

		register_in_map();
		id_last++;
#endif
	}


	AbstractWidget::AbstractWidget (AbstractWidget* parent)
		: m_z(0),
		  m_in_layout(false),
		  m_expand_x(false),
		  m_expand_y(false),
		  m_fire_events(true),
		  m_visible(true)
#ifdef DEBUG
		  , m_id(0)
#endif

	{
		bind_to(parent);

#ifdef DEBUG
		// generate a unique id
		uint64_t temp = id_last;

		while (AbstractWidget::obj_map.count(id_last) == 1) {
			id_last++;
			if (temp == id_last)
				throw std::out_of_range("Cannot assign unique id for object");
		}

		m_id = id_last;

		register_in_map();
		id_last++;
#endif

	}

	AbstractWidget::~AbstractWidget ()
	{
		if(m_parent.object.nameless) {
			if(m_parent.type == ParentContextManager) {
				ContextManager::instance()->unbind(this);
			}
			if(m_parent.type == ParentForm) {
				m_parent.object.form->m_children.erase(this);
			}
		}

		// delete all child objects in list
		std::set<AbstractWidget*>::iterator it;
		for(it = m_children.begin(); it != m_children.end(); it++)
		{
			// MUST set the m_parent to avoid double set::erase in child's destruction
			(*it)->m_parent.type = ParentUnknown;
			(*it)->m_parent.object.nameless = 0;
			delete *it;
		}

		m_children.clear();

#ifdef DEBUG
		unregister_from_map();
#endif
	}

	bool AbstractWidget::bind (AbstractWidget* child)
	{
		if (!child) return false;
		if (child == this) return false;	// cannot bind self

		if (child->m_z != m_z) {
			std::cerr << "Cannot bind a child in different layer" << std::endl;
			// TODO throw an exception
			return false;
		}

		if (child->m_parent.object.nameless) {
			if (child->m_parent.type == ParentContextManager) {
				ContextManager::instance()->unbind(child);
			}
			if (child->m_parent.type == ParentForm) {
				if(child->m_parent.object.form == this) return true;
				child->m_parent.object.form->m_children.erase(child);
			}
		}
		child->m_parent.type = ParentForm;
		child->m_parent.object.form = this;

		m_children.insert(child);

		return true;
	}

	bool AbstractWidget::unbind (AbstractWidget* child)
	{
		if(!child) return false;
		if(child == this) return false;

		if(!m_children.count(child))
			return false;

		child->m_parent.type = ParentUnknown;
		child->m_parent.object.nameless = 0;

		m_children.erase(child);

		return true;
	}

	void AbstractWidget::unbind ()
	{
		if (m_parent.object.nameless) {
			if (m_parent.type == ParentContextManager) {
				ContextManager::instance()->unbind(this);
			}
			if (m_parent.type == ParentForm) {
				m_parent.object.form->m_children.erase(this);
			}
		}

		m_parent.type = ParentUnknown;
		m_parent.object.nameless = 0;
	}

	bool AbstractWidget::bind_to (ContextManager *parent)
	{
		if(!parent) return false;

		if (m_parent.object.nameless) {
			if (m_parent.type == ParentForm) {
				m_parent.object.form->m_children.erase(this);
				m_parent.type = ParentUnknown;
				m_parent.object.nameless = 0;
			}
		}

		parent->bind(this);

		return true;
	}

	bool AbstractWidget::bind_to (AbstractWidget* parent)
	{
		if(!parent) return false;
		if(parent == this) return false;	// cannot bind_to self

		if(parent->m_z != m_z) {
			std::cerr << "Cannot bind to a parent in different layer" << std::endl;
			// TODO: throw an exception
			return false;
		}

		if (m_parent.object.nameless) {
			if (m_parent.type == ParentContextManager) {
				m_parent.object.context->unbind(this);
			}
			if (m_parent.type == ParentForm) {
				if (m_parent.object.form == parent) return true;

				m_parent.object.form->m_children.erase(this);
			}
		}

		parent->m_children.insert (this);
		m_parent.type = ParentForm;
		m_parent.object.form = parent;

		return true;
	}

	bool AbstractWidget::is_bound ()
	{
		Parent* parent = &m_parent;
		while (parent->type == ParentForm) {
			parent = &(parent->object.form->m_parent);
		}

		if (parent->type == ParentUnknown) return false;

		// return true if parent type is Context Manager
		return true;
	}

//	const Size& AbstractWidget::size () const
//	{
//		return m_size;
//	}

	void AbstractWidget::resize (unsigned int width, unsigned int height)
	{
		// If the object is managed by a layout, disallow position setting
		if(m_in_layout) return;

		Size new_size (width, height);

		if (size() == new_size) return;

		if(width < m_minimal_size.width() ||
				height < m_minimal_size.height())
			return;

		update(FormPropertySize, &new_size);

		AbstractForm::resize(new_size);

		fire_property_changed_event(FormPropertySize);
	}

	void AbstractWidget::resize (const Size& size)
	{
		// If the object is managed by a layout, disallow position setting
		if(m_in_layout) return;

		if(size.width() < m_minimal_size.width() ||
				size.height() < m_minimal_size.height())
			return;

		if (AbstractForm::size() == size) return;

//		Size new_size = size;
//
		update(FormPropertySize, &size);

		AbstractForm::resize(size);

		fire_property_changed_event(FormPropertySize);
	}

	void AbstractWidget::set_preferred_size(const Size& size)
	{
		// check the param first
		if (size.width() < m_minimal_size.width() ||
				size.height() < m_minimal_size.height())
			return;

		if(m_preferred_size.equal(size)) return;

		Size new_preferred_size = size;

		update(FormPropertyPreferredSize, &new_preferred_size);

		m_preferred_size = new_preferred_size;

		fire_property_changed_event(FormPropertyPreferredSize);
	}

	void AbstractWidget::set_preferred_size(unsigned int width, unsigned int height)
	{
		// check the param first
		if(width < m_minimal_size.width() ||
				height < m_minimal_size.height())
			return;

		if(m_preferred_size.equal(width, height)) return;

		Size new_preferred_size(width, height);

		update(FormPropertyPreferredSize, &new_preferred_size);

		m_preferred_size = new_preferred_size;

		fire_property_changed_event(FormPropertyPreferredSize);
	}

	void AbstractWidget::set_minimal_size(const Size& size)
	{
		// If the object is managed by a layout, disallow position setting
		if(m_in_layout) return;

		if (m_minimal_size.equal(size)) return;

		if(size.width() > m_preferred_size.width() ||
				size.height() > m_preferred_size.height())
			return;

		Size new_minimal_size = size;

		update(FormPropertyMinimalSize, &new_minimal_size);

		m_minimal_size = new_minimal_size;

		fire_property_changed_event(FormPropertyMinimalSize);
	}

	void AbstractWidget::set_minimal_size(unsigned int width, unsigned int height)
	{
		// If the object is managed by a layout, disallow position setting
		if(m_in_layout) return;

		if (m_minimal_size.equal(width, height)) return;

		if(width > m_preferred_size.width() ||
				height > m_preferred_size.height())
			return;

		Size new_minimal_size(width, height);

		update(FormPropertyMinimalSize, &new_minimal_size);

		m_minimal_size = new_minimal_size;

		fire_property_changed_event(FormPropertyMinimalSize);
	}

	void AbstractWidget::set_position (int x, int y)
	{
		// If the object is managed by a layout, disallow position setting
		if(m_in_layout) return;

		Point new_position(x, y);

		if (position() == new_position) return;

		update(FormPropertyPosition, &new_position);

		AbstractForm::set_position(x, y);

		fire_property_changed_event(FormPropertyPosition);
	}

	void AbstractWidget::set_position (const Point& pos)
	{
		// If the object is managed by a layout, disallow position setting
		if(m_in_layout) return;

		if (position() == pos) return;

		update(FormPropertyPosition, &pos);

		AbstractForm::set_position(pos);

		fire_property_changed_event(FormPropertyPosition);
	}

	void AbstractWidget::reset_z (int z)
	{
		if (m_z == z) return;

		AbstractWidget* root = 0;
		Parent* parent = &m_parent;
		while (parent->type == ParentForm) {
			root = parent->object.form;
			parent = &(parent->object.form->m_parent);
		}

		if (root)
			root->set_z_simple(z);
		else
			set_z_simple(z);

		if(root) {
			if (root->m_parent.type == ParentContextManager) {
					ContextManager::instance()->bind(root);
			}
		} else {
			if (m_parent.type == ParentContextManager) {
					ContextManager::instance()->bind(this);
			}
		}

		// m_property_changed.fire(FormPropertyLayer);
	}

	void AbstractWidget::set_visible (bool visible)
	{
		m_visible = visible;
	}

	void AbstractWidget::show ()
	{
		m_visible = true;
	}

	void AbstractWidget::hide ()
	{
		m_visible = false;
	}

	const std::string& AbstractWidget::name () const
	{
		return m_name;
	}

	void AbstractWidget::set_name (const std::string& name)
	{
		m_name = name;
	}

	bool AbstractWidget::contain(const Coord2d& cursor)
	{
		if (cursor.x() < position().x() ||
				cursor.y() < position().y() ||
				cursor.x() > (position().x() + size().width()) ||
				cursor.y() > (position().y() + size().height())) {
			return false;
		}

		return true;
	}

	void AbstractWidget::set_z_simple (int z)
	{
		m_z = z;

		std::set<AbstractWidget*>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); it++)
		{
			(*it)->set_z_simple (z);
		}

		// TODO: call update()
	}

	void AbstractWidget::set_pos_priv (AbstractWidget* obj, int x, int y)
	{
		if (obj->position().x() == x && obj->position().y() == y) return;

		obj->set_position(x, y);
		AbstractForm::set_position(obj, x, y);
	}

	void AbstractWidget::set_pos_priv (AbstractWidget* obj, const Point& pos)
	{
		if (obj->position() == pos) return;
		AbstractForm::set_position(obj, pos);
	}

	void AbstractWidget::resize_priv (AbstractWidget* obj, unsigned int width, unsigned int height)
	{
		if (obj->size().width() == width && obj->size().height() == height) return;

		if(width < obj->m_minimal_size.width() ||
				height < obj->m_minimal_size.height())
			return;

		Size new_size (width, height);

		obj->update(FormPropertySize, &new_size);

		AbstractForm::resize(obj, width, height);

		obj->fire_property_changed_event(FormPropertySize);
	}

	void AbstractWidget::resize_priv (AbstractWidget* obj, const Size& size)
	{
		if (obj->size() == size) return;

		if(size.width() < obj->m_minimal_size.width() ||
				size.height() < obj->m_minimal_size.height())
			return;

		Size new_size = size;

		obj->update(FormPropertySize, &new_size);

		AbstractForm::resize(obj, new_size);

		obj->fire_property_changed_event(FormPropertySize);
	}

#ifdef DEBUG

	uint64_t AbstractWidget::id_last = 1;

	map<uint64_t, AbstractWidget*> AbstractWidget::obj_map;

	inline bool AbstractWidget::register_in_map ()
	{
		AbstractWidget::obj_map[m_id] = this;
		return true;
	}

	inline bool AbstractWidget::unregister_from_map ()
	{
		AbstractWidget::obj_map.erase(m_id);
		return true;
	}

	AbstractWidget* AbstractWidget::find (uint64_t id)
	{
		AbstractWidget *ret = NULL;
		if (AbstractWidget::obj_map.count(id) == 1)
			ret = AbstractWidget::obj_map[id];

		return ret;
	}

	void AbstractWidget::print()
	{
		map<uint64_t, AbstractWidget*>::iterator it;
		std::cerr << "Print objects: "<< std::endl;
		for(it = obj_map.begin(); it != obj_map.end(); it++)
		{
			std::cerr << it->second->m_name << " ";
		}
		std::cerr << std::endl;

	}

#endif

} /* namespace BlendInt */
