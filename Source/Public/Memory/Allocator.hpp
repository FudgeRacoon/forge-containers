#ifndef IALLOCATOR_HPP
#define IALLOCATOR_HPP

#include <type_traits>

#include "Compiler.hpp"

#include "Policies/IAllocationPolicy.hpp"

using namespace std;

namespace Forge {
	/**
	 * @brief This class provides allocation and deallocation functionalities
	 * according to a specific memory policy.
	 *
	 * @tparam AllocationPolicy The type of memory allocation policy to use.
	 */
	template<typename AllocationPolicy>
	class Allocator
	{
	private:
		struct AllocationStats
		{
			Size m_peak_size;
			Size m_total_size;
			Size m_num_of_allocations;
			Size m_num_of_deallocations;
		};

	private:
		Size  m_capacity;
		Float32 m_used_space;

	private:
		AllocationStats  m_allocation_stats;
		AllocationPolicy m_allocation_policy;

	public:
		/**
		 * @brief Gets the capacity of the allocator.
		 *
		 * @return Size storing the capacity of the allocator.
		 */
		Size GetCapacity();

		/**
		 * @brief Gets the currently used space of the allocator.
		 *
		 * @return Float32 storing the currently used space of the allocator as a perecentage.
		 */
		Float32 GetUsedSpace();

	public:
		/**
		 * @brief Gets the peak size allocated during lifetime of the allocator.
		 *
		 * @return Size storing the peak size allocated by the allocator in bytes.
		 */
		Size GetPeakSize();

		/**
		 * @brief Gets the total size allocated during lifetime of the allocator.
		 *
		 * @return Size storing total size allocated by the allocator in bytes.
		 */
		Size GetTotalSize();

		/**
		 * @brief Gets the number of allocations during lifetime of the allocator.
		 *
		 * @return Size storing the number of allocations by the allocator.
		 */
		Size GetNumOfAllocations();

		/**
		 * @brief Gets the number of deallocations during lifetime of the allocator.
		 *
		 * @return Size storing the number of deallocations by the allocator.
		 */
		Size GetNumOfDeallocations();

	public:
		/**
		 * @brief Gets the allocated size of the specified address.
		 *
		 * @return Size storing the allocated size of the specified address in bytes.
		 */
		Size GetAllocatedSize(VoidPtr address);

	public:
		/**
		 * @brief Initializes the defined memory policy used by the allocator.
		 *
		 * @param capacity The size of the memory pool managed by the memory policy in bytes.
		 */
		Void Initialize(Size capacity);

		/**
		 * @brief Deinitializes the defined memory policy used by the allocator.
		 */
		Void Deinitialize();

	public:
		/**
		 * @brief Allocates a block of memory with the specified size and alignment using the defined memory policy.
		 *
		 * @param[in] size  The size of the memory block to allocate in bytes.
		 * @param[in] alignment The alignment requirement for the memory block. Must be a power of two.
		 *
		 * @return VoidPtr storing the address of the allocated memory block.
		 */
		VoidPtr Allocate(Size size, Size alignment = 4);

		/**
		 * @brief Allocates a block of memory with the specified size and alignment using the defined memory policy.
		 *
		 * @param[in] size The size of the memory block to allocate in bytes.
		 * @param[in] value The value to set each byte of the memory block to.
		 * @param[in] alignment The alignment requirement for the memory block. Must be a power of two.
		 *
		 * @return VoidPtr storing the address of the allocated memory block.
		 */
		VoidPtr Callocate(Size size, Byte value, Size alignment = 4);

		/**
		 * @brief Reallocates a block of memory with the specified size and alignment using the defined memory policy.
		 *
		 * @param[in] address The address of the memory block to reallocate.
		 * @param[in] size The size of the memory block to reallocate in bytes.
		 * @param[in] alignment The alignment requirement for the memory block. Must be a power of two.
		 *
		 * @returns VoidPtr storing the address of the reallocated memory block.
		 */
		VoidPtr Reallocate(VoidPtr address, Size size, Size alignment = 4);

	public:
		/**
		 * @brief Deallocates a block of memory with the specified address using the defined memory policy.
		 *
		 * @param[in] address The address of the memory block to deallocate.
		 */
		Void Deallocate(VoidPtr address);

	public:
		/**
		 * @brief Constructs an object of type InType using the defined memory policy.
		 *
		 * @tparam InType The type of object to construct.
		 * @tparam InArgs The type of constructor arguments.
		 *
		 * @param[in] arguments The constructor arguments to forward to the constructor of InType.
		 *
		 * @return InType* storing the address of the constructed object.
		 */
		template<typename InType, typename... Args>
		InType* ConstructObject(Args... arguments);

		/**
		 * @brief Constructs an array of objects of type InType using the defined memory policy.
		 *
		 * @tparam InType The type of object to construct.
		 * @tparam InArgs The type of constructor arguments.
		 *
		 * @param[in] count The number of objects to construct.
		 * @param[in] arguments The constructor arguments to forward to the constructor of InType.
		 *
		 * @return InType* storing the address of the constructed array.
		 */
		template<typename InType, typename... Args>
		InType* ConstructArray(Size count, Args... arguments);

	public:
		/**
		 * @brief Destruct an object of type InType using the defined memory policy.
		 *
		 * @tparam InType The type of object to destruct.
		 *
		 * @param[in] address The address of the object to destruct.
		 */
		template<typename InType>
		Void DestructObject(InType* address);

		/**
		 * @brief Destruct an array of objects of type InType using the defined memory policy.
		 *
		 * @tparam InType The type of object to destruct.
		 *
		 * @param[in] address The address of the array to destruct.
		 * @param[in] count The number of objects to destruct.
		 */
		template<typename InType>
		Void DestructArray(InType* address, Size count);

	public:
		/**
		 * @brief Resets the entire memory pool used by the allocator.
		 */
		Void Reset();
	};

}

#include "../../Private/Memory/Allocator_inl.hpp"

#endif