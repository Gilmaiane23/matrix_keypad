#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Configurações da matriz
#define COLUMNS 5
#define ROWS 5
#define NUM_LEDS 25
#define OUT_PIN 7
#define NUM_PIXELS 25

extern uint sm;  // Declaração da variável global, sem inicialização
extern PIO pio;  // Declare como extern para ser definida em outro arquivo

void bin_printf(int num);
double convertDrawingToMatrixIndex(double *desenho, int index);
void draw(double **desenhoRGB);
void animate(double ***movie, uint frames, uint sleep_time);
void desenho_pioA(double *desenho, PIO pio, uint sm, double r, double g, double b);
void desenho_pioB(double *desenho, PIO pio, uint sm, double r, double g, double b);
void desenho_pioC(double *desenho, PIO pio, uint sm, double r, double g, double b);
void desenho_pioD(double *desenho, PIO pio, uint sm, double r, double g, double b);
void desenho_pio20(double *desenho, PIO pio, uint sm, double r, double g, double b);
void executar_a(PIO pio, uint sm);
extern void desenho_on(double *desenho, PIO pio, uint sm, double r, double g, double b);
void animacao(uint8_t repeticoes, uint8_t num_frames, uint32_t desenho[num_frames][NUM_PIXELS], uint sm);
void setup_led_matrix();

extern uint32_t daniel[15][NUM_PIXELS];
extern uint32_t arthur[9][NUM_PIXELS];
extern uint32_t gil[7][NUM_PIXELS];
extern uint32_t julio[5][NUM_PIXELS];
extern uint32_t pablo[5][NUM_PIXELS];
extern uint32_t andre[10][NUM_PIXELS];
extern uint32_t daniel_alencar[8][NUM_PIXELS];
extern uint32_t xadrez[17][NUM_PIXELS];
extern double desenhopadrao[25];
extern double desenhoA[25];
extern double desenhoB[25];
extern double desenhoC[25];
extern double desenhoD[25];
extern double desenho20[25];
extern double frameA[NUM_PIXELS];
extern double frameB[NUM_PIXELS];
extern double frameC[NUM_PIXELS];
extern double frameD[NUM_PIXELS];
extern double frameE[NUM_PIXELS];


#endif // LED_MATRIX_H
