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

#ifndef _BLENDINT_FONT_PATTERN_HPP_
#define _BLENDINT_FONT_PATTERN_HPP_

#include <fontconfig/fontconfig.h>

#include <BlendInt/Core/Object.hpp>

#include <BlendInt/Font/FcCharSet.hpp>

namespace BlendInt {

	namespace Fc {

		class Pattern: public Object
		{
		public:

			// the p must be created through FcPatternCreate;
			Pattern (::FcPattern* p = 0)
			: Object(),
			  pattern_(p)
			{
				if(pattern_ == 0)
					pattern_ = FcPatternCreate();
			}

			Pattern (const Pattern& p)
			: Object(),
			  pattern_(0)
			{
				pattern_ = p.pattern_;

				if(pattern_)
					FcPatternReference(pattern_);
			}

			virtual ~Pattern ()
			{
				FcPatternDestroy(pattern_);
			}

			inline Pattern& operator = (const Pattern& orig)
			{
				if(pattern_)
					FcPatternDestroy(pattern_);

				pattern_ = orig.pattern_;

				if(pattern_)
					FcPatternReference(pattern_);

				return *this;
			}

			inline bool add (const char* object, FcValue value, bool append = true)
			{
				return FcPatternAdd(pattern_, object, value, append ? FcTrue : FcFalse);
			}

			inline bool add (const char* object, int i)
			{
				return FcPatternAddInteger(pattern_, object, i);
			}

			inline bool add (const char* object, double d)
			{
				return FcPatternAddDouble(pattern_, object, d);
			}

			// add string
			inline bool add (const char* object, const FcChar8* s)
			{
				return FcPatternAddString(pattern_, object, s);
			}

			inline bool add (const char* object, const FcMatrix* m)
			{
				return FcPatternAddMatrix(pattern_, object, m);
			}

			inline bool add (const char* object, const CharSet& c)
			{
				return FcPatternAddCharSet(pattern_, object, c.charset());
			}

			inline bool add (const char* object, bool b)
			{
				return FcPatternAddBool(pattern_, object, b ? FcTrue : FcFalse);
			}

			inline bool add (const char *object, const FcLangSet *l)
			{
				return FcPatternAddLangSet (pattern_, object, l);
			}

			inline FcResult get (const char* object, int id, FcValue* v)
			{
				return FcPatternGet(pattern_, object, id, v);
			}

			inline bool remove (const char* object, int id)
			{
				return FcPatternRemove(pattern_, object, id);
			}

			inline void default_substitute ()
			{
				FcDefaultSubstitute(pattern_);
			}

			inline void print ()
			{
				FcPatternPrint(pattern_);
			}

			inline operator bool () const
			{
				return pattern_ != 0;
			}

			::FcPattern* pattern () const {return pattern_;}

			inline static Pattern duplicate (const Pattern& pattern);

		private:

			friend inline bool operator == (const Pattern& pa, const Pattern& pb);

			::FcPattern* pattern_;

		};

		inline bool operator == (const Pattern& pa, const Pattern& pb)
		{
			return FcPatternEqual(pa.pattern_, pb.pattern_);
		}

	}

}

#endif /* _BLENDINT_FONT_PATTERN_HPP_ */