/* SPDX-License-Identifier: BSD-3-Clause */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <iostream>

#include <sawmill/metadata.hh>

TEST_CASE("sawmill::source_location") {
	const auto loc0 = sawmill::source_location::current();

	const auto loc1 = sawmill::source_location::current();

	CHECK_EQ(loc0.line(), 10);
	CHECK_EQ(loc1.line(), 12);
	CHECK_LT(loc0, loc1);
}

TEST_CASE("sawmill::Kind") {
	CHECK_EQ(sawmill::Kind::Event, static_cast<sawmill::Kind>(0b0000'0001));
	CHECK_EQ(sawmill::Kind::Slice, static_cast<sawmill::Kind>(0b0000'0010));

	CHECK(sawmill::is_event(sawmill::Kind::Event));
	CHECK(sawmill::is_slice(sawmill::Kind::Slice));

	CHECK_FALSE(sawmill::is_event(sawmill::Kind::Slice));
	CHECK_FALSE(sawmill::is_slice(sawmill::Kind::Event));
}

TEST_CASE("sawmill::Level") {
	CHECK_GT(sawmill::Level::Apocalyptic,  sawmill::Level::Catastrophic);
	CHECK_GT(sawmill::Level::Catastrophic, sawmill::Level::Critical);
	CHECK_GT(sawmill::Level::Critical,     sawmill::Level::Error);
	CHECK_GT(sawmill::Level::Error,        sawmill::Level::Warning);
	CHECK_GT(sawmill::Level::Warning,      sawmill::Level::Notice);
	CHECK_GT(sawmill::Level::Notice,       sawmill::Level::Info);
	CHECK_GT(sawmill::Level::Info,         sawmill::Level::Debug);
	CHECK_GT(sawmill::Level::Debug,         sawmill::Level::Trace);
}
