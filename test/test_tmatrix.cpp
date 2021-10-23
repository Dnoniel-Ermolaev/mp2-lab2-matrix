#include "utmatrix.h"
#include <iostream>
#include <gtest.h>

class TestMatrix : public ::testing::Test
{
protected:
	TMatrix<int> m1;
	TMatrix<int> m2;
	int RAND = rand();
public:
	TestMatrix() : m1(4), m2(4)
	{
		m1[0][0] = RAND+10;
		m1[0][1] = RAND+20;
		m1[0][2] = RAND+30;
		m1[0][3] = RAND+100;
		m1[1][1] = RAND+40;
		m1[1][2] = RAND+50;
		m1[1][3] = RAND+150;
		m1[2][2] = RAND+60;
		m1[2][3] = RAND+200;
		m1[3][3] = RAND+250;
		for (int i = 0; i < m1.GetSize(); i++)
			for (int j = i; j < m1.GetSize(); j++)
				m2[i][j] = 10;
	}
	~TestMatrix() {}
};

TEST(TMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
	TMatrix<int> m(5);

	ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST_F(TestMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m0(m1);
	EXPECT_EQ(m1, m0);
}

TEST_F(TestMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m0(m1);
	EXPECT_EQ(m1, m0);
	EXPECT_NE(&(m1), &(m0));
}

TEST_F(TestMatrix, can_get_size)
{
	EXPECT_EQ(4, m1.GetSize());
}

TEST_F(TestMatrix, can_set_and_get_element)
{
	m1[0][1] = 56;
	EXPECT_EQ(56, m1[0][1]);
}

TEST_F(TestMatrix, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW(m1[0][-1] = 5);
}

TEST_F(TestMatrix, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(m1[0][9] = 5);
}

TEST_F(TestMatrix, can_assign_matrix_to_itself)
{
	ASSERT_NO_THROW(m1 = m1);
}

TEST_F(TestMatrix, can_assign_matrices_of_equal_size)
{
	ASSERT_NO_THROW(m1 = m2);
}

TEST_F(TestMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m0(1);
	m0 = m1;
	EXPECT_EQ(4, m0.GetSize());
}

TEST_F(TestMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m0(1);
	m0 = m1;
	EXPECT_EQ(m0, m1);
}

TEST_F(TestMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m0(1);
	m0 = m1;
	EXPECT_EQ(1, m1 == m0);
}

TEST_F(TestMatrix, compare_matrix_with_itself_return_true)
{
	EXPECT_EQ(1, m1 == m1);
}

TEST_F(TestMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m0(1);
	EXPECT_NE(m0, m1);
}

TEST_F(TestMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> res(4);
	res[0][0] = RAND + 10 +10;
	res[0][1] = RAND + 20 +10;
	res[0][2] = RAND + 30 +10;
	res[0][3] = RAND + 100 +10;
	res[1][1] = RAND + 40 +10;
	res[1][2] = RAND + 50 +10;
	res[1][3] = RAND + 150 +10;
	res[2][2] = RAND + 60 +10;
	res[2][3] = RAND + 200 +10;
	res[3][3] = RAND + 250 +10;
	EXPECT_EQ(res, m1 + m2);
}

TEST_F(TestMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m0(1);
	m0[0][0] = 4;
	ASSERT_ANY_THROW(m1 + m0);
}

TEST_F(TestMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> res(4);
	res[0][0] = RAND + 10 -10;
	res[0][1] = RAND + 20 -10;
	res[0][2] = RAND + 30 -10;
	res[0][3] = RAND + 100 -10;
	res[1][1] = RAND + 40 -10;
	res[1][2] = RAND + 50 -10;
	res[1][3] = RAND + 150 -10;
	res[2][2] = RAND + 60 -10;
	res[2][3] = RAND + 200 -10;
	res[3][3] = RAND + 250 -10;
	EXPECT_EQ(res, m1 - m2);
}

TEST_F(TestMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m0(1);
	m0[0][0] = 4;
	ASSERT_ANY_THROW(m1 - m0);
}