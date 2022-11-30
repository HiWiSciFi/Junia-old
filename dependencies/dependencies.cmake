macro(register_lib NAME DIR LIBNAME)
	set(${ARGV0}_INCLUDE_DIR "${DEPENDENCY_DIR}/${ARGV1}/include")
	set(${ARGV0}_LIB_DIR "${DEPENDENCY_DIR}/${ARGV1}/lib/$<CONFIG>")
	set(${ARGV0}_LIB "${ARGV2}")
	link_directories("${DEPENDENCY_DIR}/${ARGV1}/lib/$<CONFIG>")
endmacro()

register_lib("GLFW" "glfw" "glfw3")
