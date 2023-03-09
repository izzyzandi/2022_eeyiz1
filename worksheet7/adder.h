// begin adder.h
// following lines stops this from being included more than once in each source

#ifndef MATHSLIB_ADDER_H
	#define MATHSLIB_ADDER_H

/** @file
* this file contains the declarations of all exported functions in the maths library
*/

/** Adding function					[Brief description]
* this function adds two numbers	[More detail]
* @param a is the first number		[Parameter definition]
* @param b is the second number		[Parameter definition]
* @return sum of a and b			[Return value description]
*/

#if defined(WIN32)|defined(_WIN32)
	#ifdef maths_STATIC

		#define MATHSLIB_API
	#else
		#ifdef maths_EXPORTS
			#define MATHSLIB_API __declspec (dllexport)
		#else
			#define MATHSLIB_API __declspec (dllexport)
		#endif
	#endif
#else
	#define MATHSLIB_API
#endif	

	MATHSLIB_API int add(int a, int b);


	
#endif

//end adder.h
