#ifndef STATIC_ARRAY_HPP
#define STATIC_ARRAY_HPP

#include <memory>
#include <utility>
#include <stdexcept>
#include <initializer_list>

#include "../AbstractSequencedCollection.hpp"

namespace Forge
{
	/**
	* @brief A fixed-capacity array implementation that provides efficient storage and access to 
	* elements.
	*
	* The StaticArray class template is designed to hold a fixed number of elements.The class is
	* optimized for scenarios where a constant-size array is required, with compile-time capacity
	* enforcement. This implementation avoids dynamic memory allocation, making it suitable for
	* embedded systems and performance-critical applications.
	*
	* @tparam InElementType The type of elements to be stored in the array.
	* @tparam InCapacity The maximum number of elements that the array can hold.
	*/
	template <typename InElementType, Size InCapacity>
	class StaticArray : public AbstractSequencedCollection<InElementType, NoAllocationPolicy>
	{
	STATIC_COLLECTION_TYPEDEFS(AbstractSequencedCollection, StaticArray)

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
			SelfTypeLRef operator=(SelfTypeRRef other) = default;
			SelfTypeLRef operator=(ConstSelfTypeLRef other) = default;

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
		class IteratorImpl;
		::std::unique_ptr<IteratorImpl> m_pImpl;

	private:
		ElementType m_data[InCapacity];

	public:
		/**
		 * @brief Default constructor.
		 *
		 * Initializes an empty static array with the specified capacity.
		 */
		StaticArray();

		/**
		 * @brief Fill constructor.
		 * 
		 * Initializes a static array and fills it with the specified value and count.
		 */
		StaticArray(ElementType value, Size count);

		/**
		 * @brief Buffer constructor.
		 * 
		 * Initializes a static array and fills it with the specified buffer and count.
		 */
		StaticArray(ElementTypePtr buffer, Size count);
		
		/**
		 * @brief Initializer list constructor.
		 *
		 * Initializes an empty static array with the specified initializer list.
		 */
		StaticArray(std::initializer_list<ElementType> init_list);

	public:
		/**
		 * @brief Move constructor.
		 */
		StaticArray(SelfTypeRRef other);

		/**
		 * @brief Copy constructor.
		 */
		StaticArray(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Destructor.
		 */
		~StaticArray() override;

	public:
		/**
		 * @brief Move assignment operator.
		 */
		SelfTypeLRef operator=(SelfTypeRRef other);

		/**
		 * @brief Copy assignment operator.
		 */
		SelfTypeLRef operator=(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Access operator.
		 */
		ElementTypeLRef operator[](Size index) override;

		/**
		 * @brief Const access operator.
		 */
		ConstElementTypeLRef operator[](Size index) const override;

	public:
		/**
		 * @brief Retrieves the begin iterator.
		 * 
		 * @return A reference to the begin iterator.
		 */
		typename AbstractIterator<ElementType>::SelfTypeLRef GetBeginIterator() override;

		/**
		 * @brief Retrieves the final iterator.
		 * 
		 * @return A reference to the final iterator.
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
		 * @brief Retrieves the last element in the array.
		 *
		 * @return A const reference to the last element in the array.
		 */
		ConstElementTypeLRef GetBackElement() const override;

		/**
		 * @brief Retrieves the first element in the array.
		 *
		 * @return A const reference to the first element in the array.
		 */
		ConstElementTypeLRef GetFrontElement() const override;

	public:
		/**
		 * @brief Removes the last element in the array.
		 */
		Void PopBack() override;

		/**
		 * @brief Removes the first element in the array.
		 */
		Void PopFront() override;

	public:
		/**
		 * @brief Adds an element to the end of the array.
		 *
		 * Moves the specified element into the end of the array.
		 *
		 * @param element The element to be moved and added.
		 */
		Void PushBack(ElementTypeRRef element) override;

		/**
		 * @brief Adds an element to the start of the array.
		 *
		 * Moves the specified element into the front of the array.
		 *
		 * @param element The element to be moved and added.
		 */
		Void PushFront(ElementTypeRRef element) override;

		/**
		 * @brief Adds an element to the end of the array.
		 *
		 * Copies the specified element into the end of the array.
		 *
		 * @param element The element to be copied and added.
		 */
		Void PushBack(ConstElementTypeLRef element) override;

		/**
		 * @brief Adds an element to the start of the array.
		 *
		 * Copies the specified element into the start of the array.
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
		 * @param iterator_last An iterator pointing to the last element to remove.
		 */
		Void Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	public:
		/**
		 * @brief Assigns a new value to the element at the specified index.
		 *
		 * Moves the specified element into the position pointed to by the iterator.
		 *
		 * @param index The position of the element to assign.
		 * @param element The new element to be moved and assigned.
		 */
		Void Assign(Size index, ElementTypeRRef element) override;

		/**
		 * @brief Assigns a new value to the element at the specified index.
		 *
		 * Copies the specified element into the position pointed to by the iterator.
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
		 * @param iterator_last An iterator pointing to the last element to assign.
		 */
		Void Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	public:
		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * Moves the specified element into the position pointed to by the iterator.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be moved and inserted.
		 */
		Void Insert(Size index, ElementTypeRRef element) override;

		/**
		 * @brief Inserts an element at the specified index.
		 *
		 * Copies the specified element into the position pointed to by the iterator.
		 *
		 * @param index The position of the element to insert.
		 * @param element The element to be copied and inserted.
		 */
		Void Insert(Size index, ConstElementTypeLRef element) override;

		/**
		 * @brief Inserts the elements at the specified index in the range [iterator_first,
		 * iterator_last) exclusive.
		 *
		 * @param index The position of the elements to insert.
		 * @param iterator_first An iterator pointing to the first element to insert.
		 * @param iterator_last An iterator pointing to the last element to insert.
		 */
		Void Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last) override;

	public:
		/**
		 * @brief Inserts all elements from the specified collection into this array.
		 *
		 * @param collection The collection whose elements are to be inserted.
		 * 
		 * @return True if the insertion was successful and no duplicates were added.
		 */
		Void InsertAll(typename BaseType::ConstSelfTypeLRef collection) override;

		/**
		 * @brief Removes all the elements in the specified collection from this array.
		 *
		 * @param[in] collection The collection containing elements to be removed from this array.
		 *
		 * @return True if removal was successful and the elements were found.
		 */
		Bool RemoveAll(typename BaseType::ConstSelfTypeLRef collection) override;

		/**
		 * @brief Searches for all the elements in the specified collection in this array.
		 *
		 * @param[in] collection The collection containing elements to be  search for in this array.
		 *
		 * @return True if the specified elements were found in this array.
		 */
		Bool ContainsAll(typename BaseType::ConstSelfTypeLRef collection) override;

	public:
		Void Clear() override;
	};
}

#include "../../Private/Collections/StaticArray.cpp"

#endif