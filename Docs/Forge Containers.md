# JCPP Containers Specification Document

### 1. Introduction

#### 1.1. Purpose

JCPP containers offers a seamless transition for Java developers who are accustomed to the Java container framework and find the C++ Standard Template Library (STL) challenging to work with. By providing data structures and interfaces that mirror those in Java, this library simplifies the development process for those familiar with Java, easing their adaptation to C++. This familiar structure enables developers to leverage their existing knowledge and experience, thereby reducing the learning curve and increasing productivity.

#### 1.2. Scope

JCPP containers encompasses a comprehensive suite of data structures and interfaces designed to mirror the Java container framework. The library will feature implementations of fundamental data structures such as Static and Dynamic Arrays, Doubly Linked Lists, Stacks, and Queues. These foundational components will provide the essential building blocks for a variety of applications. The library also will provide more advanced data structures, including Priority Queues, HashTables, and HashMaps, expanding the library's utility and versatility. The library will offer a collection of utility functions such as sorting, searching and filtering which adds a layer of extra functionality to the existing data structures. An allocator interface will also be included where clients can implement their own custom memory allocators. Each data structure will take as a template argument an allocator which is responsible for allocations and deallocations, as well as tracking memory statistics. The allocator will perform memory operations according to a certain set of policies that will enhance performance as clients see fit.

### 2. System Features and Requirements

#### 2.1. System Requirments

	- **Consistent API Design**
		Each data structure will inherit from core abstract classes, ensuring that all of them share a consistent interface. This uniformity makes it easier for the client to use the library as they excpect similar functionality from other data structures. The library will also probive a similar API to the Java collection framework enabling users familiar with Java to easily use the library.

	- **Generic Data Structures**
		The library is centered around providing a comprehensive and efficient set of data structures which utilizes C++ templates to support generic programming, allowing clients to create data structure instances for any type. This helps reduce code duplications in client's code leading to a more maintainable and consice codebase. 

	- **Generic Useful Algorithms**
		Common algorithms, such as sorting, searching and filtering will be implemented in a seperate utility class as generic functions that can operate on any type of data structure enforcing polymorphism. This design encapsulates complex algorithms, and allows the client to avoid writing boilerplate code. 

	- **User-Defined Memory Allocators**
		Extensible allocator interface will be provided for controlling how elements are allocated and deallocated in containers. This allows the client to define their own memory policies to suit their logic needs.

	- **User-Defined Comparision Functions**
		Extensible compartor interface will be provided for sorting and ordering elements within collections. This allows the client to define their own ordering policies for any data type to suit their logic needs.

	- **Iterators and Advanced Traversals**
		All data structures will inherit from an iterable interface, which provides a standardized way to traverse them through iterators and a for-each function. This makes traversal consistent across all data structures, simplifing the client's code and enhancing readability. 

#### 2.2. System Interfaces

	- `IIterable` interface
		- Purpose: Enables advanced traversal operations for collections.
		- Functionalities:
		
			**Accessors**

			| Method                                                         | Description                                                                          |
			|:--------------------------------------------------------------:|:------------------------------------------------------------------------------------:|
			| `Iterator<ElementType>& GetBeginIterator(Void)`                | Returns an iterator pointing to the first element in the collection.                 |
			| `Iterator<ElementType>& GetFinalIterator(Void)`                | Returns an iterator pointing to one past the last element in the collection.         |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------------:|
			| `ConstIterator<ElementType>& GetConstBeginIterator(Void) const`| Returns an iterator pointing to the first element in the collection.                 |
			| `ConstIterator<ElementType>& GetConstFinalIterator(Void) const`| Returns an iterator pointing to one past the last element in the collection.         |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------------:|
			| `ReverseIterator<ElementType>& GetReverseBeginIterator(Void)`  | Returns a reverse iterator pointing to the last element in the collection.           |
			| `ReverseIterator<ElementType>& GetReverseFinalIterator(Void)`  | Returns a reverse iterator pointing to the preceding first in the collection.        |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------------:|
			| `Void ForEach(Delegate<Void(ConstElementTypeRef)>) const`      | Applies the provided action to each element in the collection sequentially.          |

	- `IIterator` interface
		- Purpose: Provides a standardized way to traverse collections.
		- Functionalities:
	
			**Operators**

			| Method                                                         | Description                                                                          |
			|:--------------------------------------------------------------:|:------------------------------------------------------------------------------------:|   
			| `SelfType operator ++(Void)`                                   | Pre-increment Operator. Moves the iterator to the next element in the container.     |
			| `SelfType operator ++(I32)`                                    | Post-increment Operator. Moves the iterator to the next element in the container.    |
			| `SelfType operator --(Void)`                                   | Pre-decrement Operator. Moves the iterator to the previous element in the container. |
			| `SelfType operator --(I32)`                                    | Post-decrement Operator. Moves the iterator to the previous element in the container.|
			|:-----------------------------------------------------------------------------------------------------------------------------------------------------:|  
			| `ElementTypeRef operator *(Void)`                              | Dereference Operator. Returns the data the iterator is pointing to.                  |
			| `ElementTypePtr operator ->(Void)`                             | Arrow Operator. Returns the data the iterator is pointing to.                        |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------------:|
			| `Iterator operator ==(ConstIteratorRef)`                       | Equality Operator. Checks wether the iterator is equal to the specified iterator.    |
			| `Iterator operator !=(ConstIteratorRef)`                       | Equality Operator. Checks wether the iterator is not equal to the specified iterator.|

	- `IComparator` interface
		- Purpose: Specifies a class as a comparison function for sorting operations.
		- Functionalities:
		
			| Method                                                       | Description                                                                     |
			|:------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |



	- `IAllocationPolicy` interface
		- Purpose: Specifies a class as a defined memory policy to allocate and deallocate memory blocks.
		- Functionalities:
	
			| Method                                                           | Description                                                                     |
			|:----------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			| `Void Initialize(Size capacity)`                                 |                                                                                 |
			|:----------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			| `VoidPtr Allocate(Size size, Size alignment)`                    |                                                                                 |
			| `VoidPtr Callocate(Size size, Byte value, Size alignment)`       |                                                                                 |
			| `VoidPtr Reallocate(VoidPtr address, Size size, Size alignment)` |                                                                                 |
			|:----------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			| `Void Deallocate(VoidPtr address)`                               |                                                                                 |
			|:----------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			| `Void Reset()`                                                   |                                                                                 |

	- `AbstractCollection` abstract class
		- Purpose: Serves as the root interface for collections and provides common functionality.
		- Functionalities:
	
			**Capacity**

			| Method                                                        | Description                                                                     |
			|:-------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			| `Size GetSize(Void) const;`                                   | Gets the total used memory for this collection in bytes.                        |
			| `Size GetCount(Void) const;`                                  | Gets the number of elements currently stored in this collection.                |
			| `Size GetCapacity(Void) const;`                               | Gets the maximum number of elements that can be stored in this collection.      |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------:|
			| `Bool IsFull(Void) const;`                                    | Checks whether this collection is full and is storing elements at maximum size. |
			| `Bool IsEmpty(Void) const;`                                   | Checks whether this collection is empty and not storing any elements.           |

			**Modifiers**

			| Method                                                        | Description                                                                     |
			|:-------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			| `Void Clear(Void)`                                            | Removes all the elements from this collections.                                 |

	- `AbstractSequencedCollection` abstract class
		- Purpose: Serves as the root interface for sequenced collections.
		- Functionalities:
	
			**Accessors**

			| Method                                                        | Description                                                                     |
			|:-------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			| `ConstElementTypePtr GetRawData(Void) const`                  | Gets a direct pointer to the memory array managed by this list.                 |
			| `ConstElementTypeRef GetBackElement(Void) const`              |                                                                                 |
			| `ConstElementTypeRef GetFrontElement(Void) const`             |                                                                                 |

			**Modifiers**

			| Method                                                        | Description                                                                     |
			|:-------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			| `Void PushBack(ElementType element)`                          |                                                                                 |
			| `Void PushFront(ElementType element)`                         |                                                                                 |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------:|
			| `Void Assign(Iterator<ElementType>, ElementType)`             |                                                                                 |
			| `Void Assign(Iterator<ElementType>, Iterator<ElementType>)`   |                                                                                 |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------:|
			| `Void Emplace(Iterator<ElementType>, ElementType)`            |                                                                                 |
			| `Void Emplace(Iterator<ElementType>, Iterator<ElementType>)`  |                                                                                 |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------:|
			| `Void PopBack(Void)`                                          |                                                                                 |
			| `Void PopFront(Void)`                                         |                                                                                 |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------:|
			| `Void Erase(Iterator<ElementType>)`                           |                                                                                 |
			| `Void Erase(Iterator<ElementType>, Iterator<ElementType>)`    |                                                                                 |
			|:-----------------------------------------------------------------------------------------------------------------------------------------------:|
			| `Void InsertAll(ConstSelfTypeRef)`                            | Inserts all the elements in the specified collection in this collection.        |
			| `Void RemoveAll(ConstSelfTypeRef)`                            | Removes all the elements in the specified collection from this collection.      |
			| `Bool ContainsAll(ConstSelfTypeRef)`                          | Searches all the elements in the specified collection in this collection.       |

	- `AbstractOrderedCollection` abstract class
		- Purpose: Serves as the root interface for ordered collections.
		- Functionalities:
	
			**Accessors**

			| Method                                                       | Description                                                                     |
			|:------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |

			**Modifiers**

			| Method                                                       | Description                                                                     |
			|:------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |

	- `AbstractAssociativeCollection` abstract class
		- Purpose: Serves as the root interface for associative collections.
		- Functionalities:
	
			**Accessors**

			| Method                                                       | Description                                                                     |
			|:------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |

			**Modifiers**

			| Method                                                       | Description                                                                     |
			|:------------------------------------------------------------:|:-------------------------------------------------------------------------------:|
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			|                                                              |                                                                                 |
			| 

#### 2.3. System Implementations

	- `StaticArray` class
		- **Sequence Container**
			The container has its elements ordered in a strict linear sequence, thus individual elements are accesed by their position in the sequence.
		- **Fixed-size Container** 
			The container allocates the required space statically, thus its size is a compile-time constant and has no memory overhead.  
		- **Sequenced Container**
			The container is a subclass of the sequenced collection abstract class, thus it supports advanced elements access, modification and iteration.
		- **Contiguous Storage Container**
			The container has its elements stored in contiguous memory locations, allowing constant time random access to elements. Pointers to an element can be offset to access other elements.

	- `DynamicArray` class
		- **Sequence Container**
			The container has its elements ordered in a strict linear sequence, thus individual elements are accesed by their position in the sequence.
		- **Dynamic-size Container**
			The container allocates the required space dynamically, thus it can store an arbitrary number of data without having any information about the size before-hand.
		- **Sequenced Container**
			The container is a subclass of the sequenced collection abstract class, thus it supports advanced elements access, modification and iteration.
		- **Contiguous Storage Container**
			The container has its elements stored in contiguous memory locations, allowing constant time random access to elements. Pointers to an element can be offset to access other elements.
		- **Allocator-aware Container**
			The container uses an allocator object to dynamically handle its storage needs.

	- `LinkedList` class
		- **Sequence Container**
			The container has its elements ordered in a strict linear sequence, thus individual elements are accesed by their position in the sequence.
		- **Dynamic-size Container**
			The container allocates the required space dynamically, thus it can store an arbitrary number of data without having any information about the size before-hand.
		- **Sequenced Container**
			The container is a subclass of the sequenced collection abstract class, thus it supports advanced elements access, modification and iteration.
		- **Linked List Storage Container**
			The container keeps information on how to locate the next and previous elements, allowing constant time insertion and removal operations before or after a specific element with no memory overhead, but no direct random access.
		- **Allocator-aware Container**
			The container uses an allocator object to dynamically handle its storage needs.

	- `Stack` class
		- **LIFO Container**
			The container operates in a last-in first-out context, where elements are inserted and extracted only from one end of the container.
		- **Adaptor Container**
			The container uses an encapsulated object of a specific container class as its underlying container, providing a specific set of member functions to access its elements. The supported container classes are `StaticArray` and `DynamicArray`
		- **Ordered Container**
			The container is a subclass of the ordered collection abstract class, thus it supports limited elements access, modification and iteration.

	- `Queue` class
		- **FIFO Container**
			The container operates in a first-in first-out context, where elements are inserted into one end of the container and extracted from the other.
		- **Adaptor Container**
			The container uses an encapsulated object of a specific container class as its underlying container, providing a specific set of member functions to access its elements. The supported container classes are `StaticArray` and `DynamicArray`
		- **Ordered Container**
			The container is a subclass of the ordered collection abstract class, thus it supports limited elements access, modification and iteration.

	- `PriorityQueue` class
		- **Strict Ordering Criterion Container**
			The container operates according to a strict ordering criterion where the first element is always either the greatest or smallest of the elements it contains depending on the comparator provided.
		- **Ordered Container**
			The container is a subclass of the ordered collection abstract class, thus it supports limited elements access, modification and iteration.

		