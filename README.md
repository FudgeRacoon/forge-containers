
# Forge Containers

Forge Containers offers a clean, easy and powerful interface similar to the Java Collection Framework. It competes with the C++ Standard Template Library (STL) that my feel challenging to work with for beginners. By providing data structures and interfaces that mirror those in Java, this library simplifies the development process and eases adaptation to C++.

If you're a developer who finds the C++ Standard Template Library (STL) cumbersome, Forge Containers is your solution, it allows you to:

- **Leverage Familiarity**: Write clean, readable, and intuitive code using familiar patterns.
- **Focus on Development**: Spend less time learning complicated APIs and more time building.


## Features

- **Consistent API Design**
	Each data structure inherits from core abstract classes, ensuring that all of them share a consistent interface. This uniformity makes it easier for the client to use the library as they expect similar functionality from other data structures.

- **Generic Data Structures**
	The library is centered around providing a comprehensive and efficient set of data structures which utilizes C++ templates to support generic programming, allowing clients to create data structure instances for any type. This helps reduce code duplications in client's code leading to a more maintainable and consice codebase. 

- **Generic Utility Algorithms**
	Common algorithms, such as sorting, searching and filtering are implemented in a seperate utility module as generic functions that can operate on any type of data structure enforcing polymorphism. This design encapsulates complex algorithms, and allows the client to avoid writing boilerplate code. Algorithms also utilize multithreading capability to boost perfomance.

- **User-Defined Memory Allocators**
	Extensible allocator interface is provided for controlling how elements are allocated and deallocated in containers. This allows the client to define their own memory policies to suit their logic needs.

- **User-Defined Comparision Functions**
	Extensible compartor interface is provided for sorting and ordering elements within collections. This allows the client to define their own ordering policies for any data type to suit their logic needs.

- **Iterators and Advanced Traversals**
	All data structures inherit from an iterable interface, which provides a standardized way to traverse them through iterators and a for-each function. This makes traversal consistent across all data structures, simplifing the client's code and enhancing readability.


## Usage

```c++
#include <iostream>

#include <Forge/StaticArray.hpp">

int main() {
    // Create a StaticArray with a maximum capacity of 10 integers
	// using the initializer list constructor
    Forge::StaticArray<int, 10> my_array = { 1, 2, 3, 4, 5 };

    // Add elements to the back of the array
    my_array.PushBack(6);
    my_array.PushBack(7);
    my_array.PushBack(8);

    // Remove elements in indices 0, 1 and 2 effectively shifting
	// all elements in their place.
    my_array.Remove(0);
    my_array.Remove(1);
    my_array.Remove(2);

	// Insert elements 10, 11, 12 in indices 0, 1 and 2 effectively
	// shifting all elements to accomodate their place.
    my_array.Insert(0, 10);
    my_array.Insert(1, 11);
    my_array.Insert(2, 12);

	// Access elements by index using index operator
    std::cout << "Element at index 1: " << my_array[1]<< std::endl;

	// Access elements by index using At function for bound-checking
    std::cout << "Element at index 1: " << my_array.At(1) << std::endl;

    // Check the current size, count and capacity
	std::cout << "Current size (memory allocated in bytes): " << my_array.GetCount() << std::endl;
    std::cout << "Current count (number of elements occupied): " << my_array.GetCount() << std::endl;
    std::cout << "Maximum capacity (maximum number of elements): " << my_array.GetCapacity() << std::endl;

    return 0;
}
```


## Installation

#### Using Forge Containers in Your Project
Forge Containers is a header-only library, meaning you can integrate it into your project without the need for compilation or linking. Simply include the header files in your project.

1. Clone the repository to your project directory:
```bash
git clone https://github.com/yourusername/forge-containers.git
```
2. Include the necessary headers in your source code. For example:
```c++
#include "path/to/forge-containers/StaticArray.hpp"
```
#### Running Forge Containers Tests in Your Project
If you want to run the test suite to ensure the library works as expected, you will need CMake to configure and build the tests.

1. Clone the repository:
```bash
git clone https://github.com/yourusername/forge-containers.git
cd forge-containers
```
2. Create a build directory:
```bash
mkdir build
cd build
```
3. Configure the project using CMake:
```bash
cmake ..
```
4. Build the tests:
```bash
cmake --build .
```
5. Run the tests:
```bash
./Tests
```

#### Prerequisites
To use Forge Containers:

- A C++17 or later compatible compiler is required (e.g., GCC 7+, Clang 5+, or MSVC 2017+).

To build and run the tests:

- CMake 3.10 or later.
- A compatible build system (e.g., make or ninja).