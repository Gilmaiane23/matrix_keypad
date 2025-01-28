#include "led_control.h"
#include "pico/stdlib.h"

// Configuração da intensidade dos LEDs
uint32_t matrix_rgb(double brilho, double r, double g, double b) {
    unsigned char R = (unsigned char)(r * brilho * 255);
    unsigned char G = (unsigned char)(g * brilho * 255);
    unsigned char B = (unsigned char)(b * brilho * 255);
    return (G << 24) | (R << 16) | (B << 8);
}

void desenho_pio(double *desenho, PIO pio, uint sm, double r, double g, double b) {
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(desenho[24 - i], r, g, b);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

uint8_t obter_index(uint8_t i) {
    uint8_t x = i % 5;  // Coluna
    uint8_t y = i / 5;  // Linha
    return (y % 2 == 0) ? (y * 5 + x) : (y * 5 + (4 - x));
}

void anima(uint8_t num_frames, uint32_t desenho[num_frames][NUM_PIXELS], uint sm) {
    for (uint8_t i = 0; i < num_frames; i++) {
        for (uint8_t j = 0; j < NUM_PIXELS; j++) {
            uint8_t pos = obter_index(j);
            uint32_t valor_led = desenho[i][24 - pos];
            pio_sm_put_blocking(pio0, sm, valor_led);
        }
        sleep_ms(200);
    }
}

