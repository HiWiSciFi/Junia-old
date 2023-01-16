#macro(register_lib NAME DIR LIBNAME)
#	set(${ARGV0}_INCLUDE_DIR "${DEPENDENCY_DIR}/${ARGV1}/include")
#	set(${ARGV0}_LIB_DIR "${DEPENDENCY_DIR}/${ARGV1}/lib/$<CONFIG>")
#	set(${ARGV0}_LIB "${ARGV2}")
#	link_directories("${DEPENDENCY_DIR}/${ARGV1}/lib/$<CONFIG>")
#endmacro()

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${DEPENDENCY_DIR}/glfw")
set(GLFW_LIB "glfw")

# GLAD
add_subdirectory("${DEPENDENCY_DIR}/glad")
set(GLAD_LIB "glad")

# Vulkan
find_package(Vulkan REQUIRED)
if(NOT ${Vulkan_FOUND})
	message(FATAL_ERROR "Vulkan could not be found! Make sure $VULKAN_SDK environment variable is set if the problem persists.")
endif()

# OpenAL
find_package(OpenAL REQUIRED)
if(NOT ${OPENAL_FOUND})
	message(FATAL_ERROR "OpenAL could not be found! Make sure $OPENALDIR environment variable is set if the problem persists.")
endif()
