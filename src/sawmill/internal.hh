/* SPDX-License-Identifier: BSD-3-Clause */
#pragma once
#if !defined(SAWMILL_INTERNAL_HH)
#define SAWMILL_INTERNAL_HH

#if defined(_MSC_VER) && !defined(_WINDOWS)
#	define _WINDOWS 1
#endif

#ifdef _WINDOWS
#define SAWMILL_WEAK_LINKAGE __declspec(selectany)
#else
#define SAWMILL_WEAK_LINKAGE [[gnu::weak]]
#endif

namespace sawmill::internal {


}


#endif /* SAWMILL_INTERNAL */
