add_subdirectory(data_structures)
add_subdirectory(algorithms)
add_library ( data_structures
        matrix / matrix .c
)

target_link_libraries ( data_structures algorithms )