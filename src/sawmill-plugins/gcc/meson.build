# SPDX-License-Identifier: BSD-3-Clause

message('Building compiler plugin: GCC')

gcc_plugin_srcs = files([
	'plugin.cc'
])

gxx = find_program('g++', required: false, native: true)
if gxx.found()
	gcc_plugin_dir = run_command(
		gxx, '-print-file-name=plugin',
	check: true).stdout().strip()

	message('Found GCC plugin directory: @0@'.format(gcc_plugin_dir))

	gcc_plugin_dir_inc = include_directories(gcc_plugin_dir / 'include')

	gcc_plugin = shared_module(
		'sawmill-gcc',
		gcc_plugin_srcs,
		name_prefix: '',

		include_directories: [
			gcc_plugin_dir_inc
		],

		install: true,
		install_dir: get_option('datadir') / 'sawmill' / 'compiler_plugins'
	)

else
	warning('Can\'t find g++, unable to build GCC plugin')
endif
