set (DOXYFILE_OUTPUT_DIR ${cpuidpp_BINARY_DIR}/doc)

configure_file (${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in
  ${cpuidpp_BINARY_DIR}/Doxyfile @ONLY
)

add_custom_target (doxygen COMMAND $<TARGET_FILE:Doxygen::doxygen>
  COMMENT "Writing documentation to ${DOXYFILE_OUTPUT_DIR}..."
  USES_TERMINAL
  WORKING_DIRECTORY ${cpuidpp_BINARY_DIR}
)

set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES
  ${DOXYFILE_OUTPUT_DIR}
)
