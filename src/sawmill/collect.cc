/* SPDX-License-Identifier: BSD-3-Clause */

#include <sawmill/collect.hh>

namespace sawmill {
	std::shared_ptr<Collector> NULL_COLLECTOR{
		std::make_unique<NullCollector>()
	};

	std::shared_ptr<Collector> GLOBAL_COLLECTOR{NULL_COLLECTOR};
}
