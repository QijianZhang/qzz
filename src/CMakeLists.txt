aux_source_directory(. SRC)
add_library(qzz ${SRC})
target_link_libraries(qzz cutils)
