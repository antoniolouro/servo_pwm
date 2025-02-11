# servo_pwm

## Tarefa Aula Síncrona 06/02/2025 - Parte 1 - Movimentação de um servo-motor via PWM com simulação no wokwi

Esta tarefa tem cinco requisitos - os quatro primeiros foram colocados em funções separadas para facilitar a averiguiação pelo professor.
O quinto requisito está implementado no loop infinito.

**Requisito - 1** - função *pwm_req1()*

Define o divisor de clock do PWM (250) e define o valor de wrap (10000), que é o comprimento total do ciclo (período) - Isto é, foi ajustada a Fpwm = 50Hz.
Como este valor foi obtido?
Fsys = 125MHz  Fpwm = Fsys/[(divisor)*(wrap+1)] = 125Mhz/(250)*(10000) = 50MHz

**Requisito - 2** - função *pwm_req2()*

Ajusta o ciclo ativo de 2,4ms que corresponde ao duty cycle de 12%.
Como o wrap corresponde ao comprimento do ciclo em ticks, 12% de 10000 (1200) é o valor colocado no comparador, que 
produz o ciclo ativo (2,4ms de um período (Tpwm) de 20ms.
Esses 1200 ticks de clock corresponde à posição 180 graus do servo.

**Requisito - 3** - função *pwm_req3()*

Ajusta o ciclo ativo em 1,47ms, que corresponde a 7,35% de Tpwm (20ms).
Em ticks de clock, 7,35% de 10000 ticks = 735 ticks - que corresponde a 90 graus do servo.

**Requisito - 4** - função *pwm_req4()*

Ajusta o ciclo ativo em 0,5ms, que corresponde a 2,5% do ciclo de Tpwm (20ms).
Em ticks de clock, 2,5% de 10000 ticks = 250 ticks - que corresponde a 0 graus do servo.

**Requisito - 5** - *loop infinito*

Ajusta continuamente o ciclo ativo para que o ângulo do servo varie de 0-180 e de 180-0.
Isto é feito incrementando/decrementando o ciclo ativo em 5 ticks de clock por ângulo.

## Vídeo demonstrativo



[![Assista no YouTube](https://img.youtube.com/vi/jslxKx2X8CM/maxresdefault.jpg)](https://youtu.be/jslxKx2X8CM)

