#include <gtest.h>
#include "node.h"

TEST(list, can_create_list) {
	ASSERT_NO_THROW(List<int> l);
}

TEST(list, can_copy_list) {
	List<int> l1;
	ASSERT_NO_THROW(List<int> l2(l1));
}

TEST(list, can_get_element) {
	List<int> l1;
	int num = 3;
	l1.push_back(num);
	EXPECT_EQ(l1.head()->data, 3);
}

TEST(list, can_sort) {
	List<int> l1;
	int num = 3;
	int num1 = 2;
	int num2 = 1;
	l1.push_back(num2);
	l1.push_back(num1);
	l1.push_back(num);
	l1.sort();
	
	bool flag = 1;
	auto i = l1.head();
	while (i->next != nullptr)
	{
		auto j = i->next;
		if (i->data < j->data)
			flag = 0;
		i = j;
	}
	EXPECT_EQ(flag, 1);
}




