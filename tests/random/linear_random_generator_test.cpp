#include "gtest/gtest.h"
#include "src/random/linear_number_generator.h"

TEST(Random_generators_tests, linear_generator_test) {
    LinearNumberGenerator LNG;
    ASSERT_EQ(LNG.get_number_of_generations(), 0);
    ASSERT_EQ(LNG.random(), 27087);
    ASSERT_EQ(LNG.get_number_of_generations(), 1);

    LNG.set_seed(1234);
    ASSERT_EQ(LNG.get_number_of_generations(), 0);
    ASSERT_EQ(LNG.random(), 27087);
    ASSERT_EQ(LNG.get_number_of_generations(), 1);
    ASSERT_NE(LNG.random(), 27087);
}
