#include "gtest/gtest.h"

TEST(Sample_tests, addition_test) {
    int addend_a = 2;
    int addend_b = 3;

    int sum = addend_a + addend_b;

    EXPECT_EQ (sum, 5);
}
