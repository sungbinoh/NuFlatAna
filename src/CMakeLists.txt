# Specify the source files for the library
set(SOURCES
  AnalyzerCore.C
  FlatTree.C
  FSP.C
  cohpiana.C
)

set(HDRFILES
  AnalyzerCore.h
  FlatTree.h
  FSP.h
  cohpiana.h
)

# Create the shared library
add_library(NuFlatAna SHARED ${SOURCES})

# Specify output directory for the shared library
set_target_properties(NuFlatAna PROPERTIES
  PUBLIC_HEADER "${HDRFILES}"
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(NuFlatAna
PUBLIC
  ${ROOT_LIBRARIES}
  ROOT::MathMore
)

install(TARGETS NuFlatAna
    EXPORT ProjNuFlatAna-targets
    PUBLIC_HEADER DESTINATION include/ COMPONENT Development)
