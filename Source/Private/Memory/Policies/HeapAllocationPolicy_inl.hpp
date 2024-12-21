#ifndef HEAP_ALLOCATION_POLICY_INL_HPP
#define HEAP_ALLOCATION_POLICY_INL_HPP

#include <stdlib.h>

#include "Memory/MemoryUtilities.hpp"
#include "Memory/Policies/HeapAllocationPolicy.hpp"

namespace Forge
{
	Void HeapAllocationPolicy::Initialize(Size capacity)
	{
		// Do Nothing
	}
	Void HeapAllocationPolicy::Deinitialize()
	{
		// Do Nothing
	}

	VoidPtr HeapAllocationPolicy::Allocate(Size size, Size alignment)
	{
		return _aligned_malloc(size, alignment);
	}
	VoidPtr HeapAllocationPolicy::Callocate(Size size, Byte value, Size alignment)
	{
		VoidPtr address = _aligned_malloc(size, alignment);

		MemorySet(address, value, size);

		return address;
	}
	VoidPtr HeapAllocationPolicy::Reallocate(VoidPtr address, Size size, Size alignment)
	{
		return _aligned_realloc(address, size, alignment);
	}

	Void HeapAllocationPolicy::Deallocate(VoidPtr address)
	{
		_aligned_free(address);
	}

	Void HeapAllocationPolicy::Reset()
	{
		// Do Nothing
	}
}

#endif