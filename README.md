# Geração de Animações em Matriz de LEDs 5x5

## Descrição
Este projeto tem como objetivo a geração de animações em uma matriz de LEDs 5x5 utilizando o Raspberry Pi Pico W e um teclado matricial 4x4. 

O sistema permite que, ao pressionar as teclas do teclado matricial (0-9), uma animação correspondente seja exibida na matriz de LEDs RGB 5x5. Além disso, as teclas A, B, C, D, # e * possuem funções específicas para manipulação da matriz de LEDs, como desligar ou acender os LEDs com cores e intensidades predeterminadas.


## Requisitos de Funcionamento
1. **Teclado Matricial**:
   - **Teclas 0 a 9**: Acionam animações diferentes na matriz de LEDs.
   - **Tecla A**: Desliga todos os LEDs.
   - **Tecla B**: Liga todos os LEDs na cor azul com 100% de luminosidade.
   - **Tecla C**: Liga todos os LEDs na cor vermelha com 80% de luminosidade.
   - **Tecla D**: Liga todos os LEDs na cor verde com 50% de luminosidade.
   - **Tecla #**: Liga todos os LEDs na cor branca com 20% de luminosidade.
   - **Tecla * (opcional)**: Coloca o Raspberry Pi Pico W no modo de gravação via software (reboot).

2. **Animações**:
   - 10 animações diferentes (uma para cada tecla de 0 a 9), com no mínimo 5 frames (quadros) e FPS configurável para garantir fluidez.

3. **Buzzer (opcional)**:
   - Em uma das animações, o buzzer gera um sinal sonoro durante a execução da animação.

## Como Executar
1. Clone o repositório:
   ```bash
   git clone https://github.com/Gilmaiane23/matrix_keypad.git
   ```
2. Navegue até o diretório do projeto:
   ```bash
   cd matrix_keypad
   ```
3. Abra o projeto no VS Code:
   ```bash
   code .
   ```
4. Compile e simule o projeto usando o Wokwi, ou carregue o código diretamente no Raspberry Pi Pico W.

5. Conecte o teclado matricial e a matriz de LEDs RGB ao Raspberry Pi Pico W conforme o esquema de ligação indicado no projeto.

6. Execute o código e interaja com as animações através do teclado matricial.

## Testes
Cada desenvolvedor é responsável por criar testes básicos para garantir que os recursos (como animações, controles de LEDs e buzzer) estejam funcionando corretamente.


## Vídeo de Demonstração
```bash
   Link:  .
   ```
## Colaboradores
- **Líder**: [Gilmaiane Porto]
- **Desenvolvedores**: [Arthur de Oliveira Moreira]
                       [André da Silva Caldas Chagas]
                       [Daniel Alencar Penha Carvalho]
                       [Daniel Porto Braz]
                       [Isaque Coelho de Jesus]
                       [Júlio Henrique Lima de Oliveira Sousa]
                       [Pablo Henrique Dourado Souza]

## Licença
Este projeto é licenciado sob a licença MIT – consulte o arquivo LICENSE para mais detalhes.

