add_executable(start-stop
        main.c
)

target_link_libraries(start-stop pico_stdlib freertos)
pico_add_extra_outputs(start-stop)
