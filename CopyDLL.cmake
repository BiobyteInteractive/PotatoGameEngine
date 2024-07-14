file(GLOB_RECURSE DLL_FILES
    "${BINARY_DIR}/_deps/*.dll"
    "${BINARY_DIR}/engine/*.dll"
    "${SOURCE_DIR}/vendor/*.dll"
)

foreach(DLL ${DLL_FILES})
    file(COPY ${DLL} DESTINATION ${DLL_OUTPUT_DIR})
endforeach()
