/*H**********************************************************************
* FILENAME :	varargs.h					START DATE :	10 Sept 16
*
* DESCRIPTION :
*		Provides facilities for stepping through a list of function arguments of
*		an unknown number and type.
*
* NOTES :
*		This file is part of SC-CL's include library.
*
*		The type used in va_arg is supposed to match the actual type
*		after default promotions. Thus, va_arg (..., short) is not valid.
*
* LICENSE :
*
*		Copyright 2016 SC-CL
*
*		Redistribution and use in source and binary forms, with or without
*		modification, are permitted provided that the following conditions are met:
*
*		* Redistributions of source code must retain the above copyright
*		notice, this list of conditions and the following disclaimer.
*
*		* Redistributions in binary form must reproduce the above copyright
*		notice, this list of conditions and the following disclaimer in the
*		documentation and/or other materials provided with the distribution.
*
*		* Neither SC-CL nor its contributors may be used to endorse or promote products
*		derived from this software without specific prior written permission.
*
*		* Redistribution of this software in source or binary forms shall be free
*		of all charges or fees to the recipient of this software.
*
*		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*		ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*		WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*		DISCLAIMED. IN NO EVENT SHALL SC-CL BE LIABLE FOR ANY
*		DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*		(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*		LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*		(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* AUTHORS :
*		Rocko Tompkins
*		Nathan James
*H*/
#pragma once

#ifndef	_VA_LIST
#define _VA_LIST
typedef int* va_list;
#endif

/// <summary>
///	Amount of space required in an argument list (ie. the stack) for an 
///	argument of type t.
/// </summary>
/// <param name="t">The type to be evaluated.</param>
/// <returns></returns>
#define __va_argsiz(t)	\
	(((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

/// <summary>
///	Start variable argument list processing by setting AP to point to the
///	argument after pN.
/// </summary>
/// <param name="ap">
///	Uninitialized object of type va_list.
///	<para>After the call, it carries the information needed to retrieve the additional arguments using va_arg.</para>
///	<para>If ap has already been passed as first argument to a previous call to va_start or va_copy, it shall be passed to va_end before calling this function.</para>
///	</param>
/// <param name="pN">
///	Name of the last named parameter in the function definition. 
///	<para>The arguments extracted by subsequent calls to va_arg are those after pN.</para>
/// </param>
/// <returns></returns>
#define va_start(ap, pN)	\
	((ap) = (va_list)*(va_list)((char*)(&pN) + __va_argsiz(pN)))

/// <summary>
///	Increment ap to the next argument in the list while returing a
///	pointer to what ap pointed to first, which is of type t.
/// </summary>
/// <param name="ap">
///	Object of type va_list carrying information about the current retrieval state of a variable argument list.
///	<para>This object shall have been initialized by an initial call to va_start or va_copy and not have been released with va_end.</para>
///	</param>
/// <param name="t">
///	A type name.This type name is used as the type of the expression this macro expands to(i.e., its return type).
///	<para>For a type expression to be suitable for its use with va_arg, it must be such that type* produces a pointer to type.</para>
///	<para>The type shall be compatible with type of the extracted argument(as promoted according to the default argument promotions),</para>
///	<para>or one be the unsigned version of the other, or one be a void pointer and the other some other pointer type.</para>
/// </param>
/// <returns></returns>
#define va_arg(ap, t)					\
	 (((ap) = (va_list)((char*)(ap) + __va_argsiz(t))),		\
	  *((t*)((char*)(ap) - __va_argsiz(t))))

/// <summary>
///	Initializes dest as a copy of src (in its current state)
/// </summary>
/// <param name="dest">
///	Uninitialized object of type va_list.
///	<para>After the call, it carries the information needed to retrieve the same additional arguments as src.</para>
///	<para>If dest has already been passed as first argument to a previous call to va_start or va_copy, it shall be passed to va_end before calling this function.</para>
///	</param>
/// <param name="src">
///	Object of type va_list that already carries information to retrieve additional arguments with va_arg 
///	<para>(i.e., it has already been passed as first argument to va_start or va_copy ans has not yet been released with va_end).</para>
/// </param>
/// <returns></returns>
#define va_copy(dest, src) ((dest) = (src))

/// <summary>
///	End processing of variable argument list. In this case we do nothing.
/// </summary>
/// <param name="ap">
///	Object of type va_list carrying information about the current retrieval state of a variable argument list. 
///	<para>This object shall have been initialized by an initial call to va_start or va_copy and not have been released with va_end.</para>
/// </param>
/// <returns></returns>
#define va_end(ap)	((void)0)

/// <summary>
///	Gets the variable argument param count from the last argument pN
/// </summary>
/// <param name="pN">
///	Name of the last named parameter in the function definition. 
/// </param>
/// <returns></returns>
#define va_count(pN)	\
	(*(int*)((char*)(&pN) + __va_argsiz(pN) + sizeof(va_list)))

/// <summary>
///	Gets the variable argument stack count from the last argument pN
/// </summary>
/// <param name="pN">
///	Name of the last named parameter in the function definition. 
/// </param>
/// <returns></returns>
#define va_scount(pN)	\
	(*(int*)((char*)(&pN) + __va_argsiz(pN) + sizeof(va_list) + sizeof(int)))

#define __OL_N(number) number, impossible, number
#define __OL_S 1, 0, 1,
#define __OL_CIP(...) ,
#define __OL_LP (
#define __OL_EX(...) __VA_ARGS__
#define __OL_CH(...) __OL_EX(__OL_LOG __OL_LP __VA_ARGS__ __OL_CIP __VA_ARGS__ __OL_CIP __VA_ARGS__ (), \
	__OL_N(20), __OL_N(19), __OL_N(18), __OL_N(17), __OL_N(16), __OL_N(15), __OL_N(14), __OL_N(13), __OL_N(12), __OL_N(11), __OL_N(10), \
	__OL_N(9), __OL_N(8), __OL_N(7), __OL_N(6), __OL_N(5), __OL_N(4), __OL_N(3), __OL_N(2), __OL_S ))
#define __OL_LOG(		\
arg1, arg1_0, arg1_1,	\
arg2, arg2_0, arg2_1,	\
arg3, arg3_0, arg3_1,	\
arg4, arg4_0, arg4_1,	\
arg5, arg5_0, arg5_1,	\
arg6, arg6_0, arg6_1,	\
arg7, arg7_0, arg7_1,	\
arg8, arg8_0, arg8_1,	\
arg9, arg9_0, arg9_1,	\
arg10, arg10_0, arg10_1,	\
arg11, arg11_0, arg11_1,	\
arg12, arg12_0, arg12_1,	\
arg13, arg13_0, arg13_1,	\
arg14, arg14_0, arg14_1,	\
arg15, arg15_0, arg15_1,	\
arg16, arg16_0, arg16_1,	\
arg17, arg17_0, arg17_1,	\
arg18, arg18_0, arg18_1,	\
arg19, arg19_0, arg19_1,	\
arg20, arg20_0, arg20_1,	\
arg, ...) arg

#define _OVERLOAD_(name, n) name##n
#define _OVERLOAD(name, n) _OVERLOAD_(name, n)
#define OVERLOAD(func, ...) _OVERLOAD(func, __OL_CH(__VA_ARGS__)) (__VA_ARGS__)


