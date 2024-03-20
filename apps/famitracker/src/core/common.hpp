#include "common/platform.hpp"
#include "common/libraries.hpp"
#include "types.hpp"

#ifdef CORE_ISLIB
#	define  LIBEXPORT
#else
#	define  LIBIMPORT
#endif
