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

#include <utility>
#include <mutex>
#include <shared_mutex>

namespace sawmill::internal {

	/*! Simple Read-Write lock based on std::shared_mutex */
	template<typename T>
	struct rwlock final {
	private:
		template<typename U, template<typename> typename lock_t>
		struct lock_result final {
		private:
			lock_t<std::shared_mutex> _lock;
			U& _obj;
		public:
			constexpr lock_result(std::shared_mutex& mut, U& obj) noexcept :
				_lock{mut}, _obj{obj} { /* nop */ }

			[[nodiscard]]
			U* operator->() noexcept { return &_obj; }
			[[nodiscard]]
			U& operator*() noexcept { return _obj; }

		};
		std::shared_mutex _mutex{};
		T _obj;

	public:
		/*! Forwarding constructor for T */
		template<typename ...args_t>
		constexpr rwlock(args_t&&... args) noexcept :
			_obj{std::forward<args_t>(args)...} { /* nop */ }

		/*! Return a const ref version of the object
			to ensure that you can not change the result.
		*/
		[[nodiscard]]
		lock_result<const T, std::shared_lock> read() noexcept {
			return {_mutex, _obj};
		}
		[[nodiscard]]
		lock_result<T, std::unique_lock> write() noexcept {
			return {_mutex, _obj};
		}
	};
}


#endif /* SAWMILL_INTERNAL */
