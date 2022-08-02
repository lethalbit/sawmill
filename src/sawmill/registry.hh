/* SPDX-License-Identifier: BSD-3-Clause */
#pragma once
#if !defined(SAWMILL_REGISTRY_HH)
#define SAWMILL_REGISTRY_HH

#include <vector>

#include <sawmill/internal.hh>
#include <sawmill/metadata.hh>

namespace sawmill {
	struct ExecutionContext {
	private:
		Relevancy _relevance{Relevancy::Never};
		Metadata  _metadata{};
	public:
		constexpr ExecutionContext() noexcept = default;

		constexpr ExecutionContext(Metadata&& meta) noexcept :
			_metadata{std::move(meta)} { /* NOP */ }

		virtual const Metadata& metadata() const noexcept {
			return _metadata;
		}

		virtual Relevancy relevance() const noexcept {
			return _relevance;
		}

		virtual void relevance(const Relevancy rel) noexcept {
			_relevance = rel;
		}
	};

	/*!
		Here we define the SAWMILL_REGISTRY as a weak symbol.
		This allows for proper linking between libraries (dynamic and static)
		and executables and also ensures there is only one global registry
		for Sawmill to interact with.
	*/
	SAWMILL_WEAK_LINKAGE
	extern std::vector<std::nullptr_t> SAWMILL_REGISTRY;

}


#endif /* SAWMILL_REGISTRY_HH */
