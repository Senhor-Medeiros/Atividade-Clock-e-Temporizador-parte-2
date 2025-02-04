#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definições dos pinos conforme as novas configurações
#define LED_GREEN 11    // LED Verde – GPIO 11
#define LED_BLUE  12    // LED Azul – GPIO 12
#define LED_RED   13    // LED Vermelho – GPIO 13
#define BUTTON     5    // Botão A – GPIO 05

// Variável global para indicar se a sequência de temporização está ativa.
// Enquanto true, o botão não poderá reiniciar o processo.
volatile bool sequence_active = false;

// Protótipos das funções de callback para que possam ser utilizadas antes de sua definição
int64_t turn_off_blue(alarm_id_t id, void *user_data);
int64_t turn_off_red(alarm_id_t id, void *user_data);

/*
 * Callback para desligar o LED Verde.
 * Desliga o LED Verde e agenda o desligamento do LED Azul após 3000ms.
 */
int64_t turn_off_green(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN, 0);
    printf("LED Verde desligado. Dois LEDs permanecem ligados (Azul e Vermelho).\n");
    // Agenda o desligamento do LED Azul em 3000ms
    add_alarm_in_ms(3000, turn_off_blue, NULL, false);
    return 0;
}

/*
 * Callback para desligar o LED Azul.
 * Desliga o LED Azul e agenda o desligamento do LED Vermelho após 3000ms.
 */
int64_t turn_off_blue(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 0);
    printf("LED Azul desligado. Somente LED Vermelho permanece ligado.\n");
    // Agenda o desligamento do LED Vermelho em 3000ms
    add_alarm_in_ms(3000, turn_off_red, NULL, false);
    return 0;
}

/*
 * Callback para desligar o LED Vermelho.
 * Desliga o LED Vermelho e finaliza a sequência, permitindo novo acionamento.
 */
int64_t turn_off_red(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, 0);
    printf("LED Vermelho desligado. Sequência finalizada.\n");
    sequence_active = false;  // Permite novo acionamento do botão
    return 0;
}

/*
 * Callback da interrupção do botão.
 * Implementa debounce (despreza interrupções ocorridas em menos de 50 ms)
 * e só permite iniciar a sequência se nenhuma sequência anterior estiver ativa.
 */
void button_callback(uint gpio, uint32_t events) {
    static uint32_t last_interrupt_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    
    // Debounce: ignora interrupções se ocorreram há menos de 50ms
    if (current_time - last_interrupt_time < 50) {
        return;
    }
    last_interrupt_time = current_time;
    
    // Só inicia a sequência se ela não estiver ativa
    if (!sequence_active) {
        sequence_active = true;
        printf("Botão pressionado! Iniciando sequência de LEDs...\n");
        
        // Liga todos os LEDs
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 1);
        
        // Agenda o desligamento do LED Verde após 3000ms
        add_alarm_in_ms(3000, turn_off_green, NULL, false);
    }
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    printf("Sistema de temporização de LEDs iniciado.\n");
    
    // Configuração dos LEDs como saída e desligamento inicial
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);
    
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);
    
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);
    
    // Configuração do botão como entrada com resistor pull-up
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);
    
    // Configura a interrupção do botão na borda de descida (quando o botão é pressionado)
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    
    // Loop principal (infinito)
    while (true) {
        sleep_ms(1000);
        if (!sequence_active) {
            printf("Aguardando acionamento do botão...\n");
        }
    }
    
    return 0;
}