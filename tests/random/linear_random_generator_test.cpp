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

TEST(Random_generators_tests, linear_generator_upper_bound_test) {
    LinearNumberGenerator LNG;

    int upper_bound = 123;
    for(int i=0; i<12345; ++i) {
        ASSERT_LT(LNG.random(upper_bound), upper_bound);
    }
}

TEST(Random_generators_tests, linear_generator_lower_and_upper_bound_test) {
    LinearNumberGenerator LNG;

    int lower_bound = 13;
    int upper_bound = 123;
    for(int i=0; i<12345; ++i) {
        int random_value = LNG.random(lower_bound, upper_bound);
        ASSERT_LT(random_value, upper_bound);
        ASSERT_GE(random_value, lower_bound);
    }
}
