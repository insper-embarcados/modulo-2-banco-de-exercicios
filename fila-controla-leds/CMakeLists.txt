add_executable(fila-controla-leds
        main.c
)

target_link_libraries(fila-controla-leds pico_stdlib freertos)
pico_add_extra_outputs(fila-controla-leds)
