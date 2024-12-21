#include "Collections/StaticArray.hpp"

namespace Forge
{
	template<typename InType>
	static FORGE_FORCE_INLINE Void _shift_elements_forward(InType* data, Size to, Size steps, Size jumps = 0)
	{
		while(steps--) {
			MoveObject(data[to], data[(to + 1) + jumps]);

			to++;
		}
	}
	template<typename InType>
	static FORGE_FORCE_INLINE Void _shift_elements_backward(InType* data, Size to, Size steps, Size jumps = 0)
	{
		while(steps--) {
			MoveObject(data[to + jumps], data[to - 1]);

			to--;
		}
	}

	template <typename InElementType, Size InCapacity>
	StaticArray<InElementType, InCapacity>::StaticArray()
		: BaseType(0, InCapacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");
	}
	template <typename InElementType, Size InCapacity>
	StaticArray<InElementType, InCapacity>::StaticArray(ConstElementTypeLRef value, Size count)
		: BaseType(count, InCapacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");

		if (this->m_count <= 0 || this->m_count > this->m_capacity)
			throw ::std::invalid_argument("The count must be greater than 0 and less than the capacity");

		for (Size counter = 0; counter <= this->m_count; counter++)
			CopyObject(this->m_data[counter], value);
	}
	template <typename InElementType, Size InCapacity>
	StaticArray<InElementType, InCapacity>::StaticArray(ElementTypePtr buffer, Size count)
		: BaseType(count, InCapacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");

		if (this->m_count <= 0 || this->m_count > this->m_capacity)
			throw ::std::invalid_argument("The count must be greater than 0 and less than the capacity");

		CopyArray(this->m_data, buffer, this->m_count);
	}
	template<typename InElementType, Size InCapacity>
	StaticArray<InElementType, InCapacity>::StaticArray(std::initializer_list<ElementType> init_list)
		: BaseType(init_list.size(), InCapacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");

		if (this->m_count <= 0 || this->m_count > this->m_capacity)
			throw ::std::invalid_argument("The count must be greater than 0 and less than the capacity");

		CopyArray(this->m_data, init_list.begin(), this->m_count);
	}

	template <typename InElementType, Size InCapacity>
	StaticArray<InElementType, InCapacity>::StaticArray(SelfTypeRRef other)
		: BaseType(other.m_count, InCapacity)
	{
		*this = ::std::move(other);
	}
	template <typename InElementType, Size InCapacity>
	StaticArray<InElementType, InCapacity>::StaticArray(ConstSelfTypeLRef other)
		: BaseType(other.m_count, InCapacity)
	{
		*this = other;
	}

	template <typename InElementType, Size InCapacity>
	StaticArray<InElementType, InCapacity>::~StaticArray()
	{
		this->Clear();
	}

	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::SelfTypeLRef StaticArray<InElementType, InCapacity>::operator=(SelfTypeRRef other)
	{
		if (this != &other)
		{
			this->Clear();

			this->m_count = other.m_count;

			MoveArray(this->m_data, other.m_data, other.m_capacity);

			other.Clear();
		}

		return *this;
	}
	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::SelfTypeLRef StaticArray<InElementType, InCapacity>::operator=(ConstSelfTypeLRef other)
	{
		if (this != &other)
		{
			this->Clear();

			this->m_count = other.m_count;

			CopyArray(this->m_data, const_cast<ElementTypePtr>(other.m_data), other.m_capacity);
		}

		return *this;
	}

	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::ElementTypeLRef StaticArray<InElementType, InCapacity>::operator[](Size index)
	{
		return this->m_data[index];
	}
	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::ConstElementTypeLRef StaticArray<InElementType, InCapacity>::operator[](Size index) const
	{
		return this->m_data[index];
	}

	template <typename InElementType, Size InCapacity>
	typename AbstractIterator<InElementType>::SelfTypeLRef StaticArray<InElementType, InCapacity>::GetBeginIterator()
	{
		static Iterator it;

		it = Iterator(this->m_data);
		return it;
	}
	template <typename InElementType, Size InCapacity>
	typename AbstractIterator<InElementType>::SelfTypeLRef StaticArray<InElementType, InCapacity>::GetFinalIterator()
	{
		static Iterator it;

		it = Iterator(this->m_data + this->m_count);
		return it;
	}

	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::ElementTypeLRef StaticArray<InElementType, InCapacity>::At(Size index)
	{
	   if (index >= this->m_count)
			throw ::std::out_of_range("The index is out of range");

		return this->m_data[index];
	}
	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::ConstElementTypeLRef StaticArray<InElementType, InCapacity>::At(Size index) const
	{
		if (index >= this->m_count)
			throw ::std::out_of_range("The index is out of range");

		return this->m_data[index];
	}

	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::ElementTypeLRef StaticArray<InElementType, InCapacity>::GetBack()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[this->m_count - 1];
	}
	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::ElementTypeLRef StaticArray<InElementType, InCapacity>::GetFront()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[0];
	}
	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::ConstElementTypeLRef StaticArray<InElementType, InCapacity>::GetBack() const
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[this->m_count - 1];
	}
	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::ConstElementTypeLRef StaticArray<InElementType, InCapacity>::GetFront() const
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[0];
	}
	template <typename InElementType, Size InCapacity>
	typename StaticArray<InElementType, InCapacity>::ConstElementTypePtr StaticArray<InElementType, InCapacity>::GetRawData() const
	{
		return this->m_data;
	}

	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::PopBack()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		this->m_count--;
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::PopFront()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		_shift_elements_forward(this->m_data, 0, this->m_count - 1);

		this->m_count--;
	}

	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::PushBack(ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		MoveObject(this->m_data[this->m_count], element);

		this->m_count++;
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::PushFront(ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (!this->IsEmpty())
			_shift_elements_backward(this->m_data, this->m_count, this->m_count);

		MoveObject(this->m_data[0], element);

		this->m_count++;
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::PushBack(ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		CopyObject(this->m_data[this->m_count], element);

		this->m_count++;
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::PushFront(ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (!this->IsEmpty())
			_shift_elements_backward(this->m_data, this->m_count, this->m_count);

		CopyObject(this->m_data[0], element);

		this->m_count++;
	}

	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::Remove(Size index)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		Size shift_to = index;
		Size shift_steps = this->m_count - index - 1;

		_shift_elements_forward(this->m_data, shift_to, shift_steps);

		this->m_data[--this->m_count] = 0;
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (iterator_first < this->GetBeginIterator() || iterator_first >= this->GetFinalIterator())
			throw ::std::out_of_range("The static array first iterator is out of range");

		if (iterator_last < this->GetBeginIterator() || iterator_last > this->GetFinalIterator())
			throw ::std::out_of_range("The static array last iterator is out of range");

		Size range_offset = iterator_first - this->GetBeginIterator();
		Size range_difference = iterator_last - iterator_first;

		Size shift_to = range_offset;
		Size shift_steps = range_difference;
		Size shift_jumps = range_difference - 1;

		_shift_elements_forward(this->m_data, shift_to, shift_steps, shift_jumps);

		this->m_count -= range_difference;
	}

	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::Assign(Size index, ElementTypeRRef element)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		this->m_data[index] = ::std::move(element);
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::Assign(Size index, ConstElementTypeLRef element)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		this->m_data[index] = element;
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		if (this->m_count < index + (iterator_last - iterator_first))
			throw ::std::out_of_range("The range of elements exceeds the current count");

		auto itr_first = dynamic_cast<Iterator&>(iterator_first);
		auto itr_last = dynamic_cast<Iterator&>(iterator_last);

		for (auto itr = itr_first; itr != itr_last; itr++)
			this->m_data[index++] = *itr;
	}

	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::Insert(Size index, ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		Size shift_to = this->m_count;
		Size shift_steps = this->m_count - index;

		_shift_elements_backward(this->m_data, shift_to, shift_steps);

		this->m_data[index] = ::std::move(element);

		this->m_count++;
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::Insert(Size index, ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		Size shift_to = this->m_count;
		Size shift_steps = this->m_count - index;

		_shift_elements_backward(this->m_data, shift_to, shift_steps);

		this->m_data[index] = element;

		this->m_count++;
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		if (this->m_capacity < this->m_count + (iterator_last - iterator_first))
			throw ::std::length_error("The static array does not have sufficient capacity");

		auto itr_self_first = dynamic_cast<Iterator&>(iterator_first);
		auto itr_self_last = dynamic_cast<Iterator&>(iterator_last);

		Size range_difference = itr_self_last - itr_self_first;

		Size shift_to = this->m_count;
		Size shift_steps = range_difference - index;
		Size shift_jumps = range_difference - 1;

		_shift_elements_backward(this->m_data, shift_to, shift_steps, shift_jumps);

		for (auto itr = itr_self_first; itr != itr_self_last; itr++)
			this->m_data[index++] = *itr;

		this->m_count += range_difference;
	}

	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::InsertAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		if(this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_capacity < this->m_count + collection.GetCount())
			throw ::std::length_error("The static array does not have sufficient capacity");

		for (Size counter = 0; counter < collection.GetCount(); counter++)
			this->PushBack(collection[counter]);
	}
	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::RemoveAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		std::logic_error("RemoveAll is not implemented in version 0.1");
	}
	template <typename InElementType, Size InCapacity>
	Bool StaticArray<InElementType, InCapacity>::ContainsAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		std::logic_error("ContainsAll is not implemented in version 0.1");

		return false;
	}

	template <typename InElementType, Size InCapacity>
	Void StaticArray<InElementType, InCapacity>::Clear()
	{
		DestructArray(this->m_data, this->m_count);

		this->m_count = 0;
	}
}