#ifndef ABSTRACT_COLLECTION_INL_HPP
#define ABSTRACT_COLLECTION_INL_HPP

#include "AbstractCollection.hpp"

namespace Forge
{
	template<typename InElementType, typename InAllocatorType>
	FORGE_FORCE_INLINE AbstractCollection<InElementType, InAllocatorType>::AbstractCollection(Size count, Size capacity)
		: m_count(count), m_capacity(capacity)
	{
		m_allocator.Initialize(capacity);
	}

	template<typename InElementType, typename InAllocatorType>
	FORGE_FORCE_INLINE Bool AbstractCollection<InElementType, InAllocatorType>::IsFull() const
	{
		return m_count == m_capacity;
	}
	template<typename InElementType, typename InAllocatorType>
	FORGE_FORCE_INLINE Bool AbstractCollection<InElementType, InAllocatorType>::IsEmpty() const
	{
		return m_count == 0;
	}

	template<typename InElementType, typename InAllocatorType>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, InAllocatorType>::GetSize() const
	{
		return m_count * sizeof(InElementType);
	}
	template<typename InElementType, typename InAllocatorType>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, InAllocatorType>::GetCount() const
	{
		return m_count;
	}
	template<typename InElementType, typename InAllocatorType>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, InAllocatorType>::GetCapacity() const
	{
		return m_capacity;
	}


	template<typename InElementType>
	FORGE_FORCE_INLINE AbstractCollection<InElementType, NoAllocationPolicy>::AbstractCollection(Size count, Size capacity)
		: m_count(count), m_capacity(capacity) {}

	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractCollection<InElementType, NoAllocationPolicy>::IsFull() const
	{
		return m_count == m_capacity;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractCollection<InElementType, NoAllocationPolicy>::IsEmpty() const
	{
		return m_count == 0;
	}

	template<typename InElementType>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, NoAllocationPolicy>::GetSize() const
	{
		return m_capacity * sizeof(InElementType);
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, NoAllocationPolicy>::GetCount() const
	{
		return m_count;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, NoAllocationPolicy>::GetCapacity() const
	{
		return m_capacity;
	}
}

#endif