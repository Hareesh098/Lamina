#ifndef LAMINA_VERSION_H
#define LAMINA_VERSION_H

#define LAMINA_VERSION_MAJOR 3
#define LAMINA_VERSION_MINOR 1
#define LAMINA_VERSION_PATCH 0

#define LAMINA_STRFY(x) #x
#define LAMINA_TOSTR(x) LAMINA_STRFY(x)
#define LAMINA_VERSION_STR  LAMINA_TOSTR(LAMINA_VERSION_MAJOR) "." \
                             LAMINA_TOSTR(LAMINA_VERSION_MINOR) "." \
                             LAMINA_TOSTR(LAMINA_VERSION_PATCH)

#define LAMINA_NAME "Lamina"

/* ---- build metadata ---- */
#define LAMINA_BUILD_DATE   __DATE__
#define LAMINA_BUILD_TIME   __TIME__

#if defined(__clang__)
  #define LAMINA_COMPILER "Clang " __clang_version__
#elif defined(__GNUC__)
  #define LAMINA_COMPILER "GCC " __VERSION__
#elif defined(_MSC_VER)
  #define LAMINA_COMPILER "MSVC"
#else
  #define LAMINA_COMPILER "Unknown compiler"
#endif

/* Git hash injected by Makefile */
#ifndef GIT_COMMIT_HASH
#define GIT_COMMIT_HASH "unknown"
#endif

#endif

