/* SPDX-License-Identifier: BSD-3-Clause */
/* gcc/plugin.cc - Sawmill instrumentation plugin for gcc */

#include <array>
#include <cstdint>
#include <iostream>

#include <config.h>
#include <gcc-plugin.h>

/* GCC requires this godforsaken symbol */
[[maybe_unused]]
std::int32_t plugin_is_GPL_compatible{};

/* Handle the attribute */
static tree instrument_attr(tree* node, tree name, tree args, int flags, bool* no_add_attrs) {

	return nullptr;
}
/* Attributes to register. Name, Min args, Max args, decl, type, func, type ident, handler */
const auto attras = std::array<struct attribute_spec, 2>{{
	{ "instrument",  0,   -1,  true, false, false,    false,   instrument_attr },
	{}
}};



std::int32_t plugin_init(plugin_name_args* info, plugin_gcc_version* version) {
	register_callback(info->base_name, PLUGIN_ATTRIBUTES, [](void*, void*){
		register_scoped_attributes(attras.data(), "sawmill", true);
	}, nullptr);
	return {};
}
