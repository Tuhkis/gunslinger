#ifndef __GS_TYPES_H__
#define __GS_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>		// valist
#include <stdlib.h>		// malloc, realloc, free (for now)
#include <stdint.h>		// standard types
#include <limits.h>		// INT32_MAX, UINT32_MAX
#include <string.h> 	// memset
#include <float.h>		// FLT_MAX
#include <time.h>
#include <ctype.h>

#ifndef gs_inline
	#define gs_inline 			static inline
#endif
#ifndef gs_local_persist
	#define gs_local_persist 	static
#endif
#ifndef gs_global
	#define gs_global 			static
#endif

 #if (defined _WIN32 || defined _WIN64)
	#define gs_force_inline gs_inline
#elif (defined __APPLE__ || defined _APPLE)
	#define gs_force_inline static __attribute__((always_inline))
#else
	#define gs_force_inline gs_inline
#endif

/*============================================================
// Resource Declarations
============================================================*/

#define gs_resource(type)\
	gs_resource_##type

// Strongly typed declarations for resource handles (slot array handles)
#define gs_declare_resource_type(type)\
	typedef struct gs_resource(type) {\
		u32 id;\
	} gs_resource(type);\
\
	gs_force_inline\
	gs_resource(type) gs_resource_invalid_##type()\
	{\
		gs_resource(type) r;\
		r.id = u32_max;\
		return r;\
	}

#define gs_resource_invalid(type)\
	gs_resource_invalid_##type()

/*============================================================
// Result
============================================================*/

typedef enum
{
	gs_result_success,
	gs_result_in_progress,
	gs_result_incomplete,
	gs_result_failure
} gs_result;

/*================
// Color
=================*/

#define gs_hsv(...) gs_hsv_ctor(__VA_ARGS__)
#define gs_color(...) gs_color_ctor(__VA_ARGS__)

typedef struct gs_hsv_t
{
	union 
	{
		float hsv[3];
		struct 
		{
			float h, s, v;
		};
	};
} gs_hsv_t;

gs_force_inline
gs_hsv_t gs_hsv_ctor(float h, float s, float v)
{
	gs_hsv_t hsv;
	hsv.h = h;
	hsv.s = s;
	hsv.v = v;
	return hsv;
}

typedef struct gs_color_t
{
	union 
	{
		uint8_t rgba[4];
		struct 
		{
			uint8_t r, g, b, a;
		};
	};
} gs_color_t;

gs_force_inline
gs_color_t gs_color_ctor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	gs_color_t color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

#define gs_color_black 	gs_color(0, 0, 0, 255)
#define gs_color_white 	gs_color(255, 255, 255, 255)
#define gs_color_red 	gs_color(255, 0, 0, 255)
#define gs_color_green 	gs_color(0, 255, 0, 255)
#define gs_color_blue 	gs_color(0, 0, 255, 255)
#define gs_color_orange gs_color(255, 100, 0, 255)
#define gs_color_purple gs_color(128, 0, 128, 255)

gs_force_inline 
gs_color_t gs_color_alpha(gs_color_t c, uint8_t a)
{
	return gs_color(c.r, c.g, c.b, a); 
}

/*============================================================
// Primitives
============================================================*/

#ifndef __cplusplus
	#define false 		0
	#define true 		1
#endif

typedef size_t		usize;

#ifdef __cplusplus
	typedef bool 		b8;
#else
	typedef _Bool 		b8;
#endif

typedef uint8_t 		u8;
typedef int8_t 			s8;
typedef uint16_t 		u16;
typedef int16_t 		s16;
typedef uint32_t 		u32;
typedef int32_t			s32;
typedef s32 			b32;
typedef uint64_t		u64;
typedef int64_t			s64;
typedef float 	 		f32;
typedef double			f64;
typedef const char* 	const_str;

#define u16_max 		UINT16_MAX
#define u32_max			UINT32_MAX
#define s32_max			INT32_MAX
#define f32_max 		FLT_MAX
#define f32_min 		FLT_MIN


#ifdef __cplusplus
}
#endif 	// c++

#endif // __GS_TYPES_H__
