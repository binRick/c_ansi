#ifndef ANSI_STRING_UTILS_H
#define ANSI_STRING_UTILS_H
#include "c_vector/vector/vector.h"
#include <CoreServices/CoreServices.h>
#include <stdbool.h>
#ifndef ASCII_ENCODING
#define ASCII_ENCODING    kCFStringEncodingASCII
#endif
char *su_limit_string_lines_width(char *str, size_t width);
char *strip_non_ascii(const char *s);
char *strip_non_alpha(const char *s);
bool string_contains_string(const char *s1, const char *s2);
char *int_to_icon(const int b);
char *int_to_string(const int b);
char *size_to_string(const size_t b);
char *string_copy(char *s);
char *cfstring_copy(CFStringRef string);
CFStringRef cfstring_from_cstring(char *cstring);
char *cstring_from_CFString(CFStringRef cf_string);
char * CFStringCopyUTF8String(CFStringRef aString);
char *get_chars_from_CFString(CFStringRef cf_string);
char * cstring_get_ascii_string(CFStringRef data);
CFArrayRef cfarray_of_cfnumbers(void *values, size_t size, int count, CFNumberType type);
char *CFDictionaryCopyCString(CFDictionaryRef dict, const void *key);
int CFDictionaryGetInt(CFDictionaryRef dict, const void *key);
char *vector_size_ts_to_csv(struct Vector *v, int max_width);
size_t get_fp_size(FILE *fp);
size_t string_size_to_size_t(char *SIZE_STRING);
int read_16bytes_little_endian_image_buffer(unsigned char *buf);
int read_32bytes_big_endian_image_buffer(unsigned char *buf);
char *uppercase_first_word_letters(char *);
char *pad_string_right(char *s, int len, char p);
char *hash_buffer(void *s, size_t len);
char *hash_path(char *path);
char *hash_buffer(void *s, size_t len);
#endif
