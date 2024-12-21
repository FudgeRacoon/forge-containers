#ifndef STATIC_ARRAY_TESTS_HPP
#define STATIC_ARRAY_TESTS_HPP

#include <gtest/gtest.h>

#include <Collections/StaticArray.hpp>

using namespace Forge;

class StaticArrayTest : public testing::Test
{
public:
	using DEFAULT_TYPE = I32;

public:
	static constexpr Size DEFAULT_COUNT = 5;
	static constexpr Size DEFAULT_CAPACITY = 10;
	static constexpr Size DEFAULT_SIZE = DEFAULT_CAPACITY * sizeof(DEFAULT_TYPE);

public:
	DEFAULT_TYPE DEFAULT_VALUE = 12;
	DEFAULT_TYPE DEFAULT_BUFFER[DEFAULT_CAPACITY] = { 1, 2, 3, 4, 5, 0, 0, 0, 0, 0 };

protected:
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> fixture_full_array;
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> fixture_empty_array;
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> fixture_nonempty_array;

protected:
	Void SetUp() override
	{
		fixture_full_array.PushBack(1);
		fixture_full_array.PushBack(2);
		fixture_full_array.PushBack(3);
		fixture_full_array.PushBack(4);
		fixture_full_array.PushBack(5);
		fixture_full_array.PushBack(6);
		fixture_full_array.PushBack(7);
		fixture_full_array.PushBack(8);
		fixture_full_array.PushBack(9);
		fixture_full_array.PushBack(10);

		fixture_nonempty_array.PushBack(1);
		fixture_nonempty_array.PushBack(2);
		fixture_nonempty_array.PushBack(3);
		fixture_nonempty_array.PushBack(4);
		fixture_nonempty_array.PushBack(5);
	}
};

constexpr Size StaticArrayTest::DEFAULT_COUNT;
constexpr Size StaticArrayTest::DEFAULT_CAPACITY;
constexpr Size StaticArrayTest::DEFAULT_SIZE;

// -------------------------
// Default Constructor.
// -------------------------
TEST_F(StaticArrayTest, DefaultConstructor_EmptyArray_SetMemoryToZero)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array;

	EXPECT_FALSE(test_array.IsFull());
	EXPECT_TRUE(test_array.IsEmpty());

	EXPECT_EQ(test_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array.GetCount(), 0);
	EXPECT_EQ(test_array.GetCapacity(), DEFAULT_CAPACITY);
}

// -------------------------
// Fill Constructor.
// -------------------------
TEST_F(StaticArrayTest, FillConstructor_EmptyArray_SetMemoryToDefaultValue)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array(DEFAULT_VALUE, DEFAULT_COUNT);

	EXPECT_FALSE(test_array.IsFull());
	EXPECT_FALSE(test_array.IsEmpty());

	EXPECT_EQ(test_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array[counter], DEFAULT_VALUE);
}

// -------------------------
// Buffer Constructor.
// -------------------------
TEST_F(StaticArrayTest, BufferConstructor_EmptyArray_SetMemoryToDefaultBuffer)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_FALSE(test_array.IsFull());
	EXPECT_FALSE(test_array.IsEmpty());

	EXPECT_EQ(test_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array[counter], DEFAULT_BUFFER[counter]);
}

// -------------------------
// Initializer list Constructor.
// -------------------------
TEST_F(StaticArrayTest, InitializerlistConstructor_EmptyArray_SetMemoryToList)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array = { 1, 2, 3, 4, 5 };

	EXPECT_FALSE(test_array.IsFull());
	EXPECT_FALSE(test_array.IsEmpty());

	EXPECT_EQ(test_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array[counter], DEFAULT_BUFFER[counter]);
}

// -------------------------
// Move Constructor.
// -------------------------
TEST_F(StaticArrayTest, MoveConstructor_EmptyArray_MoveArrayToRecieverArray)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array_to_move = StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>(DEFAULT_BUFFER, DEFAULT_COUNT);
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array_to_recieve = std::move(test_array_to_move);

	EXPECT_FALSE(test_array_to_move.IsFull());
	EXPECT_TRUE(test_array_to_move.IsEmpty());

	EXPECT_FALSE(test_array_to_recieve.IsFull());
	EXPECT_FALSE(test_array_to_recieve.IsEmpty());

	EXPECT_EQ(test_array_to_move.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array_to_move.GetCount(), 0);
	EXPECT_EQ(test_array_to_move.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_array_to_recieve.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array_to_recieve.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array_to_recieve.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array_to_move[counter], 0);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array_to_recieve[counter], DEFAULT_BUFFER[counter]);
}

// -------------------------
// Copy Constructor.
// -------------------------
TEST_F(StaticArrayTest, CopyConstructor_EmptyArray_CopyArrayToRecieverArray)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array_to_copy = StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>(DEFAULT_BUFFER, DEFAULT_COUNT);
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array_to_recieve = test_array_to_copy;

	EXPECT_FALSE(test_array_to_copy.IsFull());
	EXPECT_FALSE(test_array_to_copy.IsEmpty());

	EXPECT_FALSE(test_array_to_recieve.IsFull());
	EXPECT_FALSE(test_array_to_recieve.IsEmpty());

	EXPECT_EQ(test_array_to_copy.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array_to_copy.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array_to_copy.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_array_to_recieve.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array_to_recieve.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array_to_recieve.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array_to_copy[counter], DEFAULT_BUFFER[counter]);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array_to_recieve[counter], DEFAULT_BUFFER[counter]);
}

// -------------------------
// Assignment Operators.
// -------------------------
TEST_F(StaticArrayTest, MoveAssignmentOperator_EmptyArray_MoveArrayToRecieverArray)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array_to_move = StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>(DEFAULT_BUFFER, DEFAULT_COUNT);
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array_to_recieve;

	test_array_to_recieve = std::move(test_array_to_move);

	EXPECT_FALSE(test_array_to_move.IsFull());
	EXPECT_TRUE(test_array_to_move.IsEmpty());

	EXPECT_FALSE(test_array_to_recieve.IsFull());
	EXPECT_FALSE(test_array_to_recieve.IsEmpty());

	EXPECT_EQ(test_array_to_move.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array_to_move.GetCount(), 0);
	EXPECT_EQ(test_array_to_move.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_array_to_recieve.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array_to_recieve.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array_to_recieve.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array_to_move[counter], 0);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array_to_recieve[counter], DEFAULT_BUFFER[counter]);
}
TEST_F(StaticArrayTest, CopyAssignmentOperator_EmptyArray_CopyArrayToRecieverArray)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array_to_copy = StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>(DEFAULT_BUFFER, DEFAULT_COUNT);
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array_to_recieve;

	test_array_to_recieve = test_array_to_copy;

	EXPECT_FALSE(test_array_to_copy.IsFull());
	EXPECT_FALSE(test_array_to_copy.IsEmpty());

	EXPECT_FALSE(test_array_to_recieve.IsFull());
	EXPECT_FALSE(test_array_to_recieve.IsEmpty());

	EXPECT_EQ(test_array_to_copy.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array_to_copy.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array_to_copy.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_array_to_recieve.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array_to_recieve.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array_to_recieve.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array_to_copy[counter], DEFAULT_BUFFER[counter]);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array_to_recieve[counter], DEFAULT_BUFFER[counter]);
}

// -------------------------
// GetIterator Functions.
// -------------------------
TEST_F(StaticArrayTest, GetIterator_NonEmptyArray_ReturnsIteratorPointingToFirstElement)
{
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetFinalIterator());

	for (Size counter = 0; itr_begin != itr_final; counter++, itr_begin++)
		EXPECT_EQ(*itr_begin, DEFAULT_BUFFER[counter]);
}
TEST_F(StaticArrayTest, GetIterator_NonEmptyArray_ReturnsIteratorPointingToPastLastElement)
{
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetFinalIterator());

	itr_final--;

	for (Size counter = DEFAULT_COUNT - 1; itr_final != itr_begin; counter--, itr_final--)
		EXPECT_EQ(*itr_final, DEFAULT_BUFFER[counter]);
}

// -------------------------
// At Function.
// -------------------------
TEST_F(StaticArrayTest, At_EmptyArray_ThrowsOutOfRangeException)
{
	EXPECT_THROW(fixture_empty_array.At(0), std::out_of_range);
}
TEST_F(StaticArrayTest, At_NonEmptyArray_ThrowsOutOfRangeException)
{
	EXPECT_THROW(fixture_nonempty_array.At(DEFAULT_COUNT), std::out_of_range);
}

TEST_F(StaticArrayTest, At_NonEmptyArray_ReturnsConstRefToAllElements)
{
	EXPECT_EQ(fixture_nonempty_array.At(DEFAULT_COUNT - 5), DEFAULT_BUFFER[DEFAULT_COUNT - 5]);
	EXPECT_EQ(fixture_nonempty_array.At(DEFAULT_COUNT - 4), DEFAULT_BUFFER[DEFAULT_COUNT - 4]);
	EXPECT_EQ(fixture_nonempty_array.At(DEFAULT_COUNT - 3), DEFAULT_BUFFER[DEFAULT_COUNT - 3]);
	EXPECT_EQ(fixture_nonempty_array.At(DEFAULT_COUNT - 2), DEFAULT_BUFFER[DEFAULT_COUNT - 2]);
	EXPECT_EQ(fixture_nonempty_array.At(DEFAULT_COUNT - 1), DEFAULT_BUFFER[DEFAULT_COUNT - 1]);
}

// -------------------------
// GetRawData Function.
// -------------------------
TEST_F(StaticArrayTest, GetRawData_NonEmptyArray_ReturnsConstPtrToInternalBuffer)
{
	const DEFAULT_TYPE* buffer = fixture_nonempty_array.GetRawData();

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(buffer[counter], DEFAULT_BUFFER[counter]);
}

// -------------------------
// GetBack Function.
// -------------------------
TEST_F(StaticArrayTest, GetBackElement_EmptyArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_empty_array.GetBack(), std::length_error);
}

TEST_F(StaticArrayTest, GetBackElement_NonEmptyArray_ReturnsConstRefToBackElement)
{
	EXPECT_EQ(fixture_nonempty_array.GetBack(), DEFAULT_BUFFER[DEFAULT_COUNT - 1]);
}

// -------------------------
// GetFront Function.
// -------------------------
TEST_F(StaticArrayTest, GetFrontElement_EmptyArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_empty_array.GetFront(), std::length_error);
}

TEST_F(StaticArrayTest, GetFrontElement_NonEmptyArray_ReturnsConstRefToFrontElement)
{
	EXPECT_EQ(fixture_nonempty_array.GetFront(), DEFAULT_BUFFER[DEFAULT_COUNT - 5]);
}

// -------------------------
// PopBack Function.
// -------------------------
TEST_F(StaticArrayTest, PopBack_EmptyArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_empty_array.PopBack(), std::length_error);
}

TEST_F(StaticArrayTest, PopBack_NonEmptyArray_RemovesTheLastElement)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.PopBack();

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT - 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT - 1; counter++)
		EXPECT_EQ(test_nonempty_array[counter], DEFAULT_BUFFER[counter]);
}

// -------------------------
// PopFront Function.
// -------------------------
TEST_F(StaticArrayTest, PopFront_EmptyArray_ThrowsOutOfRangeException)
{
	EXPECT_THROW(fixture_empty_array.PopFront(), std::length_error);
}

TEST_F(StaticArrayTest, PopFront_NonEmptyArray_RemovesTheFirstElement)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.PopFront();

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT - 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT - 1; counter++)
		EXPECT_EQ(test_nonempty_array[counter], DEFAULT_BUFFER[counter + 1]);
}

// -------------------------
// PushBack Function.
// -------------------------
TEST_F(StaticArrayTest, PushBack_FullArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_full_array.PushBack(DEFAULT_VALUE), std::length_error);
}

TEST_F(StaticArrayTest, PushBack_EmptyArray_PushesRValueElementAtTheBack)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_empty_array;

	EXPECT_EQ(test_empty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_empty_array.GetCount(), 0);
	EXPECT_EQ(test_empty_array.GetCapacity(), DEFAULT_CAPACITY);

	DEFAULT_TYPE rvalue = DEFAULT_VALUE;
	test_empty_array.PushBack(std::move(rvalue));

	EXPECT_EQ(test_empty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_empty_array.GetCount(), 1);
	EXPECT_EQ(test_empty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_empty_array[0], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, PushBack_EmptyArray_PushesLValueElementAtTheBack)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_empty_array;

	EXPECT_EQ(test_empty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_empty_array.GetCount(), 0);
	EXPECT_EQ(test_empty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_empty_array.PushBack(DEFAULT_VALUE);

	EXPECT_EQ(test_empty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_empty_array.GetCount(), 1);
	EXPECT_EQ(test_empty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_empty_array[0], DEFAULT_VALUE);
}

TEST_F(StaticArrayTest, PushBack_NonEmptyArray_PushesRValueElementAtTheBack)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	DEFAULT_TYPE rvalue = DEFAULT_VALUE;
	test_nonempty_array.PushBack(std::move(rvalue));

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[DEFAULT_COUNT], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, PushBack_NonEmptyArray_PushesLValueElementAtTheBack)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.PushBack(DEFAULT_VALUE);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[DEFAULT_COUNT], DEFAULT_VALUE);
}

// -------------------------
// PushFront Function.
// -------------------------
TEST_F(StaticArrayTest, PushFront_FullArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_full_array.PushFront(DEFAULT_VALUE), std::length_error);
}

TEST_F(StaticArrayTest, PushFront_EmptyArray_PushesRValueElementAtTheFront)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_empty_array;

	EXPECT_EQ(test_empty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_empty_array.GetCount(), 0);
	EXPECT_EQ(test_empty_array.GetCapacity(), DEFAULT_CAPACITY);

	DEFAULT_TYPE rvalue = DEFAULT_VALUE;
	test_empty_array.PushFront(std::move(rvalue));

	EXPECT_EQ(test_empty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_empty_array.GetCount(), 1);
	EXPECT_EQ(test_empty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_empty_array[0], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, PushFront_EmptyArray_PushesLValueElementAtTheFront)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_empty_array;

	EXPECT_EQ(test_empty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_empty_array.GetCount(), 0);
	EXPECT_EQ(test_empty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_empty_array.PushFront(DEFAULT_VALUE);

	EXPECT_EQ(test_empty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_empty_array.GetCount(), 1);
	EXPECT_EQ(test_empty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_empty_array[0], DEFAULT_VALUE);
}

TEST_F(StaticArrayTest, PushFront_NonEmptyArray_PushesRValueElementAtTheFront)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	DEFAULT_TYPE rvalue = DEFAULT_VALUE;
	test_nonempty_array.PushFront(std::move(rvalue));

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, PushFront_NonEmptyArray_PushesLValueElementAtTheFront)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.PushFront(DEFAULT_VALUE);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_VALUE);
}

// -------------------------
// Remove Function.
// -------------------------
TEST_F(StaticArrayTest, Erase_EmptyArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_empty_array.Remove(0), std::length_error);
	EXPECT_THROW(fixture_empty_array.Remove(5), std::length_error);
	EXPECT_THROW(fixture_empty_array.Remove(10), std::length_error);
}

TEST_F(StaticArrayTest, Erase_NonEmptyArray_ThrowsOutOfRangeException)
{
	EXPECT_THROW(fixture_nonempty_array.Remove(-1), std::out_of_range);
	EXPECT_THROW(fixture_nonempty_array.Remove(50), std::out_of_range);
	EXPECT_THROW(fixture_nonempty_array.Remove(100), std::out_of_range);
}

TEST_F(StaticArrayTest, Erase_NonEmptyArray_ErasesTheFirstElement)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Remove(0);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT - 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_BUFFER[1]);
}
TEST_F(StaticArrayTest, Erase_NonEmptyArray_ErasesTheMiddleElement)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Remove(2);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT - 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[2], DEFAULT_BUFFER[3]);
}
TEST_F(StaticArrayTest, Erase_NonEmptyArray_ErasesTheLastElement)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Remove(4);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT - 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[4], DEFAULT_BUFFER[5]);
}

// -------------------------
// Remove Range Function.
// -------------------------
TEST_F(StaticArrayTest, EraseRange_EmptyArray_ThrowsLengthErrorException)
{
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_empty_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_empty_array.GetFinalIterator());

	EXPECT_THROW(fixture_empty_array.Remove(itr_begin, itr_final), std::length_error);
}

TEST_F(StaticArrayTest, EraseRange_NonEmptyArray_ThrowsOutOfRangeException)
{
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetFinalIterator());

	itr_begin--;

	EXPECT_THROW(fixture_nonempty_array.Remove(itr_begin, itr_final), std::out_of_range);
}

TEST_F(StaticArrayTest, EraseRange_NonEmptyArray_ErasesTheFirstThreeElements)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(test_nonempty_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(test_nonempty_array.GetFinalIterator());

	itr_final--;
	itr_final--;

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Remove(itr_begin, itr_final);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT - 3);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_BUFFER[3]);
	EXPECT_EQ(test_nonempty_array[1], DEFAULT_BUFFER[4]);
}
TEST_F(StaticArrayTest, EraseRange_NonEmptyArray_ErasesTheMiddleThreeElements)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(test_nonempty_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(test_nonempty_array.GetFinalIterator());

	itr_begin++;
	itr_final--;

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Remove(itr_begin, itr_final);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT - 3);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_BUFFER[0]);
	EXPECT_EQ(test_nonempty_array[1], DEFAULT_BUFFER[4]);
}
TEST_F(StaticArrayTest, EraseRange_NonEmptyArray_ErasesTheLastThreeElements)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(test_nonempty_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(test_nonempty_array.GetFinalIterator());

	itr_begin++; itr_begin++;

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Remove(itr_begin, itr_final);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT - 3);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_BUFFER[0]);
	EXPECT_EQ(test_nonempty_array[1], DEFAULT_BUFFER[1]);
}

// -------------------------
// Assign Function.
// -------------------------
TEST_F(StaticArrayTest, Assign_EmptyArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_empty_array.Assign(0, DEFAULT_VALUE), std::length_error);
	EXPECT_THROW(fixture_empty_array.Assign(5, DEFAULT_VALUE), std::length_error);
	EXPECT_THROW(fixture_empty_array.Assign(10, DEFAULT_VALUE), std::length_error);
}

TEST_F(StaticArrayTest, Assign_FullArray_ThrowsOutOfRangeException)
{
	EXPECT_THROW(fixture_full_array.Assign(10, DEFAULT_VALUE), std::out_of_range);
}
TEST_F(StaticArrayTest, Assign_NonEmptyArray_ThrowsOutOfRangeException)
{
	EXPECT_THROW(fixture_nonempty_array.Assign(5, DEFAULT_VALUE), std::out_of_range);
}

TEST_F(StaticArrayTest, Assign_NonEmptyArray_AssignsRValueElementAtTheFront)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Assign(0, std::move(DEFAULT_VALUE));

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, Assign_NonEmptyArray_AssignsLValueElementAtTheFront)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Assign(0, DEFAULT_VALUE);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_VALUE);
}

TEST_F(StaticArrayTest, Assign_NonEmptyArray_AssignsRValueElementAtTheMiddle)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Assign(2, std::move(DEFAULT_VALUE));

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[2], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, Assign_NonEmptyArray_AssignsLValueElementAtTheMiddle)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Assign(2, DEFAULT_VALUE);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[2], DEFAULT_VALUE);
}

TEST_F(StaticArrayTest, Assign_NonEmptyArray_AssignsRValueElementAtTheEnd)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Assign(4, std::move(DEFAULT_VALUE));

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[4], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, Assign_NonEmptyArray_AssignsLValueElementAtTheEnd)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Assign(4, DEFAULT_VALUE);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[4], DEFAULT_VALUE);
}

// -------------------------
// Assign Range Function.
// -------------------------
TEST_F(StaticArrayTest, AssignRange_EmptyArray_ThrowsLengthErrorException)
{
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetFinalIterator());

	EXPECT_THROW(fixture_empty_array.Assign(0, itr_begin, itr_final), std::length_error);
}

TEST_F(StaticArrayTest, AssignRange_NonEmptyArray_ThrowsOutOfRangeException)
{
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetFinalIterator());

	EXPECT_THROW(fixture_nonempty_array.Assign(0, itr_begin, itr_final), std::out_of_range);
}

TEST_F(StaticArrayTest, AssignRange_NonEmptyArray_AssignsSecondHalfElementsFromFullArray)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetFinalIterator());

	itr_begin++;
	itr_begin++;
	itr_begin++;
	itr_begin++;
	itr_begin++;

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Assign(0, itr_begin, itr_final);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_nonempty_array[counter], fixture_full_array[counter + 5]);
}

// -------------------------
// Insert Function.
// -------------------------
TEST_F(StaticArrayTest, Insert_FullArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_full_array.Insert(10, DEFAULT_VALUE), std::length_error);
}

TEST_F(StaticArrayTest, Insert_EmptyArray_ThrowsOutOfRangeException)
{
	EXPECT_THROW(fixture_empty_array.Insert(0, DEFAULT_VALUE), std::out_of_range);
	EXPECT_THROW(fixture_empty_array.Insert(5, DEFAULT_VALUE), std::out_of_range);
	EXPECT_THROW(fixture_empty_array.Insert(10, DEFAULT_VALUE), std::out_of_range);
}
TEST_F(StaticArrayTest, Insert_NonEmptyArray_ThrowsOutOfRangeException)
{
	EXPECT_THROW(fixture_nonempty_array.Insert(5, DEFAULT_VALUE), std::out_of_range);
}

TEST_F(StaticArrayTest, Insert_NonEmptyArray_AssignsRValueElementAtTheFront)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Insert(0, std::move(DEFAULT_VALUE));

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, Insert_NonEmptyArray_AssignsLValueElementAtTheFront)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Insert(0, DEFAULT_VALUE);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[0], DEFAULT_VALUE);
}

TEST_F(StaticArrayTest, Insert_NonEmptyArray_AssignsRValueElementAtTheMiddle)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Insert(2, std::move(DEFAULT_VALUE));

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[2], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, Insert_NonEmptyArray_AssignsLValueElementAtTheMiddle)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Insert(2, DEFAULT_VALUE);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[2], DEFAULT_VALUE);
}

TEST_F(StaticArrayTest, Insert_NonEmptyArray_AssignsRValueElementAtTheEnd)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Insert(4, std::move(DEFAULT_VALUE));

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[4], DEFAULT_VALUE);
}
TEST_F(StaticArrayTest, Insert_NonEmptyArray_AssignsLValueElementAtTheEnd)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Insert(4, DEFAULT_VALUE);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 1);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	EXPECT_EQ(test_nonempty_array[4], DEFAULT_VALUE);
}

// -------------------------
// Insert Range Function.
// -------------------------
TEST_F(StaticArrayTest, InsertRange_FullArray_ThrowsLengthErrorException)
{
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_nonempty_array.GetFinalIterator());

	EXPECT_THROW(fixture_full_array.Insert(0, itr_begin, itr_final), std::length_error);
}
TEST_F(StaticArrayTest, InsertRange_NonEmptyArray_ThrowsLengthErrorException)
{
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetFinalIterator());

	EXPECT_THROW(fixture_nonempty_array.Insert(0, itr_begin, itr_final), std::length_error);
}

TEST_F(StaticArrayTest, InsertRange_NonEmptyArray_ThrowsOutOfRangeException)
{
	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetFinalIterator());

	itr_begin++;
	itr_begin++;
	itr_begin++;
	itr_begin++;
	itr_begin++;

	EXPECT_THROW(fixture_nonempty_array.Insert(5, itr_begin, itr_final), std::out_of_range);
}

TEST_F(StaticArrayTest, InsertRange_NonEmptyArray_InsertsSecondHalfElementsFromFullArray)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	auto itr_begin = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetBeginIterator());
	auto itr_final = dynamic_cast<StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>::Iterator&>(fixture_full_array.GetFinalIterator());

	itr_begin++;
	itr_begin++;
	itr_begin++;
	itr_begin++;
	itr_begin++;

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	test_nonempty_array.Insert(0, itr_begin, itr_final);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 5);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_nonempty_array[counter], fixture_full_array[counter + 5]);
}

// -------------------------
// InsertAll Function.
// -------------------------
TEST_F(StaticArrayTest, InsertAll_FullArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_full_array.InsertAll(fixture_nonempty_array), std::length_error);
}
TEST_F(StaticArrayTest, InsertAll_NonEmptyArray_ThrowsLengthErrorException)
{
	EXPECT_THROW(fixture_nonempty_array.InsertAll(fixture_full_array), std::length_error);
}

TEST_F(StaticArrayTest, InsertAll_NonEmptyArray_DoesNotPerformAnyInsertions)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	test_nonempty_array.InsertAll(fixture_empty_array);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_nonempty_array[counter], DEFAULT_BUFFER[counter]);
}
TEST_F(StaticArrayTest, InsertAll_NonEmptyArray_InsertsAllElementsOfOtherArray)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_nonempty_array(DEFAULT_BUFFER, DEFAULT_COUNT);

	test_nonempty_array.InsertAll(fixture_nonempty_array);

	EXPECT_EQ(test_nonempty_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_nonempty_array.GetCount(), DEFAULT_COUNT + 5);
	EXPECT_EQ(test_nonempty_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_CAPACITY; counter++)
		EXPECT_EQ(test_nonempty_array[counter], DEFAULT_BUFFER[counter % DEFAULT_COUNT]);
}

// -------------------------
// Clear Function.
// -------------------------
TEST_F(StaticArrayTest, Clear_NonEmptyArray_DestructsAndSetsMemoryToZero)
{
	StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY> test_array = StaticArray<DEFAULT_TYPE, DEFAULT_CAPACITY>(DEFAULT_BUFFER, DEFAULT_COUNT);

	EXPECT_FALSE(test_array.IsFull());
	EXPECT_FALSE(test_array.IsEmpty());

	EXPECT_EQ(test_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array.GetCount(), DEFAULT_COUNT);
	EXPECT_EQ(test_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array[counter], DEFAULT_BUFFER[counter]);

	test_array.Clear();

	EXPECT_FALSE(test_array.IsFull());
	EXPECT_TRUE(test_array.IsEmpty());

	EXPECT_EQ(test_array.GetSize(), DEFAULT_SIZE);
	EXPECT_EQ(test_array.GetCount(), 0);
	EXPECT_EQ(test_array.GetCapacity(), DEFAULT_CAPACITY);

	for (Size counter = 0; counter < DEFAULT_COUNT; counter++)
		EXPECT_EQ(test_array[counter], 0);
}

#endif