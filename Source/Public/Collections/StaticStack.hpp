#ifndef STATIC_STACK_HPP
#define STATIC_STACK_HPP

#include "StaticArray.hpp"
#include "AbstractSequencedCollection.hpp"

#include "Memory/Policies/NoAllocationPolicy.hpp"

namespace Forge
{
	/**
	 * @brief A stack container adaptor providing LIFO (Last In, First Out) access to
	 * elements.
	 *
	 * This class template is fixed-sized container adaptor that provides a stack interface based
	 * on a StaticArray. It supports push and pop operations, making it ideal for scenarios where
	 * elements need to be added and removed in a LIFO order. This class uses the underlying
	 * StaticArray to store the elements.
	 *
	 * @tparam InElementType The type of elements to be stored in the array.
	 * @tparam InContainerType The underlying container type used to store the elements.
	 */
	template<typename InElementType, Size InCapacity>
	class StaticStack : public AbstractSequencedCollection<InElementType, NoAllocationPolicy>
	{
	STATIC_ADAPTOR_COLLECTION_TYPEDEFS(AbstractSequencedCollection, StaticStack, StaticArray)

	private:
		ContainerType m_container;

	public:
		/**
		 * @brief Default Constructor.
		 *
		 * Initializes an empty stack.
		 */
		StaticStack();

		/**
		 * @brief Fill Constructor.
		 *
		 * Initializes a stack and fills it with the specified value and count.
		 */
		StaticStack(ElementType value, Size count);

		/**
		 * @brief Buffer Constructor.
		 *
		 * Initializes a stack and fills it with the specified buffer and count.
		 */
		StaticStack(ElementTypePtr buffer, Size count);

		/**
		 * @brief Initializer list Constructor.
		 *
		 * Initializes an empty stack with the specified initializer list.
		 */
		StaticStack(std::initializer_list<ElementType> init_list);

	public:
		/**
		 * @brief Move Constructor.
		 */
		StaticStack(SelfTypeRRef other);

		/**
		 * @brief Copy Constructor.
		 */
		StaticStack(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Destructor.
		 */
		~StaticStack() override;

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
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		ElementTypeLRef operator[](Size index) override;

		/**
		 * @brief Array Subscript Operator.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		ConstElementTypeLRef operator[](Size index) const override;

	public:
		/**
		 * @brief Gets an iterator pointing to the first element in the collection.
		 *
		 * @return IIterator pointing to the first element.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		typename AbstractIterator<ElementType>::SelfTypeLRef GetBeginIterator() override;

		/**
		 * @brief Gets an iterator pointing to one past the last element in the collection.
		 *
		 * @return IIterator pointing to one past the last element.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		typename AbstractIterator<ElementType>::SelfTypeLRef GetFinalIterator() override;

	public:
		/**
		 * @brief Retrieves a reference to the element at a specified position, with bounds checking.
		 *
		 * @param index The position of the element to retrieve.
		 *
		 * @return A reference to the element at the specified position.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		ElementTypeLRef At(Size index) override;

		/**
		 * @brief Retrieves a const reference to the element at a specified position, with bounds checking.
		 *
		 * @param index The position of the element to retrieve.
		 *
		 * @return A const reference to the element at the specified position.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
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
		 * @return A const reference to the last element.
		 */
		ConstElementTypeLRef GetBackElement() const override;

		/**
		 * @brief Retrieves the first element in the collection.
		 *
		 * @return A const reference to the first element.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		ConstElementTypeLRef GetFrontElement() const override;

	public:
		/**
		 * @brief Removes the last element in the collection.
		 */
		Void PopBack() override;

		/**
		 * @brief Removes the first element in the collection.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
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
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
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
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Void PushFront(ConstElementTypeLRef element) override;

	public:
		/**
		 * @brief Removes the element at the specified index.
		 *
		 * @param index The position of the element to erase.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Void Remove(Size index) override;

		/**
		 * @brief Removes the elements in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param iterator_first An iterator pointing to the first element to remove.
		 * @param iterator_last An iterator pointing to the past last element to remove.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Void Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	public:
		/**
		 * @brief Assigns a new element at the specified index.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be moved and assigned.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Void Assign(Size index, ElementTypeRRef element) override;

		/**
		 * @brief Assigns a new element at the specified index.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be copied and assigned.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Void Assign(Size index, ConstElementTypeLRef element) override;

		/**
		 * @brief Assigns the elements in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param index The position of the elements to assign.
		 * @param iterator_first An iterator pointing to the first element to assign.
		 * @param iterator_last An iterator pointing to the past last element to assign.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Void Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	public:
		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be moved and inserted.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Void Insert(Size index, ElementTypeRRef element) override;

		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be copied and inserted.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Void Insert(Size index, ConstElementTypeLRef element) override;

		/**
		 * @brief Inserts the elements at the specified index in the range [iterator_first, iterator_last) exclusive.
		 *
		 * @param index The position of the elements to insert.
		 * @param iterator_first An iterator pointing to the first element to insert.
		 * @param iterator_last An iterator pointing to the past last element to insert.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
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
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
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
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Void RemoveAll(typename BaseType::ConstSelfTypeLRef collection) override;

		/**
		 * @brief Searches all the elements in the specified collection in this collection.
		 *
		 * @param[in] collection The collection whose elements are to be searched in this collection.
		 *
		 * @return True if all the elements were found, otherwise false.
		 *
		 * @throws std::logic_error if used, as it is illegal for a stack.
		 */
		Bool ContainsAll(typename BaseType::ConstSelfTypeLRef collection) override;

	public:
		/**
		 * @brief Removes all the elements from this collections.
		 */
		Void Clear() override;
	};
}

#include "../../Private/Collections/StaticStack.cpp"

#endif