project ("myglrenderer")

include_directories("src")
add_subdirectory("src")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET myglrenderer PROPERTY CXX_STANDARD 17)
endif()
