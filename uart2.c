#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"
#include <stdio.h>
#include <string.h>

#define LED_R_PIN 13    // Pino do LED vermelho
#define LED_G_PIN 11    // Pino do LED verde
#define LED_B_PIN 12    // Pino do LED azul
#define BUZZER_PIN 21   // Pino do buzzer

// Configuração inicial dos pinos GPIO
void setup_gpio() {
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_put(LED_R_PIN, 0);

    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_put(LED_G_PIN, 0);

    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    gpio_put(LED_B_PIN, 0);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);
}

// Acionamento do buzzer
void activate_buzzer(int duration_ms) {
    gpio_put(BUZZER_PIN, 1);
    sleep_ms(duration_ms);
    gpio_put(BUZZER_PIN, 0);
}

// Controle dos LEDs
void control_leds(int red, int green, int blue) {
    gpio_put(LED_R_PIN, red);
    gpio_put(LED_G_PIN, green);
    gpio_put(LED_B_PIN, blue);
}

// Pisca LED
void pisca_led()
{
    control_leds(1,0,0);
    sleep_ms(400);
    control_leds(0,1,0);
    sleep_ms(400);
    control_leds(0,0,1);
    sleep_ms(400);
    control_leds(1,1,0);
    sleep_ms(400);
    control_leds(1,0,1);
    sleep_ms(400);
    control_leds(0,1,1);
    sleep_ms(400);
    control_leds(1,1,1);
    sleep_ms(400);
    control_leds(0,0,0);
}

// Interpretação dos comandos UART
void process_command(const char *command) {
    if (strcmp(command, "LED_GREEN_ON") == 0) {
        control_leds(0, 1, 0);
    } else if (strcmp(command, "LED_BLUE_ON") == 0) {
        control_leds(0, 0, 1);
    } else if (strcmp(command, "LED_RED_ON") == 0) {
        control_leds(1, 0, 0);
    } else if (strcmp(command, "LED_WHITE_ON") == 0) {
        control_leds(1, 1, 1);
    } else if (strcmp(command, "LED_OFF") == 0) {
        control_leds(0, 0, 0);
    } else if (strcmp(command, "BUZZER_ON") == 0) {
        activate_buzzer(2000);
    } else if (strcmp(command, "PISCA") == 0) {
        pisca_led();
    } else if (strcmp(command, "PISCA_BUZ") == 0) {

    } else if (strcmp(command, "REBOOT") == 0) {
        printf("Reiniciando para o modo USB Bootloader...\n");
        sleep_ms(1000);
        reset_usb_boot(0, 0);
    } else {
        printf("Comando desconhecido: %s\n", command);
    }
}

int main() {
    stdio_init_all();
    setup_gpio();
    char command[64];
    int index = 0;

    printf("Sistema inicializado. Aguarde comandos UART...\n");

    while (true) {
        if (stdio_usb_connected()) {
            int c = getchar_timeout_us(10000);
            if (c != PICO_ERROR_TIMEOUT && c != EOF) {
                if (c == '\n' || c == '\r') {
                    if (index > 0) {  // Processa apenas se há dados
                        command[index] = '\0';
                        printf("Recebido: %s\n", command);
                        process_command(command);
                        index = 0;
                    }
                } else if (index < (int)(sizeof(command) - 1)) {
                    command[index++] = (char)c;
                }
            }
        }
        sleep_ms(10);
    }
}
