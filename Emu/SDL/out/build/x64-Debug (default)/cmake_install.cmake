# Install script for directory: D:/GB_dev/gb_emu/gb_emu/Emu/SDL

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/install/x64-Debug (default)")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/SDL2-staticd.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/SDL2d.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/SDL2d.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/SDL2maind.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake"
         "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/CMakeFiles/Export/cmake/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/CMakeFiles/Export/cmake/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/CMakeFiles/Export/cmake/SDL2Targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/SDL2Config.cmake"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/SDL2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_assert.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_atomic.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_audio.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_bits.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_blendmode.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_clipboard.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_android.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_iphoneos.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_macosx.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_minimal.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_os2.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_pandora.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_psp.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_windows.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_winrt.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_config_wiz.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_copying.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_cpuinfo.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_egl.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_endian.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_error.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_events.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_filesystem.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_gamecontroller.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_gesture.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_haptic.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_hints.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_joystick.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_keyboard.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_keycode.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_loadso.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_log.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_main.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_messagebox.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_metal.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_mouse.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_mutex.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_name.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_opengl.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_opengl_glext.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_opengles.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_opengles2.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_opengles2_gl2.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_opengles2_gl2ext.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_opengles2_gl2platform.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_opengles2_khrplatform.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_pixels.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_platform.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_power.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_quit.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_rect.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_render.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_revision.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_rwops.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_scancode.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_sensor.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_shape.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_stdinc.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_surface.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_system.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_syswm.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_assert.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_common.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_compare.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_crc32.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_font.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_fuzzer.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_harness.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_images.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_log.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_md5.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_memory.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_test_random.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_thread.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_timer.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_touch.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_types.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_version.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_video.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/SDL_vulkan.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/begin_code.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/include/close_code.h"
    "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/include/SDL_config.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/GB_dev/gb_emu/gb_emu/Emu/SDL/out/build/x64-Debug (default)/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
