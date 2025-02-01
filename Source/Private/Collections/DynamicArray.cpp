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
	class DynamicArray<InElementType, InAllocationPolicy>::IteratorImpl
	{
	public:
		Iterator m_begin, m_final;

	public:
		IteratorImpl()
			: m_begin(nullptr), m_final(nullptr) {}

	public:
		typename Iterator::SelfTypeLRef GetBeginIterator(ElementTypePtr ptr, Size count)
		{
			this->m_begin = Iterator(ptr);

			return this->m_begin;
		}
		typename Iterator::SelfTypeLRef GetFinalIterator(ElementTypePtr ptr, Size count)
		{
			this->m_final = Iterator(ptr + count);

			return this->m_final;
		}
	};

	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::DynamicArray(AllocatorTypePtr allocator)
		: BaseType(0, 0)
	{
		this->m_data = nullptr;
		this->m_iterator_pimpl = ::std::make_unique<IteratorImpl>();

		this->m_allocator = allocator;
		this->m_allocator ? this->m_memory_storage = MemoryStorage::EXTERNAL :
			this->m_memory_storage = MemoryStorage::INTERNAL;

		if (this->m_memory_storage == MemoryStorage::INTERNAL)
			this->m_allocator = new AllocatorType(); // TODO: This is going to have to take in a capacity value
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::DynamicArray(Size capacity, AllocatorTypePtr allocator)
		: BaseType(0, capacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");

		this->m_iterator_pimpl = ::std::make_unique<IteratorImpl>();

		this->m_allocator = allocator;
		this->m_allocator ? this->m_memory_storage = MemoryStorage::EXTERNAL :
			this->m_memory_storage = MemoryStorage::INTERNAL;

		if (this->m_memory_storage == MemoryStorage::INTERNAL)
			this->m_allocator = new AllocatorType(); // TODO: This is going to have to take in a capacity value

		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);
		ConstructArray(this->m_data, this->m_count); // TODO: This oveload will default construct the memory region
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::DynamicArray(ConstElementTypeLRef value, Size count, AllocatorTypePtr allocator)
		: BaseType(count, count)
	{
		if (this->m_count <= 0)
			throw ::std::invalid_argument("The count must be greater than 0");

		this->m_iterator_pimpl = ::std::make_unique<IteratorImpl>();

		this->m_allocator = allocator;
		this->m_allocator ? this->m_memory_storage = MemoryStorage::EXTERNAL :
			this->m_memory_storage = MemoryStorage::INTERNAL;

		if (this->m_memory_storage == MemoryStorage::INTERNAL)
			this->m_allocator = new AllocatorType(); // TODO: This is going to have to take in a capacity value

		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);
		for (Size counter = 0; counter < this->m_count; counter++)
			CopyObject((this->m_data + counter), value);
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::DynamicArray(ConstElementTypePtr buffer, Size count, AllocatorTypePtr allocator)
		: BaseType(count, count)
	{
		if (this->m_count <= 0)
			throw ::std::invalid_argument("The count must be greater than 0");

		this->m_iterator_pimpl = ::std::make_unique<IteratorImpl>();

		this->m_allocator = allocator;
		this->m_allocator ? this->m_memory_storage = MemoryStorage::EXTERNAL :
			this->m_memory_storage = MemoryStorage::INTERNAL;

		if (this->m_memory_storage == MemoryStorage::INTERNAL)
			this->m_allocator = new AllocatorType(); // TODO: This is going to have to take in a capacity value

		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);
		CopyArray(this->m_data, buffer, this->m_count); // TODO: This needs to be updated to take in a const source pointer
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::DynamicArray(std::initializer_list<ElementType> list, AllocatorTypePtr allocator)
		: BaseType(list.size(), list.size())
	{
		if (this->m_count <= 0)
			throw ::std::invalid_argument("The count must be greater than 0");

		this->m_iterator_pimpl = ::std::make_unique<IteratorImpl>();

		this->m_allocator = allocator;
		this->m_allocator ? this->m_memory_storage = MemoryStorage::EXTERNAL :
			this->m_memory_storage = MemoryStorage::INTERNAL;

		if (this->m_memory_storage == MemoryStorage::INTERNAL)
			this->m_allocator = new AllocatorType(); // TODO: This is going to have to take in a capacity value

		this->m_data = this->m_allocator.Allocate(this->m_capcity, this->m_memory_alignment);
		CopyArray(this->m_data, list.begin(), this->m_count); // TODO: This needs to be updated to take in a const source pointer
	}

	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::DynamicArray(SelfTypeRRef other)
		: BaseType(other.m_count, other.m_capacity)
	{
		if (this == &other)
			return;

		this->Clear();

		MoveObject(this->m_count, other.m_count); // TODO: This is going to take in a the actual value rather than its address
		MoveObject(this->m_capacity, other.m_capacity); // TODO: This is going to take in a the actual value rather than its address
		MoveObject(this->m_allocator, other.m_allocator); // TODO: This is going to take in a the actual value rather than its address

		this->m_iterator_pimpl = std::move(other.m_iterator_pimpl);

		MoveArray(this->m_data, other.m_data, other.m_capacity);

		other.Clear();
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::DynamicArray(ConstSelfTypeLRef other)
		: BaseType(other.m_count, other.m_capacity)
	{
		if (this == &other)
			return;

		this->Clear();

		CopyObject(this->m_count, other.m_count); // TODO: This is going to take in a the actual value rather than its address
		CopyObject(this->m_capacity, other.m_capacity); // TODO: This is going to take in a the actual value rather than its address

		if (other.m_memory_alignment == MemoryStorage::INTERNAL) {
			this->m_allocator = new AllocatorType();
			CopyObject(*(this->m_allocator), *(other.m_allocator)); // TODO: This is going to take in a the actual value rather than its address
		}
		else {
			CopyObject(this->m_allocator, other.m_allocator); // TODO: This is going to take in a the actual value rather than its address
		}

		this->m_iterator_pimpl = ::std::make_unique<IteratorImpl>();

		CopyArray(this->m_data, other.m_data, other.m_capacity);
	}

	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::~DynamicArray()
	{
		this->Clear();

		this->m_iterator_pimpl.reset(nullptr);
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::SelfTypeLRef DynamicArray<InElementType, InAllocationPolicy>::operator=(SelfTypeRRef other)
	{
		if (this == &other)
			return;

		this->Clear();

		MoveObject(this->m_count, other.m_count); // TODO: This is going to take in a the actual value rather than its address
		MoveObject(this->m_capacity, other.m_capacity); // TODO: This is going to take in a the actual value rather than its address
		MoveObject(this->m_allocator, other.m_allocator); // TODO: This is going to take in a the actual value rather than its address

		this->m_iterator_pimpl = std::move(other.m_iterator_pimpl);

		MoveArray(this->m_data, other.m_data, other.m_capacity);

		other.Clear();

		return *this;
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::SelfTypeLRef DynamicArray<InElementType, InAllocationPolicy>::operator=(ConstSelfTypeLRef other)
	{
		if (this == &other)
			return;

		this->Clear();

		CopyObject(this->m_count, other.m_count); // TODO: This is going to take in a the actual value rather than its address
		CopyObject(this->m_capacity, other.m_capacity); // TODO: This is going to take in a the actual value rather than its address

		if (other.m_memory_alignment == MemoryStorage::INTERNAL) {
			this->m_allocator = new AllocatorType();
			CopyObject(*(this->m_allocator), *(other.m_allocator)); // TODO: This is going to take in a the actual value rather than its address
		}
		else
			CopyObject(this->m_allocator, other.m_allocator); // TODO: This is going to take in a the actual value rather than its address

		CopyArray(this->m_data, other.m_data, other.m_capacity);

		return *this;
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::ElementTypeLRef DynamicArray<InElementType, InAllocationPolicy>::operator[](Size index)
	{
		return this->m_data[index];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::ConstElementTypeLRef DynamicArray<InElementType, InAllocationPolicy>::operator[](Size index) const
	{
		return this->m_data[index];
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename AbstractIterator<InElementType>::SelfTypeLRef DynamicArray<InElementType, InAllocationPolicy>::GetBeginIterator()
	{
		return this->m_iterator_pimpl->GetBeginIterator(this->m_data, this->m_count);
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename AbstractIterator<InElementType>::SelfTypeLRef DynamicArray<InElementType, InAllocationPolicy>::GetFinalIterator()
	{
		return this->m_iterator_pimpl->GetFinalIterator(this->m_data, this->m_count);
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::ElementTypeLRef DynamicArray<InElementType, InAllocationPolicy>::At(Size index)
	{
		if (index >= this->m_count)
			throw ::std::out_of_range("The index is out of range");

		return this->m_data[index];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::ConstElementTypeLRef DynamicArray<InElementType, InAllocationPolicy>::At(Size index) const
	{
		if (index >= this->m_count)
			throw ::std::out_of_range("The index is out of range");

		return this->m_data[index];
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::ElementTypeLRef DynamicArray<InElementType, InAllocationPolicy>::GetBack()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[this->m_count - 1];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::ElementTypeLRef DynamicArray<InElementType, InAllocationPolicy>::GetFront()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[0];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::ConstElementTypeLRef DynamicArray<InElementType, InAllocationPolicy>::GetBack() const
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[this->m_count - 1];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::ConstElementTypeLRef DynamicArray<InElementType, InAllocationPolicy>::GetFront() const
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		return this->m_data[0];
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::ConstElementTypePtr DynamicArray<InElementType, InAllocationPolicy>::GetRawData() const
	{
		return this->m_data;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::Compact()
	{

	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::Resize(Size capacity)
	{

	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::Reserve(Size capacity)
	{
		if (this->m_capacity <= 0)
			throw ::std::invalid_argument("The capacity must be greater than 0");

		if (this->m_capacity == capacity)
			return;

		if (this->m_memory_storage == MemoryStorage::INTERNAL)
			this->m_allocator->Reallocate(this->m_data, this->m_capacity);
		else
		{
			ElementTypePtr new_data = this->m_allocator->Allocate(capacity);

			MoveArray(new_data, this->m_data, capacity);

			this->m_allocator->Deallocate(this->m_data);
			this->m_data = new_data;
		}

		this->m_capacity = capacity;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::PopBack()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		this->m_count--;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::PopFront()
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		_shift_elements_forward(this->m_data, 0, this->m_count - 1);

		this->m_count--;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::PushBack(ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		MoveObject((this->m_data + this->m_count), element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::PushFront(ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (!this->IsEmpty())
			_shift_elements_backward(this->m_data, this->m_count, this->m_count);

		MoveObject(this->m_data, element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::PushBack(ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		CopyObject((this->m_data + this->m_count), element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::PushFront(ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (!this->IsEmpty())
			_shift_elements_backward(this->m_data, this->m_count, this->m_count);

		CopyObject(this->m_data, element);

		this->m_count++;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::Remove(Size index)
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
	Void DynamicArray<InElementType, InAllocationPolicy>::Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
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
	Void DynamicArray<InElementType, InAllocationPolicy>::Assign(Size index, ElementTypeRRef element)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		MoveObject(this->m_data[index], element);
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::Assign(Size index, ConstElementTypeLRef element)
	{
		if (this->IsEmpty())
			throw ::std::length_error("The static array is empty");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		CopyObject(this->m_data[index], element);
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
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
	Void DynamicArray<InElementType, InAllocationPolicy>::Insert(Size index, ElementTypeRRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		Size shift_to = this->m_count;
		Size shift_steps = this->m_count - index;

		_shift_elements_backward(this->m_data, shift_to, shift_steps);

		MoveObject(this->m_data[index], element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::Insert(Size index, ConstElementTypeLRef element)
	{
		if (this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_count <= index)
			throw ::std::out_of_range("The index is out of range");

		Size shift_to = this->m_count;
		Size shift_steps = this->m_count - index;

		_shift_elements_backward(this->m_data, shift_to, shift_steps);

		CopyObject(this->m_data[index], element);

		this->m_count++;
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
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
			CopyObject(this->m_data[index++], *itr);

		this->m_count += range_difference;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::InsertAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		if(this->IsFull())
			throw ::std::length_error("The static array is full");

		if (this->m_capacity < this->m_count + collection.GetCount())
			throw ::std::length_error("The static array does not have sufficient capacity");

		for (Size counter = 0; counter < collection.GetCount(); counter++)
			this->PushBack(collection[counter]);
	}
	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::RemoveAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		std::logic_error("RemoveAll is not implemented in version 0.1");
	}
	template<typename InElementType, typename InAllocationPolicy>
	Bool DynamicArray<InElementType, InAllocationPolicy>::ContainsAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		std::logic_error("ContainsAll is not implemented in version 0.1");

		return false;
	}

	template<typename InElementType, typename InAllocationPolicy>
	Void DynamicArray<InElementType, InAllocationPolicy>::Clear()
	{
		DestructArray(this->m_data, this->m_count);

		this->m_count = 0;
	}
}