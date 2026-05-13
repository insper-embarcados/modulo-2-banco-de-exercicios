add_executable(contando-apertos
        main.c
)

target_link_libraries(contando-apertos pico_stdlib freertos)
pico_add_extra_outputs(contando-apertos)
