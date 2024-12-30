#include "Collections/StaticQueue.hpp"

namespace Forge
{
	template<typename InElementType, Size InCapacity>
	StaticQueue<InElementType, InCapacity>::StaticQueue()
		: BaseType(0, InCapacity)
	{
		this->m_container = ContainerType();
	}
	template<typename InElementType, Size InCapacity>
	StaticQueue<InElementType, InCapacity>::StaticQueue(ElementType value, Size count)
		: BaseType(count, InCapacity)
	{
		this->m_container = ContainerType(value, count);
	}
	template<typename InElementType, Size InCapacity>
	StaticQueue<InElementType, InCapacity>::StaticQueue(ElementTypePtr buffer, Size count)
		: BaseType(count, InCapacity)
	{
		this->m_container = ContainerType(buffer, count);
	}
	template<typename InElementType, Size InCapacity>
	StaticQueue<InElementType, InCapacity>::StaticQueue(std::initializer_list<ElementType> init_list)
		: BaseType(init_list.size(), InCapacity)
	{
		this->m_container = ContainerType(init_list);
	}

	template<typename InElementType, Size InCapacity>
	StaticQueue<InElementType, InCapacity>::StaticQueue(SelfTypeRRef other)
	{
		*this = ::std::move(other);
	}
	template<typename InElementType, Size InCapacity>
	StaticQueue<InElementType, InCapacity>::StaticQueue(ConstSelfTypeLRef other)
	{
		*this = other;
	}

	template<typename InElementType, Size InCapacity>
	StaticQueue<InElementType, InCapacity>::~StaticQueue()
	{
		this->Clear();
	}

	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::SelfTypeLRef StaticQueue<InElementType, InCapacity>::operator=(SelfTypeRRef other)
	{
		if (this != &other)
		{
			this->m_container = ::std::move(other.m_container);

			other.m_count = other.m_container.m_count;
			this->m_count = this->m_container.m_count;
		}

		return *this;
	}
	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::SelfTypeLRef StaticQueue<InElementType, InCapacity>::operator=(ConstSelfTypeLRef other)
	{
		if (this != &other)
		{
			this->m_container = other.m_container;

			this->m_count = this->m_container.GetCount();
		}

		return *this;
	}

	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::ElementTypeLRef StaticQueue<InElementType, InCapacity>::operator[](Size index)
	{
		throw std::logic_error("A queue only allows access to the front element");
	}
	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::ConstElementTypeLRef StaticQueue<InElementType, InCapacity>::operator[](Size index) const
	{
		throw std::logic_error("A queue only allows access to the front element");
	}

	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::ConstElementTypeLRef StaticQueue<InElementType, InCapacity>::Peek() const
	{
		return this->GetFrontElement();
	}

	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Pop()
	{
		this->PopFront();
	}

	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Push(ElementTypeRRef element)
	{
		this->PushBack(::std::move(element));
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Push(ConstElementTypeLRef element)
	{
		this->PushBack(element);
	}

	template<typename InElementType, Size InCapacity>
	typename AbstractIterator<InElementType>::SelfTypeLRef StaticQueue<InElementType, InCapacity>::GetBeginIterator()
	{
		throw std::logic_error("A queue only allows access to the front element");
	}
	template<typename InElementType, Size InCapacity>
	typename AbstractIterator<InElementType>::SelfTypeLRef StaticQueue<InElementType, InCapacity>::GetFinalIterator()
	{
		throw std::logic_error("A queue only allows access to the front element");
	}

	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::ElementTypeLRef StaticQueue<InElementType, InCapacity>::At(Size index)
	{
		throw std::logic_error("A queue only allows access to the front element");
	}
	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::ConstElementTypeLRef StaticQueue<InElementType, InCapacity>::At(Size index) const
	{
		throw std::logic_error("A queue only allows access to the front element");
	}

	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::ConstElementTypePtr StaticQueue<InElementType, InCapacity>::GetRawData() const
	{
		return this->m_container.GetRawData();
	}
	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::ConstElementTypeLRef StaticQueue<InElementType, InCapacity>::GetBackElement() const
	{
		throw std::logic_error("A queue only allows access to the front element");
	}
	template<typename InElementType, Size InCapacity>
	typename StaticQueue<InElementType, InCapacity>::ConstElementTypeLRef StaticQueue<InElementType, InCapacity>::GetFrontElement() const
	{
		return this->m_container.GetFrontElement();
	}

	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::PopBack()
	{
		throw std::logic_error("A queue only allows removal of the front element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::PopFront()
	{
		this->m_container.PopFront();

		this->m_count = this->m_container.GetCount();
	}

	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::PushBack(ElementTypeRRef element)
	{
		this->m_container.PushBack(::std::move(element));

		this->m_count = this->m_container.GetCount();
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::PushFront(ElementTypeRRef element)
	{
		throw std::logic_error("A queue only allows insertion to the front element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::PushBack(ConstElementTypeLRef element)
	{
		this->m_container.PushBack(element);

		this->m_count = this->m_container.GetCount();
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::PushFront(ConstElementTypeLRef element)
	{
		throw std::logic_error("A queue only allows insertion to the front element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Remove(Size index)
	{
		throw std::logic_error("A queue only allows removal of the front element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Remove(typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
	{
		throw std::logic_error("A queue only allows removal of the front element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Assign(Size index, ElementTypeRRef element)
	{
		throw std::logic_error("A queue only allows access to the front element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Assign(Size index, ConstElementTypeLRef element)
	{
		throw std::logic_error("A queue only allows access to the front element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Assign(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
	{
		throw std::logic_error("A queue only allows access to the front element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Insert(Size index, ElementTypeRRef element)
	{
		throw std::logic_error("A queue only allows insertion to the front element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Insert(Size index, ConstElementTypeLRef element)
	{
		throw std::logic_error("A queue only allows insertion to the front element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Insert(Size index, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_first, typename AbstractIterator<ElementType>::SelfTypeLRef iterator_last)
	{
		throw std::logic_error("A queue only allows insertion to the front element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::InsertAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		throw std::logic_error("A queue only allows insertion to the front element");
	}
	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::RemoveAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		throw std::logic_error("A queue only allows removal of the front element");
	}
	template<typename InElementType, Size InCapacity>
	Bool StaticQueue<InElementType, InCapacity>::ContainsAll(typename BaseType::ConstSelfTypeLRef collection)
	{
		throw std::logic_error("A queue only allows access to the front element");
	}

	template<typename InElementType, Size InCapacity>
	Void StaticQueue<InElementType, InCapacity>::Clear()
	{
		this->m_container.Clear();

		this->m_count = this->m_container.GetCount();
	}
}