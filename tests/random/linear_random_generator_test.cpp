#include "gtest/gtest.h"
#include "src/random/linear_number_generator.h"

TEST(Random_generators_tests, default_linear_generator_test) {
    LinearNumberGenerator LNG;
    ASSERT_EQ(LNG.get_number_of_generations(), 0);
    ASSERT_EQ(LNG.random(), 595905495);
    ASSERT_EQ(LNG.get_number_of_generations(), 1);

    LNG.set_seed(12345);
    ASSERT_EQ(LNG.get_number_of_generations(), 0);
    ASSERT_EQ(LNG.random(), 595905495);
    ASSERT_EQ(LNG.get_number_of_generations(), 1);
    ASSERT_NE(LNG.random(), 595905495);
}

TEST(Random_generators_tests, custom_linear_generator_test) {
    LinearNumberGenerator LNG(1, 999, 3, 4);
    ASSERT_EQ(LNG.random(), 7);
    ASSERT_EQ(LNG.random(), 25);
    ASSERT_EQ(LNG.random(), 79);
    ASSERT_EQ(LNG.random(), 241);
    ASSERT_EQ(LNG.get_number_of_generations(), 4);
    ASSERT_NE(LNG.get_base_seed(), LNG.get_seed());
}
