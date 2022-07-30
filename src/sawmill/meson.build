# SPDX-License-Identifier: BSD-3-Clause

sawmill_deps = [

]

sawmill_hdrs = files([
])

sawmill_srcs = files([

])

sawmill = static_library(
	'sawmill',
	sawmill_srcs,

	include_directories: [
		library_inc,
	],
	dependencies: [
		sawmill_deps,
	],

	name_prefix: '',
	pic: true,
	gnu_symbol_visibility: 'inlineshidden',
	implicit_include_directories: false,

	cpp_args: [
		'-DSAWMILL_BUILD_INTERNAL'
	],
	install: (not meson.is_subproject())
)

sawmill_dep = declare_dependency(
	include_directories: [
		library_inc,
	],
	dependencies: [
		sawmill_deps,
	],
	link_with: sawmill,
	version: meson.project_version(),
)

if not meson.is_subproject()
	install_headers(
		sawmill_hdrs + [ config_header ],
		subdir: 'sawmill'
	)

	pkgconfig = import('pkgconfig')
	pkgconfig.generate(
		subdirs: '.',
		name: 'sawmill',
		filebase: 'sawmill',
		libraries: [ sawmill ],
		version: meson.project_version(),
		description: 'A structured logging and diagnostics library for C++'
	)
endif
