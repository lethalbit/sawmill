/* SPDX-License-Identifier: BSD-3-Clause */

#include <sawmill/collect.hh>

namespace sawmill {
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
	std::shared_ptr<Collector> NULL_COLLECTOR{
		std::make_unique<NullCollector>()
	};

	// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
	std::shared_ptr<Collector> GLOBAL_COLLECTOR{NULL_COLLECTOR};
}
