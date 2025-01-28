#include "Collections/DynamicArray.hpp"

namespace Forge
{
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
		this->m_pimpl = ::std::make_unique<IteratorImpl>();

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

		this->m_pimpl = ::std::make_unique<IteratorImpl>();

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

		this->m_pimpl = ::std::make_unique<IteratorImpl>();

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

		this->m_pimpl = ::std::make_unique<IteratorImpl>();

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

		this->m_pimpl = ::std::make_unique<IteratorImpl>();

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
		: BaseType(other.m_count, InCapacity)
	{
		*this = ::std::move(other);
	}
	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::DynamicArray(ConstSelfTypeLRef other)
		: BaseType(other.m_count, InCapacity)
	{
		*this = other;
	}

	template<typename InElementType, typename InAllocationPolicy>
	DynamicArray<InElementType, InAllocationPolicy>::~DynamicArray()
	{
		this->Clear();
	}

	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::SelfTypeLRef DynamicArray<InElementType, InAllocationPolicy>::operator=(SelfTypeRRef other)
	{
		if (this != &other)
		{
			this->Clear();

			this->m_count = other.m_count;
			this->m_capacity = other.m_capacity;

			this->m_pImpl = std::move(other.m_pImpl);

			MoveArray(this->m_data, other.m_data, other.m_capacity);

			other.Clear();
		}

		return *this;
	}
	template<typename InElementType, typename InAllocationPolicy>
	typename DynamicArray<InElementType, InAllocationPolicy>::SelfTypeLRef DynamicArray<InElementType, InAllocationPolicy>::operator=(ConstSelfTypeLRef other)
	{
		if (this != &other)
		{
			this->Clear();

			this->m_count = other.m_count;

			CopyArray(this->m_data, const_cast<ElementTypePtr>(other.m_data), other.m_capacity);
		}

		return *this;
	}

}