/* SPDX-License-Identifier: BSD-3-Clause */
#pragma once
#if !defined(SAWMILL_COLLECT_HH)
#define SAWMILL_COLLECT_HH

#include <memory>
#include <optional>

#include <sawmill/internal.hh>
#include <sawmill/metadata.hh>

namespace sawmill {
	/*! Interface for implementing collectors */
	struct Collector {
		virtual Relevancy register_(Metadata& metadata) const noexcept {
			if (enabled(metadata)) {
				return Relevancy::Always;
			} else {
				return Relevancy::Never;
			}
		}

		/*! Returns if an `Event` or `Slice` with the given
			`Metadata` would be collected.
		*/
		virtual bool enabled(Metadata&) const noexcept = 0;

		/*! Returns the highest `Level` that will be collected / enabled
			by this Collector. Or `std::nullopt` if `Level` based filtering
			is not implemented.

		*/
		virtual std::optional<Level> max_level() const noexcept {
			return std::nullopt;
		}
	};

	/*! An empty collector implementation */
	struct NullCollector final : Collector {
		bool enabled(Metadata&) const noexcept override { return false; }
	};

	SAWMILL_WEAK_LINKAGE
	extern std::shared_ptr<Collector> NULL_COLLECTOR;

	SAWMILL_WEAK_LINKAGE
	extern std::shared_ptr<Collector> GLOBAL_COLLECTOR;

}


#endif /* SAWMILL_COLLECT_HH */
