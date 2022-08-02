/* SPDX-License-Identifier: BSD-3-Clause */

#include <memory>

#include <sawmill/collect.hh>
#include <sawmill/registry.hh>

namespace sawmill {
	thread_local State STATE{std::nullopt, true};

	Registry SAWMILL_REGISTRY{};
	AtomicInit GLOBAL_INIT{InitStatus::Uninitialized};

}
