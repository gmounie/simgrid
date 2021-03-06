if(DEFINED ENV{FC})
  set (GFORTRAN_EXE $ENV{FC})
else()
  find_program(GFORTRAN_EXE
    NAME gfortran
    PATH_SUFFIXES bin/
    PATHS
    /opt
    /opt/local
    /opt/csw
    /sw
    /usr
  )
endif()

mark_as_advanced(GFORTRAN_EXE)

message(STATUS "Looking for bin gfortran")
set(SMPI_FORTRAN 0)
if(NOT WIN32 AND NOT APPLE)
  if(GFORTRAN_EXE)
    message(STATUS "Found gfortran: ${GFORTRAN_EXE}")
    set(SMPI_FORTRAN 1)
  else()
    message(STATUS "Looking for bin gfortran - not found")
  endif()
else()
  message(STATUS "SMPI Fortran is disabled on Windows and MacOS platforms. Please contact the SimGrid team if you need it.")
endif()

if(NOT SMPI_FORTRAN)
  message("-- Fortran support for smpi is disabled.")
endif()
