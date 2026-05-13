add_executable(contando-apertos-2
        main.c
)

target_link_libraries(contando-apertos-2 pico_stdlib freertos)
pico_add_extra_outputs(contando-apertos-2)
