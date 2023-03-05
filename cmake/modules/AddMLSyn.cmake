function (add_re2c_source src)
	set (re2c_src)
	get_filename_component(src_abspath ${src} ABSOLUTE)
	string(REGEX REPLACE "^${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" re2c_src_abspath ${src_abspath})
	string (REGEX REPLACE ".re2c.cpp$" ".re2c_gen.cpp" re2c_src_abspath ${re2c_src_abspath})
	add_custom_command(OUTPUT ${re2c_src_abspath}
		COMMAND re2c -o ${re2c_src_abspath} ${src_abspath}
		DEPENDS ${src}
		VERBATIM
		COMMENT "[RE2C] Building ${re2c_src_abspath}"
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
	set (re2c_src ${re2c_src_abspath} PARENT_SCOPE)
endfunction()

function (translate_re2c cmd)
	set (translated_args)
	foreach (arg ${ARGN})
		if (arg MATCHES ".re2c.cpp$")
			set (re2c_arg)
			add_re2c_source(${arg})
			list (APPEND translated_args ${re2c_src})
		else()
			list (APPEND translated_args ${arg})
		endif()
	endforeach()
	cmake_language (CALL ${cmd} ${translated_args})
endfunction()

macro (add_mlsyn_executable)
	translate_re2c(add_executable ${ARGV})
endmacro()

macro (add_mlsyn_library)
	translate_re2c(add_library ${ARGV})
endmacro()
