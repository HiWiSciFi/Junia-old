# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${DEPENDENCY_DIR}/glfw")
set(GLFW_LIB "glfw")

# Vulkan
find_package(Vulkan QUIET)
if(NOT ${Vulkan_FOUND})
	message(FATAL_ERROR "Vulkan could not be found! Make sure $VULKAN_SDK environment variable is set if the problem persists.")
endif()

# OpenAL
find_package(OpenAL QUIET)
if(NOT ${OPENAL_FOUND})
	message(FATAL_ERROR "OpenAL could not be found! Make sure $OPENALDIR environment variable is set if the problem persists.")
endif()
