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
#include "animacaoIsaque.h"
#include "led_matrix.h"
#include "reboot.h"
#include "led_control.h"
#include "teclado.h"
#include "buzzer.h"

// Número de LEDs
#define NUM_PIXELS 25

// Pino de saída
#define OUT_PIN 7

//Pino de saída e frequência do buzzer
#define BUZZER 10
#define FREQUECY 1000

// Tempo do frame
#define FPS 200


uint32_t matrix_rgb_conversor(double b, double r, double g) {
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

int main() {
    inicializa_teclado();
    setup_led_matrix();
    setup_buzzer(BUZZER,FREQUECY);

    float r = 1.0, g = 1.0, b = 1.0; // Inicialização das variáveis RGB
    // Configurando a matriz de leds

    while (true) {
        char tecla = teclado();
        switch (tecla) {
            case 'A': // Todos os LEDs deverão ser desligados. ok
                desenho_pioA(desenhoA, pio, sm, r, g, b);

                break;

            case 'B': // Todos os LEDs deverão ser ligados na cor azul, no nível de intensidade de 100%.
                desenho_pioB(desenhoB, pio, sm, r, g, b); //nao executa
                break;

            case 'C': // Todos os LEDs deverão ser ligados na cor vermelha, no nível de intensidade de 80%.
                desenho_pioC(desenhoC, pio, sm, r, g, b); 
                break;

            case 'D': // Todos os LEDs deverão ser ligados na cor verde, no nível de intensidade de 50%
                desenho_pioD(desenhoD, pio, sm, r, g, b); //nao executa
                break;

            case '#': // Todos os LEDs deverão ser ligados na cor branca, no nível de intensidade de 20%.
                desenho_pio20(desenho20, pio, sm, 1.0, 1.0, 1.0); //ok
                break;

            case '*':
                reboot_device();
                break;

           case '1':
                start_buzzer(BUZZER,FREQUECY);
                animacao(1,17,xadrez,sm);
                stop_buzzer(BUZZER);
                printf("1\n");
                break;

            case '2':   //Arthur
                animacao(2,9,arthur,sm); //ok
                break;

            case '3':   //Pablo
                animacao(3, 5, pablo, sm); //ok
                break;

            case '4': 
                printf("4\n");
                break;

            case '5':
                animacao(2,10,andre,sm);
                break;

            case '6':  //Daniel Alencar
                //animate(movie, frames, 200);  
                break;

            case '7': // Julio
                printf("7\n");
                animacao(3,5,julio,sm); 
                break;

            case '8':
                animacao(2,15,daniel,sm); //Daniel
                break;

            case '9':
                animacao(2,7,gil,sm); //Gil
                break;

            case '0':
                executar_a(pio, sm); //Isaque   
                break;

            default:
                break;
        }
       
        sleep_ms(500);
    }
}
