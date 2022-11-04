#ifndef ANSI_STRING_UTILS_C
#define ANSI_STRING_UTILS_C
/////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>
/////////////////////////////////////////////////////
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "string-utils/string-utils.h"

/////////////////////////////////////////////////////
size_t get_fp_size(FILE *fp){
  long int cur_pos;

  fgetpos(fp, &cur_pos);
  fseek(fp, 0, SEEK_END);
  size_t fp_size = ftell(fp);

  fseek(fp, cur_pos, SEEK_SET);
  return(fp_size);
}

char *vector_size_ts_to_csv(struct Vector *v, int max_width){
  struct StringBuffer *sb            = stringbuffer_new();
  struct StringBuffer *cur_line      = stringbuffer_new();
  int                 cur_line_index = 0;
  int                 lines_qty      = 0;

  for (size_t i = 0; i < vector_size(v); i++) {
    if (strlen(stringbuffer_to_string(cur_line)) > (size_t)max_width) {
      if (lines_qty > 0) {
        stringbuffer_append_string(sb, "\n");
      }
      stringbuffer_append_string(sb, stringbuffer_to_string(cur_line));
      stringbuffer_clear(cur_line);
      cur_line_index = 0;
      lines_qty++;
    }else{
      if (cur_line_index > 0 && i < vector_size(v) - 1) {
        stringbuffer_append_string(cur_line, ", ");
      }
      stringbuffer_append_unsigned_long_long(cur_line, (size_t)vector_get(v, i));
      cur_line_index++;
    }
  }
  stringbuffer_append_string(sb, stringbuffer_to_string(cur_line));
  char *s = stringbuffer_to_string(sb);

  stringbuffer_release(cur_line);
  stringbuffer_release(sb);
  return(s);
}

int CFDictionaryGetInt(CFDictionaryRef dict, const void *key) {
  int value;

  return(CFNumberGetValue(CFDictionaryGetValue(dict, key), kCFNumberIntType, &value) ? value : 0);
}

char *CFDictionaryCopyCString(CFDictionaryRef dict, const void *key) {
  const void *dictValue;
  CFIndex    length;
  int        maxSize, isSuccess;
  char       *value;

  dictValue = CFDictionaryGetValue(dict, key);
  if (dictValue == NULL) {
    return(NULL);
  }
  length  = CFStringGetLength(dictValue);
  maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
  if (length == 0 || maxSize == 0) {
    value  = (char *)malloc(1);
    *value = '\0';
    return(value);
  }

  value     = (char *)malloc(maxSize);
  isSuccess = CFStringGetCString(dictValue, value, maxSize, kCFStringEncodingUTF8);

  return((isSuccess ? value : NULL));
}

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

char *uppercase_first_word_letters(char *S){
  char *s=NULL, *t, *w;
  if(!S)return(s);
  struct StringFNStrings words = stringfn_split_words(S);
  struct StringBuffer *sb = stringbuffer_new();
  for(int i=0;i<words.count;i++){
    w = words.strings[i];
    asprintf(&t,"%s%s",
        stringfn_to_uppercase(stringfn_substring(w,0,1)),
        stringfn_substring(w,1,strlen(w)-1)
        );
    stringbuffer_append_string(sb,strdup(t));
    if(t)free(t);
  }
  s = stringbuffer_to_string(sb);
  stringbuffer_release(sb);
  return(s);
}

char *size_to_string(const size_t b){
  char *s = NULL;
  struct StringBuffer *sb = stringbuffer_new_with_options(b%10, true);
  stringbuffer_append_unsigned_long_long(sb,b);
  s = stringbuffer_to_string(sb);
  stringbuffer_release(sb);
  return(s);
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

bool string_contains_string(const char *s1, const char *s2){
  if(strlen(s2)>strlen(s1))return false;
  size_t len = strlen(s2);
  char *ss;
  for(size_t i=0;i<strlen(s1)-len+1;i++){
    ss = stringfn_substring(s1,i,len);

    if(strcmp(ss,s2)==0)
      return true;
  }
  return false;
}

char *strip_non_alpha(const char *s){
  struct StringBuffer *sb = stringbuffer_new_with_options(strlen(s), true);
  for (size_t i = 0; i < strlen(s); i++) {
    char *substring = stringfn_substring(s, i, 1);
    if (substring) {
      if (stringfn_is_ascii(substring) && isalpha(substring[0])) {
        stringbuffer_append_string(sb, substring);
      }
      free(substring);
    }
  }
  char *stripped = stringbuffer_to_string(sb);

  stringbuffer_release(sb);
  return(stripped);

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

/**
 * @brief         pad_string
 *
 * @param hex_num		Number to be printed
 * @param check_num		check number to test for
 * @param width			size of output buffer
 * @param pad_char		padding character
 * @param destination	output buffer
 * @note				function to add an integer to a buffer. If the number is
 *            equal to teh check number then if will instead pack the
 *            pad character into the buffer
 *            Done originally for printing '--------' if a number was
 *            equal to Zero.
 */
void pad_string(uint32_t   hex_num,
                uint32_t   check_num,
                int        width,
                const char pad_char,
                char       *destination){
  /*
   * Example: 32-bit integer to be printed as hex
   *                      1
   * 0 1 2 3 4 5  6 7 8 9 0
   * 0 x 8 0 0 0  0 0 0 0 \0
   */
  if (destination == NULL) {
    return;
  }

  memset(destination, pad_char, width);
  destination[width - 1] = '\0';

  if (hex_num != check_num) {
    sprintf(destination, "0x%08X", hex_num);
  }
}

size_t string_size_to_size_t(char *SIZE_STRING){
  char **ep = NULL;

  return((size_t)strtoimax(SIZE_STRING, &ep, 10));
}

/**
 * @brief pad_string_ret
 *
 * @param hex_num
 * @param check_num
 * @param pad_char
 * @return
 */
char *pad_string_ret(uint32_t   hex_num,
                     uint32_t   check_num,
                     const char pad_char){
  static char pad_string[11];

  /*
   *                      1
   * 0 1 2 3 4 5  6 7 8 9 0
   * 0 x 8 0 0 0  0 0 0 0 \0
   */
  memset(pad_string, pad_char, sizeof(pad_string));
  pad_string[sizeof(pad_string) - 1] = '\0';

  if (hex_num != check_num) {
    sprintf(pad_string, "0x%08X", hex_num);
  }

  return((char *)(pad_string));
}

void safe_CFRelease(void *cfTypeRefPtr){
  CFTypeRef *obj = (CFTypeRef *)cfTypeRefPtr;

  if (obj && *obj) {
    CFRelease(*obj);
    *obj = NULL;
  }
}

char *pad_string_right(char *S, int len, char p){
  char *s= strdup(S);
  while(strlen(s)<len)
    asprintf(&s,"%s%c",s,p);
  return(s);
}

int read_32bytes_big_endian_image_buffer(unsigned char *buf) {
  return(buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3]);
}

int read_16bytes_little_endian_image_buffer(unsigned char *buf) {
  return(buf[1] << 8 | buf[0]);
}

#endif
