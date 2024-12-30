#ifndef ABSTRACT_SEQUENCED_COLLECTION_HPP
#define ABSTRACT_SEQUENCED_COLLECTION_HPP

#include "AbstractCollection.hpp"

namespace Forge
{
	/**
	 * @brief This abstract class serves as the base interface for collections that maintain a
	 * specific sequence of elements, providing common functionality for ordered collections.
	 *
	 * @tparam InElementType The type of element the collection stores.
	 * @tparam InAllocatorPolicy The type of allocator policy the collection uses to manage its memory.
	 */
	template <typename InElementType, typename InAllocatorPolicy>
	class AbstractSequencedCollection : public AbstractCollection<InElementType, InAllocatorPolicy>
	{
	public:
		using BaseType = AbstractCollection<InElementType, InAllocatorPolicy>;

	public:
		using SelfType = AbstractSequencedCollection<InElementType, InAllocatorPolicy>;
		using SelfTypePtr = AbstractSequencedCollection<InElementType, InAllocatorPolicy>*;
		using SelfTypeLRef = AbstractSequencedCollection<InElementType, InAllocatorPolicy>&;
		using SelfTypeRRef = AbstractSequencedCollection<InElementType, InAllocatorPolicy>&&;
		using ConstSelfType = const AbstractSequencedCollection<InElementType, InAllocatorPolicy>;
		using ConstSelfTypePtr = const AbstractSequencedCollection<InElementType, InAllocatorPolicy>*;
		using ConstSelfTypeLRef = const AbstractSequencedCollection<InElementType, InAllocatorPolicy>&;

	public:
		using ElementType = InElementType;
		using ElementTypePtr = InElementType*;
		using ElementTypeLRef = InElementType&;
		using ElementTypeRRef = InElementType&&;
		using ConstElementType = const InElementType;
		using ConstElementTypePtr = const InElementType*;
		using ConstElementTypeLRef = const InElementType&;

	public:
		using AllocatorPolicy = InAllocatorPolicy;
		using AllocatorPolicyPtr = InAllocatorPolicy*;
		using AllocatorPolicyLRef = InAllocatorPolicy&;
		using AllocatorPolicyRRef = InAllocatorPolicy&&;
		using ConstAllocatorPolicy = const InAllocatorPolicy;
		using ConstAllocatorPolicyPtr = const InAllocatorPolicy*;
		using ConstAllocatorPolicyLRef = const InAllocatorPolicy&;

	public:
		/**
		 * @brief Default Constructor.
		 */
		AbstractSequencedCollection(Size count, Size capacity)
			: AbstractCollection<ElementType, AllocatorPolicy>(count, capacity) {}

	public:
		/**
		 * @brief Default Destructor.
		 */
		AbstractSequencedCollection() = default;

	public:
		/**
		 * @brief Array Subscript Operator.
		 */
		virtual ElementTypeLRef operator[](Size index) = 0;

		/**
		 * @brief Array Subscript Operator.
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
		 * @return A reference to the last element.
		 */
		virtual ElementTypeLRef GetBack() = 0;

		/**
		 * @brief Retrieves the first element in the collection.
		 *
		 * @return A reference to the first element.
		 */
		virtual ElementTypeLRef GetFront() = 0;

		/**
		 * @brief Retrieves the last element in the collection.
		 *
		 * @return A const reference to the last element.
		 */
		virtual ConstElementTypeLRef GetBack() const = 0;

		/**
		 * @brief Retrieves the first element in the collection.
		 *
		 * @return A const reference to the first element.
		 */
		virtual ConstElementTypeLRef GetFront() const = 0;

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
		 * @brief Inserts an element at the end of the collection.
		 *
		 * @param element The element to be moved and added.
		 */
		virtual Void PushBack(ElementTypeRRef element) = 0;

		/**
		 * @brief Inserts an element at the start of the collection.
		 *
		 * @param element The element to be moved and added.
		 */
		virtual Void PushFront(ElementTypeRRef element) = 0;

		/**
		 * @brief Inserts an element at the end of the collection.
		 *
		 * @param element The element to be copied and added.
		 */
		virtual Void PushBack(ConstElementTypeLRef element) = 0;

		/**
		 * @brief Inserts an element at the start of the collection.
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
		 * @param iterator_last An iterator pointing to the past last element to remove.
		 */
		virtual Void Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) = 0;

	public:
		/**
		 * @brief Assigns a new element at the specified index.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be moved and assigned.
		 */
		virtual Void Assign(Size index, ElementTypeRRef element) = 0;

		/**
		 * @brief Assigns a new element at the specified index.
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
		 * @param iterator_last An iterator pointing to the past last element to assign.
		 */
		virtual Void Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) = 0;

	public:
		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be moved and inserted.
		 */
		virtual Void Insert(Size index, ElementTypeRRef element) = 0;

		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be copied and inserted.
		 */
		virtual Void Insert(Size index, ConstElementTypeLRef element) = 0;

		/**
		 * @brief Inserts the elements at the specified index in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param index The position of the elements to insert.
		 * @param iterator_first An iterator pointing to the first element to insert.
		 * @param iterator_last An iterator pointing to the past last element to insert.
		 */
		virtual Void Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) = 0;

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
		virtual Void InsertAll(ConstSelfTypeLRef collection) = 0;

		/**
		 * @brief Removes all the elements in the specified collection from this collection.
		 *
		 * This function removes the elements it can find and does not verify whether all elements
		 * were successfully located and removed. Any elements in the specified collection that are
		 * not found in this collection are simply ignored, without raising errors or exceptions.
		 *
		 * @param[in] collection The collection whose elements are to be removed from this collection.
		 */
		virtual Void RemoveAll(ConstSelfTypeLRef collection) = 0;

		/**
		 * @brief Searches all the elements in the specified collection in this collection.
		 *
		 * @param[in] collection The collection whose elements are to be searched in this collection.
		 *
		 * @return True if all the elements were found, otherwise false.
		 */
		virtual Bool ContainsAll(ConstSelfTypeLRef collection) = 0;
	};
}

#endif