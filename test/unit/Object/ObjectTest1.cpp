#include "ObjectTest1.hpp"
#include <BlendInt/Core/Object.hpp>

#include <iostream>

using namespace BlendInt;

ObjectTest1::ObjectTest1()
: testing::Test()
{
	// TODO: add constructor code
}

ObjectTest1::~ObjectTest1()
{
	// TODO: add destructor code
}

/**
 * test new Object 
 *
 * Expected result: 
 */
TEST_F(ObjectTest1, New1)
{
	// TODO: add test code here
    ObjectPtr obj1 = Object::Create();

    ObjectPtr obj2 = Object::Create();

    obj2 = obj1;

    std::cout << "Object ref count: " << obj1->ref_count() << std::endl;

	ASSERT_TRUE(true);
}

