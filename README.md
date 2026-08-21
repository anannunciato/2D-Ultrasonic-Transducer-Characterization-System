<p align="center">
  <b>Language / Idioma:</b> 🇺🇸 <a href="#english">English</a> · 🇧🇷 <a href="#português">Português</a>
</p>

---

# 2D Ultrasonic Transducer Characterization System

> **Artigo / Article** — Desenvolvimento de Ferramentas para Sistema de Caracterização de Transdutores de Ultrassom
> 
> **Autores / Authors:** Ana Clara Annunciato de Oliveira · Ana Laura Waideman de Oliveira · Joaquim Miguel Maia · Amauri Amorin Assef

---
<a id="arquitetura-do-sistema-pt"></a>
### Arquitetura do Sistema
![Arquitetura do Sistema](arranjo.png)  

O sistema opera de forma integrada: o LabVIEW (via comunicação serial e USB) envia comandos ao Arduino Mega 2560 para coordenar os motores de passo dos eixos X e Z na malha de varredura zigue-zague. Simultaneamente, o Arduino gera sinais de sincronismo (100 Hz) para o gerador de pulsos (Pulser/Receiver), enquanto a aquisição das formas de onda do hidrofone é feita pelo osciloscópio conectado via Ethernet ao LabVIEW.

<a id="hardware-utilizado-pt"></a>
### Hardware Utilizado
* **Arduino Mega 2560** (Placa de controle e gerador de sincronismo)
* **CNC Shield V3 + Drivers DRV8825** (Configurados em micropasso de 1/32)
* **2x Motores de Passo NEMA 17** ($1.8^\circ$/passo, fuso TR8x2)
* **LCD Keypad Shield 16x2** (Interface Homem-Máquina local modificada)
* **Chaves Fim de Curso** (Segurança mecânica e limite dos eixos)

<a id="estrutura-do-repositório-pt"></a>
### Estrutura do Repositório

```text
.
├── documentacao/
│   ├── artigo.pdf                 # Artigo completo do projeto
│   └── lista_de_materiais.pdf    # Relação detalhada de componentes de hardware
│
├── firmware-arduino/
│   └── firmware_arduino/         # Código-fonte principal em C/C++ (Arduino IDE)
│       └── firmware_arduino.ino  # Firmware de controle dos eixos X/Z e sincronismo (100 Hz)
│
├── software-labview/
│   ├── bibliotecas/               # Dependências e drivers VISA do LabVIEW
│   └── Varredura_2D.vi            # Interface principal de automação de malha em zigue-zague
│
└── README.md                      # Documentação geral do projeto
