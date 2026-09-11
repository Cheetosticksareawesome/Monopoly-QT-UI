# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\UIApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\UIApp_autogen.dir\\ParseCache.txt"
  "UIApp_autogen"
  )
endif()
