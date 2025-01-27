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

    uint32_t verde,amarelo,azul,vermelho;

    amarelo=conversor(183,241,14);   //255/203/0
    verde=conversor(6,67,7);      //0/148/64  
    azul=conversor(26,18,78);      //48/38/129
    vermelho=conversor(250,10,10);

    printf("O amarelo: 0x%x\n", amarelo);
    printf("O verde: 0x%x\n", verde);
    printf("O azul: 0x%x\n", azul);
    printf("O vermelho: 0x%x\n", vermelho);

}