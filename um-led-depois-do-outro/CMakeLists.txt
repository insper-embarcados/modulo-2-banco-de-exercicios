add_executable(um-led-depois-do-outro
        main.c
)

target_link_libraries(um-led-depois-do-outro pico_stdlib freertos)
pico_add_extra_outputs(um-led-depois-do-outro)
