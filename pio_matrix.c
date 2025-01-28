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

#include "animacoes.h"
// Animação Isaque
#include "animacaoIsaque.h"

// Número de LEDs
#define NUM_PIXELS 25

// Pino de saída
#define OUT_PIN 7

// Tempo do frame
#define FPS 200

// Configuração teclado matricial
uint8_t linhas[4] = {16, 17, 18, 28};
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


// Funções para as animações 

uint8_t obter_index(uint8_t i) {
    uint8_t x = i % 5;  // Coluna
    uint8_t y = i / 5;  // Linha
    if (y % 2 == 0) {
        return y * 5 + x;
    } else {
        return y * 5 + (4 - x);
    }
}

//rotina para acionar a matrix de leds - ws2812b

void anima(uint8_t num_frames,uint32_t desenho[num_frames][NUM_PIXELS],uint sm){
    uint32_t valor_led;
    for (uint8_t i = 0; i < num_frames; i++){
        for (uint8_t j = 0; j < NUM_PIXELS; j++) 
        {
            uint8_t pos = obter_index(j);
            valor_led = desenho[i][24-pos] * 5.0;
            pio_sm_put_blocking(pio0, sm, valor_led);
        }
        sleep_ms(FPS);
    }
}

void animacao(uint8_t repeticoes,uint8_t num_frames,uint32_t desenho[num_frames][NUM_PIXELS],uint sm){
    for(uint8_t i=0;i<repeticoes;i++){
        anima(num_frames,desenho,sm);
    }
}

//Função para reboot
void reboot_device() {
    reset_usb_boot(0, 0);
}


// Programa principal
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
                animacao(2,7,gil,sm);
                break;

            case '2':   //Arthur
                animacao(2,9,arthur,sm);
                break;

            case '3':   //Pablo
                animacao(3, 5, pablo, sm);
                break;

            case '4': // Daniel Porto
                animacao(2,15,daniel,sm);
                break;

            case '5':
                animacao(2,10,andre,sm);
                break;

            case '6':
                break;

            case '7': // Julio
                animacao(3,5,julio,sm);
                break;

            case '8':
                break;

            case '9':
                executar_animacao(pio, sm); //Isaque
                break;

            case '0'://buzzer

            break;

            default:
            break;
        }

        sleep_ms(300);
        
    }
}

