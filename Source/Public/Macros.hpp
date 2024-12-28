#ifndef MACROS_HPP
#define MACROS_HPP

#define STATIC_COLLECTION_TYPEDEFS(BASE_TYPE, SUB_TYPE)						\
public:																		\
	using BaseType = BASE_TYPE<InElementType, NoAllocationPolicy>;			\
																			\
	using SelfType = SUB_TYPE<InElementType, InCapacity>;					\
	using SelfTypePtr = SUB_TYPE<InElementType, InCapacity>*;				\
	using SelfTypeLRef = SUB_TYPE<InElementType, InCapacity>&;				\
	using SelfTypeRRef = SUB_TYPE<InElementType, InCapacity>&&;				\
	using ConstSelfType = const SUB_TYPE<InElementType, InCapacity>;		\
	using ConstSelfTypePtr = const SUB_TYPE<InElementType, InCapacity>*;	\
	using ConstSelfTypeLRef = const SUB_TYPE<InElementType, InCapacity>&;	\
																			\
	using ElementType = InElementType;										\
	using ElementTypePtr = InElementType*;									\
	using ElementTypeLRef = InElementType&;									\
	using ElementTypeRRef = InElementType&&;								\
	using ConstElementType = const InElementType;							\
	using ConstElementTypePtr = const InElementType*;						\
	using ConstElementTypeLRef = const InElementType&;

#define STATIC_ADAPTOR_COLLECTION_TYPEDEFS(BASE_TYPE, SUB_TYPE, COL_TYPE)	\
public:																		\
	using BaseType = BASE_TYPE<InElementType, NoAllocationPolicy>;			\
																			\
	using SelfType = SUB_TYPE<InElementType, InCapacity>;					\
	using SelfTypePtr = SUB_TYPE<InElementType, InCapacity>*;				\
	using SelfTypeLRef = SUB_TYPE<InElementType, InCapacity>&;				\
	using SelfTypeRRef = SUB_TYPE<InElementType, InCapacity>&&;				\
	using ConstSelfType = const SUB_TYPE<InElementType, InCapacity>;		\
	using ConstSelfTypePtr = const SUB_TYPE<InElementType, InCapacity>*;	\
	using ConstSelfTypeLRef = const SUB_TYPE<InElementType, InCapacity>&;	\
																			\
	using ElementType = InElementType;										\
	using ElementTypePtr = InElementType*;									\
	using ElementTypeLRef = InElementType&;									\
	using ElementTypeRRef = InElementType&&;								\
	using ConstElementType = const InElementType;							\
	using ConstElementTypePtr = const InElementType*;						\
	using ConstElementTypeLRef = const InElementType&;						\
																			\
	using ContainerType = COL_TYPE<InElementType, InCapacity>;

#endif