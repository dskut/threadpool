set(SOURCES
    main.cpp
)

add_executable(demo ${SOURCES})
target_link_libraries(demo threadpool)
