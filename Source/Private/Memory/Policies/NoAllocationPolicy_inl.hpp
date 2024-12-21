#ifndef NO_ALLOCATION_POLICY_INL_HPP
#define NO_ALLOCATION_POLICY_INL_HPP

#include <stdlib.h>

#include "Memory/MemoryUtilities.hpp"
#include "Memory/Policies/NoAllocationPolicy.hpp"

namespace Forge
{
	Void NoAllocationPolicy::Initialize(Size capacity)
	{
		// Do Nothing
	}
	Void NoAllocationPolicy::Deinitialize()
	{
		// Do Nothing
	}

	VoidPtr NoAllocationPolicy::Allocate(Size size, Size alignment)
	{
		return nullptr;
	}
	VoidPtr NoAllocationPolicy::Callocate(Size size, Byte value, Size alignment)
	{
	   return nullptr;
	}
	VoidPtr NoAllocationPolicy::Reallocate(VoidPtr address, Size size, Size alignment)
	{
		return nullptr;
	}

	Void NoAllocationPolicy::Deallocate(VoidPtr address)
	{
		// Do Nothing
	}

	Void NoAllocationPolicy::Reset()
	{
		// Do Nothing
	}
}

#endif