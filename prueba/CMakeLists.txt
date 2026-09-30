cmake_minimum_required(VERSION 3.13)

# 1. Importar el SDK de Pico (debe apuntar al archivo .cmake correcto)
include(pico_sdk_import.cmake)

project(mi_proyecto C CXX ASM)

# 2. Inicializar el SDK de Pico (¡Esto activa los comandos como pico_enable_stdio_usb!)
pico_sdk_init()

add_executable(mi_proyecto
    main.c
)

# 3. Vincular tu proyecto con la librería estándar de Pico
target_link_libraries(mi_proyecto pico_stdlib)

# 4. Habilitar la salida USB (Ahora CMake ya conocerá el comando)
pico_enable_stdio_usb(mi_proyecto 1)
pico_enable_stdio_uart(mi_proyecto 0)