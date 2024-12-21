#ifndef ALLOCATOR_INL_HPP
#define ALLOCATOR_INL_HPP

#include "Compiler.hpp"

#include "Memory/Allocator.hpp"
#include "Memory/MemoryUtilities.hpp"

namespace Forge
{
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Size Allocator<AllocationPolicy>::GetCapacity()
	{
		return m_capacity;
	}
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Float32 Allocator<AllocationPolicy>::GetUsedSpace()
	{
		return m_used_space;
	}
	
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Size Allocator<AllocationPolicy>::GetPeakSize()
	{
		return m_allocation_stats.m_peak_size;
	}
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Size Allocator<AllocationPolicy>::GetTotalSize()
	{
		return m_allocation_stats.m_total_size;
	}
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Size Allocator<AllocationPolicy>::GetNumOfAllocations()
	{
		return m_allocation_stats.m_num_of_allocs;
	}
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Size Allocator<AllocationPolicy>::GetNumOfDeallocations()
	{
		return m_allocation_stats.m_num_of_deallocs;
	}

	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Size Allocator<AllocationPolicy>::GetAllocatedSize(VoidPtr address)
	{
		return 0;
	}

	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Void Allocator<AllocationPolicy>::Initialize(Size capacity)
	{   
		m_capacity = capacity;
		m_used_space = 0.0f;

		m_allocation_stats.m_peak_size = 0;
		m_allocation_stats.m_total_size = 0;
		m_allocation_stats.m_num_of_allocations = 0;
		m_allocation_stats.m_num_of_deallocations = 0;

		m_allocation_policy.Initialize(capacity);
	}
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Void Allocator<AllocationPolicy>::Deinitialize()
	{
		m_capacity = 0;
		m_used_space = 0.0f;

		m_allocation_stats.m_peak_size = 0;
		m_allocation_stats.m_total_size = 0;
		m_allocation_stats.m_num_of_allocations = 0;
		m_allocation_stats.m_num_of_deallocations = 0;

		m_allocation_policy.Deinitialize();
	}

	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE VoidPtr Allocator<AllocationPolicy>::Allocate(Size size, Size alignment)
	{
		if(size == 0) {
			return nullptr;
		}

		if(alignment < 1 || (alignment & (alignment - 1)) != 0) {
			return nullptr;
		}

		VoidPtr address = m_allocation_policy.Allocate(size, alignment);

		if(m_allocation_stats.m_peak_size < size) {
			m_allocation_stats.m_peak_size = size;
		}

		m_allocation_stats.m_total_size += size;
		m_allocation_stats.m_num_of_allocations += 1;

		m_used_space = (m_allocation_stats.m_total_size / m_capacity) * 100.0f;

		return address;
	}
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE VoidPtr Allocator<AllocationPolicy>::Callocate(Size size, Byte value, Size alignment)
	{
		if(size == 0) {
			return nullptr;
		}

		if(alignment < 1 || (alignment & (alignment - 1)) != 0) {
			return nullptr;
		}

		VoidPtr address = m_allocation_policy.Callocate(size, value, alignment);

		if(m_allocation_stats.m_peak_size < size) {
			m_allocation_stats.m_peak_size = size;
		}

		m_allocation_stats.m_total_size += size;
		m_allocation_stats.m_num_of_allocations += 1;

		m_used_space = (m_allocation_stats.m_total_size / m_capacity) * 100.0f;

		return address;
	}
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE VoidPtr Allocator<AllocationPolicy>::Reallocate(VoidPtr address, Size size, Size alignment)
	{
		if(size == 0) {
			this->Deallocate(address);
			return nullptr;
		}

		if( alignment < 1 || (alignment & (alignment - 1)) != 0) {
			return nullptr;
		}

		m_allocation_stats.m_total_size -= GetAllocatedSize(address);

		VoidPtr new_address = m_allocation_policy.Reallocate(address, size, alignment);

		if(m_allocation_stats.m_peak_size < size) {
			m_allocation_stats.m_peak_size = size;
		}

		m_allocation_stats.m_total_size += size;
		m_allocation_stats.m_num_of_allocations += 1;

		m_used_space = (m_allocation_stats.m_total_size / m_capacity) * 100.0f;

		return new_address;
	}
	
	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Void Allocator<AllocationPolicy>::Deallocate(VoidPtr address)
	{
		m_allocation_stats.m_total_size -= GetAllocatedSize(address);

		m_allocation_policy.Deallocate(address);

		m_allocation_stats.m_num_of_deallocations += 1;

		m_used_space = (m_allocation_stats.m_total_size / m_capacity) * 100.0f;
	}

	template<typename AllocationPolicy>
	template<typename InType, typename... Args>
	FORGE_FORCE_INLINE InType* Allocator<AllocationPolicy>::ConstructObject(Args... arguments)
	{   
		InType* object_address = reinterpret_cast<InType*>(this->Allocate(sizeof(InType)));

		ConstructObject(object_address, ::std::forward(arguments... ));

		return object_address;
	}
	template<typename AllocationPolicy>
	template<typename InType, typename... Args>
	FORGE_FORCE_INLINE InType* Allocator<AllocationPolicy>::ConstructArray(Size count, Args... arguments)
	{
		InType* object_array_address = reinterpret_cast<InType*>(this->Allocate(sizeof(InType) * count));

		ConstructArray(object_array_address, count, ::std::forward(arguments...));

		return object_array_address;
	}
	
	template<typename AllocationPolicy>
	template<typename InType>
	FORGE_FORCE_INLINE Void Allocator<AllocationPolicy>::DestructObject(InType* address)
	{
		DestructObject(address);

		this->Deallocate(address);
	}
	template<typename AllocationPolicy>
	template<typename InType>
	FORGE_FORCE_INLINE Void Allocator<AllocationPolicy>::DestructArray(InType* address, Size count)
	{
		DestructArray(address, count);

		this->Deallocate(address);
	}

	template<typename AllocationPolicy>
	FORGE_FORCE_INLINE Void Allocator<AllocationPolicy>::Reset()
	{
		m_used_space = 0.0f;

		m_allocation_stats.m_peak_size = 0;
		m_allocation_stats.m_total_size = 0;
		m_allocation_stats.m_num_of_allocations = 0;
		m_allocation_stats.m_num_of_deallocations = 0;

		m_allocation_policy.Reset();
	}
}

#endif