# Banco de Exercícios - Sistemas Embarcados

Coleção de exercícios de firmware baremetal para o Raspberry Pi Pico (RP2040). Cada exercício explora um periférico ou conceito diferente de sistemas embarcados.

---

## Exercícios

### [barra-de-leds](./barra-de-leds/)

Controle de uma barra de LEDs com contador. Uma chave define se o botão vai incrementar ou decrementar o valor exibido na barra. O exercício exige o uso de interrupções e a implementação das funções `bar_init()` e `bar_display()`.

**Periféricos:** GPIO (saída para LEDs, entrada para botão e chave), Interrupções externas

---

### [buzzer-com-timer](./buzzer-com-timer/)

Controle de frequência de um buzzer usando timers. O firmware deve fazer o buzzer variar continuamente do agudo para o grave. O uso de `sleep_ms()` e similares é proibido — o controle de tempo deve ser feito exclusivamente com timers.

**Periféricos:** GPIO (saída para buzzer), Timer

---

### [dois-sensores-distancia](./dois-sensores-distancia/)

Leitura de dois sensores ultrassônicos SR-04 com impressão da distância no terminal. O firmware deve detectar e reportar falhas em qualquer sensor. Todo o controle deve ser feito via interrupções, sem o uso de `gpio_get()`.

**Periféricos:** GPIO (trigger e echo dos sensores SR-04), Interrupções externas, UART (printf)

---

### [jogo-reflexo](./jogo-reflexo/)

Implementação de um jogo estilo *Genius* com sequência fixa de 10 cores. O jogo exibe uma sequência crescente de LEDs e o jogador deve repetir a ordem apertando os botões corretos. A cada rodada acertada, a sequência aumenta em uma cor. Ao errar, o jogo termina e exibe a pontuação.

**Periféricos:** GPIO (saída para LEDs, entrada para botões), Interrupções externas, UART (printf)

---

### [pisca-led-adc](./pisca-led-adc/)

LED piscando com frequência controlada por um potenciômetro lido via ADC. Três zonas de tensão definem o comportamento: desligado (0–1V), pisca a 300ms (1–2V) e pisca a 500ms (2–3.3V). O controle de tempo deve usar timers, sem `sleep_ms()`.

**Periféricos:** GPIO (saída para LED), ADC (leitura do potenciômetro), Timer

---

### [pisca-led-dois-botoes](./pisca-led-dois-botoes/)

Dois LEDs (verde e amarelo) piscando com frequências e durações diferentes, ativados por botões independentes. Regra especial: se os dois LEDs estiverem piscando ao mesmo tempo e o tempo de um terminar, ambos param imediatamente. O controle usa timers e interrupções.

**Periféricos:** GPIO (saída para LEDs, entrada para botões), Interrupções externas, Timer

---

### [pisca-led-tempo-botao](./pisca-led-tempo-botao/)

O tempo que o botão vermelho fica pressionado define por quanto tempo o LED ficará piscando. Enquanto o botão está pressionado, o LED apaga. Ao soltar, o LED pisca pelo mesmo tempo que o botão foi mantido. Usa timers e interrupções.

**Periféricos:** GPIO (saída para LED, entrada para botão), Interrupções externas, Timer

---

### [pisca-led-tres-botoes](./pisca-led-tres-botoes/)

Três LEDs (amarelo, azul, verde) controlados por três botões, cada um com comportamento diferente de ativação:
- Amarelo: toggle ao **apertar**
- Azul: toggle ao **soltar**
- Verde: aceso apenas enquanto **mantido pressionado**

Todos os LEDs piscam sincronizados a 200ms. O uso de timers é proibido neste exercício.

**Periféricos:** GPIO (saída para LEDs, entrada para botões), Interrupções externas

---

### [pisca-led-um-botao](./pisca-led-um-botao/)

Ao pressionar um botão, dois LEDs (amarelo a 500ms e azul a 150ms) começam a piscar por exatamente 5 segundos e depois param automaticamente. O firmware deve usar exatamente 3 timers independentes: um para cada LED e um para o alarme de 5 segundos.

**Periféricos:** GPIO (saída para LEDs, entrada para botão), Interrupções externas, Timer (3 instâncias independentes)

---

### [pisca-led-um-depois-o-outro](./pisca-led-um-depois-o-outro/)

Dois LEDs piscam em sequência, um após o outro. O botão pressionado define qual LED começa:
- Botão amarelo: LED amarelo pisca por 1s (5Hz), depois LED azul pisca por 2s (2Hz)
- Botão azul: LED azul pisca por 2s (2Hz), depois LED amarelo pisca por 1s (5Hz)

Usa timers e interrupções, sem funções de delay.

**Periféricos:** GPIO (saída para LEDs, entrada para botões), Interrupções externas, Timer

---

### [senha](./senha/)

Sistema de senha com 4 botões. O usuário define uma senha apertando 4 botões em sequência e depois tenta reproduzi-la. Um LED roxo acende a cada botão pressionado, LED verde ao acertar a senha, e LED vermelho ao errar. Usa interrupções sem `gpio_get()`.

**Periféricos:** GPIO (saída para LEDs, entrada para botões), Interrupções externas

---

### [seven-seg](./seven-seg/)

Contador de 0 a 9 exibido em um display de 7 segmentos. Cada vez que o botão é apertado, o valor incrementa; ao chegar em 9, volta para 0. O exercício exige a implementação das funções `seven_seg_init()` e `seven_seg_display()`, usando interrupções.

**Periféricos:** GPIO (saída para os segmentos do display, entrada para botão), Interrupções externas

---

### [teclado-matricial](./teclado-matricial/)

Leitura de um teclado matricial com varredura por linhas e colunas. O firmware detecta qual tecla foi pressionada e imprime no terminal, usando muito menos pinos GPIO do que uma ligação direta. Usa interrupções, sem `gpio_get()`.

**Periféricos:** GPIO (linhas e colunas do teclado matricial), Interrupções externas, UART (printf)
