# CMakeList.txt: CGM 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("cgm")

# 1. 递归收集所有 .cpp .hpp文件（包括子目录）
file(GLOB_RECURSE CGM_IMPL_SOURCES
  "${CMAKE_SOURCE_DIR}/src/**/*.hpp"  # 模板成员函数的实现（如vector_impl.hpp）
  "${CMAKE_SOURCE_DIR}/src/**/*.cpp"  # 若有非模板辅助函数，可保留
)

# 定义静态库（包含预实例化的模板实现）
add_library(cgm STATIC ${CGM_IMPL_SOURCES})

# 暴露公共头文件目录（客户端必须包含此目录）
target_include_directories(cgm PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cgm PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(tests)
