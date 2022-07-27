# SPDX-License-Identifier: BSD-3-Clause

message('Building compiler plugin: Clang')

clang_plugin_srcs = files([
	'plugin.cc'
])


llvm_dep = dependency(
	'llvm',
	required: false,
	version: '>= 14.0',
)

if llvm_dep.found()
	clang_plugin_inc =  include_directories(llvm_dep.get_variable(
		configtool: 'includedir'
	))

	clang_plugin_lib = llvm_dep.get_variable(
		configtool: 'libdir'
	).split(' ')

	message('Found clang include directory: @0@'.format(clang_plugin_inc))

	if not cxx.check_header(
		'clang/Frontend/FrontendPluginRegistry.h',
		include_directories: clang_plugin_inc
	)
		warning('Can\'t find clang headers, unable to build clang plugin')
	else
		clang_plugin_dep = declare_dependency(
			include_directories: [
				clang_plugin_inc,
			],
			dependencies: cxx.find_library(
				'libclang',
				dirs: clang_plugin_lib
			)
		)

		clang_plugin = shared_module(
			'sawmill-clang',
			clang_plugin_srcs,
			name_prefix: '',

			include_directories: [

			],

			dependencies: [
				clang_plugin_dep
			],

			install: true,
			install_dir: get_option('datadir') / 'sawmill' / 'compiler_plugins'
		)
	endif
else
	warning('Can\'t find LLVM install, unable to build clang plugin')
endif
