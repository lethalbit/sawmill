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

		**Warning** While there are 8Ki reserved ExecutionContext
		slots, any more will cause an expensive realloc to 16Ki
		entries.

	*/

	struct Registry final {
	private:
		rwlock<std::vector<ExecutionContext>> _contexts{};
		rwlock<std::vector<std::nullptr_t>> _dispatchers{};


	public:
		Registry() noexcept {
			/* Reserved 8Ki ExecutionContext entries */
			_contexts.write()->reserve(8192);
			/* Reserve 64 dispatchers */
			_dispatchers.write()->reserve(64);
		}

		void register_context(ExecutionContext&& ctx) noexcept {
			_contexts.write()->emplace_back(std::move(ctx));
			// TODO: Update Relevancy
		}

		void register_dispatcher() noexcept {
			_dispatchers.write()->emplace_back(nullptr);
			// TODO: Update Relevancy
		}

		void refresh_relevancy() noexcept {
			auto lock = _dispatchers.write();

			/* this is /totally/ std::erase_if, right? */
			lock->erase(std::remove_if(lock->begin(), lock->end(), [](const auto& n){
				return false;
			}), lock->end());

			// TODO: Update context relevancies
		}
	};

	/*!
		Here we define the SAWMILL_REGISTRY as a weak symbol.
		This allows for proper linking between libraries (dynamic and static)
		and executables and also ensures there is only one global registry
		for Sawmill to interact with.
	*/
	SAWMILL_WEAK_LINKAGE
	extern Registry SAWMILL_REGISTRY;

}


#endif /* SAWMILL_REGISTRY_HH */
