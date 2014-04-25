#include "debug.h"

#include <stdio.h>	// for printf functions
#include <string.h> // for strncat
#include <stdarg.h> // for the va_ arg list

#include "Windows.h"

//! Path seperators are different on Unix compared to windows
#if defined(WIN32) || defined(_WIN32)

#define PATH_SEP '\\'
#define STRNCAT	strncat_s

#else

#define PATH_SEP '/' 
#define STRNCAT	strncat

#endif

//! Grab only the file name not the full path
#define FILE_NAME(filepath) (strrchr(filepath, PATH_SEP) ? strrchr(filepath, PATH_SEP) + 1 : filepath)

//! The max buffer size for the final string. if we run into errors then we can up this
#define FINAL_STR_MAX 	256

//! The alignment of the messages, will need to be expanded for long file names or any other data put in the headr
#define FINAL_ALIGNMENT 25

//! Actual debug log method, used to produce the log output
//! \warning never call directly, always call one of the various LOG macros
void _log(const char* file, int line, const char* format, ...)
{ 
	//! The final output string
	char finalStr[FINAL_STR_MAX];	

	// THE HEADER
	//! print in the formatted prefix into the output
#if defined(WIN32) || defined(_WIN32)
	sprintf_s( finalStr, "%s:%i", FILE_NAME(file) , line );
#else 
	snprintf( finalStr, FINAL_STR_MAX, "%s:%i", FILE_NAME(file) , line );
#endif

	// Check the alignment amount
	const int len = strlen(finalStr);
	int alighnment = FINAL_ALIGNMENT - len;

	// Ammend the alignment
	for( int i = 0; i < alighnment; i++ )
		STRNCAT( finalStr, " " , FINAL_STR_MAX );

	// Ammend a little arrow
	STRNCAT(finalStr, " -> ", FINAL_STR_MAX);


	// THE OUTPUT
	//! concatonate the format string from the debug message into the output
	STRNCAT(finalStr, format, FINAL_STR_MAX);
	STRNCAT(finalStr, "\n", FINAL_STR_MAX);

	//! Grab the list
	va_list args;
	va_start (args, format);

	//! print to stderr the final string with it's arguments
	vfprintf( stderr, finalStr, args );

	//! close the list
	va_end (args);

}

