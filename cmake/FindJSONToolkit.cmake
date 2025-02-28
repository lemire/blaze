if(NOT JSONToolkit_FOUND)
  if(BLAZE_INSTALL)
    set(JSONTOOLKIT_INSTALL ON CACHE BOOL "enable JSON Toolkit installation")
  else()
    set(JSONTOOLKIT_INSTALL OFF CACHE BOOL "disable JSON Toolkit installation")
  endif()

  add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/jsontoolkit")
  set(JSONToolkit_FOUND ON)
endif()
