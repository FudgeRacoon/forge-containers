#ifndef ABSTRACT_ITERATOR_HPP
#define ABSTRACT_ITERATOR_HPP

#include "Compiler.hpp"

namespace Forge
{
	/**
	 * @brief This interface provides a standardized way to traverse collections.
	 *
	 * @tparam InElementType The type of element the iterator traverses.
	 */
	template <typename InElementType>
	class AbstractIterator
	{
	public:
		using ElementType = InElementType;
		using ElementTypePtr = InElementType*;
		using ElementTypeLRef = InElementType&;
		using ElementTypeRRef = InElementType&&;
		using ConstElementType = const InElementType;
		using ConstElementTypePtr = const InElementType*;
		using ConstElementTypeLRef = const InElementType&;

	public:
		using SelfType = AbstractIterator<InElementType>;
		using SelfTypePtr = AbstractIterator<InElementType> *;
		using SelfTypeLRef = AbstractIterator<InElementType> &;
		using SelfTypeRRef = AbstractIterator<InElementType> &&;
		using ConstSelfType = const AbstractIterator<InElementType>;
		using ConstSelfTypePtr = const AbstractIterator<InElementType> *;
		using ConstSelfTypeLRef = const AbstractIterator<InElementType> &;

	protected:
		ElementTypePtr m_ptr;

	public:
		/**
		 * @brief Default Constructor.
		 */
		AbstractIterator();

		/**
		 * @brief Pointer Constructor.
		 */
		AbstractIterator(ElementTypePtr ptr);

	public:
		/**
		 * @brief Move Constructor.
		 */
		AbstractIterator(SelfTypeRRef other);

		/**
		 * @brief Copy Constructor.
		 */
		AbstractIterator(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Default Destructor.
		 */
		virtual ~AbstractIterator();

	public:
		/**
		 * @brief Move Assignment Operator.
		 */
		SelfTypeLRef operator=(SelfTypeRRef other);

		/**
		 * @brief Copy Assignment Operator.
		 */
		SelfTypeLRef operator=(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Equality Operator.
		 */
		Bool operator==(ConstSelfTypeLRef other);

		/**
		 * @brief Inequality Operator.
		 */
		Bool operator!=(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Less than Operator.
		 */
		Bool operator<(ConstSelfTypeLRef other);

		/**
		 * @brief Greater than Operator.
		 */
		Bool operator>(ConstSelfTypeLRef other);

		/**
		 * @brief Less than or equal Operator.
		 */
		Bool operator<=(ConstSelfTypeLRef other);

		/**
		 * @brief Greater than or equal Operator.
		 */
		Bool operator>=(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Subtract Operator.
		 */
		SelfTypeLRef operator-(Size value);

		/**
		 * @brief Addition Operator.
		 */
		SelfTypeLRef operator+(Size value);

		/**
		 * @brief Distance Operator.
		 */
		Size operator-(ConstSelfTypeLRef other);

	public:
		/**
		 * @brief Arrow Operator.
		 */
		virtual ElementTypePtr operator->() = 0;

		/**
		 * @brief Derefrence Operator.
		 */
		virtual ElementTypeLRef operator*() = 0;

	public:
		/**
		 * @brief Pre-increment Operator.
		 */
		virtual SelfTypeLRef operator++() = 0;

		/**
		 * @brief Pre-decrement Operator.
		 */
		virtual SelfTypeLRef operator--() = 0;

		/**
		 * @brief Post-increment Operator.
		 */
		virtual SelfTypeLRef operator++(I32) = 0;

		/**
		 * @brief Post-decrement Operator.
		 */
		virtual SelfTypeLRef operator--(I32) = 0;
	};
}

#include "../Private/AbstractIterator_inl.hpp"

#endif