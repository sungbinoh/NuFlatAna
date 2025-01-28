add_executable(run_cohpiana run_cohpiana.C)

target_link_libraries(run_cohpiana
 PRIVATE
  NuFlatAna
  ${ROOT_LIBRARIES}
)
target_include_directories(
  run_cohpiana PRIVATE 
  ${CMAKE_SOURCE_DIR}
)

install(TARGETS run_cohpiana )

add_custom_command(
  TARGET run_cohpiana
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:run_cohpiana> ${CMAKE_SOURCE_DIR}
  COMMENT "Copying run_cohpiana to the main directory"
)
