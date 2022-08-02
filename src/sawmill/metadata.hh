/* SPDX-License-Identifier: BSD-3-Clause */
#pragma once
#if !defined(SAWMILL_METADATA_HH)
#define SAWMILL_METADATA_HH

#include <cstdint>
#include <string_view>
#include <optional>
#include <type_traits>


namespace sawmill {
	using namespace std::literals::string_view_literals;

	/*! A rough facsimile of the C++20 std::source_location */
	struct source_location final {
	private:
		using loc_t = std::size_t;

		loc_t _line;
		loc_t _column;
		std::string_view _file;
		std::string_view _func;

		constexpr source_location(loc_t ln, loc_t col, std::string_view file, std::string_view func) noexcept :
		 _line{ln}, _column{col}, _file{file}, _func{func} { /* nop */ }

	public:
		constexpr source_location(const source_location&) = default;
		constexpr source_location(source_location&& ) = default;

#if defined(__clang__) and (__clang_major__ >= 9) and !defined(__apple_build_version__)
		/* Non-apple Clang */
		[[nodiscard]]
		inline static constexpr source_location current(
			loc_t ln          = __builtin_LINE(),
			loc_t col         = __builtin_COLUMN(),
			const char* file  = __builtin_FILE(),
			const char* func  = __builtin_FUNCTION()
		) noexcept {
			return { ln, col, file, func };
		}
#elif defined(__clang__) and (__clang_major__ >= 9) and defined(__apple_build_version__)
		inline static constexpr source_location current(
			loc_t ln          = __builtin_LINE(),
			loc_t col         = 0,
			const char* file  = __builtin_FILE(),
			const char* func  = __builtin_FUNCTION()
		) noexcept {
			return { ln, col, file, func };
		}
#elif defined(__GNUC__) and (__GNUC__ > 4)
		/* GCC */
		[[nodiscard]]
		inline static constexpr source_location current(
			loc_t ln          = __builtin_LINE(),
			loc_t col         = 0,
			const char* file  = __builtin_FILE(),
			const char* func  = __builtin_FUNCTION()
		) noexcept {
			return { ln, col, file, func };
		}
#else /* MSVC, et. al. */
		[[nodiscard]]
		inline static constexpr source_location current(
			loc_t ln          = 0,
			loc_t col         = 0,
			const char* file  = "unknown",
			const char* func  = "unknown"
		) noexcept {
			return { ln, col, file, func };
		}
#endif
		[[nodiscard]]
		constexpr loc_t line() const noexcept { return _line; }
		[[nodiscard]]
		constexpr loc_t column() const noexcept { return _column; }

		[[nodiscard]]
		constexpr std::string_view file_name() const noexcept { return _file; }
		[[nodiscard]]
		constexpr std::string_view function_name() const noexcept { return _func; }

		[[nodiscard]]
		inline constexpr bool operator==(const source_location& rh) const noexcept {
			return  (_column == rh._column) &&
					(_line == rh._line)     &&
					(_file == rh._file)     &&
					(_func == rh._func);
		}

		[[nodiscard]]
		inline constexpr bool operator!=(const source_location& rh) const noexcept {
			return !operator==(rh);
		}

		[[nodiscard]]
		inline constexpr bool operator>(const source_location& rh) const noexcept {
			return (_file == rh._file) && (_func == rh._func) && (
				(_column > rh._column) || (_line > rh._line)
			);
		}

		[[nodiscard]]
		inline constexpr bool operator>=(const source_location& rh) const noexcept {
			return (_file == rh._file) && (_func == rh._func) && (
				(_column >= rh._column) || (_line >= rh._line)
			);
		}

		[[nodiscard]]
		inline constexpr bool operator<(const source_location& rh) const noexcept {
			return (_file == rh._file) && (_func == rh._func) && (
				 (_column < rh._column) || (_line < rh._line)
			);
		}

		[[nodiscard]]
		inline constexpr bool operator<=(const source_location& rh) const noexcept {
			return (_file == rh._file) && (_func == rh._func) && (
				(_column <= rh._column) || (_line <= rh._line)
			);
		}
	};

	/*! The 'Kind' of trigger that was emitted */
	enum struct Kind : std::uint8_t {
		/*! This was an `event(...)` call */
		Event  = 0b0000'0001,
		/*! This was a `slice` enter of exit */
		Slice  = 0b0000'0010,
	};

	[[nodiscard]]
	constexpr inline bool is_event(const Kind k) noexcept {
		using U = std::underlying_type_t<Kind>;
		return (static_cast<U>(k) & static_cast<U>(Kind::Event)) == static_cast<U>(Kind::Event);

	}

	[[nodiscard]]
	constexpr inline bool is_slice(const Kind k) noexcept {
		using U = std::underlying_type_t<Kind>;
		return (static_cast<U>(k) & static_cast<U>(Kind::Slice)) == static_cast<U>(Kind::Slice);

	}

	/*! Event/Span level */
	enum struct Level : std::uint8_t {
		/*! Trace, lowest priority and very verbose  */
		Trace        = 0x00U,
		/*! Debug, lower priority */
		Debug        = 0x01U,
		/*! Informational, Useful but also fairly verbose*/
		Info         = 0x02U,
		/*! Notice, Something to pay attention to */
		Notice       = 0x03U,
		/*! Warnings, Important information */
		Warning      = 0x04U,
		/*! Recoverable Error, Fairly important */
		Error        = 0x05U,
		/*! Non-recoverable Error, Very important */
		Critical     = 0x06U,
		/*! Non-recoverable error, may be in an unsafe/unknown state */
		Catastrophic = 0x07U,
		/*! Non-recoverable error, potential corruption of data and system state */
		Apocalyptic  = 0x08U,
	};


	[[nodiscard]]
	constexpr inline bool operator>(const Level lh, const Level rh) noexcept {
		using U = std::underlying_type_t<Level>;
		return static_cast<U>(lh) > static_cast<U>(rh);
	}

	[[nodiscard]]
	constexpr inline bool operator>=(const Level lh, const Level rh) noexcept {
		using U = std::underlying_type_t<Level>;
		return static_cast<U>(lh) >= static_cast<U>(rh);
	}

	[[nodiscard]]
	constexpr inline bool operator<(const Level lh, const Level rh) noexcept {
		using U = std::underlying_type_t<Level>;
		return static_cast<U>(lh) < static_cast<U>(rh);
	}

	[[nodiscard]]
	constexpr inline bool operator<=(const Level lh, const Level rh) noexcept {
		using U = std::underlying_type_t<Level>;
		return static_cast<U>(lh) <= static_cast<U>(rh);
	}


	/*! The relevancy of a a given <THING> */
	enum struct Relevancy : std::uint8_t {
		/*! It is never relevant to the Collector */
		Never        = 0x00U,
		/*! Sometimes it is relevant */
		Occasionally = 0x01U,
		/*! It is always relevant */
		Always       = 0x02U,
	};

	/*! Metadata describing an `event` or `slice`



	*/
	struct Metadata {
		std::string_view _name;
		std::string_view _target;
		Level _level;
		std::optional<source_location> _loc;
	};

}


#endif /* SAWMILL_METADATA_HH */
