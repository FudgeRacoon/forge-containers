#ifndef ITERATOR_INL_HPP
#define ITERATOR_INL_HPP

#include <utility>

#include "AbstractIterator.hpp"
#include "Memory/MemoryUtilities.hpp"

namespace Forge
{
	template<typename InElementType>
	FORGE_FORCE_INLINE AbstractIterator<InElementType>::AbstractIterator()
		: m_ptr(nullptr) {}
	template<typename InElementType>
	FORGE_FORCE_INLINE AbstractIterator<InElementType>::AbstractIterator(ElementTypePtr ptr)
		: m_ptr(ptr) {}

	template<typename InElementType>
	FORGE_FORCE_INLINE AbstractIterator<InElementType>::AbstractIterator(SelfTypeRRef other)
	{
		*this = std::move(other);
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE AbstractIterator<InElementType>::AbstractIterator(ConstSelfTypeLRef other)
	{
		*this = other;
	}

	template<typename InElementType>
	FORGE_FORCE_INLINE AbstractIterator<InElementType>::~AbstractIterator()
	{
		MemorySet(this, 0, sizeof(SelfType));
	}

	template<typename InElementType>
	FORGE_FORCE_INLINE typename AbstractIterator<InElementType>::SelfTypeLRef AbstractIterator<InElementType>::operator =(SelfTypeRRef other)
	{
		MemoryCopy(this, &other, sizeof(SelfType));
		MemoryZero(&other, sizeof(SelfType));

		return *this;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE typename AbstractIterator<InElementType>::SelfTypeLRef AbstractIterator<InElementType>::operator =(ConstSelfTypeLRef other)
	{
		MemoryCopy(this, const_cast<SelfTypePtr>(&other), sizeof(SelfType));
		
		return *this;
	}

	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractIterator<InElementType>::operator ==(ConstSelfTypeLRef other)
	{
		return this->m_ptr == other.m_ptr;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractIterator<InElementType>::operator !=(ConstSelfTypeLRef other)
	{
		return this->m_ptr != other.m_ptr;
	}

	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractIterator<InElementType>::operator <(ConstSelfTypeLRef other)
	{
		return this->m_ptr < other.m_ptr;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractIterator<InElementType>::operator >(ConstSelfTypeLRef other)
	{
		return this->m_ptr > other.m_ptr;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractIterator<InElementType>::operator <=(ConstSelfTypeLRef other)
	{
		return this->m_ptr <= other.m_ptr;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Bool AbstractIterator<InElementType>::operator >=(ConstSelfTypeLRef other)
	{
		return this->m_ptr >= other.m_ptr;
	}

	template<typename InElementType>
	FORGE_FORCE_INLINE typename AbstractIterator<InElementType>::SelfTypeLRef AbstractIterator<InElementType>::operator -(Size value)
	{
		this->m_ptr -= value;

		return *this;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE typename AbstractIterator<InElementType>::SelfTypeLRef AbstractIterator<InElementType>::operator +(Size value)
	{
		this->m_ptr += value;

		return *this;
	}
	template<typename InElementType>
	FORGE_FORCE_INLINE Size AbstractIterator<InElementType>::operator -(ConstSelfTypeLRef other)
	{
		return static_cast<Size>(this->m_ptr - other.m_ptr);
	}
}

#endif