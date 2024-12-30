#ifndef STATIC_QUEUE_HPP
#define STATIC_QUEUE_HPP

#include "StaticArray.hpp"
#include "AbstractSequencedCollection.hpp"

#include "Memory/Policies/NoAllocationPolicy.hpp"

namespace Forge
{
	/**
	 * @brief A queue container adaptor providing FIFO (First In, First Out) access to
	 * elements.
	 *
	 * This class template is fixed-sized container adaptor that provides a queue interface
	 * based on a StaticArray. It supports push and pop operations, making it ideal for scenarios
	 * where elements need to be added and removed in a FIFO order. This class uses the underlying
	 * StaticArray to store the elements.
	 *
	 * @tparam InElementType The type of elements to be stored in the array.
	 * @tparam InContainerType The underlying container type used to store the elements.
	 */
	template<typename InElementType, Size InCapacity>
	class StaticQueue : public AbstractSequencedCollection<InElementType, NoAllocationPolicy>
	{
	STATIC_ADAPTOR_COLLECTION_TYPEDEFS(AbstractSequencedCollection, StaticQueue, StaticArray)

	private:
		ContainerType m_container;

	public:
		/**
		 * @brief Default Constructor.
		 *
		 * Initializes an empty queue.
		 */
		StaticQueue();

		/**
		 * @brief Fill Constructor.
		 *
		 * Initializes a queue and fills it with the specified value and count.
		 */
		StaticQueue(ElementType value, Size count);

		/**
		 * @brief Buffer Constructor.
		 *
		 * Initializes a queue and fills it with the specified buffer and count.
		 */
		StaticQueue(ElementTypePtr buffer, Size count);

		/**
		 * @brief Initializer list Constructor.
		 *
		 * Initializes an empty queue with the specified initializer list.
		 */
		StaticQueue(std::initializer_list<ElementType> init_list);

	public:
		/**
		 * @brief Move Constructor.
		 */
		StaticQueue(SelfTypeRRef other);

		/**
		 * @brief Copy Constructor.
		 */
		StaticQueue(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Destructor.
		 */
		~StaticQueue() override;

	public:
		/**
		 * @brief Move Assignment Operator.
		 */
		SelfTypeLRef operator=(SelfTypeRRef other);

		/**
		 * @brief Copy Assignment Operator.
		 */
		SelfTypeLRef operator=(ConstSelfTypeLRef other);

	private:
		/**
		 * @brief Array Subscript Operator.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		ElementTypeLRef operator[](Size index) override;

		/**
		 * @brief Array Subscript Operator.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		ConstElementTypeLRef operator[](Size index) const override;

	public:
		/**
		 * @brief Retrieves the top element in the collection.
		 *
		 * This function effectively calls GetFrontElement()
		 *
		 * @return A const reference to the top element.
		 */
		ConstElementTypeLRef Peek() const;

	public:
		/**
		 * @brief Removes the top element in the collection.
		 *
		 * This function effectively calls PopFront()
		 */
		Void Pop();

	public:
		/**
		 * @brief Inserts an element at the top of the collection.
		 *
		 * This function effectively calls PushBack()
		 *
		 * @param element The element to be moved and added.
		 */
		Void Push(ElementTypeRRef element);

		/**
		 * @brief Inserts an element at the top of the collection.
		 *
		 * This function effectively calls PushBack()
		 *
		 * @param element The element to be copied and added.
		 */
		Void Push(ConstElementTypeLRef element);

	private:
		/**
		 * @brief Gets an iterator pointing to the first element in the collection.
		 *
		 * @return IIterator pointing to the first element.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		typename AbstractIterator<ElementType>::SelfTypeLRef GetBeginIterator() override;

		/**
		 * @brief Gets an iterator pointing to one past the last element in the collection.
		 *
		 * @return IIterator pointing to one past the last element.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		typename AbstractIterator<ElementType>::SelfTypeLRef GetFinalIterator() override;

	private:
		/**
		 * @brief Retrieves a reference to the element at a specified position, with bounds checking.
		 *
		 * @param index The position of the element to retrieve.
		 *
		 * @return A reference to the element at the specified position.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		ElementTypeLRef At(Size index) override;

		/**
		 * @brief Retrieves a const reference to the element at a specified position, with bounds checking.
		 *
		 * @param index The position of the element to retrieve.
		 *
		 * @return A const reference to the element at the specified position.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		ConstElementTypeLRef At(Size index) const override;

	private:
		/**
		 * @brief Retrieves a pointer to the underlying data array.
		 *
		 * @return A const pointer to the the underlying data array.
		 */
		ConstElementTypePtr GetRawData() const override;

		/**
		 * @brief Retrieves the last element in the collection.
		 *
		 * @return A const reference to the last element.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		ConstElementTypeLRef GetBackElement() const override;

		/**
		 * @brief Retrieves the first element in the collection.
		 *
		 * @return A const reference to the first element.
		 */
		ConstElementTypeLRef GetFrontElement() const override;

	private:
		/**
		 * @brief Removes the last element in the collection.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void PopBack() override;

		/**
		 * @brief Removes the first element in the collection.
		 */
		Void PopFront() override;

	private:
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
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void PushFront(ElementTypeRRef element) override;

		/**
		 * @brief Inserts an element at the end of the collection.
		 *
		 * @param element The element to be moved and added.
		 */
		Void PushBack(ConstElementTypeLRef element) override;

		/**
		 * @brief Inserts an element at the start of the collection.
		 *
		 * @param element The element to be copied and added.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void PushFront(ConstElementTypeLRef element) override;

	private:
		/**
		 * @brief Removes the element at the specified index.
		 *
		 * @param index The position of the element to erase.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void Remove(Size index) override;

		/**
		 * @brief Removes the elements in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param iterator_first An iterator pointing to the first element to remove.
		 * @param iterator_last An iterator pointing to the past last element to remove.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	private:
		/**
		 * @brief Assigns a new element at the specified index.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be moved and assigned.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void Assign(Size index, ElementTypeRRef element) override;

		/**
		 * @brief Assigns a new element at the specified index.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be copied and assigned.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void Assign(Size index, ConstElementTypeLRef element) override;

		/**
		 * @brief Assigns the elements in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param index The position of the elements to assign.
		 * @param iterator_first An iterator pointing to the first element to assign.
		 * @param iterator_last An iterator pointing to the past last element to assign.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	private:
		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be moved and inserted.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void Insert(Size index, ElementTypeRRef element) override;

		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be copied and inserted.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void Insert(Size index, ConstElementTypeLRef element) override;

		/**
		 * @brief Inserts the elements at the specified index in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param index The position of the elements to insert.
		 * @param iterator_first An iterator pointing to the first element to insert.
		 * @param iterator_last An iterator pointing to the past last element to insert.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	private:
		/**
		 * @brief Inserts all elements in the specified collection into this collection.
		 *
		 * This function inserts all elements and does not verify wether duplicates exist. Any
		 * element that already exists in this collection will still insert another copy, without
		 * raising errors or exceptions.
		 *
		 * @param collection The collection whose elements are to be inserted into this collection.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
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
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Void RemoveAll(typename BaseType::ConstSelfTypeLRef collection) override;

		/**
		 * @brief Searches all the elements in the specified collection in this collection.
		 *
		 * @param[in] collection The collection whose elements are to be searched in this collection.
		 *
		 * @return True if all the elements were found, otherwise false.
		 *
		 * @throws std::logic_error if used, as it is illegal for a queue.
		 */
		Bool ContainsAll(typename BaseType::ConstSelfTypeLRef collection) override;

	public:
		/**
		 * @brief Removes all the elements from this collections.
		 */
		Void Clear() override;
	};
}

#include "../../Private/Collections/StaticQueue.cpp"

#endif