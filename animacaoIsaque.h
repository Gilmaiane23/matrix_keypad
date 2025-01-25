#ifndef ISQUEANIMACAO_H
#define ISQUEANIMACAO_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pio_matrix.pio.h"

// Configurações gerais
#define NUM_PIXELS 25
#define OUT_PIN 7

// Estrutura para configurar cores RGB
typedef struct
{
    uint8_t r, g, b; // Valores RGB (0-255)
} Cor;

// Configuração das cores
const Cor cores[] = {
    {0, 255, 0}, // Verde
    {0, 0, 255}, // Azul
};

double frameA[NUM_PIXELS] = {0.0, 0.0, 0.0, 0.0, 0.0,
                              0.0, 1.8, 1.8, 1.8, 0.0,
                              1.8, 0.0, 0.0, 0.0, 1.8,
                              0.0, 1.8, 0.0, 1.8, 0.0,
                              0.0, 0.0, 0.0, 0.0, 0.0};

double frameB[NUM_PIXELS] = {0.0, 0.0, 0.0, 0.0, 0.0,
                              0.0, 1.8, 1.8, 1.8, 0.0,
                              1.8, 0.0, 0.0, 0.0, 1.8,
                              0.0, 1.1, 0.0, 1.8, 0.0,
                              0.0, 0.0, 0.0, 0.0, 0.};

double frameC[NUM_PIXELS] = {0.0, 0.0, 0.0, 0.0, 0.0,
                              0.0, 1.8, 1.8, 1.8, 0.0,
                              1.8, 0.0, 0.0, 0.0, 1.8,
                              0.0, 1.8, 0.0, 1.8, 0.0,
                              0.0, 0.0, 0.0, 0.0, 0.};

double frameD[NUM_PIXELS] = {0.0, 0.0, 0.0, 0.0, 0.0,
                              0.0, 1.8, 1.8, 1.8, 0.0,
                              1.8, 0.0, 0.0, 0.0, 1.8,
                              0.0, 1.1, 0.0, 1.8, 0.0,
                              0.0, 0.0, 0.0, 0.0, 0.};

double frameE[NUM_PIXELS] = {0.0, 0.0, 0.0, 0.0, 0.0,
                               0.0, 1.8, 1.8, 1.8, 0.0,
                               1.8, 0.0, 0.0, 0.0, 1.8,
                               0.0, 1.8, 0.0, 1.8, 0.0,
                               0.0, 0.0, 0.0, 0.0, 0.};

// Função para converter brilho e cor em um valor 32 bits
uint32_t calcular_rgb(uint8_t r, uint8_t g, uint8_t b, double brilho)
{
    uint8_t R = (uint8_t)(r * brilho);
    uint8_t G = (uint8_t)(g * brilho);
    uint8_t B = (uint8_t)(b * brilho);
    return (G << 24) | (R << 16) | (B << 8);
}

// Função para aplicar um padrão específico na matriz de LEDs
void aplicar_padrao(PIO pio, uint sm, const Cor *cor, const double *padrao)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        uint32_t valor_led = calcular_rgb(cor->r, cor->g, cor->b, padrao[i]);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Função de animação principal
void executar_animacao(PIO pio, uint sm)
{
    const double *padroes[] = { frameA, frameB, frameC, frameD, frameE};
    int num_padroes = sizeof(padroes) / sizeof(padroes[0]);

    for (int i = 0; i < num_padroes; i++)
    {
        for (int j = 0; j < sizeof(cores) / sizeof(cores[0]); j++)
        {
            aplicar_padrao(pio, sm, &cores[j], padroes[i]);
            sleep_ms(200); // Exibe cada padrão com uma cor por 500ms
        }
    }

    // Apagar os LEDs ao final da animação
    aplicar_padrao(pio, sm, &(Cor){0, 0, 0}, frameA); // Define cor preta
}

#endif 
