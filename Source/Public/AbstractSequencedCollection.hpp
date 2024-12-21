#ifndef ABSTRACT_SEQUENCED_COLLECTION_HPP
#define ABSTRACT_SEQUENCED_COLLECTION_HPP

#include "AbstractCollection.hpp"

namespace Forge
{
	template <typename InElementType, typename InAllocatorType>
	class AbstractSequencedCollection : public AbstractCollection<InElementType, InAllocatorType>
	{
	public:
		using BaseType = AbstractCollection<InElementType, InAllocatorType>;

	public:
		using SelfType = AbstractSequencedCollection<InElementType, InAllocatorType>;
		using SelfTypePtr = AbstractSequencedCollection<InElementType, InAllocatorType>*;
		using SelfTypeLRef = AbstractSequencedCollection<InElementType, InAllocatorType>&;
		using SelfTypeRRef = AbstractSequencedCollection<InElementType, InAllocatorType>&&;
		using ConstSelfType = const AbstractSequencedCollection<InElementType, InAllocatorType>;
		using ConstSelfTypePtr = const AbstractSequencedCollection<InElementType, InAllocatorType>*;
		using ConstSelfTypeLRef = const AbstractSequencedCollection<InElementType, InAllocatorType>&;

	public:
		using ElementType = InElementType;
		using ElementTypePtr = InElementType*;
		using ElementTypeLRef = InElementType&;
		using ElementTypeRRef = InElementType&&;
		using ConstElementType = const InElementType;
		using ConstElementTypePtr = const InElementType*;
		using ConstElementTypeLRef = const InElementType&;

	public:
		using AllocatorType = InAllocatorType;
		using AllocatorTypePtr = InAllocatorType*;
		using AllocatorTypeLRef = InAllocatorType&;
		using AllocatorTypeRRef = InAllocatorType&&;
		using ConstAllocatorType = const InAllocatorType;
		using ConstAllocatorTypePtr = const InAllocatorType*;
		using ConstAllocatorTypeLRef = const InAllocatorType&;

	public:
		/**
		 * @brief Default Constructor.
		 */
		AbstractSequencedCollection(Size count, Size capacity)
			: AbstractCollection<ElementType, AllocatorType>(count, capacity) {}

	public:
		/**
		 * @brief Default Destructor.
		 */
		AbstractSequencedCollection() = default;

	public:
		/**
		 * @brief Member Access Operator.
		 */
		virtual ElementTypeLRef operator[](Size index) = 0;

		/**
		 * @brief Member Access Operator.
		 */
		virtual ConstElementTypeLRef operator[](Size index) const = 0;

	public:
		/**
		 * @brief Retrieves a reference to the element at a specified position, with bounds checking.
		 *
		 * @param index The position of the element to retrieve.
		 * @return A reference to the element at the specified position.
		 */
		virtual ElementTypeLRef At(Size index) = 0;

		/**
		 * @brief Retrieves a const reference to the element at a specified position, with bounds checking.
		 *
		 * @param index The position of the element to retrieve.
		 * @return A const reference to the element at the specified position.
		 */
		virtual ConstElementTypeLRef At(Size index) const = 0;

	public:
		/**
		 * @brief Retrieves a pointer to the underlying data array.
		 *
		 * @return A const pointer to the the underlying data array.
		 */
		virtual ConstElementTypePtr GetRawData() const = 0;

		/**
		 * @brief Retrieves the last element in the collection.
		 *
		 * @return A const reference to the last element in the collection.
		 */
		virtual ConstElementTypeLRef GetBackElement() const = 0;

		/**
		 * @brief Retrieves the first element in the collection.
		 *
		 * @return A const reference to the first element in the collection.
		 */
		virtual ConstElementTypeLRef GetFrontElement() const = 0;

	public:
		/**
		 * @brief Removes the last element in the collection.
		 */
		virtual Void PopBack() = 0;

		/**
		 * @brief Removes the first element in the collection.
		 */
		virtual Void PopFront() = 0;

	public:
		/**
		 * @brief Adds an element to the end of the collection.
		 *
		 * Moves the specified element into the end of the collection.
		 *
		 * @param element The element to be moved and added.
		 */
		virtual Void PushBack(ElementTypeRRef element) = 0;

		/**
		 * @brief Adds an element to the start of the collection.
		 *
		 * Moves the specified element into the front of the collection.
		 *
		 * @param element The element to be moved and added.
		 */
		virtual Void PushFront(ElementTypeRRef element) = 0;

		/**
		 * @brief Adds an element to the end of the collection.
		 *
		 * Copies the specified element into the end of the collection.
		 *
		 * @param element The element to be copied and added.
		 */
		virtual Void PushBack(ConstElementTypeLRef element) = 0;

		/**
		 * @brief Adds an element to the start of the collection.
		 *
		 * Copies the specified element into the start of the collection.
		 *
		 * @param element The element to be copied and added.
		 */
		virtual Void PushFront(ConstElementTypeLRef element) = 0;

	public:
		/**
		 * @brief Removes the element at the specified index.
		 *
		 * @param index The position of the element to remove.
		 */
		virtual Void Remove(Size index) = 0;

		/**
		 * @brief Removes the elements in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param iterator_first An iterator pointing to the first element to remove.
		 * @param iterator_last An iterator pointing to the last element to remove.
		 */
		virtual Void Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) = 0;

	public:
		/**
		 * @brief Assigns a new value to the element at the specified index.
		 *
		 * Moves the specified element into the position pointed to by the iterator.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be moved and assigned.
		 */
		virtual Void Assign(Size index, ElementTypeRRef element) = 0;

		/**
		 * @brief Assigns a new value to the element at the specified index.
		 *
		 * Copies the specified element into the position pointed to by the iterator.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be copied and assigned.
		 */
		virtual Void Assign(Size index, ConstElementTypeLRef element) = 0;

		/**
		 * @brief Assigns the elements in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param index The position of the elements to assign.
		 * @param iterator_first An iterator pointing to the first element to assign.
		 * @param iterator_last An iterator pointing to the last element to assign.
		 */
		virtual Void Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) = 0;

	public:
		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * Moves the specified element into the position pointed to by the iterator.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be moved and inserted.
		 */
		virtual Void Insert(Size index, ElementTypeRRef element) = 0;

		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * Copies the specified element into the position pointed to by the iterator.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be copied and inserted.
		 */
		virtual Void Insert(Size index, ConstElementTypeLRef element) = 0;

		/**
		 * @brief Inserts the elements at the specified index in the range [iterator_first,
		 * iterator_last) exclusive.
		 *
		 * @param index The position of the elements to insert.
		 * @param iterator_first An iterator pointing to the first element to insert.
		 * @param iterator_last An iterator pointing to the last element to insert.
		 */
		virtual Void Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) = 0;

	public:
		/**
		 * @brief Inserts all elements from the specified collection into this collection.
		 *
		 * @param collection The collection whose elements are to be inserted.
		 *
		 * @return True if the insertion was successful and no duplicates were added, if supported.
		 */
		virtual Void InsertAll(ConstSelfTypeLRef collection) = 0;

		/**
		 * @brief Removes all the elements in the specified collection from this collection.
		 *
		 * @param[in] collection The collection containing elements to be removed from this collection.
		 *
		 * @return True if removal was successful and the elements were found.
		 */
		virtual Bool RemoveAll(ConstSelfTypeLRef collection) = 0;

		/**
		 * @brief Searches for all the elements in the specified collection in this collection.
		 *
		 * @param[in] collection The collection containing elements to be  search for in this collection.
		 *
		 * @return True if the specified elements were found in this collection.
		 */
		virtual Bool ContainsAll(ConstSelfTypeLRef collection) = 0;
	};
}

#endif