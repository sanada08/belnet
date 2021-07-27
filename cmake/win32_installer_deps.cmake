if(NOT GUI_ZIP_URL)
  set(GUI_ZIP_URL "https://oxen.rocks/beldex-coin/beldex-network-control-panel/belnet-gui-windows-32bit-v0.3.8.zip")
  set(GUI_ZIP_HASH_OPTS EXPECTED_HASH SHA256=60c2b738cf997e5684f307e5222498fd09143d495a932924105a49bf59ded8bb)
endif()

set(TUNTAP_URL "https://build.openvpn.net/downloads/releases/latest/tap-windows-latest-stable.exe")
set(TUNTAP_EXE "${CMAKE_BINARY_DIR}/tuntap-install.exe")
set(BOOTSTRAP_URL "https://seed.belnet.org/belnet.signed")
set(BOOTSTRAP_FILE "${CMAKE_BINARY_DIR}/bootstrap.signed")

file(DOWNLOAD
    ${TUNTAP_URL}
    ${TUNTAP_EXE})

file(DOWNLOAD
    ${BOOTSTRAP_URL}
    ${BOOTSTRAP_FILE})

file(DOWNLOAD
    ${GUI_ZIP_URL}
    ${CMAKE_BINARY_DIR}/belnet-gui.zip
    ${GUI_ZIP_HASH_OPTS})

execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_BINARY_DIR}/belnet-gui.zip
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

install(DIRECTORY ${CMAKE_BINARY_DIR}/gui DESTINATION share COMPONENT gui)
install(PROGRAMS ${TUNTAP_EXE} DESTINATION bin COMPONENT tuntap)
install(FILES ${BOOTSTRAP_FILE} DESTINATION share COMPONENT belnet)

set(CPACK_PACKAGE_INSTALL_DIRECTORY "Belnet")
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/win32-setup/belnet.ico")
set(CPACK_NSIS_DEFINES "RequestExecutionLevel admin")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "ifFileExists $INSTDIR\\\\bin\\\\tuntap-install.exe 0 +2\\nExecWait '$INSTDIR\\\\bin\\\\tuntap-install.exe /S'\\nExecWait '$INSTDIR\\\\bin\\\\belnet.exe --install'\\nExecWait 'sc failure belnet reset= 60 actions= restart/1000'\\nExecWait '$INSTDIR\\\\bin\\\\belnet.exe -g C:\\\\ProgramData\\\\belnet\\\\belnet.ini'\\nCopyFiles '$INSTDIR\\\\share\\\\bootstrap.signed' C:\\\\ProgramData\\\\belnet\\\\bootstrap.signed\\n")
set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "ExecWait 'net stop belnet'\\nExecWait 'taskkill /f /t /im belnet-gui.exe'\\nExecWait '$INSTDIR\\\\bin\\\\belnet.exe --remove'\\nRMDir /r /REBOOTOK C:\\\\ProgramData\\\\belnet")
set(CPACK_NSIS_CREATE_ICONS_EXTRA
    "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Belnet.lnk' '$INSTDIR\\\\share\\\\gui\\\\belnet-gui.exe'"
)
set(CPACK_NSIS_DELETE_ICONS_EXTRA
    "Delete '$SMPROGRAMS\\\\$START_MENU\\\\Belnet.lnk'"
)

get_cmake_property(CPACK_COMPONENTS_ALL COMPONENTS)
list(REMOVE_ITEM CPACK_COMPONENTS_ALL "Unspecified")
