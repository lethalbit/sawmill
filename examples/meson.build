# SPDX-License-Identifier: BSD-3-Clause
message('Building examples')

example_srcs = [

]

foreach ex : example_srcs
	executable(
		ex,
		'@0@.cc'.format(ex),
		dependencies: [
			sawmill_dep
		],
		install: false
	)
	if get_option('install_examples')
		install_data(
			'@0@.cc'.format(ex),
			install_mode: 'rw-r--r--',
			install_dir : get_option('datadir') / 'sawmill' / 'examples'
		)
	endif
endforeach
