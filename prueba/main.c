#include "pico/stdlib.h"
#include <stdio.h>

int main()
{

    // LED integrado de la Raspberry Pi Pico
    const uint LED_PIN = 25;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Inicializa USB serial
    stdio_init_all();

    // Esperar un poco para que la PC detecte el USB
    sleep_ms(2000);

    printf("Hola desde la Raspberry Pi Pico!\n");

    while (true)
    {

        gpio_put(LED_PIN, 1);
        printf("LED ENCENDIDO\n");
        sleep_ms(1000);

        gpio_put(LED_PIN, 0);
        printf("LED APAGADO\n");
        sleep_ms(1000);
    }
}