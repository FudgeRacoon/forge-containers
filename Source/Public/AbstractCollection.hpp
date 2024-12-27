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
	 * @brief This abstract class serves as the root interface for all collections and provides
	 * common functionality.
	 *
	 * @tparam InElementType The type of element the collection stores.
	 * @tparam InAllocatorPolicy The type of allocator policy the collection uses to manage its memory.
	 */
	template <typename InElementType, typename InAllocatorPolicy = HeapAllocationPolicy>
	class AbstractCollection : public IIterable<InElementType>
	{
	public:
		using SelfType = AbstractCollection<InElementType, InAllocatorPolicy>;
		using SelfTypePtr = AbstractCollection<InElementType, InAllocatorPolicy>*;
		using SelfTypeLRef = AbstractCollection<InElementType, InAllocatorPolicy>&;
		using SelfTypeRRef = AbstractCollection<InElementType, InAllocatorPolicy>&&;
		using ConstSelfType = const AbstractCollection<InElementType, InAllocatorPolicy>;
		using ConstSelfTypePtr = const AbstractCollection<InElementType, InAllocatorPolicy>*;
		using ConstSelfTypeLRef = const AbstractCollection<InElementType, InAllocatorPolicy>&;

	public:
		using ElementType = InElementType;
		using ElementTypePtr = InElementType*;
		using ElementTypeLRef = InElementType&;
		using ElementTypeRRef = InElementType&&;
		using ConstElementType = const InElementType;
		using ConstElementTypePtr = const InElementType*;
		using ConstElementTypeLRef = const InElementType&;

	public:
		using AllocatorType = InAllocatorPolicy;
		using AllocatorTypePtr = InAllocatorPolicy*;
		using AllocatorTypeLRef = InAllocatorPolicy&;
		using AllocatorTypeRRef = InAllocatorPolicy&&;
		using ConstAllocatorType = const InAllocatorPolicy;
		using ConstAllocatorTypePtr = const InAllocatorPolicy*;
		using ConstAllocatorTypeLRef = const InAllocatorPolicy&;

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
		 * @brief Checks if this collection is at maximum capacity.
		 *
		 * @return True if at maximum capacity, otherwise false.
		 */
		virtual Bool IsFull() const;

		/**
		 * @brief Checks if this collection is not storing any elements.
		 *
		 * @return True if not storing any elements, otherwise false.
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
		 * @brief Gets the number of elements stored in this collection.
		 *
		 * @return Size storing the number of elements stored.
		 */
		virtual Size GetCount() const;

		/**
		 * @brief Gets the maximum number of elements that can be stored in this collection.
		 *
		 * @return Size storing the maximum number of elements that can be stored.
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
	 * @tparam InElementType The type of element the collection stores.
	 * @tparam InAllocatorPolicy The type of allocator the collection uses to manage its memory.
	 */
	template <typename InElementType>
	class AbstractCollection<InElementType, NoAllocationPolicy> : public IIterable<InElementType>
	{
	public:
		using SelfType = AbstractCollection<InElementType, NoAllocationPolicy>;
		using SelfTypePtr = AbstractCollection<InElementType, NoAllocationPolicy>*;
		using SelfTypeLRef = AbstractCollection<InElementType, NoAllocationPolicy>&;
		using SelfTypeRRef = AbstractCollection<InElementType, NoAllocationPolicy>&&;
		using ConstSelfType = const AbstractCollection<InElementType, NoAllocationPolicy>;
		using ConstSelfTypePtr = const AbstractCollection<InElementType, NoAllocationPolicy>*;
		using ConstSelfTypeLRef = const AbstractCollection<InElementType, NoAllocationPolicy>&;

	public:
		using ElementType = InElementType;
		using ElementTypePtr = InElementType*;
		using ElementTypeLRef = InElementType&;
		using ElementTypeRRef = InElementType&&;
		using ConstElementType = const InElementType;
		using ConstElementTypePtr = const InElementType*;
		using ConstElementTypeLRef = const InElementType&;

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
		 * @brief Checks if this collection is at maximum capacity.
		 *
		 * @return True if at maximum capacity, otherwise false.
		 */
		virtual Bool IsFull() const;

		/**
		 * @brief Checks if this collection is not storing any elements.
		 *
		 * @return True if not storing any elements, otherwise false.
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
		 * @brief Gets the number of elements stored in this collection.
		 *
		 * @return Size storing the number of elements stored.
		 */
		virtual Size GetCount() const;

		/**
		 * @brief Gets the maximum number of elements that can be stored in this collection.
		 *
		 * @return Size storing the maximum number of elements that can be stored.
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