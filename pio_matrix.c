#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

// Arquivo .pio
#include "pio_matrix.pio.h"

// Número de LEDs
#define NUM_PIXELS 25

// Pino de saída
#define OUT_PIN 7

// Configuração teclado matricial
uint8_t linhas[4] = {16, 17, 18, 8};
uint8_t colunas[4] = {19, 20, 4, 9};
uint8_t n_lin = 4, n_col = 4;

char teclas[4][4] = {{'1', '2', '3', 'A'},
                     {'4', '5', '6', 'B'},
                     {'7', '8', '9', 'C'},
                     {'*', '0', '#', 'D'}};

void inicializa_teclado() {
    for (uint8_t i = 0; i < n_lin; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 1);
    }

    for (uint8_t i = 0; i < n_col; i++) {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]);
    }
}

char teclado() {
    for (uint8_t i = 0; i < n_lin; i++) {
        gpio_put(linhas[i], 0);
        for (uint8_t j = 0; j < n_col; j++) {
            if (!gpio_get(colunas[j])) {
                char caractere = teclas[i][j];
                while (!gpio_get(colunas[j])) {
                    sleep_ms(10);
                }
                gpio_put(linhas[i], 1);
                return caractere;
            }
        }
        gpio_put(linhas[i], 1);
    }
    return ' '; // Retorna espaço caso nenhuma tecla seja pressionada
}


// Desenhos

double desenhopadrao[25] = {0.1, 0.1, 0.1, 0.1, 0.1,
                           0.0, 0.0, 0.0, 0.0, 0.1, 
                           0.1, 0.0, 0.0, 0.0, 0.1,
                           0.0, 0.0, 0.0, 0.0, 0.1,
                           0.1, 0.1, 0.1, 0.1, 0.1};

//vetor para criar imagem na matriz de led - A
double desenhoA[25] = {0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0, 
                        0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0};

//vetor para criar imagem na matriz de led - B
double desenhoB[25] = {1.0, 1.0, 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0, 1.0, 1.0, 
                      1.0, 1.0, 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0, 1.0, 1.0,
                      1.0, 1.0, 1.0, 1.0, 1.0};

//vetor para criar imagem na matriz de led - C
double desenhoC[25] = {0.8, 0.8, 0.8, 0.8, 0.8,
                       0.8, 0.8, 0.8, 0.8, 0.8, 
                       0.8, 0.8, 0.8, 0.8, 0.8,
                       0.8, 0.8, 0.8, 0.8, 0.8,
                       0.8, 0.8, 0.8, 0.8, 0.8};

//vetor para criar imagem na matriz de led - D
double desenhoD[25] = {0.5, 0.5, 0.5, 0.5, 0.5,
                       0.5, 0.5, 0.5, 0.5, 0.5, 
                       0.5, 0.5, 0.5, 0.5, 0.5,
                       0.5, 0.5, 0.5, 0.5, 0.5, 
                       0.5, 0.5, 0.5, 0.5, 0.5,};

//vetor para criar imagem na matriz de led - #
double desenho20[25] = {0.2, 0.2, 0.2, 0.2, 0.2,
                        0.2, 0.2, 0.2, 0.2, 0.2, 
                        0.2, 0.2, 0.2, 0.2, 0.2,
                        0.2, 0.2, 0.2, 0.2, 0.2,
                        0.2, 0.2, 0.2, 0.2, 0.2};


//Configuração intensidade dos LEDs
uint32_t matrix_rgb(double brilho, double r, double g, double b) {
    unsigned char R = (unsigned char)(r * brilho * 255);
    unsigned char G = (unsigned char)(g * brilho * 255);
    unsigned char B = (unsigned char)(b * brilho * 255);
    return (G << 24) | (R << 16) | (B << 8);
}


//Funções para controle dos LEDs
void desenho_on(double *desenho, PIO pio, uint sm, double r, double g, double b) {  //Ao ligar o Raspberry
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(desenho[24 - i], 0, 0, b);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

void desenho_pioA(double *desenho, PIO pio, uint sm, double r, double g, double b) { //A OFF
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(desenho[24 - i], r, g, b);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

void desenho_pioB(double *desenho, PIO pio, uint sm, double r, double g, double b) {  //B azul
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(desenho[24 - i], 0, 0, b);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

void desenho_pioC(double *desenho, PIO pio, uint sm, double r, double g, double b) {  //C vermelho
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(desenho[24 - i], r, 0, 0);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

void desenho_pioD(double *desenho, PIO pio, uint sm, double r, double g, double b) {  //D verde , 50%
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(desenho[24 - i], 0, g, 0);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

void desenho_pio20(double *desenho, PIO pio, uint sm, double r, double g, double b) {  // # branca, 20%
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(desenho[24 - i], r, g, b);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}



//Função para reboot
void reboot_device() {
    reset_usb_boot(0, 0);
}



int main() {
    PIO pio = pio0;
    bool ok;
    double r = 1.0, g = 1.0, b = 1.0; // Cores padrão

    ok = set_sys_clock_khz(133000, false);
    stdio_init_all();
    inicializa_teclado();

    printf("Iniciando a transmissão PIO\n");
    if (ok) printf("Clock set to %ld Hz\n", clock_get_hz(clk_sys));

    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);
    desenho_on(desenhopadrao, pio, sm, r,g,b);

    while (true) {
        char tecla = teclado();
        switch (tecla) {

            case 'A': //Todos os LEDs deverão ser desligados.
                desenho_pioA(desenhoA, pio, sm, r, g, b);
                break;
            case 'B': //Todos os LEDs deverão ser ligados na cor azul, no nível de intensidade de 100%.
                desenho_pioB(desenhoB, pio, sm, r, g, b);
                break;

            case 'C': //Todos os LEDs deverão ser ligados na cor vermelha, no nível de intensidade de 80%.
                desenho_pioC(desenhoC, pio, sm, r, g, b);
                break;

            case 'D': //todos os LEDs deverão serligados na cor verde, no nível de intensidade de 50%
                desenho_pioD(desenhoD, pio, sm, r, g, b);
                break;

            case '#': //Todos os LEDs deverão ser ligados na cor branca, no nível de intensidade de 20%.
                desenho_pio20(desenho20, pio, sm, 1.0, 1.0, 1.0); 
                break;

            case '*':
                reboot_device();
                break;

            case '1':  //GIL
                
                break;

            case '2':
                break;

            case '3':
                break;

            case '4':
                break;

            case '5':
                break;

            case '6':
                break;

            case '7':
                break;

            case '8':
                break;

            case '9':
                break;

            case '0'://buzzer

            break;

            default:
            break;
        }

        sleep_ms(300);
        
    }
}
