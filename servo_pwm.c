#include <stdio.h> //biblioteca padrão da linguagem C
#include "pico/stdlib.h" //subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM
#define SERVO_PIN 22 // GPIO 22 como PWM
#define SERVO_0_DEG 250     // 0 graus (0,5ms) - 2,5% de 10000 ticks
#define SERVO_90_DEG 735    // 90 graus (1,47ms) - 7,35% de 10000 ticks    
#define SERVO_180_DEG 1200  // 180 graus (2,4ms) - 12% de 10000 ticks
#define SERVO_0_CALIB 270  // 0 graus (0,5ms) - 2,7% de 10000 ticks - calibração para alinhar com 7,35% e 12%

static uint slice;


// função que configura o PWM
void pwm_setup()   {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM
    slice = pwm_gpio_to_slice_num(SERVO_PIN); //obter o canal PWM da GPIO
}
//--------------------------------------------------------------------------------------------
 // função que prepara o pwm de acordo com o Requisito 1 da tarefa:
 // Ajusta o pwm para gerar um sinal de 50Hz
 // Para obter Fpwm = 50Hz com Fclk=125MHz, o divisor de clock é ajustado para 250 e o wrap para 10000 (0 a 9999)
 
void pwm_req1()
{
  pwm_set_clkdiv(slice, SERVO_0_DEG); //define o divisor de clock do PWM
  pwm_set_wrap(slice, 9999); //define o valor de wrap - 10000 ticks
}
//--------------------------------------------------------------------------------------------

// Função que prepara o pwm de acordo com o Requisito 2 da tarefa
// Ciclo ativo de 2,4ms que corresponde ao duty cycle de 12%.
// Como o wrap corresponde ao comprimento do ciclo em ticks, 12% (1200) é o valor colocado no comparador, que 
// corresponde à parte do ciclo que fica em nível alto (2,4ms de um ciclo de 20ms (50Hz)).
// Esses 1200 ticks de clock corresponde ao 180 graus do servo.
void pwm_req2()
{
  pwm_set_gpio_level(SERVO_PIN, SERVO_180_DEG); //ciclo ativo do pwm (12% de 10000 ticks)
  pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente
}
//--------------------------------------------------------------------------------------------

// No Requisito 3, o ciclo ativo é de 1,47ms, que corresponde a 7,35% do ciclo de 20ms (50Hz).
// Consequentemente é 7,35% de 10000 ticks = 735 ticks - que corresponde a 90 graus do servo.
void pwm_req3()
{
  pwm_set_gpio_level(SERVO_PIN, SERVO_90_DEG); //ciclo ativo do pwm (7,35% de 10000 ticks)
}
//--------------------------------------------------------------------------------------------

// No Requisito 4, o ciclo ativo é de 0,5ms, que corresponde a 2,5% do ciclo de 20ms (50Hz).
// Consequentemente é 2,5% de 10000 ticks = 250 ticks - que corresponde a 0 graus do servo.
void pwm_req4()
{
  pwm_set_gpio_level(SERVO_PIN, SERVO_0_DEG); //ciclo ativo do pwm (2,5% de 10000 ticks)
}


int main()
{
  const uint8_t step = 5; //passo para incrementar/decrementar o ângulo do servo
  uint16_t duty_C = SERVO_0_CALIB;  // O duty Cycle define o ângulo - 270 corresponde ao zero graus
 
  //Obs. Embora na função pwm_req4 o valor de duty_C seja 250 (por imposição da questão), no loop será usado
  // o valor 270 para manter a simetria nas distâncias: 1200-735=465 -> 735-465=270.
  // Por regra de três o step é 5 (5,167).

  uint8_t direcao = 1;  // flag para indicar incremento/decremento do ângulo
  stdio_init_all(); //inicializa a serial, se necessário
  pwm_setup(); //configura o PWM
  pwm_req1(); //configura o PWM para 50Hz
  sleep_ms(5000);
  pwm_req2(); //configura o PWM para 180 graus
  printf("Servo na posição 180 graus\n");
  sleep_ms(5000);
  pwm_req3(); //configura o PWM para 90 graus
  printf("Servo na posição 90 graus\n");
  sleep_ms(5000);
  pwm_req4(); //configura o PWM para 0 graus
  printf("Servo na posição 0 graus\n");
  sleep_ms(5000);
  printf("Movendo o servo de 0 a 180 graus e de 180 a 0 graus\n");

//loop infinito para mover o servo de 0 a 180 graus ida e volta
//Corresponde ao requisito 5 da tarefa
 while (true) {
  if(direcao) {
    duty_C = duty_C + step; //incrementa ângulo em aprox 1 grau
    if (duty_C >= SERVO_180_DEG) //chegou aos 180 graus?
      direcao = 0;
      
  }
  else
  {
    duty_C = duty_C - step;  //decrementa Ângulo aprox 1 grau
    if (duty_C <= SERVO_0_CALIB)  //chegou aos 0 graus?
      direcao = 1;
  }

  pwm_set_gpio_level(SERVO_PIN, duty_C);
  sleep_ms(10);
  
  
 }
}