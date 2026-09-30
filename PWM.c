#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// -----------------------------
// Pines del driver
// -----------------------------
#define IN1 2
#define IN2 3
#define ENA 4

// -----------------------------
// Configuración del PWM
// -----------------------------
void setup_pwm()
{
    gpio_set_function(ENA, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(ENA);

    // Frecuencia aproximada de 1000 Hz
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125.0f);
    pwm_config_set_wrap(&config, 999);

    pwm_init(slice_num, &config, true);
}

// -----------------------------
// Control de velocidad
// -----------------------------
void set_speed(int percent)
{

    if (percent < 0)
        percent = 0;

    if (percent > 100)
        percent = 100;

    uint16_t duty = (percent * 999) / 100;

    uint slice_num = pwm_gpio_to_slice_num(ENA);
    uint channel = pwm_gpio_to_channel(ENA);

    pwm_set_chan_level(slice_num, channel, duty);
}

// -----------------------------
// Dirección hacia adelante
// -----------------------------
void forward()
{
    gpio_put(IN1, 1);
    gpio_put(IN2, 0);
}

// -----------------------------
// Dirección hacia atrás
// -----------------------------
void reverse()
{
    gpio_put(IN1, 0);
    gpio_put(IN2, 1);
}

// -----------------------------
// Detener motor
// -----------------------------
void stop_motor()
{

    set_speed(0);

    gpio_put(IN1, 0);
    gpio_put(IN2, 0);
}

// -----------------------------
// Cambio gradual de velocidad
// -----------------------------
void ramp_to(int start, int end, int step = 10, int delay_ms = 100)
{

    // Validar valores
    if (end > 100)
    {
        printf("Te pasaste :(\n");
        end = 100;
    }

    if (start < 0)
    {
        printf("Te falto :(\n");
        start = 0;
    }

    if (end < 0)
    {
        printf("Te pasaste :(\n");
        end = 0;
    }

    if (start > 100)
    {
        printf("Te falto :(\n");
        start = 100;
    }

    // -------------------------
    // Aumentar velocidad
    // -------------------------
    if (start < end)
    {

        for (int speed = start; speed <= end; speed += step)
        {

            set_speed(speed);

            printf("Velocidad: %d %%\n", speed);

            sleep_ms(delay_ms);
        }
    }

    // -------------------------
    // Disminuir velocidad
    // -------------------------
    else
    {

        for (int speed = start; speed >= end; speed -= step)
        {

            set_speed(speed);

            printf("Velocidad: %d %%\n", speed);

            sleep_ms(delay_ms);
        }
    }
}

// -----------------------------
// Programa principal
// -----------------------------
int main()
{

    stdio_init_all();

    // Configurar pines de dirección
    gpio_init(IN1);
    gpio_set_dir(IN1, GPIO_OUT);

    gpio_init(IN2);
    gpio_set_dir(IN2, GPIO_OUT);

    // Configurar PWM
    setup_pwm();

    stop_motor();

    while (true)
    {

        // =========================
        // ADELANTE
        // =========================

        printf("\nFORWARD\n");

        forward();

        printf("Acelerando 0 -> 100 %%\n");

        ramp_to(0, 100, 5, 100);

        sleep_ms(2000);

        printf("Desacelerando 100 -> 0 %%\n");

        ramp_to(100, 0, 5, 100);

        stop_motor();

        sleep_ms(2000);

        // =========================
        // REVERSA
        // =========================

        printf("\nREVERSE\n");

        reverse();

        printf("Acelerando 0 -> 100 %%\n");

        ramp_to(0, 100, 5, 100);

        sleep_ms(2000);

        printf("Desacelerando 100 -> 0 %%\n");

        ramp_to(100, 0, 5, 100);

        stop_motor();

        sleep_ms(2000);
    }

    return 0;
}