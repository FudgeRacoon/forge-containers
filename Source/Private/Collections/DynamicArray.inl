#include "Collections/DynamicArray.hpp"

namespace Forge
{
	template<typename InType>
	static FORGE_FORCE_INLINE Void _shift_elements_forward(InType* data, Size to, Size steps, Size jumps = 0)
	{
		while(steps--) {
			MoveObject(data + to, *(data + ((to + 1) + jumps)));

			to++;
		}
	}
	template<typename InType>
	static FORGE_FORCE_INLINE Void _shift_elements_backward(InType* data, Size to, Size steps, Size jumps = 0)
	{
		while(steps--) {
			MoveObject(data + (to + jumps), *(data + (to - 1)));

			to--;
		}
	}

	template<typename InElementType, typename InAllocationPolicy>
	DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::DynamicArrayWithPolicy(AllocatorTypePtr allocator)
		: BaseType(0, 0)
	{
		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = nullptr;
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::DynamicArrayWithPolicy(Size capacity, AllocatorTypePtr allocator)
		: BaseType(0, capacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");

		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);

		ConstructArray(this->m_data, this->m_count);
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::DynamicArrayWithPolicy(ConstElementTypeLRef value, Size count, AllocatorTypePtr allocator)
		: BaseType(count, count)
	{
		if (this->m_count <= 0)
			throw ::std::invalid_argument("The count must be greater than 0");

		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);

		for (Size counter = 0; counter < this->m_count; counter++)
			CopyObject((this->m_data + counter), value);
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::DynamicArrayWithPolicy(ConstElementTypePtr buffer, Size count, AllocatorTypePtr allocator)
		: BaseType(count, count)
	{
		if (this->m_count <= 0)
			throw ::std::invalid_argument("The count must be greater than 0");

		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);

		CopyArray(this->m_data, buffer, this->m_count);
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::DynamicArrayWithPolicy(std::initializer_list<ElementType> list, AllocatorTypePtr allocator)
		: BaseType(list.size(), list.size())
	{
		if (this->m_count <= 0)
			throw ::std::invalid_argument("The count must be greater than 0");

		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);

		CopyArray(this->m_data, list.begin(), this->m_count);
	}

	template<typename InElementType, typename InAllocationPolicy>
	DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::DynamicArrayWithPolicy(SelfTypeRRef other)
		: BaseType(other.m_count, other.m_capacity)
	{
		*this = std::move(other);
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::DynamicArrayWithPolicy(ConstSelfTypeLRef other)
		: BaseType(other.m_count, other.m_capacity)
	{
		*this = other;
	}

	template<typename InElementType, typename InAllocationPolicy>
	DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::~DynamicArrayWithPolicy()
	{
		this->Clear();

		this->m_allocator.Deallocate(this->m_data);
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::SelfTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::operator=(SelfTypeRRef other)
	{
		if (this == &other)
			return;

		this->Clear();

		this->m_count = other.m_count;
		this->m_capacity = other.m_capacity;
		this->m_allocator = other.m_allocator;
		MoveArray(this->m_data, other.m_data, other.m_capacity);

		other.Clear();

		MemoryZero(this, sizeof(DynamicArrayWithPolicy<InElementType, InAllocationPolicy>));

		return *this;
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::SelfTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::operator=(ConstSelfTypeLRef other)
	{
		if (this == &other)
			return;

		this->Clear();

		this->m_count = other.m_count;
		this->m_capacity = other.m_capacity;
		this->m_allocator = other.m_allocator;
		CopyArray(this->m_data, other.m_data, other.m_capacity);

		return *this;
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ElementTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::operator[](Size index)
	{
		return this->m_data[index];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ConstElementTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::operator[](Size index) const
	{
		return this->m_data[index];
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename AbstractIterator<InElementType>::SelfTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::GetBeginIterator()
	{
		static Iterator it;

		it = Iterator(this->m_data);
		return it;
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename AbstractIterator<InElementType>::SelfTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::GetFinalIterator()
	{
		static Iterator it;

		it = Iterator(this->m_data + this->m_count);
		return it;
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ElementTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::At(Size index)
	{
		if (index >= this->m_count)
			throw ::std::out_of_range("The index is out of range");

		return this->m_data[index];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ConstElementTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::At(Size index) const
	{
		if (index >= this->m_count)
			throw ::std::out_of_range("The index is out of range");

		return this->m_data[index];
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ElementTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::GetBack()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[this->m_count - 1];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ElementTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::GetFront()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[0];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ConstElementTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::GetBack() const
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[this->m_count - 1];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ConstElementTypeLRef DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::GetFront() const
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[0];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ConstElementTypePtr DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::GetRawData() const
	{
		return this->m_data;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Compact()
	{
		this->Reserve((this->m_count +
			(this->m_memory_alignment - 1)) & ~(this->m_memory_alignment - 1));
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Resize(Size capacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");

		if (this->m_capacity >= capacity)
			return;

		Size new_capacity = std::max(this->m_capacity + (this->m_capacity / 2), capacity);

		this->Reserve((new_capacity + (this->m_memory_alignment - 1)) & ~(this->m_memory_alignment - 1));
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Reserve(Size capacity)
	{
		if (this->m_capacity == capacity)
			return;

		if (capacity <= 0) {
			this->m_capacity = 0;
			this->m_allocator->Deallocate(this->m_data);

			return;
		}

		this->m_capacity = capacity;
		this->m_data = this->m_allocator->Reallocate(this->m_data, this->m_capacity, this->m_memory_alignment);
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::PopBack()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		this->m_count--;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::PopFront()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		_shift_elements_forward(this->m_data, 0, this->m_count - 1);

		this->m_count--;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::PushBack(ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		this->Resize(this->m_count + 1);

		MoveObject((this->m_data + this->m_count), element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::PushFront(ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		this->Resize(this->m_count + 1);

		if (!this->IsEmpty())
			_shift_elements_backward(this->m_data, this->m_count, this->m_count);

		MoveObject(this->m_data, element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::PushBack(ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		this->Resize(this->m_count + 1);

		CopyObject((this->m_data + this->m_count), element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::PushFront(ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		this->Resize(this->m_count + 1);

		if (!this->IsEmpty())
			_shift_elements_backward(this->m_data, this->m_count, this->m_count);

		CopyObject(this->m_data, element);

		this->m_count++;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Remove(Size index)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		Size shift_to = index;
		Size shift_steps = this->m_count - index - 1;

		_shift_elements_forward(this->m_data, shift_to, shift_steps);

		this->m_count--;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
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

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Assign(Size index, ElementTypeRRef element)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		MoveObject(this->m_data[index], element);
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Assign(Size index, ConstElementTypeLRef element)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		CopyObject(this->m_data[index], element);
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
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
			CopyObject(this->m_data[index++], *itr);
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Insert(Size index, ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		this->Resize(this->m_count + 1);

		Size shift_to = this->m_count;
		Size shift_steps = this->m_count - index;

		_shift_elements_backward(this->m_data, shift_to, shift_steps);

		MoveObject(this->m_data[index], element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Insert(Size index, ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		this->Resize(this->m_count + 1);

		Size shift_to = this->m_count;
		Size shift_steps = this->m_count - index;

		_shift_elements_backward(this->m_data, shift_to, shift_steps);

		CopyObject(this->m_data[index], element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
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

		this->Resize(this->m_count + range_difference);

		Size shift_to = this->m_count;
		Size shift_steps = range_difference - index;
		Size shift_jumps = range_difference - 1;

		_shift_elements_backward(this->m_data, shift_to, shift_steps, shift_jumps);

		for (auto itr = itr_self_first; itr != itr_self_last; itr++)
			CopyObject(this->m_data[index++], *itr);

		this->m_count += range_difference;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::InsertAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		if(this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_capacity < this->m_count + collection.GetCount())
			throw ::std::length_error("The static array does not have sufficient capacity");

		this->Resize(this->m_count + collection.GetCount());

		for (Size counter = 0; counter < collection.GetCount(); counter++)
			this->PushBack(collection[counter]);
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::RemoveAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		std::logic_error("RemoveAll is not implemented in version 0.1");
	}
	template<typename InElementType, typename InAllocationPolicy>
	Bool DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::ContainsAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		std::logic_error("ContainsAll is not implemented in version 0.1");

		return false;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArrayWithPolicy<InElementType, InAllocationPolicy>::Clear()
	{
		DestructArray(this->m_data, this->m_count);

		this->m_count = 0;
	}


	template<typename InElementType>
	DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::DynamicArrayWithPolicy(AllocatorTypePtr allocator)
		: BaseType(0, 0)
	{
		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = nullptr;
	}
	template<typename InElementType>
	DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::DynamicArrayWithPolicy(Size capacity, AllocatorTypePtr allocator)
		: BaseType(0, capacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");

		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);

		ConstructArray(this->m_data, this->m_count);
	}
	template<typename InElementType>
	DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::DynamicArrayWithPolicy(ConstElementTypeLRef value, Size count, AllocatorTypePtr allocator)
		: BaseType(count, count)
	{
		if (this->m_count <= 0)
			throw ::std::invalid_argument("The count must be greater than 0");

		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);

		for (Size counter = 0; counter < this->m_count; counter++)
			CopyObject((this->m_data + counter), value);
	}
	template<typename InElementType>
	DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::DynamicArrayWithPolicy(ConstElementTypePtr buffer, Size count, AllocatorTypePtr allocator)
		: BaseType(count, count)
	{
		if (this->m_count <= 0)
			throw ::std::invalid_argument("The count must be greater than 0");

		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);

		CopyArray(this->m_data, buffer, this->m_count);
	}
	template<typename InElementType>
	DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::DynamicArrayWithPolicy(std::initializer_list<ElementType> list, AllocatorTypePtr allocator)
		: BaseType(list.size(), list.size())
	{
		if (this->m_count <= 0)
			throw ::std::invalid_argument("The count must be greater than 0");

		constexpr U8 type_alignment = alignof(InElementType);

		this->m_memory_alignment = type_alignment;
		this->m_capacity_alignment = 16;

		this->m_allocator = allocator;
		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);

		CopyArray(this->m_data, list.begin(), this->m_count);
	}

	template<typename InElementType>
	DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::DynamicArrayWithPolicy(SelfTypeRRef other)
		: BaseType(other.m_count, other.m_capacity)
	{
		*this = std::move(other);
	}
	template<typename InElementType>
	DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::DynamicArrayWithPolicy(ConstSelfTypeLRef other)
		: BaseType(other.m_count, other.m_capacity)
	{
		*this = other;
	}

	template<typename InElementType>
	DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::~DynamicArrayWithPolicy()
	{
		this->Clear();

		this->m_allocator.Deallocate(this->m_data);
	}

	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::SelfTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::operator=(SelfTypeRRef other)
	{
		if (this == &other)
			return;

		this->Clear();

		this->m_count = other.m_count;
		this->m_capacity = other.m_capacity;
		this->m_allocator = other.m_allocator;
		MoveArray(this->m_data, other.m_data, other.m_capacity);

		other.Clear();

		MemoryZero(this, sizeof(DynamicArrayWithPolicy<InElementType, InAllocationPolicy>));

		return *this;
	}
	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::SelfTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::operator=(ConstSelfTypeLRef other)
	{
		if (this == &other)
			return;

		this->Clear();

		this->m_count = other.m_count;
		this->m_capacity = other.m_capacity;
		this->m_allocator = other.m_allocator;
		CopyArray(this->m_data, other.m_data, other.m_capacity);

		return *this;
	}

	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ElementTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::operator[](Size index)
	{
		return this->m_data[index];
	}
	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ConstElementTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::operator[](Size index) const
	{
		return this->m_data[index];
	}

	template<typename InElementType>
	typename AbstractIterator<InElementType>::SelfTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::GetBeginIterator()
	{
		static Iterator it;

		it = Iterator(this->m_data);
		return it;
	}
	template<typename InElementType>
	typename AbstractIterator<InElementType>::SelfTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::GetFinalIterator()
	{
		static Iterator it;

		it = Iterator(this->m_data + this->m_count);
		return it;
	}

	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ElementTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::At(Size index)
	{
		if (index >= this->m_count)
			throw ::std::out_of_range("The index is out of range");

		return this->m_data[index];
	}
	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ConstElementTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::At(Size index) const
	{
		if (index >= this->m_count)
			throw ::std::out_of_range("The index is out of range");

		return this->m_data[index];
	}

	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ElementTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::GetBack()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[this->m_count - 1];
	}
	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ElementTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::GetFront()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[0];
	}
	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ConstElementTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::GetBack() const
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[this->m_count - 1];
	}
	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ConstElementTypeLRef DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::GetFront() const
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[0];
	}
	template<typename InElementType>
	typename DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ConstElementTypePtr DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::GetRawData() const
	{
		return this->m_data;
	}

	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Compact()
	{
		this->Reserve((this->m_count +
			(this->m_memory_alignment - 1)) & ~(this->m_memory_alignment - 1));
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Resize(Size capacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");

		if (this->m_capacity >= capacity)
			return;

		Size new_capacity = std::max(this->m_capacity + (this->m_capacity / 2), capacity);

		this->Reserve((new_capacity + (this->m_memory_alignment - 1)) & ~(this->m_memory_alignment - 1));
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Reserve(Size capacity)
	{
		if (this->m_capacity == capacity)
			return;

		if (capacity <= 0) {
			this->m_capacity = 0;
			this->m_allocator->Deallocate(this->m_data);

			return;
		}

		this->m_capacity = capacity;
		this->m_data = this->m_allocator->Reallocate(this->m_data, this->m_capacity, this->m_memory_alignment);
	}

	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::PopBack()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		this->m_count--;
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::PopFront()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		_shift_elements_forward(this->m_data, 0, this->m_count - 1);

		this->m_count--;
	}

	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::PushBack(ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		this->Resize(this->m_count + 1);

		MoveObject((this->m_data + this->m_count), element);

		this->m_count++;
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::PushFront(ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		this->Resize(this->m_count + 1);

		if (!this->IsEmpty())
			_shift_elements_backward(this->m_data, this->m_count, this->m_count);

		MoveObject(this->m_data, element);

		this->m_count++;
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::PushBack(ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		this->Resize(this->m_count + 1);

		CopyObject((this->m_data + this->m_count), element);

		this->m_count++;
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::PushFront(ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		this->Resize(this->m_count + 1);

		if (!this->IsEmpty())
			_shift_elements_backward(this->m_data, this->m_count, this->m_count);

		CopyObject(this->m_data, element);

		this->m_count++;
	}

	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Remove(Size index)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		Size shift_to = index;
		Size shift_steps = this->m_count - index - 1;

		_shift_elements_forward(this->m_data, shift_to, shift_steps);

		this->m_count--;
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
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

	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Assign(Size index, ElementTypeRRef element)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		MoveObject(this->m_data[index], element);
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Assign(Size index, ConstElementTypeLRef element)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		CopyObject(this->m_data[index], element);
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
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
			CopyObject(this->m_data[index++], *itr);
	}

	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Insert(Size index, ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		this->Resize(this->m_count + 1);

		Size shift_to = this->m_count;
		Size shift_steps = this->m_count - index;

		_shift_elements_backward(this->m_data, shift_to, shift_steps);

		MoveObject(this->m_data[index], element);

		this->m_count++;
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Insert(Size index, ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		this->Resize(this->m_count + 1);

		Size shift_to = this->m_count;
		Size shift_steps = this->m_count - index;

		_shift_elements_backward(this->m_data, shift_to, shift_steps);

		CopyObject(this->m_data[index], element);

		this->m_count++;
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
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

		this->Resize(this->m_count + range_difference);

		Size shift_to = this->m_count;
		Size shift_steps = range_difference - index;
		Size shift_jumps = range_difference - 1;

		_shift_elements_backward(this->m_data, shift_to, shift_steps, shift_jumps);

		for (auto itr = itr_self_first; itr != itr_self_last; itr++)
			CopyObject(this->m_data[index++], *itr);

		this->m_count += range_difference;
	}

	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::InsertAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		if(this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_capacity < this->m_count + collection.GetCount())
			throw ::std::length_error("The static array does not have sufficient capacity");

		this->Resize(this->m_count + collection.GetCount());

		for (Size counter = 0; counter < collection.GetCount(); counter++)
			this->PushBack(collection[counter]);
	}
	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::RemoveAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		std::logic_error("RemoveAll is not implemented in version 0.1");
	}
	template<typename InElementType>
	Bool DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::ContainsAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		std::logic_error("ContainsAll is not implemented in version 0.1");

		return false;
	}

	template<typename InElementType>
	Void DynamicArrayWithPolicy<InElementType, HeapAllocationPolicy>::Clear()
	{
		DestructArray(this->m_data, this->m_count);

		this->m_count = 0;
	}
}