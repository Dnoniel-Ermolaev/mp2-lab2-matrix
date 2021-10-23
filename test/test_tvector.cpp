#include "utmatrix.h"

#include <gtest.h>

class TesVector : public ::testing::Test
{
protected:
	TVector<int> v1;
	TVector<int> v2;
public:
	TesVector() : v1(3), v2(3)
	{
		v1[0] = 1;
		v1[1] = 2;
		v1[2] = 3;
		for (int i = 0; i < v1.GetSize(); i++)
			v2[i] = 4;
	}
	~TesVector() {}
};

TEST(TVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
	ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
	TVector<int> v(10);

	ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST_F(TesVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> v0(v1);
	EXPECT_EQ(v0, v1);
}

TEST_F(TesVector, copied_vector_has_its_own_memory)
{
	TVector<int> v0(v1);
	EXPECT_NE(&v0, &v1);
}

TEST(TVector, can_get_size)
{
	TVector<int> v(4);
	EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
	TVector<int> v(4, 2);
	EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(4);
	v[0] = 4;
	EXPECT_EQ(4, v[0]);
}

TEST_F(TesVector, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW(v1[-1]);
}

TEST_F(TesVector, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(v1[9]);
}

TEST_F(TesVector, can_assign_vector_to_itself)
{
	ASSERT_NO_THROW(v1 = v2);
}

TEST_F(TesVector, can_assign_vectors_of_equal_size)
{
	v1 = v2;
	EXPECT_EQ(v1, v2);
}

TEST_F(TesVector, assign_operator_change_vector_size)
{
	EXPECT_EQ(v1.GetSize(), 3);
}

TEST_F(TesVector, can_assign_vectors_of_different_size)
{
	TVector<int> v0(1);
	v0[0] = 9;
	v0 = v1;
	EXPECT_EQ(v0, v1);
}

TEST_F(TesVector, compare_equal_vectors_return_true)
{
	TVector<int> v0(1);
	v0[0] = 9;
	v0 = v1;
	EXPECT_EQ(1, v0 == v1);
}

TEST_F(TesVector, compare_vector_with_itself_return_true)
{
	EXPECT_EQ(1, v1 == v1);
}

TEST_F(TesVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> v0(1);
	v0[0] = 9;
	EXPECT_NE(v1, v0);
}

TEST_F(TesVector, can_add_scalar_to_vector)
{
	TVector<int> res(3);
	res[0] = 1 + 2;
	res[1] = 2 + 2;
	res[2] = 3 + 2;
	EXPECT_EQ(res, v1 + 2);
}

TEST_F(TesVector, can_subtract_scalar_from_vector)
{
	TVector<int> res(3);
	res[0] = 1 - 2;
	res[1] = 2 - 2;
	res[2] = 3 - 2;
	EXPECT_EQ(res, v1 - 2);
}

TEST_F(TesVector, can_multiply_scalar_by_vector)
{
	TVector<int> res(3);
	res[0] = 1 * 2;
	res[1] = 2 * 2;
	res[2] = 3 * 2;
	EXPECT_EQ(res, v1 * 2);
}

TEST_F(TesVector, can_add_vectors_with_equal_size)
{
	TVector<int> res(3);
	res[0] = 1 + 4;
	res[1] = 2 + 4;
	res[2] = 3 + 4;
	EXPECT_EQ(res, v1 + v2);
}

TEST_F(TesVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v0(1);
	v0[0] = 9;
	ASSERT_ANY_THROW(v0 + v1);
}

TEST_F(TesVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> res(3);
	res[0] = 1 - 4;
	res[1] = 2 - 4;
	res[2] = 3 - 4;
	EXPECT_EQ(res, v1 - v2);
}

TEST_F(TesVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v0(1);
	v0[0] = 9;
	ASSERT_ANY_THROW(v0 - v1);
}

TEST_F(TesVector, can_multiply_vectors_with_equal_size)
{
	EXPECT_EQ(24, v1 * v2);
}

TEST_F(TesVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v0(1);
	v0[0] = 9;
	ASSERT_ANY_THROW(v0 * v1);
}