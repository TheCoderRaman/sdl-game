#include "debug.h"

#include <stdio.h>	// for printf functions
#include <string.h> // for strncat
#include <stdarg.h> // for the va_ arg list

//! Path seperators are different on Unix compared to windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#define PATH_SEP '\\'
#else
	#define PATH_SEP '/' 
#endif

//! Grab only the file name not the full path
#define FILE_NAME(filepath) (strrchr(filepath, PATH_SEP) ? strrchr(filepath, PATH_SEP) + 1 : filepath)

//! The max buffer size for the final string. if we run into errors then we can up this
#define FINAL_STR_MAX 	256

void _debug_log(const char* file, int line, const char* format , ... )
{ 
	//! The final output string
	char finalStr[FINAL_STR_MAX];	

	//! print in the formatted prefix into the output
	sprintf( finalStr, "%s:%i -> ", FILE_NAME(file) , line );

	//! concatonate the format string from the debug message into the output
	strncat( finalStr, format , FINAL_STR_MAX);

	//! Grab the list
	va_list args;
	va_start (args, format);

	//! print to stderr the final string with it's arguments
	vfprintf( stderr, finalStr, args );

	//! close the list
	va_end (args);

}
