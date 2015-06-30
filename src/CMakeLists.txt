set(CMAKE_PREFIX_PATH /usr/local/opt/qt5/lib/cmake )
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(OpenGL)

QT5_ADD_RESOURCES(RESOURCES meshview.qrc)
include_directories (/usr/local/include/eigen3)

add_executable(meshview Camera.cpp
Camera.hpp
ChangeColorWidget.cpp
ChangeColorWidget.hpp
Color3f.hpp
ExporterCamera.cpp
ExporterCamera.hpp
ExporterMesh.cpp
ExporterMesh.hpp
GLWidget.cpp
GLWidget.hpp
ImporterCamera.cpp
ImporterCamera.hpp
ImporterMesh.cpp
ImporterMesh.hpp
Light.cpp
Light.hpp
MainWindow.cpp
MainWindow.hpp
Mesh.cpp
Mesh.hpp
Model.cpp
Model.hpp
MouseEvent.cpp
MouseEvent.hpp
MouseListener.cpp
MouseListener.hpp
Preference.cpp
Preference.hpp
View.cpp
View.hpp
VirtualTrackball.cpp
VirtualTrackball.hpp
main.cpp
${RESOURCES}
)

target_link_libraries(meshview ${OPENGL_LIBRARY} )
QT5_USE_MODULES(meshview Widgets OpenGL)
