#pragma once
/////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>
/////////////////////////////////////////////////////
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "string-utils/string-utils.h"

/////////////////////////////////////////////////////

CFArrayRef cfarray_of_cfnumbers(void *values, size_t size, int count, CFNumberType type){
  CFNumberRef temp[count];

  for (int i = 0; i < count; ++i) {
    temp[i] = CFNumberCreate(NULL, type, ((char *)values) + (size * i));
  }

  CFArrayRef result = CFArrayCreate(NULL, (const void **)temp, count, &kCFTypeArrayCallBacks);

  for (int i = 0; i < count; ++i) {
    CFRelease(temp[i]);
  }

  return(result);
}

char * CFStringCopyUTF8String(CFStringRef aString){
  if (aString == NULL) {
    return(NULL);
  }

  CFIndex length  = CFStringGetLength(aString);
  CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);

  char    *buffer = (char *)malloc(maxSize);

  if (CFStringGetCString(aString, buffer, maxSize, kCFStringEncodingUTF8)) {
    return(buffer);
  }

  return(buffer);
}

char * cstring_get_ascii_string(CFStringRef data) {
  const char *bytes = NULL;
  char       *chars = NULL;
  size_t     len    = 0;

  bytes = CFStringGetCStringPtr(data, ASCII_ENCODING);
  if (bytes == NULL) {
    len   = (size_t)CFStringGetLength(data) + 1;
    chars = (char *)calloc(len, sizeof(char));
    if (chars != NULL) {
      if (!CFStringGetCString(data, chars, (CFIndex)len, ASCII_ENCODING)) {
        free(chars);
        chars = NULL;
      }
    }
  } else {
    len   = strlen(bytes) + 1;
    chars = (char *)calloc(len, sizeof(char));
    if (chars != NULL) {
      strcpy(chars, bytes);
    }
  }
  return(chars);
}

char *get_chars_from_CFString(CFStringRef cf_string) {
  CFIndex length = CFStringGetLength(cf_string);
  CFIndex size   = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
  CFIndex used_size;
  CFRange range   = CFRangeMake(0, length);
  char    *string = malloc(size);

  CFStringGetBytes(
    cf_string, range, kCFStringEncodingUTF8, '?', false, (unsigned char *)string,
    size - 1, &used_size);
  string[used_size] = '\0';
  return(string);
}

char *cstring_from_CFString(CFStringRef cf_string) {
  CFIndex length = CFStringGetLength(cf_string);
  CFIndex size   = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
  CFIndex used_size;
  CFRange range   = CFRangeMake(0, length);
  char    *string = malloc(size);

  CFStringGetBytes(
    cf_string, range, kCFStringEncodingUTF8, '?', false, (unsigned char *)string,
    size - 1, &used_size);
  string[used_size] = '\0';
  return(string);
}

CFStringRef cfstring_from_cstring(char *cstring){
  CFStringRef cfstring = CFStringCreateWithCString(NULL, cstring, kCFStringEncodingUTF8);

  return(cfstring);
}

char *cfstring_copy(CFStringRef string) {
  CFIndex num_bytes = CFStringGetMaximumSizeForEncoding(CFStringGetLength(string), kCFStringEncodingUTF8);
  char    *result   = malloc(num_bytes + 1);

  if (!result) {
    return(NULL);
  }

  if (!CFStringGetCString(string, result, num_bytes + 1, kCFStringEncodingUTF8)) {
    free(result);
    result = NULL;
  }

  return(result);
}

char *string_copy(char *s) {
  int  length  = strlen(s);
  char *result = malloc(length + 1);

  if (!result) {
    return(NULL);
  }

  memcpy(result, s, length);
  result[length] = '\0';
  return(result);
}

char *int_to_string(const int b){
  struct StringBuffer *sb = stringbuffer_new_with_options(8, true);

  if (b == 1) {
    stringbuffer_append_string(sb, "Yes");
  }else{
    stringbuffer_append_string(sb, "No");
  }
  char *s = stringbuffer_to_string(sb);

  stringbuffer_release(sb);
  return(s);
}

char *int_to_icon(const int b){
  struct StringBuffer *sb = stringbuffer_new_with_options(8, true);

  if (b == 1) {
    stringbuffer_append_string(sb, "✅");
  }else{
    stringbuffer_append_string(sb, "❌");
  }
  char *s = stringbuffer_to_string(sb);

  stringbuffer_release(sb);
  return(s);
}

char *strip_non_ascii(const char *s){
  struct StringBuffer *sb = stringbuffer_new_with_options(strlen(s), true);

  for (size_t i = 0; i < strlen(s); i++) {
    char *substring = stringfn_substring(s, i, 1);
    if (substring) {
      if (stringfn_is_ascii(substring)) {
        stringbuffer_append_string(sb, substring);
      }
      free(substring);
    }
  }
  char *stripped = stringbuffer_to_string(sb);

  stringbuffer_release(sb);
  return(stripped);
}
