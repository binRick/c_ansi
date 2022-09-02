#pragma once
#include <CoreServices/CoreServices.h>
#include <stdbool.h>
#ifndef ASCII_ENCODING
#define ASCII_ENCODING    kCFStringEncodingASCII
#endif
char *strip_non_ascii(const char *s);
char *int_to_icon(const int b);
char *int_to_string(const int b);
char *string_copy(char *s);
char *cfstring_copy(CFStringRef string);
CFStringRef cfstring_from_cstring(char *cstring);
char *cstring_from_CFString(CFStringRef cf_string);
char * CFStringCopyUTF8String(CFStringRef aString);
char *get_chars_from_CFString(CFStringRef cf_string);
char * cstring_get_ascii_string(CFStringRef data);
