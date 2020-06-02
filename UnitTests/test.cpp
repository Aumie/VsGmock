#include "pch.h"
#include <gmock/gmock.h>
#include "../GG/Mathh.h"
TEST(TestCaseName, TestName) {
	auto m = new Mathh();
  EXPECT_EQ(m->add(1,1), 2);
}