/**
 *	@brief Detecta las caracteristicas actuales del entorno de destino de la compilacion.
 *	@todo Segmentar caracteristicas segun la version del compilador
 */

#ifndef __EXENG_DETECTENV_HPP__
#define __EXENG_DETECTENV_HPP__

//Detetect architecture
#  if defined(__alph_) || defined(__alpha) || defined(_M_ALPHA)
#    define EXENG_ALPHA
#  elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64)
#    define EXENG_AMD64
#  elif defined(i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__i386) || defined(_M_IX86) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__)
#    define EXENG_IA32
#  elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64)
#    define EXENG_IA64
#  elif defined(__sparc__) || defined(__sparc)
#    define EXENG_SPARC
#  elif defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(__ppc__) || defined(_M_PPC) || defined(_ARCH_PPC)
#    define EXENG_POWERPC
#  endif

//Detect byte order
#  if defined(EXENG_IA32) || defined(EXENG_IA64) || defined(EXENG_AMD64) 
#    define EXENG_LITTLE_ENDIAN
#  elif defined(EXENG_ALPHA) || defined(EXENG_SPARC) || defined(EXENG_POWERPC) 
#    define EXENG_BIG_ENDIAN 
#  else
#    define EXENG_LITTLE_ENDIAN
#  endif

//Detec compiler wide
#if defined(EXENG_IA32) || defined(EXENG_SPARC) || defined(EXENG_SPARC) || defined(EXENG_POWERPC)
#  define EXENG_32
#elif defined(EXENG_IA64) || defined(EXENG_AMD64)
#  define EXENG_64
#endif

//Detect operating system
#  if defined(_WIN32) || defined(WIN32) || defined(_WINDOWS) || defined(__WIN32__)
#    define EXENG_WINDOWS
#  elif defined(__unix__) || defined(unix)
#    define EXENG_UNIX
#  elif defined(__gnu_linux__) || defined(__linux) || defined(linux)
#    define EXENG_LINUX
#  elif defined(__APPLE__)
#    define EXENG_MACOS
#  elif defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
#    define EXENG_DOS
#  endif

//Detect current compiler
#  if defined (_MSC_VER)
#    define EXENG_MSVC _MSC_VER
#  elif defined (__GNUG__)
#    define EXENG_GCC 
#  elif defined (__BORLANDC__)
#    define EXENG_BCC
#  elif defined (__COMO__)
#    define EXENG_COMEAU
#  elif defined (__INTEL_COMPILER) || defined (__ICL)
#    define EXENG_ICC
#  elif defined (__DMC__)
#    define EXENG_DMC
#  endif

//Define the EXENG_DEPRECATED macro.
#  if defined (EXENG_GCC)
#    if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)
#      define EXENG_DEPRECATED __attribute__((__deprecated__))
#    else
#      define EXENG_DEPRECATED 
#    endif
#  elif defined (EXENG_MSVC)
#    if _MSC_VER >= 1310
#      define EXENG_DEPRECATED __declspec(deprecated)
#    else
#      define EXENG_DEPRECATED 
#    endif
#  else 
#    define EXENG_DEPRECATED 
#  endif

#endif  //__EXENG_DETECTENV_HPP__
