#ifndef STRINGCOMPAT_H
#define STRINGCOMPAT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

#ifndef snprintf
#define snprintf _snprintf
#endif

#ifndef strncasecmp
#define strncasecmp strnicmp
#endif

#ifndef strcasecmp
#define strcasecmp stricmp
#endif

// asprintf ?? https://github.com/XenonofArcticus/GLSL-Debugger/blob/master/GLSLCompiler/glslang/OSDependent/Windows/asprintf.h
static int vasprintf(char **s, const char *format, va_list ap)
{
        /* Guess we need no more than 100 bytes. */
        int n, size = 100;
        va_list save_ap;

        if ((*s = (char*) malloc(size)) == NULL)
                return -1;
        while (1) {
                /* wwork on a copy of the va_list because of a bug
                 in the vsnprintf implementation in x86_64 libc
                 */
#ifdef __va_copy
                __va_copy(save_ap, ap);
#else
                save_ap = ap;
#endif
                /* Try to print in the allocated space. */
                n = _vsnprintf(*s, size, format, save_ap);
                va_end(save_ap);
                /* If that worked, return the string. */
                if (n > -1 && n < size) {
                        return n;
                }
                /* Else try again with more space. */
                if (n > -1) { /* glibc 2.1 */
                        size = n + 1; /* precisely what is needed */
                } else { /* glibc 2.0 */
                        size *= 2; /* twice the old size */
                }
                if ((*s = (char*) realloc(*s, size)) == NULL) {
                        return -1;
                }
        }
}

static int asprintf(char **s, const char *format, ...)
{
        va_list vals;
        int result;

        va_start(vals, format);
        result = vasprintf(s, format, vals);
        va_end(vals);
        return result;
}

static char* strnstr(const char *s1, const char *s2, size_t n) {
  size_t len = strlen(s2);
  if (n >= len) {
    char c = *s2;
    const char *end = s1 + (n - len);
    const char *s;
    for (s = s1; *s && s <= end; s++) {
      if (*s == c && !strncmp(s, s2, len)) {
        return (char *)s;
      }
    }
  }
  return NULL;
}

// https://www.opensource.apple.com/source/gcc/gcc-5666.3/libiberty/strndup.c
static char* strndup(const char *s, size_t n) 
{
  char *result;
  size_t len = strlen (s);

  if (n < len)
    len = n;

  result = (char *) malloc (len + 1);
  if (!result)
    return 0;

  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}

// http://ftp-archive.freebsd.org/pub/FreeBSD-Archive/old-releases/i386/1.0-RELEASE/ports/textutils/lib/stpcpy.c
static char* stpcpy (char *dest, const char *source)
{
  while ((*dest++ = *source++) != '\0')
    /* Do nothing. */ ;
  return dest - 1;
}

// http://www.opensource.apple.com/source/Libc/Libc-320/string/FreeBSD/strcasestr.c
static char* strcasestr(const char *s, const char *find)
{
    char c, sc;
    size_t len;

    if ((c = *find++) != 0) {
        c = tolower((unsigned char)c);
        len = strlen(find);
        do {
            do {
                if ((sc = *s++) == 0)
                    return (NULL);
            } while ((char)tolower((unsigned char)sc) != c);
        } while (strncasecmp(s, find, len) != 0);
        s--;
    }
    return ((char *)s);
}

#ifdef __cplusplus
}
#endif

#endif STRINGCOMPAT_H