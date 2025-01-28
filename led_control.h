#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <stdint.h>
#include "hardware/pio.h"

#define NUM_PIXELS 25

uint32_t matrix_rgb(double brilho, double r, double g, double b);
void desenho_pio(double *desenho, PIO pio, uint sm, double r, double g, double b);
uint8_t obter_index(uint8_t i);
void anima(uint8_t num_frames, uint32_t desenho[num_frames][NUM_PIXELS], uint sm);
void animacao(uint8_t repeticoes, uint8_t num_frames, uint32_t desenho[num_frames][NUM_PIXELS], uint sm);

#endif // LED_CONTROL_H
