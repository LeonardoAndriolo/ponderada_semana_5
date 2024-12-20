# Sistema de Tráfego Inteligente

Este projeto simulou um sistema de semáforos inteligentes que se comunicavam entre si e ajustavam o fluxo de veículos de forma eficiente. Utilizando sensores de luz (LDR), os semáforos adaptavam seu funcionamento automaticamente, inclusive para um 'modo noturno', explorando conceitos de *Smart Cities*.

## Objetivo

Nosso objetivo foi criar um semáforo inteligente, capaz de detectar a presença de veículos por meio de um sensor de luz (LDR) e adaptar seu comportamento automaticamente para diferentes condições.

## Estrutura do Projeto

### Montagem Física (Programação com LDR e Modo Noturno)

Nesta primeira parte, nosso foco foi a montagem dos componentes físicos e a programação dos semáforos. Montamos dois semáforos e os conectamos um deles ao sensor LDR, permitindo a detecção da passagem de veículos simulados através da variação de luz..

- **Sensor LDR**: Utilizado para detectar a presença de veículos através da variação da luminosidade;
- **Modo Noturno**: Os semáforos mudavam automaticamente para um modo de operação noturna quando a luminosidade ambiente diminuir.

O protótipo de semáforos em miniatura foi montado em uma estrutura de madeira cortada a laser, conectado a uma protoboard com fios. A figura a seguir mostra o modelo:

<div align="center"> <sub> Figura 1 - Montagem do Teste</sub>

<img src="assets\semaforo_1.jpeg" style="width: 50%;"><br>
<sup> Fonte: Material produzido pelos autores (2024).</sup> </div>

Utilizamos um sensor de luz LDR para ativar o modo noturno e dois ESP32.

<div align="center"> <sub> Figura 2 - Sensor LDR</sub>

<img src="assets\sensor_ldr.jpeg" style="width: 50%;"><br>
<sup> Fonte: Material produzido pelos autores (2024).</sup> </div>

<div align="center"> <sub> Figura 3 - Montagem dos ESP32</sub>

<img src="assets\montagem_esp32.jpeg" style="width: 50%;"><br>
<sup> Fonte: Material produzido pelos autores (2024).</sup> </div>

A seguir, apresentamos dois vídeos com os modos programados do sistema: normal e noturno. No primeiro, é possível ver o semáforo funcionando normalmente alternando as cores entre verde, amarelo e vermelhor de acordo com um temporizador. Já no segundo, com baixa luminosidade no sensor (representada ao colocar o dedo sobre o sensor), o semáforo muda para o modo noturno e não mais acende o LED verde, ficando apenas no amarelo.

<div align="center"> <sub> Video 1 —  Modo Normal</sub>

https://github.com/user-attachments/assets/cd71df87-66ea-4fab-89a5-2e4d05f4ef0b

<sup> Fonte: Material produzido pelos autores (2024).</sup> </div>

<div align="center"> <sub> Video 2 — Modo Noturno</sub>

https://github.com/user-attachments/assets/0ba769ea-14e7-4069-add1-9c9cc77e7d6d

<sup> Fonte: Material produzido pelos autores (2024).</sup> </div>

### Interface Online

Nesta parte, utilizamos uma plataforma desenvolvida por Gabriel Scarpelin (nosso *Tech lead*). Nela, podemos verificar o funcionamento das luzes do semáforo, assim como definir intervalos de ativação dos LEDs. A imagem a seguir representa a plataforma.

<div align="center"> <sub> Figura 4 - Interface da Plataforma</sub>

<img src="assets\interface_GS.jpeg" style="width: 50%;"><br>
<sup> Fonte: Material produzido pelos autores (2024).</sup> </div>

O código da plataforma pode ser acessado [aqui](https://github.com/GabrielScarpelinDiniz/plataforma-semaforos/blob/main/README.md). Também adicionamos os arquivos .ino utilizados para rodar o software nos ESP32.

## Tecnologias Utilizadas

- **ESP32** para controle dos semáforos;
- **Sensores LDR** para detecção de veículos;
- **Plataforma customizada** para centralizar e monitorar os dados;
- **Interface Web** para visualização do status dos semáforos.

