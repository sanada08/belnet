# macos specific cpack stuff goes here

# Here we build belnet-network-control-panel into 'belnet-gui.app' in "extra/" where a postinstall
# script will then move it to /Applications/.

set(BELNET_GUI_REPO "https://github.com/beldex-coin/beldex-network-control-panel.git"
    CACHE STRING "Can be set to override the default belnet-gui git repository")
set(BELNET_GUI_CHECKOUT "origin/master"
    CACHE STRING "Can be set to specify a particular branch or tag to build from BELNET_GUI_REPO")
set(MACOS_SIGN_APP ""  # FIXME: it doesn't use a Apple Distribution key because WTF knows.
    CACHE STRING "enable codesigning of the stuff inside the .app and the belnet binary -- use a 'Apple Distribution' key (or description) from `security find-identity -v`")
set(MACOS_SIGN_PKG ""
    CACHE STRING "enable codesigning of the .pkg -- use a 'Developer ID Installer' key (or description) from `security find-identity -v`")
set(MACOS_NOTARIZE_USER ""
    CACHE STRING "set macos notarization username; can also set it in ~/.notarization.cmake")
set(MACOS_NOTARIZE_PASS ""
    CACHE STRING "set macos notarization password; can also set it in ~/.notarization.cmake")
set(MACOS_NOTARIZE_ASC ""
    CACHE STRING "set macos notarization asc provider; can also set it in ~/.notarization.cmake")

include(ExternalProject)

message(STATUS "Building UninstallBelnet.app")

ExternalProject_Add(belnet-uninstaller
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/contrib/macos/uninstaller
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR} -DMACOS_SIGN=${MACOS_SIGN_APP}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
)

message(STATUS "Building BelnetGUI.app from ${BELNET_GUI_REPO} @ ${BELNET_GUI_CHECKOUT}")

if(NOT BUILD_STATIC_DEPS)
    message(FATAL_ERROR "Building an installer on macos requires -DBUILD_STATIC_DEPS=ON")
endif()



ExternalProject_Add(belnet-gui
    DEPENDS oxenmq::oxenmq
    GIT_REPOSITORY "${BELNET_GUI_REPO}"
    GIT_TAG "${BELNET_GUI_CHECKOUT}"
    CMAKE_ARGS -DMACOS_APP=ON -DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR} -DMACOS_SIGN=${MACOS_SIGN_APP}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DBUILD_SHARED_LIBS=OFF
        "-DOXENMQ_LIBRARIES=$<TARGET_FILE:oxenmq::oxenmq>$<SEMICOLON>$<TARGET_FILE:libzmq>$<SEMICOLON>$<TARGET_FILE:sodium>"
        "-DOXENMQ_INCLUDE_DIRS=$<TARGET_PROPERTY:oxenmq::oxenmq,INCLUDE_DIRECTORIES>"
        )

install(PROGRAMS ${CMAKE_SOURCE_DIR}/contrib/macos/belnet_uninstall.sh
        DESTINATION "bin/"
        COMPONENT belnet)

install(DIRECTORY ${PROJECT_BINARY_DIR}/BelnetGUI.app
        DESTINATION "../../Applications/Belnet"
        USE_SOURCE_PERMISSIONS
        COMPONENT gui
        PATTERN "*"
        )

install(DIRECTORY ${PROJECT_BINARY_DIR}/UninstallBelnet.app
        DESTINATION "../../Applications/Belnet"
        USE_SOURCE_PERMISSIONS
        COMPONENT gui
        PATTERN "*"
        )

# copy files that will be later moved by the postinstall script to proper locations
install(FILES ${CMAKE_SOURCE_DIR}/contrib/macos/belnet_macos_daemon_script.sh
  ${CMAKE_SOURCE_DIR}/contrib/macos/network.beldex.belnet.daemon.plist
  ${CMAKE_SOURCE_DIR}/contrib/macos/belnet-newsyslog.conf
  DESTINATION "extra/"
  COMPONENT belnet)

set(CPACK_COMPONENTS_ALL belnet gui)

set(CPACK_COMPONENT_BELNET_DISPLAY_NAME "Belnet Service")
set(CPACK_COMPONENT_BELNET_DESCRIPTION "Main Belnet runtime service, managed by Launchd")

set(CPACK_COMPONENT_GUI_DISPLAY_NAME "Belnet GUI")
set(CPACK_COMPONENT_GUI_DESCRIPTION "Small GUI which provides stats and limited runtime control of the Belnet service. Resides in the system tray.")

set(CPACK_GENERATOR "productbuild")
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/belnet")
set(CPACK_PREINSTALL_BELNET_SCRIPT ${CMAKE_SOURCE_DIR}/contrib/macos/preinstall)
set(CPACK_POSTFLIGHT_BELNET_SCRIPT ${CMAKE_SOURCE_DIR}/contrib/macos/postinstall)

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")

set(CPACK_PRODUCTBUILD_IDENTITY_NAME "${MACOS_SIGN_PKG}")

if(MACOS_SIGN_APP)
    add_custom_target(sign ALL
        echo "Signing belnet and belnet-vpn binaries"
        COMMAND codesign -s "${MACOS_SIGN_APP}" --strict --options runtime --force -vvv $<TARGET_FILE:belnet> $<TARGET_FILE:belnet-vpn>
        DEPENDS belnet belnet-vpn
        )
endif()

if(MACOS_SIGN_APP AND MACOS_SIGN_PKG)
    if(NOT MACOS_NOTARIZE_USER)
        if(EXISTS "$ENV{HOME}/.notarization.cmake")
            include("$ENV{HOME}/.notarization.cmake")
        endif()
    endif()
    if(MACOS_NOTARIZE_USER AND MACOS_NOTARIZE_PASS AND MACOS_NOTARIZE_ASC)
        message(STATUS "'notarization' target enabled")
        configure_file(${CMAKE_SOURCE_DIR}/contrib/macos/notarize.py.in ${CMAKE_CURRENT_BINARY_DIR}/contrib/notarize.py ESCAPE_QUOTES @ONLY)
        file(COPY ${CMAKE_CURRENT_BINARY_DIR}/contrib/notarize.py DESTINATION ${PROJECT_BINARY_DIR} FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
        add_custom_target(notarize ./notarize.py)
    else()
        message(WARNING "Not enable 'notarization' target: signing is enabled but notarization info not provided. Create ~/.notarization.cmake or set cmake parameters directly")
    endif()
endif()
