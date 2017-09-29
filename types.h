

#ifndef __BASIC_TYPE__
#define __BASIC_TYPE__

#include <stdint.h>

typedef int8_t		i8;
typedef int16_t		i16;
typedef int32_t		i32;
typedef int64_t		i64;

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;

typedef char		CHAR;
typedef int16_t		CHAR2;
typedef int32_t		CHAR4;
typedef int64_t		CHAR8;

//typedef uint16_t	WCHAR;
typedef int32_t		WCHAR2;
typedef int64_t		WCHAR4;

typedef UINT		FLAG_T;
typedef UINT		ID;

#define SIZE_OF_TCHAR(n)				(sizeof(TCHAR)*n)
#define SIZE_OF_ARRAY(_array,_type)		(sizeof(_array)/sizeof(_type))
//#define SIZE_OF_PTCHAR_ARRAY(_array)	(sizeof(_array)/sizeof(PTCHAR))
//  ------------------------------------------------------------------------------
//	Format		BYTE 1		BYTE 2		BYTE 3		BYTE 4		...		BYTE n
//	------------------------------------------------------------------------------
//	real * 4	SXXX XXXX	XMMM MMMM	MMMM MMMM	MMMM MMMM
//	real * 8	SXXX XXXX	XXXX MMMM	MMMM MMMM	MMMM MMMM	...		MMMM MMMM
//	real * 10	SXXX XXXX	XXXX XXXX	1MMM MMMM	MMMM MMMM	...		MMMM MMMM
//  ------------------------------------------------------------------------------
typedef float		f32;
typedef double		f64;

#endif // !__BASIC_TYPE__



#include <string>


#ifdef _MSC_VER
#	include <tchar.h>
#endif

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>,
	std::allocator<TCHAR> > _tstring;