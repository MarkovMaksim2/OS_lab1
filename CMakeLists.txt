# CMakeList.txt : CMake project for lab1_new, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("lab1_new")

set(SRC_DIR ./)

link_directories("C:/msys64/mingw64/lib")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")


set(SOURCES
    ${SRC_DIR}/Main.cpp
    ${SRC_DIR}/shell/Shell.cpp
    ${SRC_DIR}/shell/output/Output.cpp
    ${SRC_DIR}/shell/input/Input.cpp
)

set(HEADER_FILES
    ${SRC_DIR}/shell/Shell.hpp
    ${SRC_DIR}/shell/output/Output.hpp
    ${SRC_DIR}/shell/Command.hpp
    ${SRC_DIR}/shell/input/Input.hpp
)

# Add source to this project's executable.
add_executable (lab1 ${SOURCES} ${HEADER_FILES})
target_link_libraries(lab1 PRIVATE C:/msys64/mingw64/lib/libgit2.dll.a)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
