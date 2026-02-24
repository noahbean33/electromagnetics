# same options for all examples
function(buildexample TARGET)
    custom_add_executable_from_dir(${TARGET} .)

    target_link_libraries(${TARGET} PRIVATE m)
    ConfigurePETSC(${TARGET})
    ConfigureMPI(${TARGET})

    target_compile_features(${TARGET} PRIVATE c_std_11)

    if ( CMAKE_C_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
        target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
    endif()
    if ( CMAKE_C_COMPILER_ID MATCHES "Clang")
        target_compile_options(${TARGET} PRIVATE -Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn)
    endif()
endfunction(buildexample)

option(COMPILE_3_5 "Compile ch3.5" ON)
if (COMPILE_3_5)
add_subdirectory(ch3.5)
endif()

option(COMPILE_3_5-2 "Compile ch3.5-2" ON)
if (COMPILE_3_5-2)
add_subdirectory(ch3.5-2)
endif()

option(COMPILE_3_8 "Compile ch3.8" ON)
if (COMPILE_3_8)
add_subdirectory(ch3.8)
endif()

option(COMPILE_3_9 "Compile ch3.9" ON)
if (COMPILE_3_9)
add_subdirectory(ch3.9)
endif()

option(COMPILE_3_10 "Compile ch3.10" ON)
if (COMPILE_3_10)
add_subdirectory(ch3.10)
endif()

option(COMPILE_3_11 "Compile ch3.11" ON)
if (COMPILE_3_11)
add_subdirectory(ch3.11)
endif()

option(COMPILE_3_12 "Compile ch3.12" ON)
if (COMPILE_3_12)
add_subdirectory(ch3.12)
endif()

option(COMPILE_3_12-2 "Compile ch3.12-2" ON)
if (COMPILE_3_12-2)
add_subdirectory(ch3.12-2)
endif()

# option(COMPILE_4_5 "Compile ch4.5" ON)
# if (COMPILE_4_5)
# add_subdirectory(ch4.5)
# endif()
