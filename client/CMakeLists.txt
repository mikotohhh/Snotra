#
# Dependencies
#
find_package(Threads)

#
# Sources
#
set(SOURCES
    client.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})


#
# Target
#
add_executable(client ${SOURCES})
target_link_libraries(client
    PRIVATE
        snotra_proto
)
