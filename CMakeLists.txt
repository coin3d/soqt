cmake_minimum_required(VERSION 2.8.11)

project(SoQt)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(CheckCXXSourceCompiles)
include(CheckFunctionExists)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckStructHasMember)
include(CheckSymbolExists)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

option(COIN_IV_EXTENSIONS "Enable extra open inventor extensions" ON)
option(SOQT_BUILD_SHARED_LIBS "Build shared libraries" ON)
option(USE_QT5 "Prefer Qt5 over Qt4 if available" ON)
option(WITH_STATIC_DEFAULTS "Enable defaults from being statically linked in" ON)

find_package(OpenGL REQUIRED)

if(USE_QT5)
	find_package(Qt5 COMPONENTS Core Gui OpenGL Widgets QUIET)
endif()

if(Qt5_FOUND)
	set(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${Qt5Widgets_LIBRARIES})
	string(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" QT_VERSION_MAJOR "${Qt5Core_VERSION_STRING}")
	string(REGEX REPLACE "^[0-9]+\\.([0-9])+\\.[0-9]+.*" "\\1" QT_VERSION_MINOR "${Qt5Core_VERSION_STRING}")
	string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" QT_VERSION_PATCH "${Qt5Core_VERSION_STRING}")
else()
	set(QT_USE_IMPORTED_TARGETS ON)
	find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
	include(${QT_USE_FILE})
endif()

find_package(Coin REQUIRED CONFIG)
find_package(X11)

set(SOQT_MAJOR_VERSION "1")
set(SOQT_MINOR_VERSION "6")
set(SOQT_MICRO_VERSION "0")
set(SOQT_BETA_VERSION "a")
set(SOQT_VERSION "${SOQT_MAJOR_VERSION}.${SOQT_MINOR_VERSION}.${SOQT_MICRO_VERSION}${SOQT_BETA_VERSION}")
set(VERSION "${SOQT_VERSION}")

set(CMAKE_REQUIRED_INCLUDES ${OPENGL_INCLUDE_DIR})
set(CMAKE_REQUIRED_LIBRARIES Coin::Coin ${OPENGL_LIBRARIES})

check_include_files(windows.h HAVE_WINDOWS_H)
check_include_files(sys/types.h HAVE_SYS_TYPES_H)

set(GUI_TOOLKIT_VERSION ${QT_VERSION_MAJOR}${QT_VERSION_MINOR}${QT_VERSION_PATCH})
check_symbol_exists(__func__ "" FUNC)
check_symbol_exists(__PRETTY_FUNCTION__ "" PRETTY_FUNCTION)
check_symbol_exists(__FUNCTION__ "" FUNCTION)
if(FUNC)
	set(HAVE_C_COMPILER_FUNCTION_NAME_VAR __func__)
	set(HAVE_CPP_COMPILER_FUNCTION_NAME_VAR __func__)
elseif(PRETTY_FUNCTION)
	set(HAVE_C_COMPILER_FUNCTION_NAME_VAR __PRETTY_FUNCTION__)
	set(HAVE_CPP_COMPILER_FUNCTION_NAME_VAR __PRETTY_FUNCTION__)
elseif(FUNCTION)
	set(HAVE_C_COMPILER_FUNCTION_NAME_VAR __FUNCTION__)
	set(HAVE_CPP_COMPILER_FUNCTION_NAME_VAR __FUNCTION__)
endif()
check_include_files(dlfcn.h HAVE_DLFCN_H)
check_symbol_exists(GetEnvironmentVariable windows.h HAVE_GETENVIRONMENTVARIABLE)
check_library_exists(GL glXChooseVisual "" HAVE_GLX)
if(HAVE_WINDOWS_H)
	check_include_files("windows.h;GL/glu.h" HAVE_GL_GLU_H)
	check_include_files("windows.h;GL/gl.h" HAVE_GL_GL_H)
else()
	check_include_files(GL/glu.h HAVE_GL_GLU_H)
	check_include_files(GL/gl.h HAVE_GL_GL_H)
endif()
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(memory.h HAVE_MEMORY_H)
check_include_files(netinet/in.h HAVE_NETINET_IN_H)
check_include_files(OpenGL/glu.h HAVE_OPENGL_GLU_H)
check_include_files(OpenGL/gl.h HAVE_OPENGL_GL_H)
if(HAVE_SYS_TYPES_H)
	check_cxx_source_compiles("
		#include <sys/types.h>
		#include <pthread.h>
		int main() { struct timespec timeout; timeout.tv_nsec = 0; return 0; }
	" HAVE_PTHREAD_TIMESPEC_NSEC)
else()
	check_cxx_source_compiles("
		#include <pthread.h>
		int main() { struct timespec timeout; timeout.tv_nsec = 0; return 0; }
	" HAVE_PTHREAD_TIMESPEC_NSEC)
endif()
check_cxx_source_compiles("
	#include <Inventor/SbImage.h>
	int main() { SbImage::addReadImageCB(NULL, NULL); return 0; }
" HAVE_SBIMAGE_ADDREADIMAGECB)
check_cxx_source_compiles("
	#include <Inventor/nodes/SoPerspectiveCamera.h>
	int main() { SoPerspectiveCamera * c = new SoPerspectiveCamera; c->setStereoMode(SoCamera::MONOSCOPIC); return 0; }
" HAVE_SOCAMERA_SETSTEREOMODE)
check_cxx_source_compiles("
	#include <Inventor/misc/SoContextHandler.h>
	int main() { SoContextHandler::destructingContext(0); return 0; }
" HAVE_SOCONTEXTHANDLER)
check_cxx_source_compiles("
	#include <Inventor/events/SoKeyboardEvent.h>
	int main() { SoKeyboardEvent::Key key = SoKeyboardEvent::DELETE; return 0; }
" HAVE_SOKEYBOARDEVENT_DELETE)
check_cxx_source_compiles("
	#include <Inventor/events/SoMouseButtonEvent.h>
	int main() { SoMouseButtonEvent::Button button = SoMouseButtonEvent::BUTTON5; return 0; }
" HAVE_SOMOUSEBUTTONEVENT_BUTTON5)
check_cxx_source_compiles("
	#include <Inventor/nodes/SoPolygonOffset.h>
	int main() { SoPolygonOffset * p = new SoPolygonOffset; return 0; }
" HAVE_SOPOLYGONOFFSET)
check_cxx_source_compiles("
	#include <Inventor/actions/SoGLRenderAction.h>
	int main() { int num = (int) SoGLRenderAction::SORTED_LAYERS_BLEND; return 0; }
" HAVE_SORTED_LAYERS_BLEND)
check_cxx_source_compiles("
	#include <Inventor/VRMLnodes/SoVRMLBackground.h>
	int main() { SoVRMLBackground * p = new SoVRMLBackground; return 0; }
" HAVE_SOVRMLBACKGROUND)
check_cxx_source_compiles("
	#include <Inventor/VRMLnodes/SoVRMLFog.h>
	int main() { SoVRMLFog * p = new SoVRMLFog; return 0; }
" HAVE_SOVRMLFOG)
check_cxx_source_compiles("
	#include <Inventor/VRMLnodes/SoVRMLMaterial.h>
	int main() { SoVRMLMaterial * p = new SoVRMLMaterial; return 0; }
" HAVE_SOVRMLMATERIAL)
check_cxx_source_compiles("
	#include <Inventor/VRMLnodes/SoVRMLViewpoint.h>
	int main() { SoVRMLViewpoint * p = new SoVRMLViewpoint; return 0; }
" HAVE_SOVRMLVIEWPOINT)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(sys/stat.h HAVE_SYS_STAT_H)
check_include_files(sys/time.h HAVE_SYS_TIME_H)
check_include_files(tlhelp32.h HAVE_TLHELP32_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_cxx_source_compiles("
	#include <windows.h>
	int main() {
		CreateDirectory(NULL, NULL);
		RemoveDirectory(NULL);
		SetLastError(0);
		GetLastError();
		LocalAlloc(0, 1);
		LocalFree(NULL);
		return 0;
	}
" HAVE_WIN32_API)
check_symbol_exists(LoadLibrary windows.h HAVE_WIN32_LOADLIBRARY)
check_include_files(X11/Xlib.h HAVE_X11_AVAILABLE)
check_include_files(X11/extensions/SGIMisc.h HAVE_X11_EXTENSIONS_SGIMISC_H)
check_include_files(X11/extensions/XInput.h HAVE_X11_EXTENSIONS_XINPUT_H)
check_include_files(X11/Xproto.h HAVE_X11_XPROTO_H)
set(PACKAGE "SoQt")
set(PACKAGE_BUGREPORT "coin-support@coin3d.org")
set(PACKAGE_NAME "SoQt")
set(PACKAGE_STRING "SoQt ${SOQT_VERSION}")
set(PACKAGE_TARNAME "soqt")
set(PACKAGE_URL "https://bitbucket.org/Coin3D/soqt")
set(PACKAGE_VERSION "${SOQT_VERSION}")
check_include_files("assert.h;ctype.h;errno.h;float.h;limits.h;locale.h;math.h;setjmp.h;signal.h;stdarg.h;stddef.h;stdio.h;stdlib.h;string.h;time.h" STDC_HEADERS)
set(USE_EXCEPTIONS ON)
set(X_DISPLAY_MISSING ON)

set(HAVE_JOYSTICK_LINUX OFF)

configure_file(src/config.h.cmake.in src/config.h)

set(COMPONENTHEADER Q_OBJECT)
set(EVENT "QEvent *")
set(gui qt)
set(Gui Qt)
set(GUI QT)
set(WIDGET "QWidget *")

add_subdirectory(src/Inventor/Qt/common)

file(GLOB_RECURSE COMMON_HDRS ${CMAKE_CURRENT_BINARY_DIR}/src/*.h)
file(GLOB_RECURSE COMMON_SRCS ${CMAKE_CURRENT_BINARY_DIR}/src/*.cpp)

set(
	HDRS
	src/Inventor/Qt/SoQtComponentP.h
	src/Inventor/Qt/SoQtGLWidgetP.h
	src/Inventor/Qt/SoQtImageReader.h
	src/Inventor/Qt/SoQtInternal.h
	src/Inventor/Qt/SoQtP.h
	src/Inventor/Qt/SoQtSignalThread.h
	src/Inventor/Qt/devices/6DOFEvents.h
	src/Inventor/Qt/devices/SoQtDeviceP.h
	src/Inventor/Qt/viewers/SoQtFullViewerP.h
	src/Inventor/Qt/viewers/SoQtExaminerViewerP.h
	src/Inventor/Qt/viewers/SoQtPlaneViewerP.h
	src/Inventor/Qt/widgets/QtNativePopupMenu.h
	src/Inventor/Qt/widgets/SoQtGLArea.h
	src/Inventor/Qt/widgets/SoQtThumbWheel.h
)

set(
	SRCS
	src/Inventor/Qt/SoQt.cpp
	src/Inventor/Qt/SoQtComponent.cpp
	src/Inventor/Qt/SoQtGLWidget.cpp
	src/Inventor/Qt/SoQtImageReader.cpp
	src/Inventor/Qt/SoQtSignalThread.cpp
	src/Inventor/Qt/devices/6DOFEvents.cpp
	src/Inventor/Qt/devices/SoQtDevice.cpp
	src/Inventor/Qt/devices/SoQtInputFocus.cpp
	src/Inventor/Qt/devices/SoQtKeyboard.cpp
	src/Inventor/Qt/devices/SoQtMouse.cpp
	src/Inventor/Qt/viewers/ExaminerViewer.cpp
	src/Inventor/Qt/viewers/FullViewer.cpp
	src/Inventor/Qt/viewers/PlaneViewer.cpp
	src/Inventor/Qt/widgets/QtNativePopupMenu.cpp
	src/Inventor/Qt/widgets/SoQtGLArea.cpp
	src/Inventor/Qt/widgets/SoQtThumbWheel.cpp
)

macro(qt_generate_moc infile outfile)
	if(Qt5_FOUND)
		qt5_generate_moc(${infile} ${outfile})
	elseif(Qt4_FOUND)
		qt4_generate_moc(${infile} ${outfile})
	endif()
	
	if(NOT IS_ABSOLUTE ${outfile})
		list(APPEND MOC_SRCS ${CMAKE_CURRENT_BINARY_DIR}/${outfile})
	else()
		list(APPEND MOC_SRCS ${outfile})
	endif()
endmacro()

qt_generate_moc(src/Inventor/Qt/SoQtComponentP.h src/Inventor/Qt/moc_SoQtComponentP.icc)
qt_generate_moc(src/Inventor/Qt/SoQtGLWidgetP.h src/Inventor/Qt/moc_SoQtGLWidgetP.icc)
qt_generate_moc(src/Inventor/Qt/SoQtMaterialList.cpp src/Inventor/Qt/moc_SoQtMaterialList.icc)
qt_generate_moc(src/Inventor/Qt/SoQtMaterialSliderSet.h src/Inventor/Qt/moc_SoQtMaterialSliderSet.icc)
qt_generate_moc(src/Inventor/Qt/SoQtP.h src/Inventor/Qt/moc_SoQtP.icc)
qt_generate_moc(src/Inventor/Qt/SoQtSignalThread.h src/Inventor/Qt/moc_SoQtSignalThread.icc)
qt_generate_moc(src/Inventor/Qt/SoQtSliderSetBase.h src/Inventor/Qt/moc_SoQtSliderSetBase.icc)
qt_generate_moc(src/Inventor/Qt/SoQtTransformSliderSet.h src/Inventor/Qt/moc_SoQtTransformSliderSet.icc)
qt_generate_moc(src/Inventor/Qt/viewers/SoQtExaminerViewerP.h src/Inventor/Qt/viewers/moc_SoQtExaminerViewerP.icc)
qt_generate_moc(src/Inventor/Qt/viewers/SoQtFullViewerP.h src/Inventor/Qt/viewers/moc_SoQtFullViewerP.icc)
qt_generate_moc(src/Inventor/Qt/viewers/SoQtPlaneViewerP.h src/Inventor/Qt/viewers/moc_SoQtPlaneViewerP.icc)
qt_generate_moc(src/Inventor/Qt/widgets/QtNativePopupMenu.h src/Inventor/Qt/widgets/moc_QtNativePopupMenu.icc)
qt_generate_moc(src/Inventor/Qt/widgets/SoQtGLArea.h src/Inventor/Qt/widgets/moc_SoQtGLArea.icc)
qt_generate_moc(src/Inventor/Qt/widgets/SoQtThumbWheel.h src/Inventor/Qt/widgets/moc_SoQtThumbWheel.icc)

if(HAVE_JOYSTICK_LINUX)
	list(APPEND HDRS src/Inventor/Qt/devices/SoQtLinuxJoystick.h)
	list(APPEND SRCS src/Inventor/Qt/devices/SoQtLinuxJoystick.cpp)
	qt_generate_moc(src/Inventor/Qt/devices/SoQtLinuxJoystick.h src/Inventor/Qt/devices/moc_SoQtLinuxJoystick.icc)
endif()

if(SOQT_BUILD_SHARED_LIBS)
	add_library(SoQt SHARED ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS} ${MOC_SRCS})
	target_compile_definitions(SoQt PRIVATE -DSOQT_MAKE_DLL INTERFACE -DSOQT_DLL)
else()
	add_library(SoQt STATIC ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS} ${MOC_SRCS})
	target_compile_definitions(SoQt INTERFACE -DSOQT_NOT_DLL)
endif()

set_target_properties(SoQt PROPERTIES DEBUG_POSTFIX d VERSION ${VERSION})

target_compile_definitions(SoQt PRIVATE -DHAVE_CONFIG_H -DSOQT_INTERNAL)

if(CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
	target_compile_definitions(SoQt PRIVATE -DSOQT_DEBUG=1)
else()
	target_compile_definitions(SoQt PRIVATE -DSOQT_DEBUG=0)
endif()

target_include_directories(
	SoQt
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(SoQt PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(SoQt Coin::Coin ${OPENGL_LIBRARIES} ${QT_LIBRARIES})

if(X11_FOUND)
	target_include_directories(SoQt PUBLIC ${X11_INCLUDE_DIR})
	target_link_libraries(SoQt ${X11_LIBRARIES})
endif()
if(X11_Xi_FOUND)
	target_include_directories(SoQt PUBLIC ${X11_Xi_INCLUDE_DIR})
	target_link_libraries(SoQt ${X11_Xi_LIB})
endif()

set(
	INST_HDRS
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/SoQt.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/SoQtBasic.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/SoQtColorEditor.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/SoQtComponent.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/SoQtCursor.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/SoQtObject.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/SoQtGLWidget.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/SoQtRenderArea.h
)

set(
	INST_DEVICES_HDRS
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/devices/SoQtDevice.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/devices/SoQtKeyboard.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/devices/SoQtMouse.h
)

if(HAVE_JOYSTICK_LINUX)
	list(APPEND INST_DEVICES_HDRS ${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/devices/SoQtLinuxJoystick.h)
endif()

set(
	INST_EDITORS_HDRS
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/editors/SoQtColorEditor.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/editors/SoQtMaterialEditor.h
)

set(
	INST_NODES_HDRS
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/nodes/SoGuiColorEditor.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/nodes/SoGuiMaterialEditor.h
)

set(
	INST_VIEWERS_HDRS
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/viewers/SoQtConstrainedViewer.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/viewers/SoQtExaminerViewer.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/viewers/SoQtFlyViewer.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/viewers/SoQtFullViewer.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/viewers/SoQtPlaneViewer.h
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/viewers/SoQtViewer.h
)

set(
	INST_WIDGETS_HDRS
	${CMAKE_CURRENT_BINARY_DIR}/src/Inventor/Qt/widgets/SoQtPopupMenu.h
	src/Inventor/Qt/widgets/SoQtThumbWheel.h
)

install(FILES ${INST_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/Qt COMPONENT develoment)
install(FILES ${INST_DEVICES_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/Qt/devices COMPONENT develoment)
install(FILES ${INST_EDITORS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/Qt/editors COMPONENT develoment)
install(FILES ${INST_NODES_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/Qt/nodes COMPONENT develoment)
install(FILES ${INST_VIEWERS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/Qt/viewers COMPONENT develoment)
install(FILES ${INST_WIDGETS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/Qt/widgets COMPONENT develoment)

install(
	TARGETS	SoQt
	EXPORT SoQt
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtime NAMELINK_SKIP
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime
)

if(SOQT_BUILD_SHARED_LIBS)
	install(
		TARGETS	SoQt
		EXPORT SoQt
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development NAMELINK_ONLY
	)
endif()

if(MSVC AND SOQT_BUILD_SHARED_LIBS AND ${CMAKE_MAJOR_VERSION} GREATER 2 AND ${CMAKE_MINOR_VERSION} GREATER 0)
	install(FILES $<TARGET_PDB_FILE:SoQt> DESTINATION ${CMAKE_INSTALL_BINDIR} CONFIGURATIONS Debug RelWithDebInfo COMPONENT debug)
endif()

configure_package_config_file(
  soqt-config.cmake.in soqt-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SoQt-${SOQT_VERSION}
)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/soqt-config.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SoQt-${SOQT_VERSION}
	COMPONENT develoment
)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/soqt-config-version.cmake
	VERSION ${VERSION}
	COMPATIBILITY ExactVersion
)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/soqt-config-version.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SoQt-${SOQT_VERSION}
	COMPONENT develoment
)

install(
	EXPORT SoQt
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SoQt-${SOQT_VERSION}
	NAMESPACE SoQt::
	FILE soqt-export.cmake
	COMPONENT develoment
)

set(CPACK_COMPONENT_DEVELOPMENT_DEPENDS runtime)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_DEPENDS "lib${PACKAGE_TARNAME}${QT_VERSION_MAJOR}-20")
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_NAME "lib${PACKAGE_TARNAME}${QT_VERSION_MAJOR}-dev")
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_SECTION "libdevel")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${PACKAGE_URL})
set(CPACK_DEBIAN_PACKAGE_NAME "lib${PACKAGE_TARNAME}${QT_VERSION_MAJOR}")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_RUNTIME_PACKAGE_NAME "lib${PACKAGE_TARNAME}${QT_VERSION_MAJOR}-20")
set(CPACK_DEBIAN_RUNTIME_PACKAGE_SECTION "libs")
set(CPACK_NSIS_PACKAGE_NAME ${PACKAGE_STRING})
set(CPACK_NSIS_URL_INFO_ABOUT ${PACKAGE_URL})
set(CPACK_PACKAGE_CONTACT ${PACKAGE_BUGREPORT})
set(CPACK_PACKAGE_DISPLAY_NAME ${PACKAGE_STRING})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PACKAGE_TARNAME}-${PACKAGE_VERSION}")
set(CPACK_PACKAGE_NAME ${PACKAGE_TARNAME})
set(CPACK_PACKAGE_VERSION ${SOQT_MAJOR_VERSION}.${SOQT_MINOR_VERSION}.${SOQT_MICRO_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${SOQT_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${SOQT_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${SOQT_MICRO_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_RPM_development_PACKAGE_NAME "${PACKAGE_TARNAME}-devel")
set(CPACK_RPM_development_PACKAGE_REQUIRES "${PACKAGE_TARNAME}")
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_PACKAGE_LICENSE "BSD")
set(CPACK_RPM_PACKAGE_NAME ${PACKAGE_TARNAME})
set(CPACK_RPM_PACKAGE_URL ${PACKAGE_URL})
set(CPACK_RPM_runtime_PACKAGE_NAME "${PACKAGE_TARNAME}")

if(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
endif()

include(CPack)
