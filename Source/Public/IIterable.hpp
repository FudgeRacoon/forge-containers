#ifndef IITERABLE_HPP
#define IITERABLE_HPP

namespace Forge
{
	template<typename InElementType>
	class AbstractIterator;

	/**
	 * @brief This interface enables advanced traversal operations for collections
	 * using iterators and allows collections to be the target of for-each iteration.
	 * 
	 * @tparam InInElementType The type of element the iterable contains.
	 */
	template<typename InElementType>
	class IIterable
	{
	public:
		/**
		 * @brief Gets an iterator pointing to the first element in the collection.
		 * 
		 * @return IIterator pointing to the first element in the collection.
		 */
		virtual typename AbstractIterator<InElementType>::SelfTypeLRef GetBeginIterator() = 0;
		/**
		 * @brief Gets an iterator pointing to one past the last element in the collection.
		 * 
		 * @return IIterator pointing to one past the last element in the collection.
		 */
		virtual typename AbstractIterator<InElementType>::SelfTypeLRef GetFinalIterator() = 0;
	};
}

#endif