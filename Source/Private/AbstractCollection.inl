#ifndef ABSTRACT_COLLECTION_INL_HPP
#define ABSTRACT_COLLECTION_INL_HPP

#include "AbstractCollection.hpp"

namespace Forge
{
	template<typename InElementType, typename InAllocatorPolicy>
	FORGE_FORCE_INLINE AbstractCollection<InElementType, InAllocatorPolicy>::AbstractCollection(Size count, Size capacity)
		: m_count(count), m_capacity(capacity) {}

	template<typename InElementType, typename InAllocatorPolicy>
	FORGE_FORCE_INLINE Bool AbstractCollection<InElementType, InAllocatorPolicy>::IsFull() const
	{
		return this->m_count == this->m_capacity;
	}
	template<typename InElementType, typename InAllocatorPolicy>
	FORGE_FORCE_INLINE Bool AbstractCollection<InElementType, InAllocatorPolicy>::IsEmpty() const
	{
		return this->m_count == 0;
	}

	template<typename InElementType, typename InAllocatorPolicy>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, InAllocatorPolicy>::GetSize() const
	{
		return this->m_count * sizeof(InElementType);
	}
	template<typename InElementType, typename InAllocatorPolicy>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, InAllocatorPolicy>::GetCount() const
	{
		return this->m_count;
	}
	template<typename InElementType, typename InAllocatorPolicy>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, InAllocatorPolicy>::GetCapacity() const
	{
		return this->m_capacity;
	}


	template<typename InElementType>
	FORGE_FORCE_INLINE AbstractCollection<InElementType, NoAllocationPolicy>::AbstractCollection(Size count, Size capacity)
		: m_count(count), m_capacity(capacity) {}

	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractCollection<InElementType, NoAllocationPolicy>::IsFull() const
	{
		return this->m_count == this->m_capacity;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractCollection<InElementType, NoAllocationPolicy>::IsEmpty() const
	{
		return this->m_count == 0;
	}

	template<typename InElementType>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, NoAllocationPolicy>::GetSize() const
	{
		return this->m_capacity * sizeof(InElementType);
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, NoAllocationPolicy>::GetCount() const
	{
		return this->m_count;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Size AbstractCollection<InElementType, NoAllocationPolicy>::GetCapacity() const
	{
		return this->m_capacity;
	}
}

#endif