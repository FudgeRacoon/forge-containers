#ifndef ABSTRACT_COLLECTION_HPP
#define ABSTRACT_COLLECTION_HPP

#include "Macros.hpp"
#include "Compiler.hpp"

#include "IIterable.hpp"
#include "AbstractIterator.hpp"

#include "Memory/Allocator.hpp"
#include "Memory/MemoryUtilities.hpp"
#include "Memory/Policies/NoAllocationPolicy.hpp"
#include "Memory/Policies/HeapAllocationPolicy.hpp"

namespace Forge
{
	/**
	 * @brief This abstract class serves as the root interface for all collections
	 * and provides common functionality.
	 *
	 * @tparam InElementType The type of element the collection contains.
	 * @tparam InAllocatorPolicy The type of allocator policy the collection uses to manage its memory.
	 */
	template <typename InElementType, typename InAllocatorPolicy = HeapAllocationPolicy>
	class AbstractCollection : public IIterable<InElementType>
	{
	protected:
		Size m_count;
		Size m_capacity;

	protected:
		Allocator<InAllocatorPolicy> m_allocator;

	public:
		/**
		 * @brief Default Constructor.
		 */
		AbstractCollection(Size count, Size capacity);

	public:
		/**
		 * @brief Default Destructor.
		 */
		virtual ~AbstractCollection() = default;

	public:
		/**
		 * @brief Checks whether this collection is full and is at maximum capacity.
		 *
		 * @return True if this collection is full, otherwise false.
		 */
		virtual Bool IsFull() const;

		/**
		 * @brief Checks whether this collection is empty and not storing any elements.
		 *
		 * @return True if this collection is empty.
		 */
		virtual Bool IsEmpty() const;

	public:
		/**
		 * @brief Gets the total used memory for this collection in bytes.
		 *
		 * @return Size storing the total used memory in bytes.
		 */
		virtual Size GetSize() const;

		/**
		 * @brief Gets the number of elements currently stored in this collection.
		 *
		 * @return Size storing the number of elements.
		 */
		virtual Size GetCount() const;

		/**
		 * @brief Gets the maximum number of elements that can be stored in this collection.
		 *
		 * @return Size storing the maximum number of elements.
		 */
		virtual Size GetCapacity() const;

	public:
		/**
		 * @brief Removes all the elements from this collections.
		 */
		virtual Void Clear() = 0;
	};

	/**
	 * @brief This abstract class serves as the root interface for all collections
	 * and provides common functionality.
	 *
	 * @tparam InElementType The type of element the collection contains.
	 * @tparam InAllocatorPolicy The type of allocator the collection uses to manage its memory.
	 */
	template <typename InElementType>
	class AbstractCollection<InElementType, NoAllocationPolicy> : public IIterable<InElementType>
	{
	protected:
		Size m_count;
		Size m_capacity;

	public:
		/**
		 * @brief Default Constructor.
		 */
		AbstractCollection(Size count, Size capacity);

	public:
		/**
		 * @brief Default Destructor.
		 */
		virtual ~AbstractCollection() = default;

	public:
		/**
		 * @brief Checks whether this collection is full and is at maximum capacity.
		 *
		 * @return True if this collection is full, otherwise false.
		 */
		virtual Bool IsFull() const;

		/**
		 * @brief Checks whether this collection is empty and not storing any elements.
		 *
		 * @return True if this collection is empty.
		 */
		virtual Bool IsEmpty() const;

	public:
		/**
		 * @brief Gets the total used memory for this collection in bytes.
		 *
		 * @return Size storing the total used memory in bytes.
		 */
		virtual Size GetSize() const;

		/**
		 * @brief Gets the number of elements currently stored in this collection.
		 *
		 * @return Size storing the number of elements.
		 */
		virtual Size GetCount() const;

		/**
		 * @brief Gets the maximum number of elements that can be stored in this collection.
		 *
		 * @return Size storing the maximum number of elements.
		 */
		virtual Size GetCapacity() const;

	public:
		/**
		 * @brief Removes all the elements from this collections.
		 */
		virtual Void Clear() = 0;
	};
}

#include "../Private/AbstractCollection_inl.hpp"

#endif