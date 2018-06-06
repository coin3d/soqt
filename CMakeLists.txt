cmake_minimum_required(VERSION 3.0)

set(gui qt)
set(Gui Qt)
set(GUI QT)
set(WIDGET QWidget*)
set(EVENT QEvent*)
set(COMPONENTHEADER Q_OBJECT)

set(SO${GUI}_MAJOR_VERSION 1)
set(SO${GUI}_MINOR_VERSION 6)
set(SO${GUI}_MICRO_VERSION 0)
set(SO${GUI}_BETA_VERSION a)
set(SO${GUI}_VERSION ${SO${GUI}_MAJOR_VERSION}.${SO${GUI}_MINOR_VERSION}.${SO${GUI}_MICRO_VERSION}${SO${GUI}_BETA_VERSION})

project(So${Gui} VERSION ${SO${GUI}_MAJOR_VERSION}.${SO${GUI}_MINOR_VERSION}.${SO${GUI}_MICRO_VERSION})
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

string(TIMESTAMP SO${GUI}_BUILD_YEAR "%Y")
math(EXPR SO${GUI}_SO_VERSION ${PROJECT_VERSION_MAJOR}*20)
set(VERSION ${SO${GUI}_VERSION})

option(COIN_IV_EXTENSIONS "Enable extra open inventor extensions" ON)
option(SO${GUI}_BUILD_SHARED_LIBS "Build shared libraries" ON)
option(USE_QT5 "Prefer Qt5 over Qt4 if available" ON)
option(WITH_STATIC_DEFAULTS "Enable statically linked in default materials" ON)
option(HAVE_SPACENAV_SUPPORT "Enable Space Navigator support" ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(CheckCXXSourceCompiles)
include(CheckFunctionExists)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckStructHasMember)
include(CheckSymbolExists)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "${CMAKE_PROJECT_NAME} requires an out of source build. Please create a separate build directory and run 'cmake <path_to_${CMAKE_PROJECT_NAME}> [options]' from there.")
endif()

set(CMAKE_BUILD_TYPE Release) # has no effect for multi configuration generators (VisualStudio, Xcode)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)
find_package(Coin REQUIRED)
#find_package(superglu REQUIRED)

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

find_package(X11)

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

set(CMAKE_REQUIRED_INCLUDES ${OPENGL_INCLUDE_DIR})
set(CMAKE_REQUIRED_LIBRARIES ${OPENGL_LIBRARIES})

check_library_exists(GL glXChooseVisual "" HAVE_GLX)
if(HAVE_WINDOWS_H)
	check_include_files("windows.h;GL/gl.h" HAVE_GL_GL_H)
	check_include_files("windows.h;GL/glu.h" HAVE_GL_GLU_H)
else()
	check_include_files(GL/gl.h HAVE_GL_GL_H)
	check_include_files(GL/glu.h HAVE_GL_GLU_H)
endif()
check_include_files(OpenGL/gl.h HAVE_OPENGL_GL_H)
check_include_files(OpenGL/glu.h HAVE_OPENGL_GLU_H)

unset(CMAKE_REQUIRED_INCLUDES)
unset(CMAKE_REQUIRED_LIBRARIES)

check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(memory.h HAVE_MEMORY_H)
check_include_files(netinet/in.h HAVE_NETINET_IN_H)
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

set(CMAKE_REQUIRED_LIBRARIES Coin::Coin)

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

unset(CMAKE_REQUIRED_LIBRARIES)

check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(sys/stat.h HAVE_SYS_STAT_H)
check_include_files(sys/time.h HAVE_SYS_TIME_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files("assert.h;ctype.h;errno.h;float.h;limits.h;locale.h;math.h;setjmp.h;signal.h;stdarg.h;stddef.h;stdio.h;stdlib.h;string.h;time.h" STDC_HEADERS)
if(HAVE_WINDOWS_H)
	check_include_files("windows.h;tlhelp32.h" HAVE_TLHELP32_H)
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
	if(HAVE_WIN32_LOADLIBRARY)
		set(HAVE_DYNAMIC_LINKING 1)
	endif()
	check_symbol_exists(GetEnvironmentVariable windows.h HAVE_GETENVIRONMENTVARIABLE)
endif()
set(USE_EXCEPTIONS ON)
set(X_DISPLAY_MISSING ON)
set(HAVE_JOYSTICK_LINUX OFF)
check_include_files(X11/Xlib.h HAVE_X11_AVAILABLE)
if(HAVE_X11_AVAILABLE)
	check_include_files(X11/extensions/SGIMisc.h HAVE_X11_EXTENSIONS_SGIMISC_H)
	check_include_files(X11/extensions/XInput.h HAVE_X11_EXTENSIONS_XINPUT_H)
	check_include_files(X11/Xproto.h HAVE_X11_XPROTO_H)
endif()

set(PACKAGE ${PROJECT_NAME})
set(PACKAGE_DESCRIPTION "A Qt Gui-toolkit binding for Coin")
set(PACKAGE_BUGREPORT "coin-support@coin3d.org")
set(PACKAGE_NAME ${PROJECT_NAME})
set(PACKAGE_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
set(PACKAGE_TARNAME ${PROJECT_NAME_LOWER})
set(PACKAGE_URL "https://bitbucket.org/Coin3D/${PROJECT_NAME_LOWER}")
set(PACKAGE_VERSION ${PROJECT_VERSION})
set(PACKAGE_HOST ${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_HOST_SYSTEM_NAME})
set(PACKAGE_COMPILER ${CMAKE_CXX_COMPILER})
set(PACKAGE_REQUIREMENTS "Coin")

configure_file(src/config.h.cmake.in src/config.h)

add_subdirectory(data)
add_subdirectory(src/Inventor/${Gui}/common)

file(GLOB_RECURSE COMMON_HDRS ${CMAKE_BINARY_DIR}/src/*.h)
file(GLOB_RECURSE COMMON_SRCS ${CMAKE_BINARY_DIR}/src/*.cpp)

set(HDRS
	src/Inventor/${Gui}/So${Gui}ComponentP.h
	src/Inventor/${Gui}/So${Gui}GLWidgetP.h
	src/Inventor/${Gui}/So${Gui}ImageReader.h
	src/Inventor/${Gui}/So${Gui}Internal.h
	src/Inventor/${Gui}/SoQtP.h
	src/Inventor/${Gui}/So${Gui}SignalThread.h
	src/Inventor/${Gui}/devices/6DOFEvents.h
	src/Inventor/${Gui}/devices/So${Gui}DeviceP.h
	src/Inventor/${Gui}/devices/So${Gui}SpacenavDevice.h
	src/Inventor/${Gui}/viewers/So${Gui}ExaminerViewerP.h
	src/Inventor/${Gui}/viewers/So${Gui}FullViewerP.h
	src/Inventor/${Gui}/viewers/So${Gui}PlaneViewerP.h
	src/Inventor/${Gui}/widgets/So${Gui}GLArea.h
	src/Inventor/${Gui}/widgets/So${Gui}ThumbWheel.h
	src/Inventor/${Gui}/widgets/${Gui}NativePopupMenu.h
)

set(SRCS
	src/Inventor/${Gui}/So${Gui}.cpp
	src/Inventor/${Gui}/So${Gui}Component.cpp
	src/Inventor/${Gui}/So${Gui}GLWidget.cpp
	#src/Inventor/${Gui}/So${Gui}MaterialList.cpp
	src/Inventor/${Gui}/So${Gui}ImageReader.cpp
	src/Inventor/${Gui}/So${Gui}SignalThread.cpp
	src/Inventor/${Gui}/devices/6DOFEvents.cpp
	src/Inventor/${Gui}/devices/So${Gui}Device.cpp
	src/Inventor/${Gui}/devices/So${Gui}InputFocus.cpp
	src/Inventor/${Gui}/devices/So${Gui}Keyboard.cpp
	src/Inventor/${Gui}/devices/So${Gui}Mouse.cpp
	src/Inventor/${Gui}/devices/So${Gui}SpacenavDevice.cpp
	src/Inventor/${Gui}/viewers/ExaminerViewer.cpp
	src/Inventor/${Gui}/viewers/FullViewer.cpp
	src/Inventor/${Gui}/viewers/PlaneViewer.cpp
	#src/Inventor/${Gui}/viewers/WalkViewer.cpp
	src/Inventor/${Gui}/widgets/So${Gui}GLArea.cpp
	src/Inventor/${Gui}/widgets/So${Gui}ThumbWheel.cpp
	src/Inventor/${Gui}/widgets/${Gui}NativePopupMenu.cpp
)

macro(qt_generate_moc infile outfile)
	if(Qt5_FOUND)
		qt5_generate_moc(${infile} ${outfile})
	elseif(Qt4_FOUND)
		qt4_generate_moc(${infile} ${outfile})
	endif()
	
	if(NOT IS_ABSOLUTE ${outfile})
		list(APPEND MOC_SRCS ${CMAKE_BINARY_DIR}/${outfile})
	else()
		list(APPEND MOC_SRCS ${outfile})
	endif()
endmacro()

qt_generate_moc(src/Inventor/${Gui}/So${Gui}ComponentP.h              src/Inventor/${Gui}/moc_So${Gui}ComponentP.icc)
qt_generate_moc(src/Inventor/${Gui}/So${Gui}GLWidgetP.h               src/Inventor/${Gui}/moc_So${Gui}GLWidgetP.icc)
qt_generate_moc(src/Inventor/${Gui}/So${Gui}MaterialList.cpp          src/Inventor/${Gui}/moc_So${Gui}MaterialList.icc)
qt_generate_moc(src/Inventor/${Gui}/So${Gui}MaterialSliderSet.h       src/Inventor/${Gui}/moc_So${Gui}MaterialSliderSet.icc)
qt_generate_moc(src/Inventor/${Gui}/SoQtP.h                           src/Inventor/${Gui}/moc_SoQtP.icc)
qt_generate_moc(src/Inventor/${Gui}/So${Gui}SignalThread.h            src/Inventor/${Gui}/moc_So${Gui}SignalThread.icc)
qt_generate_moc(src/Inventor/${Gui}/So${Gui}SliderSetBase.h           src/Inventor/${Gui}/moc_So${Gui}SliderSetBase.icc)
qt_generate_moc(src/Inventor/${Gui}/So${Gui}TransformSliderSet.h      src/Inventor/${Gui}/moc_So${Gui}TransformSliderSet.icc)
qt_generate_moc(src/Inventor/${Gui}/viewers/So${Gui}ExaminerViewerP.h src/Inventor/${Gui}/viewers/moc_So${Gui}ExaminerViewerP.icc)
qt_generate_moc(src/Inventor/${Gui}/viewers/So${Gui}FullViewerP.h     src/Inventor/${Gui}/viewers/moc_So${Gui}FullViewerP.icc)
qt_generate_moc(src/Inventor/${Gui}/viewers/So${Gui}PlaneViewerP.h    src/Inventor/${Gui}/viewers/moc_So${Gui}PlaneViewerP.icc)
#qt_generate_moc(src/Inventor/${Gui}/viewers/So${Gui}WalkViewerP.h    src/Inventor/${Gui}/viewers/moc_So${Gui}WalkViewerP.icc)
qt_generate_moc(src/Inventor/${Gui}/widgets/${Gui}NativePopupMenu.h    src/Inventor/${Gui}/widgets/moc_${Gui}NativePopupMenu.icc)
qt_generate_moc(src/Inventor/${Gui}/widgets/So${Gui}GLArea.h          src/Inventor/${Gui}/widgets/moc_So${Gui}GLArea.icc)
qt_generate_moc(src/Inventor/${Gui}/widgets/So${Gui}ThumbWheel.h      src/Inventor/${Gui}/widgets/moc_So${Gui}ThumbWheel.icc)

if(HAVE_JOYSTICK_LINUX)
	list(APPEND HDRS src/Inventor/${Gui}/devices/So${Gui}LinuxJoystick.h)
	list(APPEND SRCS src/Inventor/${Gui}/devices/So${Gui}LinuxJoystick.cpp)
	qt_generate_moc(src/Inventor/${Gui}/devices/So${Gui}LinuxJoystick.h src/Inventor/${Gui}/devices/moc_So${Gui}LinuxJoystick.icc)
endif()

if(SO${GUI}_BUILD_SHARED_LIBS)
	if(WIN32)
		configure_file(src/${PROJECT_NAME}.rc.cmake.in src/${PROJECT_NAME}.rc)
		set(SO${GUI}_RESSOURCE ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}.rc CACHE INTERNAL "SO${GUI}_RESSOURCE")
		set(CMAKE_RELEASE_POSTFIX ${PROJECT_VERSION_MAJOR})
		set(CMAKE_MINSIZEREL_POSTFIX ${PROJECT_VERSION_MAJOR})
		set(CMAKE_RELWITHDEBINFO_POSTFIX ${PROJECT_VERSION_MAJOR})
		set(CMAKE_DEBUG_POSTFIX ${PROJECT_VERSION_MAJOR}d)
	endif()
	add_library(${PROJECT_NAME} SHARED ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS} ${SO${GUI}_RESSOURCE} ${MOC_SRCS})
	target_compile_definitions(${PROJECT_NAME} PRIVATE SO${GUI}_MAKE_DLL INTERFACE SO${GUI}_DLL)
else()
	if(WIN32)
		set(CMAKE_RELEASE_POSTFIX ${PROJECT_VERSION_MAJOR}s)
		set(CMAKE_MINSIZEREL_POSTFIX ${PROJECT_VERSION_MAJOR}s)
		set(CMAKE_RELWITHDEBINFO_POSTFIX ${PROJECT_VERSION_MAJOR}s)
		set(CMAKE_DEBUG_POSTFIX ${PROJECT_VERSION_MAJOR}sd)
	endif()
	add_library(${PROJECT_NAME} STATIC ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS} ${MOC_SRCS})
	target_compile_definitions(${PROJECT_NAME} INTERFACE SO${GUI}_NOT_DLL)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${SO${GUI}_VERSION} SOVERSION ${SO${GUI}_SO_VERSION})

target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_CONFIG_H SO${GUI}_INTERNAL SO${GUI}_DEBUG=$<CONFIG:Debug>)
if(MSVC)
	target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_NONSTDC_NO_DEPRECATE _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS)
endif()

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
#		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/Inventor/Qt>
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
		$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
		${OPENGL_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} Coin::Coin ${OPENGL_LIBRARIES} ${QT_LIBRARIES})

if(X11_FOUND)
	target_include_directories(${PROJECT_NAME} PUBLIC ${X11_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
endif()
if(X11_Xi_FOUND)
	target_include_directories(${PROJECT_NAME} PUBLIC ${X11_Xi_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${X11_Xi_LIB})
endif()

##### small test programs (to be run interactively)
add_subdirectory(test-code)

##### documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(SOGUI_DOC_HTML YES)
	set(SOGUI_DOC_HTML_HELP NO)
	if(WIN32)
		set(SOGUI_DOC_MAN NO)
		find_program(HHC_PROGRAM NAMES hhc.exe PATHS "C:/Program Files/HTML Help Workshop" "C:/Program Files (x86)/HTML Help Workshop" DOC "HTML Help Compiler program")
		if(HHC_PROGRAM)
			option(SO${GUI}_BUILD_DOC_CHM "Create compressed HTML help (requires HHC)" OFF)
			mark_as_advanced(HHC_PROGRAM)
		else()
			set(SO${GUI}_BUILD_DOC_CHM OFF)
		endif()
		if(SO${GUI}_BUILD_DOC_CHM)
			set(SOGUI_DOC_HTML_HELP YES)
			set(GENERATE_TREEVIEW NO)
		else()
			set(HHC_PROGRAM)
			set(GENERATE_TREEVIEW YES)
		endif()
	else()
		set(SOGUI_DOC_MAN YES)
		set(GENERATE_TREEVIEW YES)
		set(HHC_PROGRAM)
	endif()

	set(DOXYGEN_INTERNAL_DOCS NO)
	set(DOXYGEN_EXTRACT_PRIVATE NO)
	set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
	set(DOXYGEN_EXCLUDE)

	configure_file(src/Inventor/${Gui}/common/sogui.doxygen.cmake.in Doxyfile @ONLY)
	add_custom_target(${PROJECT_NAME}_docs ALL
		${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
	if(WIN32)
		install(DIRECTORY ${CMAKE_BINARY_DIR}/html DESTINATION ${CMAKE_INSTALL_DOCDIR})
	else()
		install(DIRECTORY ${CMAKE_BINARY_DIR}/html DESTINATION ${CMAKE_INSTALL_DOCDIR})
		install(DIRECTORY ${CMAKE_BINARY_DIR}/man DESTINATION ${CMAKE_INSTALL_MANDIR})
	endif()
endif(DOXYGEN_FOUND)

set(INST_HDRS
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/So${Gui}.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/So${Gui}Basic.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/So${Gui}ColorEditor.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/So${Gui}Component.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/So${Gui}Cursor.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/So${Gui}GLWidget.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/So${Gui}Object.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/So${Gui}RenderArea.h
)

set(INST_DEVICES_HDRS
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/devices/So${Gui}Device.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/devices/So${Gui}Keyboard.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/devices/So${Gui}Mouse.h
)

if(HAVE_JOYSTICK_LINUX)
	list(APPEND INST_DEVICES_HDRS ${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/devices/So${Gui}LinuxJoystick.h)
endif()

set(INST_EDITORS_HDRS
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/editors/So${Gui}ColorEditor.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/editors/So${Gui}MaterialEditor.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/devices/So${Gui}SpacenavDevice.h
)

set(INST_NODES_HDRS
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/nodes/SoGuiColorEditor.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/nodes/SoGuiMaterialEditor.h
)

set(INST_VIEWERS_HDRS
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/viewers/So${Gui}ConstrainedViewer.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/viewers/So${Gui}ExaminerViewer.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/viewers/So${Gui}FlyViewer.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/viewers/So${Gui}FullViewer.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/viewers/So${Gui}PlaneViewer.h
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/viewers/So${Gui}Viewer.h
	#${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/viewers/So${Gui}WalkViewer.h
)

set(INST_WIDGETS_HDRS
	${CMAKE_BINARY_DIR}/src/Inventor/${Gui}/widgets/So${Gui}PopupMenu.h
	src/Inventor/${Gui}/widgets/So${Gui}ThumbWheel.h
)

install(FILES ${INST_HDRS}         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}         COMPONENT development)
install(FILES ${INST_DEVICES_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/devices COMPONENT development)
install(FILES ${INST_EDITORS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/editors COMPONENT development)
install(FILES ${INST_NODES_HDRS}   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/nodes   COMPONENT development)
install(FILES ${INST_VIEWERS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/viewers COMPONENT development)
install(FILES ${INST_WIDGETS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/widgets COMPONENT development)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtime NAMELINK_SKIP
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime
)

if(SO${GUI}_BUILD_SHARED_LIBS)
	install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development NAMELINK_ONLY)
endif()

if(MSVC)
	if(SO${GUI}_BUILD_SHARED_LIBS)
		install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION ${CMAKE_INSTALL_BINDIR} CONFIGURATIONS Debug RelWithDebInfo COMPONENT debug)
	else()
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7")                       # Override default /Zi to embed
		set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Z7")     # debugging info in the .lib.
	endif()
endif()

configure_package_config_file(${PROJECT_NAME_LOWER}-config.cmake.in ${PROJECT_NAME_LOWER}-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
)

write_basic_package_version_file(${CMAKE_BINARY_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY ExactVersion
)

# To make the component usable not only from the install directory but also from the build directory
export(
	TARGETS ${PROJECT_NAME}
	FILE ${PROJECT_NAME_LOWER}-export.cmake
)

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME_LOWER}-config.cmake ${CMAKE_BINARY_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
	COMPONENT development
)

install(EXPORT ${PROJECT_NAME}
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
	NAMESPACE ${PROJECT_NAME}::
	FILE ${PROJECT_NAME_LOWER}-export.cmake
	COMPONENT development
)

set(CPACK_COMPONENT_DEVELOPMENT_DEPENDS "runtime")
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_DEPENDS lib${PACKAGE_TARNAME}${QT_VERSION_MAJOR}-${SO${GUI}_SO_VERSION})
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_NAME lib${PACKAGE_TARNAME}${QT_VERSION_MAJOR}-dev)
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_SECTION "libdevel")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${PACKAGE_URL})
set(CPACK_DEBIAN_PACKAGE_NAME lib${PACKAGE_TARNAME}${QT_VERSION_MAJOR})
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_RUNTIME_PACKAGE_NAME lib${PACKAGE_TARNAME}${QT_VERSION_MAJOR}-${SO${GUI}_SO_VERSION})
set(CPACK_DEBIAN_RUNTIME_PACKAGE_SECTION "libs")
set(CPACK_NSIS_PACKAGE_NAME ${PACKAGE_STRING})
set(CPACK_NSIS_URL_INFO_ABOUT ${PACKAGE_URL})
set(CPACK_PACKAGE_DESCRIPTION_FILE ${PROJECT_SOURCE_DIR}/README)
set(CPACK_PACKAGE_CONTACT ${PACKAGE_BUGREPORT})
set(CPACK_PACKAGE_DISPLAY_NAME ${PACKAGE_STRING})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PACKAGE_TARNAME}-${PACKAGE_VERSION})
set(CPACK_PACKAGE_NAME ${PACKAGE_TARNAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/COPYING)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_RPM_development_PACKAGE_NAME ${PACKAGE_TARNAME}-devel)
set(CPACK_RPM_development_PACKAGE_REQUIRES ${PACKAGE_TARNAME})
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_PACKAGE_LICENSE "BSD")
set(CPACK_RPM_PACKAGE_NAME ${PACKAGE_TARNAME})
set(CPACK_RPM_PACKAGE_URL ${PACKAGE_URL})
set(CPACK_RPM_runtime_PACKAGE_NAME ${PACKAGE_TARNAME})
# workaround for erroneous inclusion of system directories
# see https://stackoverflow.com/questions/24983181/cpack-generates-rpms-with-files-entries-that-conflict-with-the-rpm-spec-how-to
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/lib64/cmake")

if(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
endif()

include(CPack)
