#ifndef TYPE_DEFINITIONS_HPP
#define TYPE_DEFINITIONS_HPP

#if defined(__GNUC__)
#define FORGE_COMPILER_GCC
#elif defined(_MSC_VER)
#define FORGE_COMPILER_MSVC
#elif defined(__llvm__)
#define FORGE_COMPILER_LLVM
#elif defined(__clang__)
#define FORGE_COMPILER_CLANG
#else
#error "Unable to detect compiler."
#endif

#if defined(FORGE_COMPILER_GCC)
#define FORGE_FORCE_INLINE __attribute__((always_inline)) inline
#elif defined(FORGE_COMPILER_MSVC)
#define FORGE_FORCE_INLINE __forceinline
#elif defined(FORGE_COMPILER_CLANG)
#error "Clang is not currently supported."
#elif defined(FORGE_COMPILER_LLVM)
#error "Intel compiler is not currently supported."
#endif

namespace Forge
{
	typedef void Void, *VoidPtr;
	typedef const void *ConstVoidPtr;

	typedef bool Bool, *BoolPtr;
	typedef const bool ConstBool, *ConstBoolPtr;

	typedef char Char, *CharPtr;
	typedef const char ConstChar, *ConstCharPtr;

	typedef float Float32, *Float32Ptr;
	typedef double Float64, *Float64Ptr;
	typedef const float ConstFloat32, *ConstFloat32Ptr;
	typedef const double ConstFloat64, *ConstFloat64Ptr;

#if defined(FORGE_COMPILER_MSVC)
	typedef signed __int8 I8, *I8Ptr;
	typedef signed __int16 I16, *I16Ptr;
	typedef signed __int32 I32, *I32Ptr;
	typedef signed __int64 I64, *I64Ptr;
	typedef const signed __int8 ConstI8, *ConstI8Ptr;
	typedef const signed __int16 ConstI16, *ConstI16Ptr;
	typedef const signed __int32 ConstI32, *ConstI32Ptr;
	typedef const signed __int64 ConstI64, *ConstI64Ptr;

	typedef unsigned __int8 U8, *U8Ptr;
	typedef unsigned __int16 U16, *U16Ptr;
	typedef unsigned __int32 U32, *U32Ptr;
	typedef unsigned __int64 U64, *U64Ptr;
	typedef const unsigned __int8 ConstU8, *ConstU8Ptr;
	typedef const unsigned __int16 ConstU16, *ConstU16Ptr;
	typedef const unsigned __int32 ConstU32, *ConstU32Ptr;
	typedef const unsigned __int64 ConstU64, *ConstU64Ptr;

	typedef unsigned __int8 Byte, *BytePtr;
	typedef const unsigned __int8 ConstByte, *ConstBytePtr;

#if defined(_M_X64) || defined(_M_ARM64)
	typedef unsigned __int64 Size, *SizePtr;
	typedef const unsigned __int64 ConstSize, *ConstSizePtr;
#else
	typedef unsigned __int32 Size, *SizePtr;
	typedef const unsigned __int32 ConstSize, *ConstSizePtr;
#endif

#elif defined(FORGE_COMPILER_GCC)
#include <stdint.h>

	typedef int8_t I8, *I8Ptr;
	typedef int16_t I16, *I16Ptr;
	typedef int32_t I32, *I32Ptr;
	typedef int64_t I64, *I64Ptr;
	typedef const int8_t ConstI8, *ConstI8Ptr;
	typedef const int16_t ConstI16, *ConstI16Ptr;
	typedef const int32_t ConstI32, *ConstI32Ptr;
	typedef const int64_t ConstI64, *ConstI64Ptr;

	typedef uint8_t U8, *U8Ptr;
	typedef uint16_t U16, *U16Ptr;
	typedef uint32_t U32, *U32Ptr;
	typedef uint64_t U64, *U64Ptr;
	typedef const uint8_t ConstU8, *ConstU8Ptr;
	typedef const uint16_t ConstU16, *ConstU16Ptr;
	typedef const uint32_t ConstU32, *ConstU32Ptr;
	typedef const uint64_t ConstU64, *ConstU64Ptr;

	typedef uint8_t Byte, *BytePtr;
	typedef const uint8_t ConstByte, *ConstBytePtr;

#if defined(__x86_64__) || defined(__LP64__)
	typedef uint64_t Size, *SizePtr;
	typedef const uint64_t ConstSize, *ConstSizePtr;
#else
	typedef uint32_t Size, *SizePtr;
	typedef const uint32_t ConstSize, *ConstSizePtr;
#endif

#endif
}

#endif