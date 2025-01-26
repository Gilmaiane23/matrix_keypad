#include <stdio.h>
#include <stdint.h>

double intensidade=0.1;

uint32_t conversor(unsigned char R, unsigned char G, unsigned char B){
    R*=intensidade;
    G*=intensidade;
    B*=intensidade;

    return (G << 24) | (R << 16) | (B << 8);
}

int main(){

    uint32_t verde,amarelo,azul;

    amarelo=conversor(255,203,0);   //255/203/0
    verde=conversor(0,148,64);      //0/148/64
    azul=conversor(48,38,129);      //48/38/129

    printf("O amarelo: 0x%x\n", amarelo);
    printf("O verde: 0x%x\n", verde);
    printf("O azul: 0x%x\n", azul);

}