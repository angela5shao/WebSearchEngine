#include "alistint.h"
#include "gtest/gtest.h"

class ArrayListTest : public testing::Test {
protected: // You can remove any or all of the following functions if its body is empty.

	ArrayListTest() { // do set-up work for each test here.
	}

	virtual ~ArrayListTest() { // do clean-up work that doesn't throw exceptions
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() { // called immediately after constructor (right before each test)
		list1.insert(0, 10);
		list1.insert(1, 11);
		list1.insert(2, 12);
	}

	virtual void TearDown() { // called immediately after each test (right before destructor)
	}

	// Objects declared here can be used by all tests in the test case.
	AListInt list1;
	AListInt list2;
};

TEST_F(ArrayListTest, Copy) { // delete list1 to fully test!!
	AListInt* listA = new AListInt;
	for (int j=0; j<5; j++) {
		listA->insert(j, 10+j);
	}

	list2 = AListInt(*listA);
	delete listA;

	for (int i = 0 ; i < 5; i++) {
		EXPECT_EQ(list2.get(i), 10+i);
	}
}

TEST_F(ArrayListTest, Assign) { // delete list1 to fully test!!
	AListInt* listA = new AListInt;
	for (int j=0; j<5; j++) {
		listA->insert(j, 10+j);
	}

	list2 = *listA;
	delete listA;

	for (int i = 0 ; i < 5; i++) {
		EXPECT_EQ(list2.get(i), 10+i);
	}
}
/*
TEST_F(ArrayListTest, Destructor) {
	
}*/

TEST_F(ArrayListTest, theSize) {
	EXPECT_EQ(list1.size(), 3);
	EXPECT_EQ(list2.size(), 0);
}

TEST_F(ArrayListTest, Empty) {
	EXPECT_TRUE(list2.empty());
	EXPECT_TRUE(!list1.empty());
}

TEST_F(ArrayListTest, Insert) {
	list2.insert(-1, 10); // out of bounds
	EXPECT_EQ(list2.size(), 0);
	list2.insert(1, 10); // out of bounds
	EXPECT_EQ(list2.size(), 0);

	list2.insert(0, 100);
	EXPECT_EQ(list2.size(), 1);

	for (int i=1; i<5; i++) list2.insert(i, 100+i);
	EXPECT_EQ(list2.size(), 5);
	
	list2.insert(5, 105); // resize
	EXPECT_EQ(list2.size(), 6);
}

TEST_F(ArrayListTest, Remove) {
	list2.remove(0); // empty
	EXPECT_EQ(list2.size(), 0);

	list2.insert(0, 100); 
	list2.remove(1); // out of bounds
	EXPECT_EQ(list2.size(), 1);
	list2.remove(-1);
	EXPECT_EQ(list2.size(), 1);

	list2.remove(0);
	EXPECT_EQ(list2.size(), 0);
}

TEST_F(ArrayListTest, Set) {
	list1.set(0, 555);
	EXPECT_EQ(list1.size(), 3);
	EXPECT_EQ(list1.get(1), 11);
	EXPECT_EQ(list1.get(0), 555);

	list1.set(5, 111); // out of bounds
	EXPECT_EQ(list1.size(), 3);
}

TEST_F(ArrayListTest, Get) {
	EXPECT_EQ(list1.get(0), 10);
	EXPECT_EQ(list1.get(4), 10);
}

TEST_F(ArrayListTest, Concatenate) {
	AListInt bigList = list1 + list2;
	EXPECT_EQ(bigList.size(), 3);

	list2.insert(0, 333);
	AListInt bigList2 = list2 + list1;
	EXPECT_EQ(bigList2.size(), 4);
}

TEST_F(ArrayListTest, Access) {
	EXPECT_EQ(list1[3], 10);
	EXPECT_EQ(list1[2], 12);
	EXPECT_EQ(list1[6], 10);
}