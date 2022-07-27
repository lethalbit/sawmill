# SPDX-License-Identifier: BSD-3-Clause

message('Building compiler plugins')

plugin_common = files([

])

llvm_dep = dependency(
	'llvm',
	required: false,
	version: '>= 14.0',
)

gxx = find_program(
	'g++',
	required: false,
	native: true
)


if get_option('plugin_clang') and llvm_dep.found()
	message('Building compiler plugin: Clang')

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
			plugin_common + files(['clang.cc']),
			name_prefix: '',

			dependencies: [
				clang_plugin_dep
			],

			install: true,
			install_dir: get_option('datadir') / 'sawmill' / 'compiler_plugins'
		)
	endif
elif not llvm_dep.found()
	warning('Can\'t find LLVM install, unable to build clang plugin')
endif

if get_option('plugin_gcc') and gxx.found()
	if not is_windows
		gcc_plugin_dir = run_command(
			gxx, '-print-file-name=plugin',
		check: true).stdout().strip()

		message('Found GCC plugin directory: @0@'.format(gcc_plugin_dir))

		gcc_plugin_inc = include_directories(gcc_plugin_dir / 'include')

		if not cxx.check_header(
			'gcc-plugin.h',
			include_directories: gcc_plugin_inc
		)
			warning('Can\'t find gcc headers, unable to build gcc plugin')
		else
			gcc_plugin = shared_module(
				'sawmill-gcc',
				plugin_common + files(['gcc.cc']),
				name_prefix: '',

				include_directories: [
					gcc_plugin_inc
				],

				install: true,
				install_dir: get_option('datadir') / 'sawmill' / 'compiler_plugins'
			)
		endif
	else
		warning('Not building GCC plugin on windows')
	endif
elif not gxx.found()
	warning('Can\'t find g++, unable to build GCC plugin')
endif
