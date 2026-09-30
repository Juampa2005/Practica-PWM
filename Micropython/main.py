
from machine import Pin, PWM
from time import sleep_ms

# Pines del driver
IN1 = Pin(2, Pin.OUT)
IN2 = Pin(3, Pin.OUT)
ENA = PWM(Pin(4))

# Configuración del PWM
ENA.freq(1000)


# -----------------------------
# Control de velocidad
# -----------------------------
def set_speed(percent):
    duty = int(percent * 65535 / 100)
    ENA.duty_u16(duty)


# -----------------------------
# Dirección hacia adelante
# -----------------------------
def forward():
    IN1.value(1)
    IN2.value(0)


# -----------------------------
# Dirección hacia atrás
# -----------------------------
def reverse():
    IN1.value(0)
    IN2.value(1)


# -----------------------------
# Detener motor
# -----------------------------
def stop():
    set_speed(0)
    IN1.value(0)
    IN2.value(0)


# -----------------------------
# Cambio gradual de velocidad
# -----------------------------
def ramp_to(start, end, step=10, delay_ms=100):

    if end > 100:
        print("Te pasaste :(")
        end = 101

    if start < 0:
        print("Te faltó :(")
        start = 0

    if end < 0:
        print("Te pasaste :(")
        end = 0

    if start > 100:
        print("Te faltó :(")
        start = 100

    # Si vamos hacia arriba
    if start < end:
        for speed in range(start, end, step):
            set_speed(speed)
            print("Velocidad:", speed, "%")
            sleep_ms(delay_ms)

    # Si vamos hacia abajo
    else:
        for speed in range(start, end, -step):
            set_speed(speed)
            print("Velocidad:", speed, "%")
            sleep_ms(delay_ms)


# -----------------------------
# Programa principal
# -----------------------------
while True:

    # =========================
    # ADELANTE
    # =========================
    print("FORWARD")
    forward()

    print("Acelerando 0 -> 100 %")
    ramp_to(0, 101, 5, 100)

    sleep_ms(2000)

    print("Desacelerando 100 -> 0 %")
    ramp_to(100, -1, 5, 100)

    stop()
    sleep_ms(2000)

    # =========================
    # REVERSA
    # =========================
    print("REVERSE")
    reverse()

    print("Acelerando 0 -> 100 %")
    ramp_to(0, 101, 5, 100)

    sleep_ms(2000)

    print("Desacelerando 100 -> 0 %")
    ramp_to(100, -1, 5, 100)

    stop()
    sleep_ms(2000)
