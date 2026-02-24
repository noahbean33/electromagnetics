# Locate PETSc include paths and libraries
# PETSc can be found at https://gitlab.com/petsc/petsc

# This module defines
# PETSC_INCLUDE_DIRS, where to find petsc.h, etc.
# PETSC_LIBRARIES, the libraries to link against to use petsc.
# PETSC_FOUND, If false, don't try to use petsc.

function(ConfigurePETSC TARGET)
  message(STATUS "Looking for PETSc")

  pkg_check_modules(PETSC REQUIRED petsc)

  TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE ${PETSC_INCLUDEDIR})
  TARGET_LINK_LIBRARIES(${TARGET} PRIVATE ${PETSC_LIBRARIES})
  TARGET_COMPILE_OPTIONS(${TARGET} PRIVATE ${PETSC_CFLAGS})
  TARGET_LINK_OPTIONS(${TARGET} PRIVATE ${PETSC_LDFLAGS})

endfunction(ConfigurePETSC)
