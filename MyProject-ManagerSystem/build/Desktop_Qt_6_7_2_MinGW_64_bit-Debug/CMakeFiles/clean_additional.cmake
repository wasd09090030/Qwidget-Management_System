# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MyProject-ManagerSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MyProject-ManagerSystem_autogen.dir\\ParseCache.txt"
  "MyProject-ManagerSystem_autogen"
  )
endif()
