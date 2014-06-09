#ifndef _TEXTUREATLASTEST1_HPP_
#define _TEXTUREATLASTEST1_HPP_

#include <gtest/gtest.h>
#include <Common/Window.hpp>
#include <BlendInt/Core/Object.hpp>

class TextureAtlasTest1: public testing::Test
{
public:
	TextureAtlasTest1 ();
	virtual ~TextureAtlasTest1 ();

protected:

	virtual void SetUp ()
	{
#ifdef DEBUG
		ASSERT_TRUE(BlendInt::Object::CheckAllocatedObjects());
#endif
	}

	virtual void TearDown ()
	{
#ifdef DEBUG
		ASSERT_TRUE(BlendInt::Object::CheckAllocatedObjects());
#endif
	}
};

#endif  // _TEXTUREATLASTEST1_HPP_