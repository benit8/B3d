##
## B3d, 2019
## CMakeLists.txt
##

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
cmake_policy(SET CMP0076 NEW)

project(B3d VERSION 0.1.0 LANGUAGES CXX C)
add_library(B3d SHARED)
add_subdirectory(extern)

target_compile_features(B3d
PUBLIC
	cxx_std_17
)

target_compile_options(B3d
PUBLIC
	-W -Wall -Wextra
PRIVATE
	-g3
)

target_include_directories(B3d
PUBLIC
	sources
PRIVATE
	sources/B
)

target_sources(B3d
PUBLIC
	sources/B/Color.hpp
	sources/B/Position.hpp
	sources/B/Rect.hpp
	sources/B/SimpleApplication.hpp
	sources/B/Size.hpp

	sources/B/Graphics/Drawable.hpp
	sources/B/Graphics/Event.hpp
	sources/B/Graphics/Keyboard.hpp
	sources/B/Graphics/Line.hpp
	sources/B/Graphics/Mouse.hpp
	sources/B/Graphics/Renderable.hpp
	sources/B/Graphics/Renderer.hpp
	sources/B/Graphics/Surface.hpp
	sources/B/Graphics/Window.hpp
	sources/B/Graphics/X11.hpp

	sources/B/Math/Matrix.hpp
	sources/B/Math/Vector2.hpp
	sources/B/Math/Vector3.hpp

	sources/B/Rendering/Mesh.hpp
	sources/B/Rendering/MeshLoader.hpp
	sources/B/Rendering/Polygon.hpp
	sources/B/Rendering/Transformable.hpp
	sources/B/Rendering/Vertex.hpp

	sources/B/Utils/Logger.hpp
	sources/B/Utils/Timeout.hpp

PRIVATE
	sources/B/Color.cpp
	sources/B/SimpleApplication.cpp

	sources/B/Graphics/Keyboard.cpp
	sources/B/Graphics/Line.cpp
	sources/B/Graphics/Renderer.cpp
	sources/B/Graphics/Window.cpp
	sources/B/Graphics/X11.cpp

	sources/B/Math/Matrix.cpp
	sources/B/Math/Vector2.cpp
	sources/B/Math/Vector3.cpp

	sources/B/Rendering/Mesh.cpp
	sources/B/Rendering/MeshLoader.cpp
	# sources/B/Rendering/Polygon.cpp
	sources/B/Rendering/Transformable.cpp
	sources/B/Rendering/Vertex.cpp

	sources/B/Utils/EventListener.hpp
	sources/B/Utils/Logger.cpp
	sources/B/Utils/Signal.hpp
	sources/B/Utils/Timeout.cpp
)

target_link_libraries(B3d
PUBLIC
	B X11 Xext
)