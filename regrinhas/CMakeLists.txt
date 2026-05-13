add_executable(regrinhas
        main.c
)

target_link_libraries(regrinhas pico_stdlib freertos)
pico_add_extra_outputs(regrinhas)
