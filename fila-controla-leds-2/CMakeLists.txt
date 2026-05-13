add_executable(fila-controla-leds-2
        main.c
)

target_link_libraries(fila-controla-leds-2 pico_stdlib freertos)
pico_add_extra_outputs(fila-controla-leds-2)
