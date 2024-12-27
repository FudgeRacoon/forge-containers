#ifndef NO_ALLOCATION_POLICY_HPP
#define NO_ALLOCATION_POLICY_HPP

#include "../../Compiler.hpp"

#include "IAllocationPolicy.hpp"

namespace Forge {
	class NoAllocationPolicy : public IAllocationPolicy
	{
	public:
		/**
		 * @brief Initializes a memory pool with the specified capacity using a defined memory policy.
		 *
		 * @param capacity The size of the memory pool to initialize in bytes.
		 */
		Void Initialize(Size capacity) override;

		/**
		 * @brief Deinitializes the memory pool managed by the defined memory policy.
		 */
		Void Deinitialize() override;

	public:
		/**
		 * @brief Allocates a block of memory with the specified size and alignment from the memory pool.
		 *
		 * @param[in] size      The size of the memory block to allocate in bytes.
		 * @param[in] alignment The alignment requirement for the memory block. Must be a power of two.
		 *
		 * @return VoidPtr storing the address the allocated memory block.
		 */
		VoidPtr Allocate(Size size, Size alignment) override;

		/**
		 * @brief Allocates a block of memory with the specified size and alignment from the memory pool.
		 *
		 * @param[in] size      The size of the memory block to allocate in bytes.
		 * @param[in] value     The value to set each byte of the memory block to.
		 * @param[in] alignment The alignment requirement for the memory block. Must be a power of two.
		 *
		 * @return VoidPtr storing the address the allocated memory block.
		 */
		VoidPtr Callocate(Size size, Byte value, Size alignment) override;

		/**
		 * @brief Reallocates a block of memory with the specified size and alignment from the memory pool.
		 *
		 * @param[in] address   The address of the memory block to reallocate.
		 * @param[in] size      The size of the memory block to reallocate in bytes.
		 * @param[in] alignment The alignment requirement for the memory block. Must be a power of two.
		 *
		 * @returns VoidPtr storing the address the reallocated memory block.
		 */
		VoidPtr Reallocate(VoidPtr address, Size size, Size alignment) override;

	public:
		/**
		 * @brief Deallocates a block of memory with the specified address from the memory pool.
		 *
		 * @param[in] address The address of the memory block to deallocate.
		 */
		Void Deallocate(VoidPtr address) override;

	public:
		/**
		 * @brief Resets the entire memory pool.
		 */
		Void Reset() override;
	};
}

#include "../../../Private/Memory/Policies/NoAllocationPolicy_inl.hpp"

#endif