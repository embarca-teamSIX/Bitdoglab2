## Controle de LEDs e Buzzer via UART na Raspberry Pi Pico

Este projeto implementa um sistema de controle de LEDs RGB e um buzzer utilizando a Raspberry Pi Pico. O sistema recebe comandos via comunicação UART (USB serial) e executa ações correspondentes.

---

## Requisitos

- Placa Raspberry Pi Pico.
- LEDs RGB conectados aos pinos:
  - GPIO 11 (LED Verde).
  - GPIO 12 (LED Azul).
  - GPIO 13 (LED Vermelho).
- Buzzer conectado ao pino GPIO 21.
- Cabo USB para conectar a Raspberry Pi Pico ao computador.
- Software de monitoramento serial (ex.: PuTTY, CoolTerm, VSCode com extensão serial, etc.).

---

## Compilação e Upload

1. Instale o **SDK do Raspberry Pi Pico** e configure o ambiente de desenvolvimento (ex.: VSCode, CMake, etc.).
2. Compile o código utilizando o seguinte comando no terminal:
   ```bash
   cmake .. && make
   ```
3. Com a Raspberry Pi Pico em **modo bootloader** (pressione e segure o botão BOOTSEL enquanto conecta o cabo USB), copie o arquivo `main.uf2` gerado para a unidade montada.

---

## Conexão Serial

Após o upload do firmware, abra o monitor serial no seu software preferido com os seguintes parâmetros:

- **Baud rate:** 115200  
- **Data bits:** 8  
- **Paridade:** Nenhuma  
- **Stop bits:** 1  

Quando o programa iniciar, você verá a seguinte mensagem no terminal serial:

```
Sistema inicializado. Aguarde comandos UART...
```

---

## Comandos Disponíveis e Suas Funções

- **`LED_GREEN_ON`**  
  Liga o LED verde.

- **`LED_BLUE_ON`**  
  Liga o LED azul.

- **`LED_RED_ON`**  
  Liga o LED vermelho.

- **`SIRENE_ON`**  
  Ativa O buzzer em uma sequencia que emula sirene e com LEDs piscando emulando estrobo.

- **`LED_WHITE_ON`**  
  Liga todos os LEDs (misturando RGB para gerar branco).

- **`LED_OFF`**  
  Desliga todos os LEDs.

- **`BUZZER_ON`**  
  Ativa o buzzer por 2 segundos.

- **`PISCA`**  
  Faz o led piscar em diversas combinações de cores diferentes, combinando o RGB

- **`SOS`**  
  Ativa o sinal de SOS em código morse com o led rgb da placa

- **`REBOOT`**  
  Reinicia a Raspberry Pi Pico no modo USB Bootloader.

---

### Exemplo de uso no monitor serial:
1. Envie o comando:
   ```
   LED_GREEN_ON
   ```
2. Saída esperada no terminal:
   ```
   Recebido: LED_GREEN_ON
   ```

---

## Funcionamento do Código

1. A Raspberry Pi Pico é configurada para utilizar os pinos GPIO como saída.
2. Após a inicialização, o código entra em um loop infinito, aguardando comandos recebidos pela comunicação UART.
3. Ao receber um comando:
   - Liga ou desliga os LEDs RGB de acordo com o comando recebido.
   - Aciona o buzzer, se o comando correspondente for enviado.
   - Reinicia a placa, caso o comando seja `REBOOT`.
4. Caso um comando inválido seja enviado, a mensagem abaixo será exibida no terminal serial:
   ```
   Comando desconhecido
   ```

O sistema foi otimizado para evitar erros de buffer, garantindo que apenas comandos válidos sejam processados corretamente.

---

## Solução de Problemas

- Certifique-se de que a Pico está conectada corretamente via USB e em modo bootloader ao copiar o arquivo `main.uf2`.
- Use um cabo USB apropriado que suporte transferência de dados.
- Verifique se o monitor serial está configurado corretamente (vide seção **Conexão Serial**).
- Se a Raspberry Pi Pico não responder, tente desconectá-la e reconectá-la manualmente.

---

## Autores

- Deividson Ribeiro
- Jorge de Palma Conceição
- Gleison Fonseca de Paula

**Formação Básica em Sistemas Embarcados - Embarcatech**
