#ifndef MD5PARSER_H_INCLUDED
#define MD5PARSER_H_INCLUDED
#include <stdio.h>
#include "openssl/md5.h"

/*
This program uses md5 library from openssl
https://github.com/openssl/openssl/tree/master/include/openssl
Compile with gcc -o md5parser.c -lcrypto
*/

/*
String to MD5 parser
	Input 
 		string to check -> constant char
		string length -> int
		out pointer -> string -> malloc(sizeof(char)*strLength);
	Output
		33 character of md5 -> string -> char out[33];
*/
char *strMD5(const char *str, int length, char *out);

#endif
