#include "alistint.h"

class ArrayListTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	ArrayListTest() {
		// You can do set-up work for each test here.
	}

	virtual ~ArrayListTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		AListInt list1;
		list1.insert(0, 10);
		list1.insert(1, 11);
		list1.insert(2, 12);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	//AListInt list1;
};

TEST_F(ArrayListTest, Copy) {
	AListInt* list2 = new AListInt(list1);
	for (int i = 0 ; i < list.size(); i++) {
		EXPECT_EQ(list2.get(i), list1.get(i));
	}
}