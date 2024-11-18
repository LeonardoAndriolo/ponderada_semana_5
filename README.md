# Sistema de Tráfego Inteligente

Este projeto simulou um sistema de semáforos inteligentes que se comunicavam entre si e ajustavam o fluxo de veículos de forma eficiente. Utilizando sensores de luz (LDR), os semáforos adaptavam seu funcionamento automaticamente, inclusive para um 'modo noturno', explorando conceitos de *Smart Cities*.

## Objetivo

Nosso objetivo foi criar um semáforo inteligente, capaz de detectar a presença de veículos por meio de um sensor de luz (LDR) e adaptar seu comportamento automaticamente para diferentes condições.

## Estrutura do Projeto

### Montagem Física (Programação com LDR e Modo Noturno)

Nesta primeira parte, nosso foco foi a montagem dos componentes físicos e a programação dos semáforos. Montamos dois semáforos e os conectamos um deles ao sensor LDR, permitindo a detecção da passagem de veículos simulados através da variação de luz..

- **Sensor LDR**: Utilizado para detectar a presença de veículos através da variação da luminosidade;
- **Modo Noturno**: Os semáforos mudavam automaticamente para um modo de operação noturna quando a luminosidade ambiente diminuir.

Adicionar imagem do protótipo

Adicionar código do IDE

### Configuração da Interface Online

Nesta parte, nosso objetivo foi desenvolver uma interface online simples e funcional que permitisse:

- Ajustar o comportamento dos semáforos, incluindo a ativação manual do modo noturno.
- Visualizar os dados captados pelo sensor LDR em tempo real.

## Como Executar o Projeto

Para executar o projeto e garantir que todas as funcionalidades fossem implementadas corretamente, seguimos os passos detalhados abaixo com atenção:

1. **Montagem do Hardware**: Montamos os semáforos e conectamos os sensores LDR conforme o esquemático fornecido.
2. **Programar o Modo Noturno**: Programamos o microcontrolador para alterar o comportamento dos semáforos conforme a detecção de variação de luz.
3. **Interface Online**: Configuramos a interface online para o controle do sistema.

## Tecnologias Utilizadas

- **Arduino/ESP32** para controle dos semáforos.
- **Sensores LDR** para detecção de veículos.
- **Plataforma** para centralizar e monitorar os dados.
- **Interface Web** para controle dos semáforos.

## Licença

Este projeto está sob a licença MIT. Consultem o arquivo `LICENSE` para mais informações.

