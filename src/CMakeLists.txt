configure_file(config.h.cmake.in config.h)

add_subdirectory(Inventor/${Gui}/common)

file(GLOB_RECURSE COMMON_HDRS ${CMAKE_CURRENT_BINARY_DIR}/*.h)
file(GLOB_RECURSE COMMON_SRCS ${CMAKE_CURRENT_BINARY_DIR}/*.cpp)

set(HDRS
  Inventor/${Gui}/So${Gui}ComponentP.h
  Inventor/${Gui}/So${Gui}GLWidgetP.h
  Inventor/${Gui}/So${Gui}ImageReader.h
  Inventor/${Gui}/So${Gui}Internal.h
  Inventor/${Gui}/SoQtP.h
  Inventor/${Gui}/So${Gui}SignalThread.h
  Inventor/${Gui}/devices/6DOFEvents.h
  Inventor/${Gui}/devices/So${Gui}DeviceP.h
  Inventor/${Gui}/devices/So${Gui}SpacenavDevice.h
  Inventor/${Gui}/viewers/So${Gui}ExaminerViewerP.h
  Inventor/${Gui}/viewers/So${Gui}FullViewerP.h
  Inventor/${Gui}/viewers/So${Gui}PlaneViewerP.h
  Inventor/${Gui}/widgets/So${Gui}GLArea.h
  Inventor/${Gui}/widgets/So${Gui}ThumbWheel.h
  Inventor/${Gui}/widgets/${Gui}NativePopupMenu.h
)

set(SRCS
  Inventor/${Gui}/So${Gui}.cpp
  Inventor/${Gui}/So${Gui}Component.cpp
  Inventor/${Gui}/So${Gui}GLWidget.cpp
  #Inventor/${Gui}/So${Gui}MaterialList.cpp
  Inventor/${Gui}/So${Gui}ImageReader.cpp
  Inventor/${Gui}/So${Gui}SignalThread.cpp
  Inventor/${Gui}/devices/6DOFEvents.cpp
  Inventor/${Gui}/devices/So${Gui}Device.cpp
  Inventor/${Gui}/devices/So${Gui}InputFocus.cpp
  Inventor/${Gui}/devices/So${Gui}Keyboard.cpp
  Inventor/${Gui}/devices/So${Gui}Mouse.cpp
  Inventor/${Gui}/devices/So${Gui}SpacenavDevice.cpp
  Inventor/${Gui}/viewers/ExaminerViewer.cpp
  Inventor/${Gui}/viewers/FullViewer.cpp
  Inventor/${Gui}/viewers/PlaneViewer.cpp
  #Inventor/${Gui}/viewers/WalkViewer.cpp
  Inventor/${Gui}/widgets/So${Gui}GLArea.cpp
  Inventor/${Gui}/widgets/So${Gui}ThumbWheel.cpp
  Inventor/${Gui}/widgets/${Gui}NativePopupMenu.cpp
)

macro(qt_generate_moc infile outfile)
  if(Qt5_FOUND)
    qt5_generate_moc(${infile} ${outfile})
  elseif(Qt4_FOUND)
    qt4_generate_moc(${infile} ${outfile})
  endif()

  if(NOT IS_ABSOLUTE ${outfile})
    list(APPEND MOC_SRCS "${CMAKE_CURRENT_BINARY_DIR}/${outfile}")
  else()
    list(APPEND MOC_SRCS ${outfile})
  endif()
endmacro()

qt_generate_moc(Inventor/${Gui}/So${Gui}ComponentP.h              Inventor/${Gui}/moc_So${Gui}ComponentP.icc)
qt_generate_moc(Inventor/${Gui}/So${Gui}GLWidgetP.h               Inventor/${Gui}/moc_So${Gui}GLWidgetP.icc)
qt_generate_moc(Inventor/${Gui}/So${Gui}MaterialList.cpp          Inventor/${Gui}/moc_So${Gui}MaterialList.icc)
qt_generate_moc(Inventor/${Gui}/So${Gui}MaterialSliderSet.h       Inventor/${Gui}/moc_So${Gui}MaterialSliderSet.icc)
qt_generate_moc(Inventor/${Gui}/SoQtP.h                           Inventor/${Gui}/moc_SoQtP.icc)
qt_generate_moc(Inventor/${Gui}/So${Gui}SignalThread.h            Inventor/${Gui}/moc_So${Gui}SignalThread.icc)
qt_generate_moc(Inventor/${Gui}/So${Gui}SliderSetBase.h           Inventor/${Gui}/moc_So${Gui}SliderSetBase.icc)
qt_generate_moc(Inventor/${Gui}/So${Gui}TransformSliderSet.h      Inventor/${Gui}/moc_So${Gui}TransformSliderSet.icc)
qt_generate_moc(Inventor/${Gui}/viewers/So${Gui}ExaminerViewerP.h Inventor/${Gui}/viewers/moc_So${Gui}ExaminerViewerP.icc)
qt_generate_moc(Inventor/${Gui}/viewers/So${Gui}FullViewerP.h     Inventor/${Gui}/viewers/moc_So${Gui}FullViewerP.icc)
qt_generate_moc(Inventor/${Gui}/viewers/So${Gui}PlaneViewerP.h    Inventor/${Gui}/viewers/moc_So${Gui}PlaneViewerP.icc)
#qt_generate_moc(Inventor/${Gui}/viewers/So${Gui}WalkViewerP.h     Inventor/${Gui}/viewers/moc_So${Gui}WalkViewerP.icc)
qt_generate_moc(Inventor/${Gui}/widgets/${Gui}NativePopupMenu.h   Inventor/${Gui}/widgets/moc_${Gui}NativePopupMenu.icc)
qt_generate_moc(Inventor/${Gui}/widgets/So${Gui}GLArea.h          Inventor/${Gui}/widgets/moc_So${Gui}GLArea.icc)
qt_generate_moc(Inventor/${Gui}/widgets/So${Gui}ThumbWheel.h      Inventor/${Gui}/widgets/moc_So${Gui}ThumbWheel.icc)

if(HAVE_JOYSTICK_LINUX)
  list(APPEND HDRS Inventor/${Gui}/devices/So${Gui}LinuxJoystick.h)
  list(APPEND SRCS Inventor/${Gui}/devices/So${Gui}LinuxJoystick.cpp)
  qt_generate_moc(Inventor/${Gui}/devices/So${Gui}LinuxJoystick.h Inventor/${Gui}/devices/moc_So${Gui}LinuxJoystick.icc)
endif()

if(WIN32)
  if(MINGW)
    set(SO${GUI}_DEFAULT_SHARED_POSTFIX "")
    set(SO${GUI}_DEFAULT_STATIC_POSTFIX "")
  else()
    # On Windows the major version number is part of the library name
    set(SO${GUI}_DEFAULT_SHARED_POSTFIX ${PROJECT_VERSION_MAJOR})
    set(SO${GUI}_DEFAULT_STATIC_POSTFIX ${PROJECT_VERSION_MAJOR}s)
  endif()
  if(SO${GUI}_BUILD_SHARED_LIBS)
    set(SO${GUI}_DEFAULT_POSTFIX ${SO${GUI}_DEFAULT_SHARED_POSTFIX})
  else()
    set(SO${GUI}_DEFAULT_POSTFIX ${SO${GUI}_DEFAULT_STATIC_POSTFIX})
  endif()
  set(CMAKE_RELEASE_POSTFIX ${SO${GUI}_DEFAULT_POSTFIX})
  set(CMAKE_MINSIZEREL_POSTFIX ${SO${GUI}_DEFAULT_POSTFIX})
  set(CMAKE_RELWITHDEBINFO_POSTFIX ${SO${GUI}_DEFAULT_POSTFIX})
  set(CMAKE_DEBUG_POSTFIX ${SO${GUI}_DEFAULT_POSTFIX}d)
elseif(APPLE)
else()
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

if(SO${GUI}_BUILD_SHARED_LIBS)
  add_library(${PROJECT_NAME} SHARED ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS} ${MOC_SRCS})
else()
  add_library(${PROJECT_NAME} STATIC ${HDRS} ${COMMON_HDRS} ${SRCS} ${COMMON_SRCS} ${MOC_SRCS})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${SO${GUI}_VERSION} SOVERSION ${SO${GUI}_SO_VERSION})

target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_CONFIG_H SO${GUI}_INTERNAL SO${GUI}_DEBUG=$<CONFIG:Debug>)

if(WIN32)
  if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_NONSTDC_NO_DEPRECATE _CRT_SECURE_NO_DEPRECATE _CRT_SECURE_NO_WARNINGS _USE_MATH_DEFINES)
  endif()
  if(SO${GUI}_BUILD_SHARED_LIBS)
    configure_file(${PROJECT_NAME}.rc.cmake.in ${PROJECT_NAME}.rc)
    target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc")
    target_compile_definitions(${PROJECT_NAME} PRIVATE SO${GUI}_MAKE_DLL INTERFACE SO${GUI}_DLL)
  else()
    target_compile_definitions(${PROJECT_NAME} INTERFACE SO${GUI}_NOT_DLL)
    if(MSVC)
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7")                       # Override default /Zi to embed
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Z7")     # debugging info in the .lib.
    endif()
  endif()
endif()

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
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

# Add a target to generate API documentation with Doxygen
if(SO${GUI}_BUILD_DOCUMENTATION)
  find_package(Doxygen)
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
  endif()

  set(DOXYGEN_TAGFILES "${Coin_DOC_DIR}/html/Coin.tag=${Coin_DOC_DIR}/html")

# ############################################################################
# Setup documentation options
# ############################################################################
  set(GENERATE_HTMLHELP NO)
  set(DOXYGEN_GENERATE_MAN NO)
  set(GENERATE_QHP NO)
  set(GENERATE_TREEVIEW YES)
  set(HHC_PROGRAM)
  if(WIN32)
    if(SO${GUI}_BUILD_DOC_CHM)
      find_program(HHC_PROGRAM NAMES hhc.exe PATHS "C:/Program Files/HTML Help Workshop" "C:/Program Files (x86)/HTML Help Workshop" DOC "HTML Help Compiler program")
      if(NOT HHC_PROGRAM)
        message(FATAL_ERROR "Missing program HTML Help Compiler")
      else()
        set(GENERATE_HTMLHELP YES)
        set(GENERATE_TREEVIEW NO)
        mark_as_advanced(HHC_PROGRAM)
      endif()
    endif()
  else()
    if(SO${GUI}_BUILD_DOC_MAN)
      set(DOXYGEN_GENERATE_MAN YES)
    endif()
  endif()
  if(SO${GUI}_BUILD_DOC_QTHELP)
    find_program(QHG_LOCATION NAMES qhelpgenerator qhelpgenerator-qt5 DOC "Qt qhelpgenerator")
    if(NOT QHG_LOCATION)
      message(FATAL_ERROR "Missing program Qt qhelpgenerator")
    else()
      set(GENERATE_QHP YES)
      mark_as_advanced(QHG_LOCATION)
    endif()
  endif()

  set(DOXYGEN_INTERNAL_DOCS NO)
  set(DOXYGEN_EXTRACT_PRIVATE NO)
  set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
  set(DOXYGEN_EXCLUDE)

  set(DOXYFILE "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
  set(DOXYGEN_OUTPUT "${CMAKE_BINARY_DIR}/html/index.html")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Inventor/${Gui}/common/sogui.doxygen.cmake.in" ${DOXYFILE} @ONLY)

# ############################################################################
# Setup documentation targets
# ############################################################################
  add_custom_command(
    OUTPUT ${DOXYGEN_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E echo_append "Generating API documentation with Doxygen "
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
    COMMAND ${CMAKE_COMMAND} -E echo "done."
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS ${DOXYFILE}
  )
  add_custom_target(documentation ALL DEPENDS ${DOXYGEN_OUTPUT})

# ############################################################################
# Install built documentation files
# ############################################################################
  install(DIRECTORY "${CMAKE_BINARY_DIR}/html" DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT documentation REGEX ".*\\.(chm|qch)" EXCLUDE)
  if(GENERATE_HTMLHELP)
    install(FILES "${CMAKE_BINARY_DIR}/html/${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.chm" DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT documentation)
  endif()
  if(GENERATE_QHP)
    install(FILES "${CMAKE_BINARY_DIR}/html/${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.qch" DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT documentation)
  endif()
  if(DOXYGEN_GENERATE_MAN)
    install(DIRECTORY "${CMAKE_BINARY_DIR}/man/man3" DESTINATION ${CMAKE_INSTALL_MANDIR} COMPONENT documentation)
    message(STATUS "CMAKE_INSTALL_MANDIR ${CMAKE_INSTALL_MANDIR}")
  endif()
endif()

# ############################################################################
# Install headers
# ############################################################################

set(INST_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}Basic.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}ColorEditor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}Component.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}Cursor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}GLWidget.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}Object.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/So${Gui}RenderArea.h"
)

set(INST_DEVICES_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}Device.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}Keyboard.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}Mouse.h"
)

if(HAVE_JOYSTICK_LINUX)
  list(APPEND INST_DEVICES_HDRS "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}LinuxJoystick.h")
endif()

set(INST_EDITORS_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/editors/So${Gui}ColorEditor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/editors/So${Gui}MaterialEditor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/devices/So${Gui}SpacenavDevice.h"
)

set(INST_NODES_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/nodes/SoGuiColorEditor.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/nodes/SoGuiMaterialEditor.h"
)

set(INST_VIEWERS_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}ConstrainedViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}ExaminerViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}FlyViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}FullViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}PlaneViewer.h"
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}Viewer.h"
  #"${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/viewers/So${Gui}WalkViewer.h"
)

set(INST_WIDGETS_HDRS
  "${CMAKE_CURRENT_BINARY_DIR}/Inventor/${Gui}/widgets/So${Gui}PopupMenu.h"
  Inventor/${Gui}/widgets/So${Gui}ThumbWheel.h
)

install(FILES ${INST_HDRS}         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}         COMPONENT development)
install(FILES ${INST_DEVICES_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/devices COMPONENT development)
install(FILES ${INST_EDITORS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/editors COMPONENT development)
install(FILES ${INST_NODES_HDRS}   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/nodes   COMPONENT development)
install(FILES ${INST_VIEWERS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/viewers COMPONENT development)
install(FILES ${INST_WIDGETS_HDRS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Inventor/${Gui}/widgets COMPONENT development)

# ############################################################################
# Install targets
# ############################################################################

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtime NAMELINK_SKIP
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime
)

if(SO${GUI}_BUILD_SHARED_LIBS)
  install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT development NAMELINK_ONLY)
  if(MSVC)
    install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION ${CMAKE_INSTALL_BINDIR} CONFIGURATIONS Debug RelWithDebInfo COMPONENT debug)
  endif()
endif()

# ############################################################################
# Install pkgconfig file and CMake config package
# ############################################################################

if(UNIX OR MINGW)
  configure_file("${CMAKE_SOURCE_DIR}/So${Gui}.pc.cmake.in" So${Gui}.pc @ONLY)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/So${Gui}.pc" DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()

configure_package_config_file("${CMAKE_SOURCE_DIR}/${PROJECT_NAME_LOWER}-config.cmake.in" ${PROJECT_NAME_LOWER}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
)

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY ExactVersion
)

# To make the component usable not only from the install directory but also from the build directory
export(
  TARGETS ${PROJECT_NAME}
  FILE ${PROJECT_NAME_LOWER}-export.cmake
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}-config-version.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  COMPONENT development
)

install(EXPORT ${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${PROJECT_NAME_LOWER}-export.cmake
  COMPONENT development
)
