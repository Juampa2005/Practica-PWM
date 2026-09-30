# Control de motor paso a paso con Raspberry Pi Pico

## Integrantes

* **Juan Pablo Ruiz Gil**
* **Marco Uriel Castañeda Ávila**
* **Eduardo Gabriel Prado Granados**

## Descripción

Este proyecto consiste en el control de un **motor paso a paso mediante una Raspberry Pi Pico**, utilizando un puente **L298N**, un controlador para el motor paso a paso y diferentes elementos de entrada.

El sistema permite al usuario:

* Girar el motor hacia adelante.
* Girar el motor hacia atrás.
* Detener el motor.
* Controlar la velocidad mediante un potenciómetro.

El circuito fue desarrollado y simulado utilizando **Wokwi**.

---

## Componentes

El proyecto utiliza los siguientes componentes:

* Raspberry Pi Pico
* Puente H L298N
* Controlador `stepper-esc`
* Motor paso a paso
* Botón FORWARD
* Botón REVERSE
* Botón STOP
* Potenciómetro

---

# Botones de control

El sistema cuenta con tres botones para controlar el movimiento del motor.

### FORWARD

El botón FORWARD está conectado al:

```text
GP14
```

Cuando se presiona, el programa recibe la señal correspondiente y establece el movimiento del motor hacia adelante.

```text
GP14 → FORWARD
```

---

### REVERSE

El botón REVERSE está conectado al:

```text
GP15
```

Al presionarlo, se cambia el sentido de giro del motor.

```text
GP15 → REVERSE
```

---

### STOP

El botón STOP está conectado al:

```text
GP16
```

Al presionarlo, el sistema detiene el movimiento del motor.

```text
GP16 → STOP
```

Los tres botones tienen su otra terminal conectada a **GND**.

---

# Control de velocidad

Para controlar la velocidad se utiliza un **potenciómetro**.

El potenciómetro está conectado de la siguiente manera:

| Potenciómetro | Raspberry Pi Pico |
| ------------- | ----------------- |
| SIG           | GP26              |
| VCC           | 3V3               |
| GND           | GND               |

El pin **GP26** funciona como una entrada analógica.

Al girar el potenciómetro, cambia el valor analógico leído por la Raspberry Pi Pico. El programa puede utilizar este valor para determinar la velocidad de giro del motor.

En otras palabras:

```text
Potenciómetro
      ↓
   GP26 ADC
      ↓
Lectura analógica
      ↓
Conversión a velocidad
      ↓
Motor
```

---

# ¿Cómo funciona el sistema?

El funcionamiento general puede dividirse en tres partes:

```text
             ┌─────────────────┐
             │ Raspberry Pi    │
             │     Pico        │
             └────────┬────────┘
                      │
          ┌───────────┼───────────┐
          │           │           │
          ↓           ↓           ↓
       FORWARD     REVERSE       STOP
        GP14        GP15         GP16
                      │
                      │
                 ┌────▼─────┐
                 │  L298N   │
                 └────┬─────┘
                      │
                      ↓
                Stepper ESC
                      │
                      ↓
                Motor paso a paso
                      
       Potenciómetro → GP26
              ↓
       Control de velocidad
```

---

## Secuencia de funcionamiento

### 1. Seleccionar dirección

El usuario puede presionar uno de los botones:

```text
FORWARD
REVERSE
STOP
```

Dependiendo del botón presionado, la Raspberry Pi Pico determina qué acción debe realizar.

### 2. Ajustar velocidad

El usuario puede girar el potenciómetro.

La Raspberry Pi Pico lee el valor de **GP26** mediante su convertidor analógico-digital (ADC).

Este valor puede convertirse a un nivel de velocidad para controlar el motor.

### 3. Movimiento

Cuando se selecciona FORWARD o REVERSE, la Raspberry Pi Pico genera las señales necesarias para que el motor se mueva en el sentido seleccionado.

El L298N funciona como etapa de control de las señales que llegan al controlador del motor.

### 4. Detener

Al presionar el botón STOP, el programa detiene el movimiento del motor.

---

# Pines utilizados

| Pin  | Elemento            | Función           |
| ---- | ------------------- | ----------------- |
| GP2  | L298N IN1           | Dirección         |
| GP3  | L298N IN2           | Dirección         |
| GP4  | L298N ENA           | PWM               |
| GP14 | Botón FORWARD       | Adelante          |
| GP15 | Botón REVERSE       | Reversa           |
| GP16 | Botón STOP          | Detener           |
| GP26 | Potenciómetro       | Lectura analógica |
| 3V3  | Potenciómetro / ESC | Alimentación      |
| GND  | Circuito            | Tierra común      |

---

# PWM

El pin **GP4** se utiliza para generar una señal PWM.

PWM significa **Pulse Width Modulation** o modulación por ancho de pulso.

Esta técnica permite controlar el nivel de energía promedio de una señal mediante el porcentaje de tiempo que permanece activa.

Por ejemplo:

```text
0 %   → Sin señal
25 %  → Señal baja
50 %  → Señal media
75 %  → Señal alta
100 % → Señal máxima
```

En este proyecto, el PWM se utiliza como parte del control de velocidad.

---

# Lectura del potenciómetro

El potenciómetro está conectado al ADC del Raspberry Pi Pico mediante **GP26**.

Su funcionamiento es:

```text
Girar a la izquierda
        ↓
Valor ADC menor
        ↓
Velocidad menor


Girar a la derecha
        ↓
Valor ADC mayor
        ↓
Velocidad mayor
```

Esto permite que el usuario tenga un control físico de la velocidad del motor.

---

# Lógica del programa

De manera general, el programa realiza las siguientes operaciones:

```text
INICIO
  ↓
Configurar GPIO
  ↓
Configurar PWM
  ↓
Configurar ADC
  ↓
Leer botones
  ↓
Leer potenciómetro
  ↓
¿FORWARD?
  ├── Sí → Motor hacia adelante
  │
  └── No
       ↓
    ¿REVERSE?
       ├── Sí → Motor hacia atrás
       │
       └── No
            ↓
         ¿STOP?
            └── Sí → Detener motor
  ↓
Leer nuevamente
  ↓
REPETIR
```

El programa permanece ejecutándose continuamente para responder a las acciones del usuario.

---

# Participación de los integrantes

## Juan Pablo Ruiz Gil

Participó en el desarrollo de la programación del sistema, incluyendo la configuración de los GPIO, el control de dirección del motor, el uso del PWM y la lectura del potenciómetro.

También participó en la integración del código con el circuito y en las pruebas de funcionamiento.

## Marco Uriel Castañeda Ávila

Participó en el diseño y armado del circuito en Wokwi, realizando las conexiones entre la Raspberry Pi Pico, el L298N, el controlador del motor, los botones y el potenciómetro.

También colaboró en las pruebas del sistema y en la verificación del funcionamiento de los controles.


### FORWARD

Hace que el motor gire hacia adelante.

### REVERSE

Hace que el motor gire en sentido contrario.

### STOP

Detiene el motor.

### POTENCIÓMETRO

Permite modificar la velocidad del motor.

El sistema combina **entradas digitales**, mediante los botones, y una **entrada analógica**, mediante el potenciómetro, para controlar un motor paso a paso utilizando la Raspberry Pi Pico.

---

# Tecnologías utilizadas

* C++
* Raspberry Pi Pico
* Wokwi
* Raspberry Pi Pico SDK
* GPIO
* PWM
* ADC
* L298N
* Motor paso a paso
