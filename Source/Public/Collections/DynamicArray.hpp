#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <memory>
#include <utility>
#include <stdexcept>
#include <initializer_list>

#include "AbstractSequencedCollection.hpp"

namespace Forge
{
	template <typename InElementType, typename InAllocationPolicy = HeapAllocationPolicy>
	class DynamicArray : public AbstractSequencedCollection<InElementType, InAllocationPolicy>
	{
	DYNAMIC_COLLECTION_TYPEDEFS(AbstractSequencedCollection, DynamicArray)

	public:
		class Iterator : public AbstractIterator<ElementType>
		{
		public:
			using BaseType = AbstractIterator<ElementType>;

		public:
			using SelfType = Iterator;
			using SelfTypePtr = Iterator*;
			using SelfTypeLRef = Iterator&;
			using SelfTypeRRef = Iterator&&;
			using ConstSelfType = const Iterator;
			using ConstSelfTypePtr = const Iterator*;
			using ConstSelfTypeLRef = const Iterator&;

		public:
			Iterator()
				: BaseType() {}
			Iterator(ElementTypePtr ptr)
				: BaseType(ptr) {}

		public:
			Iterator(SelfTypeRRef other)
				: BaseType(other) {}
			Iterator(ConstSelfTypeLRef other)
				: BaseType(other) {}

		public:
			~Iterator() = default;

		public:
			ElementTypePtr operator->() override
			{
				return this->m_ptr;
			}
			ElementTypeLRef operator*() override
			{
				return *this->m_ptr;
			}

		public:
			SelfTypeLRef operator++() override
			{
				this->m_ptr++;

				return *this;
			}
			SelfTypeLRef operator--() override
			{
				this->m_ptr--;

				return *this;
			}
			SelfTypeLRef operator++(I32) override
			{
				SelfType temp = *this;

				this->m_ptr++;

				return temp;
			}
			SelfTypeLRef operator--(I32) override
			{
				SelfType temp = *this;

				this->m_ptr--;

				return temp;
			}
		};

	private:
		enum MemoryStorage {
			INTERNAL = 0,
			EXTERNAL
		};

		enum MemoryAlignment {
			ALIGNMENT_4 = 0,
			ALIGNMENT_8,
			ALIGNMENT_16
		};

	private:
		class IteratorImpl;
		::std::unique_ptr<IteratorImpl> m_pImpl;

	private:
		ElementTypePtr m_data;

	public:
		/**
		 * @brief Default Constructor.
		 *
		 * Initializes an empty dynamic array with no capacity.
		 */
		DynamicArray(Allocator<InAllocationPolicy>* allocator = nullptr);

		/**
		 * @brief Intial Capacity Constructor.
		 *
		 * Initializes an empty dynamic array with the specified capacity.
		 */
		DynamicArray(Size capacity, Allocator<InAllocationPolicy>* allocator = nullptr);

		/**
		 * @brief Fill Constructor.
		 *
		 * Initializes a dynamic array and fills it with the specified value and count.
		 */
		DynamicArray(ConstElementTypeLRef value, Size count, Allocator<InAllocationPolicy>* allocator = nullptr);

		/**
		 * @brief Buffer Constructor.
		 *
		 * Initializes a dynamic array and fills it with the specified buffer and count.
		 */
		DynamicArray(ConstElementTypePtr buffer, Size count, Allocator<InAllocationPolicy>* allocator = nullptr);

		/**
		 * @brief Initializer list Constructor.
		 *
		 * Initializes an empty dynamic array with the specified initializer list.
		 */
		DynamicArray(std::initializer_list<ElementType> list, Allocator<InAllocationPolicy>* allocator = nullptr);

	public:
		/**
		 * @brief Move Constructor.
		 */
		DynamicArray(SelfTypeRRef);

		/**
		 * @brief Copy Constructor.
		 */
		DynamicArray(ConstSelfTypeLRef);

	public:
		/**
		 * @brief Destructor.
		 */
		~DynamicArray();

	public:
		/**
		 * @brief Move Assignment Operator.
		 */
		SelfTypeLRef operator=(SelfTypeRRef other);

		/**
		 * @brief Copy Assignment Operator.
		 */
		SelfTypeLRef operator=(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Array Subscript Operator.
		 */
		ElementTypeLRef operator[](Size index) override;

		/**
		 * @brief Array Subscript Operator.
		 */
		ConstElementTypeLRef operator[](Size index) const override;

	public:
		/**
		 * @brief Gets an iterator pointing to the first element in the collection.
		 *
		 * @return IIterator pointing to the first element.
		 */
		typename AbstractIterator<ElementType>::SelfTypeLRef GetBeginIterator() override;

		/**
		 * @brief Gets an iterator pointing to one past the last element in the collection.
		 *
		 * @return IIterator pointing to one past the last element.
		 */
		typename AbstractIterator<ElementType>::SelfTypeLRef GetFinalIterator() override;

	public:
		/**
		 * @brief Retrieves a reference to the element at a specified position, with bounds checking.
		 *
		 * @param index The position of the element to retrieve.
		 * @return A reference to the element at the specified position.
		 */
		ElementTypeLRef At(Size index) override;

		/**
		 * @brief Retrieves a const reference to the element at a specified position, with bounds checking.
		 *
		 * @param index The position of the element to retrieve.
		 * @return A const reference to the element at the specified position.
		 */
		ConstElementTypeLRef At(Size index) const override;

	public:
		/**
		 * @brief Retrieves a pointer to the underlying data array.
		 *
		 * @return A const pointer to the the underlying data array.
		 */
		ConstElementTypePtr GetRawData() const override;

		/**
		 * @brief Retrieves the last element in the collection.
		 *
		 * @return A reference to the last element.
		 */
		ElementTypeLRef GetBack() override;

		/**
		 * @brief Retrieves the first element in the collection.
		 *
		 * @return A const reference to the first element.
		 */
		ElementTypeLRef GetFront() override;

		/**
		 * @brief Retrieves the last element in the collection.
		 *
		 * @return A const reference to the last element.
		 */
		ConstElementTypeLRef GetBack() const override;

		/**
		 * @brief Retrieves the first element in the collection.
		 *
		 * @return A const reference to the first element.
		 */
		ConstElementTypeLRef GetFront() const override;

	public:
		/**
		 * @brief Removes the last element in the collection.
		 */
		Void PopBack() override;

		/**
		 * @brief Removes the first element in the collection.
		 */
		Void PopFront() override;

	public:
		/**
		 * @brief Inserts an element at the end of the collection.
		 *
		 * @param element The element to be moved and added.
		 */
		Void PushBack(ElementTypeRRef element) override;

		/**
		 * @brief Inserts an element at the start of the collection.
		 *
		 * @param element The element to be moved and added.
		 */
		Void PushFront(ElementTypeRRef element) override;

		/**
		 * @brief Inserts an element at the end of the collection.
		 *
		 * @param element The element to be copied and added.
		 */
		Void PushBack(ConstElementTypeLRef element) override;

				/**
		 * @brief Inserts an element at the start of the collection.
		 *
		 * @param element The element to be copied and added.
		 */
		Void PushFront(ConstElementTypeLRef element) override;

	public:
		/**
		 * @brief Removes the element at the specified index.
		 *
		 * @param index The position of the element to erase.
		 */
		Void Remove(Size index) override;

		/**
		 * @brief Removes the elements in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param iterator_first An iterator pointing to the first element to remove.
		 * @param iterator_last An iterator pointing to the past last element to remove.
		 */
		Void Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	public:
		/**
		 * @brief Assigns a new element at the specified index.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be moved and assigned.
		 */
		Void Assign(Size index, ElementTypeRRef element) override;

		/**
		 * @brief Assigns a new element at the specified index.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be copied and assigned.
		 */
		Void Assign(Size index, ConstElementTypeLRef element) override;

		/**
		 * @brief Assigns the elements in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param index The position of the elements to assign.
		 * @param iterator_first An iterator pointing to the first element to assign.
		 * @param iterator_last An iterator pointing to the past last element to assign.
		 */
		Void Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	public:
		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be moved and inserted.
		 */
		Void Insert(Size index, ElementTypeRRef element) override;

		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be copied and inserted.
		 */
		Void Insert(Size index, ConstElementTypeLRef element) override;

		/**
		 * @brief Inserts the elements at the specified index in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param index The position of the elements to insert.
		 * @param iterator_first An iterator pointing to the first element to insert.
		 * @param iterator_last An iterator pointing to the past last element to insert.
		 */
		Void Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	public:
		/**
		 * @brief Inserts all elements in the specified collection into this collection.
		 *
		 * This function inserts all elements and does not verify wether duplicates exist. Any
		 * element that already exists in this collection will still insert another copy, without
		 * raising errors or exceptions.
		 *
		 * @param collection The collection whose elements are to be inserted into this collection.
		 */
		Void InsertAll(typename BaseType::ConstSelfTypeLRef collection) override;

		/**
		 * @brief Removes all the elements in the specified collection from this collection.
		 *
		 * This function removes the elements it can find and does not verify whether all elements
		 * were successfully located and removed. Any elements in the specified collection that are
		 * not found in this collection are simply ignored, without raising errors or exceptions.
		 *
		 * @param[in] collection The collection whose elements are to be removed from this collection.
		 */
		Void RemoveAll(typename BaseType::ConstSelfTypeLRef collection) override;

		/**
		 * @brief Searches all the elements in the specified collection in this collection.
		 *
		 * @param[in] collection The collection whose elements are to be searched in this collection.
		 *
		 * @return True if all the elements were found, otherwise false.
		 */
		Bool ContainsAll(typename BaseType::ConstSelfTypeLRef collection) override;

	public:
		Void Compact();

		Void Resize(Size capacity);

		Void Reserve(Size capacity);

	public:
		/**
		 * @brief Removes all the elements from this collections.
		 */
		Void Clear() override;
	};
}

#endif