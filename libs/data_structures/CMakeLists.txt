add_library(data_structures
        ordered_array_set/ordered_array_set.c
        unordered_array_set/unordered_array_set.c
        vector/vector.c
        vectorVoid/vectorVoid.c
        matrix/matrix.c
)

target_link_libraries(data_structures algorithms)