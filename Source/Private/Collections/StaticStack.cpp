#include "Collections/StaticStack.hpp"

namespace Forge
{
	template<typename InElementType, Size InCapacity>
	StaticStack<InElementType, InCapacity>::StaticStack()
		: BaseType(0, InCapacity)
	{
		this->m_container = ContainerType();
	}
	template<typename InElementType, Size InCapacity>
	StaticStack<InElementType, InCapacity>::StaticStack(ElementType value, Size count)
		: BaseType(count, InCapacity)
	{
		this->m_container = ContainerType(value, count);
	}
	template<typename InElementType, Size InCapacity>
	StaticStack<InElementType, InCapacity>::StaticStack(ElementTypePtr buffer, Size count)
		: BaseType(count, InCapacity)
	{
		this->m_container = ContainerType(buffer, count);
	}
	template<typename InElementType, Size InCapacity>
	StaticStack<InElementType, InCapacity>::StaticStack(std::initializer_list<ElementType> init_list)
		: BaseType(init_list.size(), InCapacity)
	{
		this->m_container = ContainerType(init_list);
	}

	template<typename InElementType, Size InCapacity>
	StaticStack<InElementType, InCapacity>::StaticStack(SelfTypeRRef other)
	{
		*this = ::std::move(other);
	}
	template<typename InElementType, Size InCapacity>
	StaticStack<InElementType, InCapacity>::StaticStack(ConstSelfTypeLRef other)
	{
		*this = other;
	}

	template<typename InElementType, Size InCapacity>
	StaticStack<InElementType, InCapacity>::~StaticStack()
	{
		this->Clear();
	}

	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::SelfTypeLRef StaticStack<InElementType, InCapacity>::operator=(SelfTypeRRef other)
	{
		if (this != &other)
		{
			this->m_container = ::std::move(other.m_container);

			other.m_count = other.m_count;
			this->m_count = this->m_container.m_count;
		}

		return *this;
	}
	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::SelfTypeLRef StaticStack<InElementType, InCapacity>::operator=(ConstSelfTypeLRef other)
	{
		if (this != &other)
		{
			this->m_container = other.m_container;

			other.m_count = other.m_count;
			this->m_count = this->m_container.m_count;
		}

		return *this;
	}

	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::ElementTypeLRef StaticStack<InElementType, InCapacity>::operator[](Size index)
	{
		throw std::logic_error("A stack only allows access to the back element");
	}
	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::ConstElementTypeLRef StaticStack<InElementType, InCapacity>::operator[](Size index) const
	{
		throw std::logic_error("A stack only allows access to the back element");
	}

	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::ConstElementTypeLRef StaticStack<InElementType, InCapacity>::Peek() const
	{
		return this->GetBackElement();
	}

	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Pop()
	{
		this->PopBack();
	}

	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Push(ElementTypeRRef element)
	{
		this->PushBack(::std::move(element));
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Push(ConstElementTypeLRef element)
	{
		this->PushBack(element);
	}

	template<typename InElementType, Size InCapacity>
	typename AbstractIterator<InElementType>::SelfTypeLRef StaticStack<InElementType, InCapacity>::GetBeginIterator()
	{
		throw std::logic_error("A stack only allows access to the back element");
	}
	template<typename InElementType, Size InCapacity>
	typename AbstractIterator<InElementType>::SelfTypeLRef StaticStack<InElementType, InCapacity>::GetFinalIterator()
	{
		throw std::logic_error("A stack only allows access to the back element");
	}

	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::ElementTypeLRef StaticStack<InElementType, InCapacity>::At(Size index)
	{
		throw std::logic_error("A stack only allows access to the back element");
	}
	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::ConstElementTypeLRef StaticStack<InElementType, InCapacity>::At(Size index) const
	{
		throw std::logic_error("A stack only allows access to the back element");
	}

	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::ConstElementTypePtr StaticStack<InElementType, InCapacity>::GetRawData() const
	{
		return this->m_container.GetRawData();
	}
	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::ConstElementTypeLRef StaticStack<InElementType, InCapacity>::GetBackElement() const
	{
		return this->m_container.GetBackElement();
	}
	template<typename InElementType, Size InCapacity>
	typename StaticStack<InElementType, InCapacity>::ConstElementTypeLRef StaticStack<InElementType, InCapacity>::GetFrontElement() const
	{
		throw std::logic_error("A stack only allows access to the back element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::PopBack()
	{
		this->m_container.PopBack();

		this->m_count = this->m_container.m_count;
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::PopFront()
	{
		throw std::logic_error("A stack only allows removal of the back element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::PushBack(ElementTypeRRef element)
	{
		this->m_container.PushBack(::std::move(element));

		this->m_count = this->m_container.m_count;
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::PushFront(ElementTypeRRef element)
	{
		throw std::logic_error("A stack only allows insertion to the back element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::PushBack(ConstElementTypeLRef element)
	{
		this->m_container.PushBack(element);

		this->m_count = this->m_container.m_count;
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::PushFront(ConstElementTypeLRef element)
	{
		throw std::logic_error("A stack only allows insertion to the back element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Remove(Size index)
	{
		throw std::logic_error("A stack only allows removal of the back element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
	{
		throw std::logic_error("A stack only allows removal of the back element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Assign(Size index, ElementTypeRRef element)
	{
		throw std::logic_error("A stack only allows access to the back element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Assign(Size index, ConstElementTypeLRef element)
	{
		throw std::logic_error("A stack only allows access to the back element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
	{
		throw std::logic_error("A stack only allows access to the back element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Insert(Size index, ElementTypeRRef element)
	{
		throw std::logic_error("A stack only allows insertion to the back element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Insert(Size index, ConstElementTypeLRef element)
	{
		throw std::logic_error("A stack only allows insertion to the back element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
	{
		throw std::logic_error("A stack only allows insertion to the back element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::InsertAll(typename BaseType::ConstSelfTypeLRef collection)
	{

	}
	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::RemoveAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		throw std::logic_error("A stack only allows removal of the back element");
	}
	template<typename InElementType, Size InCapacity>
	Bool StaticStack<InElementType, InCapacity>::ContainsAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		throw std::logic_error("A stack only allows access to the back element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticStack<InElementType, InCapacity>::Clear()
	{
		this->m_container.Clear();

		this->m_count = this->m_container.m_count;
	}
}