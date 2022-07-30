# SPDX-License-Identifier: BSD-3-Clause

message('Building sawmill collector: file')

sawmill_file_srcs = files([

])


sawmill_file = library(
	'sawmill-file',
	sawmill_file_srcs,
	include_directories: [
		library_inc,
		include_directories('.')
	],

	dependencies: [
		sawmill_deps,
	],

	gnu_symbol_visibility: 'inlineshidden',
	implicit_include_directories: false,
	install: (not meson.is_subproject())
)
