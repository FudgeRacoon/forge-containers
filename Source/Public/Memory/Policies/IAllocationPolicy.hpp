#ifndef IALLOCATION_POLICY_HPP
#define IALLOCATION_POLICY_HPP

#include "../../Compiler.hpp"

namespace Forge {
	/**
	 * @brief This interface specifies a class as a defined memory policy to
	 * allocate and deallocate memory blocks.
	 */
	class IAllocationPolicy
	{
	public:
		/**
		 * @brief Initializes a memory pool with the specified capacity using a defined memory policy.
		 *
		 * @param capacity The size of the memory pool to initialize in bytes.
		 */
		virtual Void Initialize(Size capacity) = 0;

		/**
		 * @brief Deinitializes the memory pool managed by the defined memory policy.
		 */
		virtual Void Deinitialize() = 0;

	public:
		/**
		 * @brief Allocates a block of memory with the specified size and alignment from the memory pool.
		 *
		 * @param[in] size      The size of the memory block to allocate in bytes.
		 * @param[in] alignment The alignment requirement for the memory block. Must be a power of two.
		 *
		 * @return VoidPtr storing the address the allocated memory block.
		 */
		virtual VoidPtr Allocate(Size size, Size alignment) = 0;

		/**
		 * @brief Allocates a block of memory with the specified size and alignment from the memory pool.
		 *
		 * @param[in] size      The size of the memory block to allocate in bytes.
		 * @param[in] value     The value to set each byte of the memory block to.
		 * @param[in] alignment The alignment requirement for the memory block. Must be a power of two.
		 *
		 * @return VoidPtr storing the address the allocated memory block.
		 */
		virtual VoidPtr Callocate(Size size, Byte value, Size alignment) = 0;

		/**
		 * @brief Reallocates a block of memory with the specified size and alignment from the memory pool.
		 *
		 * @param[in] address   The address of the memory block to reallocate.
		 * @param[in] size      The size of the memory block to reallocate in bytes.
		 * @param[in] alignment The alignment requirement for the memory block. Must be a power of two.
		 *
		 * @returns VoidPtr storing the address the reallocated memory block.
		 */
		virtual VoidPtr Reallocate(VoidPtr address, Size size, Size alignment) = 0;

	public:
		/**
		 * @brief Deallocates a block of memory with the specified address from the memory pool.
		 *
		 * @param[in] address The address of the memory block to deallocate.
		 */
		virtual Void Deallocate(VoidPtr address) = 0;

	public:
		/**
		 * @brief Resets the entire memory pool.
		 */
		virtual Void Reset() = 0;
	};
}

#endif