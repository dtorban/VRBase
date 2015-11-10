# Create a library from the source files in this directory.

project (vrbase)

#This is how you specific source file individually
set (SOURCEFILES 
		source/event/mouse/MouseListener.cpp
		source/event/mouse/MouseTranslator.cpp
		source/event/mouse/MouseTrackball.cpp
		source/event/mouse/MouseScale.cpp
		source/scene/CompositeScene.cpp
		source/Box.cpp
		source/Mesh.cpp
		source/Shader.cpp
		source/Texture.cpp)
set (HEADERFILES 
		include/vrbase/Scene.h
		include/vrbase/event/mouse/MouseListener.h
		include/vrbase/event/mouse/MouseTranslator.h
		include/vrbase/event/mouse/MouseTrackball.h
		include/vrbase/event/mouse/MouseScale.h
		include/vrbase/scene/CompositeScene.h
		include/vrbase/Box.h
		include/vrbase/EventListener.h
		include/vrbase/Shader.h
		include/vrbase/Mesh.h
		include/vrbase/Texture.h)
source_group("Header Files" FILES ${HEADERFILES})

include_directories (
  .
  include
)

add_library (${PROJECT_NAME} ${SOURCEFILES} ${HEADERFILES})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION "VRBase/include")

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION VRBase/lib
         ARCHIVE DESTINATION VRBase/lib
         RUNTIME DESTINATION VRBase/bin)