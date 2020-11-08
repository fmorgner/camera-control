set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "avr")

set(CROSS_GCC_PREFIX "avr-")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

find_program(CMAKE_OBJDUMP "${CROSS_GCC_PREFIX}objdump" DOC "Path to ${CROSS_GCC_PREFIX}objdump")
find_program(CMAKE_OBJCOPY "${CROSS_GCC_PREFIX}objcopy" DOC "Path to ${CROSS_GCC_PREFIX}objcopy")
find_program(CMAKE_NM "${CROSS_GCC_PREFIX}nm" DOC "Path to ${CROSS_GCC_PREFIX}nm")
find_program(CMAKE_CXX_COMPILER_RANLIB "${CROSS_GCC_PREFIX}ranlib" DOC "Path to ${CROSS_GCC_PREFIX}ranlib")
find_program(CMAKE_STRIP "${CROSS_GCC_PREFIX}strip" DOC "Path to ${CROSS_GCC_PREFIX}strip")
find_program(CMAKE_LINKER "${CROSS_GCC_PREFIX}ld" DOC "Path to ${CROSS_GCC_PREFIX}ld")
find_program(CMAKE_ASM_COMPILER "${CROSS_GCC_PREFIX}gcc" DOC "Path to ${CROSS_GCC_PREFIX}gcc")
find_program(CMAKE_C_COMPILER "${CROSS_GCC_PREFIX}gcc" DOC "Path to ${CROSS_GCC_PREFIX}gcc")
find_program(CMAKE_CXX_COMPILER_AR "${CROSS_GCC_PREFIX}ar" DOC "Path to ${CROSS_GCC_PREFIX}ar")
find_program(CMAKE_CXX_COMPILER "${CROSS_GCC_PREFIX}g++" DOC "Path to ${CROSS_GCC_PREFIX}g++")

# Base Compiler Flags

set(CMAKE_CXX_FLAGS_INIT
    "-ffunction-sections \
    -fdata-sections"
)

# Base Linker Flags

set(CMAKE_EXE_LINKER_FLAGS_INIT
    "-Wl,--gc-sections"
)