# Dino Game en Arduino con LCD 16x2 y Buzzer

Este proyecto implementa el clásico **juego del Dinosaurio de Chrome** en una pantalla **LCD 16x2**, controlado por un **Arduino Mega (ATmega2560)**.  
El juego incluye:

- Animación del Dino caminando.
- Obstáculos aleatorios (ramas y aves).
- Detección de colisiones.
- Sistema de puntaje.
- **Salto automático** mediante un pulsador.
- **Música de fondo** ("Time To Level Up" simplificada).
- Efectos de sonido (salto y *Game Over*).

---

## Vista del Proyecto




---

## Componentes Necesarios

- 1x Arduino Mega 2560 (puede funcionar en Arduino UNO con cambios mínimos).
- 1x Pantalla LCD **16x2** en modo paralelo.
- 1x Buzzer (activo o pasivo).
- 1x Pulsador.
- 1x Potenciómetro de 10kΩ (para el contraste del LCD).
- Resistencias de 220Ω o 330Ω (si el buzzer lo requiere).
- Protoboard y cables de conexión tipo macho-macho.

---

## Conexiones del Hardware

La siguiente tabla resume las conexiones entre el **Arduino Mega 2560**, la pantalla LCD, el buzzer y el pulsador:

| **Componente**        | **Pin en el dispositivo** | **Pin en Arduino Mega** | **Descripción** |
|------------------------|----------------------------|--------------------------|------------------|
| **LCD 16x2**           | RS                        | 7                        | Selección de registros |
|                        | EN                        | 6                        | Enable (habilitación) |
|                        | D4                        | 5                        | Datos (bit 4) |
|                        | D5                        | 4                        | Datos (bit 5) |
|                        | D6                        | 3                        | Datos (bit 6) |
|                        | D7                        | 2                        | Datos (bit 7) |
|                        | VSS                       | GND                      | Tierra |
|                        | VDD                       | +5V                      | Alimentación |
|                        | VO                        | Potenciómetro (10kΩ)     | Ajuste de contraste |
| **Buzzer**             | VCC (+)                   | Pin 11                   | Salida de sonido (tono/melodía) |
|                        | GND (-)                   | GND                      | Tierra |
| **Pulsador (Salto)**   | Terminal 1                | Pin 13                   | Entrada digital para saltar |
|                        | Terminal 2                | GND                      | Tierra (usar resistencia pull-down si es necesario) |
| **Alimentación**       | 5V                        | 5V Arduino               | Fuente de la placa |
|                        | GND                       | GND Arduino              | Tierra común |

---

## Esquema de Conexión


<img width="600" height="600" alt="hardward" src="https://github.com/user-attachments/assets/461d4f36-5f5b-4892-b522-4f8ed4753383" />

