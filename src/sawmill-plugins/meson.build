# SPDX-License-Identifier: BSD-3-Clause

message('Building compiler plugins')

if get_option('plugin_clang')
	subdir('clang')
endif

if get_option('plugin_gcc')
	if not is_windows
		subdir('gcc')
	else
		warning('Not building GCC plugin on windows')
	endif
endif
