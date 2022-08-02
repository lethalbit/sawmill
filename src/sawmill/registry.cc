/* SPDX-License-Identifier: BSD-3-Clause */

#include <memory>

#include <sawmill/collect.hh>
#include <sawmill/registry.hh>

namespace sawmill {
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
	thread_local State STATE{std::nullopt, true};

	// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
	Registry SAWMILL_REGISTRY{};
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
	AtomicInit GLOBAL_INIT{InitStatus::Uninitialized};

}
