# SPDX-License-Identifier: BSD-3-Clause

message('Building tests')

test_srcs = [
]

doctest = dependency('doctest',  required: false, version: '>=2.4.8-1')
if not doctest.found()
	message('Did not find local doctest install, bundling')
	doctest_wrap = subproject('doctest', default_options: [])
	doctest = doctest_wrap.get_variable('doctest_dep')
endif

foreach test : test_srcs
	_ = executable(
		test,
		'@0@.cc'.format(test),
		include_directories: [
			library_inc
		],
		dependencies: [
			doctest
		],
		install: false
	)
	test(test, _)
endforeach
