CMAKE_MINIMUM_REQUIRED(VERSION 3.12) # cmake最低版本要求

PROJECT(SudokuSolver VERSION 1.3.2)    # 工程名 CppTemplate
set(PRE_RELEASE "alpha.4") # 是否为预发布版本
# 获取 git commit id 和 commit 时间
find_package(Git QUIET)
if(GIT_FOUND)
  message("git found: ${GIT_EXECUTABLE}")
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    message("git folder found: ${CMAKE_CURRENT_SOURCE_DIR}/.git")
    execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "GIT_COMMIT_ID"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd --date=short
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "GIT_COMMIT_DATE"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    message("git commit id: ${GIT_COMMIT_ID}")
    message("git commit date: ${GIT_COMMIT_DATE}")
  endif()
endif()


configure_file(SudokuSolverConfig.h.in SudokuSolverConfig.h) # 生成配置文件

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # 添加c++11标准支持

SET(CMAKE_BUILD_TYPE "Release")  # Debug模式 选项: Release Debug MinSizeRel RelWithDebInfo

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  # debug模式下 gdb相关选项
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") # release模式下 gdb相关选项

# set(CMAKE_VERBOSE_MAKEFILE ON) # 开启调试 出现问题时开启

# enable_testing() # 打开测试

add_definitions(-DDEBUG) # 相当于代码中 #define DEBUG

# add_subdirectory(test) # 添加test子目录

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin") # 可执行文件输出目录

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include") # 头文件包含目录

# 这段代码可以区分操作系统
MESSAGE("Identifying the OS...")
if(WIN32)
  MESSAGE("This is Windows.")
  exec_program("cmd" ${PROJECT_SOURCE_DIR} ARGS "/c chcp" OUTPUT_VARIABLE CHCP_OUT)
  string(REGEX MATCH "[0-9]+" CODE_PAGE ${CHCP_OUT})
  message("Active code page: ${CODE_PAGE}")
  if(CODE_PAGE EQUAL 936 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    MESSAGE("This is Windows Chinese. Change the charset to GBK.")
    add_compile_options("-fexec-charset=GBK")
  endif()
elseif(APPLE)
  MESSAGE("This is MacOS.")
elseif(UNIX)
  MESSAGE("This is Linux.")
endif()
# 这段代码可以区分操作系统

AUX_SOURCE_DIRECTORY(src DIR_SRCS) # 添加源代码文件夹, 自动扫描所有文件
AUX_SOURCE_DIRECTORY(assets DIR_SRCS) # 添加资源文件夹, 自动扫描所有文件
add_executable(sudoku_solver  # 输出名为sudoku_solver的可执行文件
   ${DIR_SRCS}
)
# 也可以这么写
# add_executable(chess  # 输出名为chess的可执行文件
#    ./src/main.cpp
# )
# 添加该文件夹以包括config文件
target_include_directories(sudoku_solver PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
