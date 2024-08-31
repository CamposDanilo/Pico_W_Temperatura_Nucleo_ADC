//Programa habilita Temp sensor Onboard da placa Pico W
//Faz a leitura da ADC canal 4, então converte o valor em tensão
// e depois converte em temperatura de acordo com a equação encontrada no Manual SDK
// Configurado para imprimir o valor de Temperatura do processador na serial USB(115200)
// a frenquencia de leitura deve ser inserida pelo usuario em MILIsegundos.
// o led da plca alterna o estado toda vez que a leitura ADC é realizada.
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "string.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

volatile bool led_status;

bool per_timer(struct repeating_timer *t){
    const float fator = 3.3f / (1 << 12);
    uint16_t result = adc_read();
    const float volts = result * fator;
    const float calc = (27 - (volts - 0.706) / 0.001727);
    printf("Temp: %.2f Celsius\n",calc);
    led_status = !led_status;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN,led_status);
    return true;
}


int main() {
    stdio_init_all();
    cyw43_arch_init();
    adc_init();
    adc_select_input(4);
    adc_set_temp_sensor_enabled(true);
    sleep_ms(7000);
    struct repeating_timer timer;
    printf("Leitura de temperatura do Processador\n");


    while(true){

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN,false);
        int tempo = 0;

        do{
            printf("Scan do sensor(miliseg):    (-1 para PARAR leituras)\n");
        }while(scanf("%d",&tempo)<0 && tempo == 0);

        if (tempo == -1){
            cancel_repeating_timer(&timer);
            continue;
        }
        add_repeating_timer_ms(tempo,&per_timer,NULL,&timer);
        
    }

    return 0;
}