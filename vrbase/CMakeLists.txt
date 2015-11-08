# Create a library from the source files in this directory.

project (vrbase)

#This is how you specific source file individually
set (SOURCEFILES 
		source/scene/CompositeScene.cpp
		source/Box.cpp
		source/Mesh.cpp
		source/Shader.cpp
		source/Texture.cpp)
set (HEADERFILES 
		include/vrbase/Scene.h
		include/vrbase/scene/CompositeScene.h
		include/vrbase/Box.h
		include/vrbase/Shader.h
		include/vrbase/Mesh.h
		include/vrbase/Texture.h)
source_group("Header Files" FILES ${HEADERFILES})

include_directories (
  .
  include
)

add_library (${PROJECT_NAME} source/main.cpp)
# ${SOURCEFILES} ${HEADERFILES})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION "include")

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
         RUNTIME DESTINATION bin)