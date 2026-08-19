# Desenvolvimento de uma Plataforma de Baixo Custo para Varredura 2D e Caracterização de Campos Acústicos Ultrassônicos

<p align="center">
  <a href="#lang-pt">🇧🇷 Português</a> •
  <a href="#lang-en">🇺🇸 English</a>
</p>

---

<a id="lang-pt"></a>
# 🇧🇷 Português

## Sumário
- [Título do Projeto](#-desenvolvimento-de-uma-plataforma-de-baixo-custo-para-varredura-2d-e-caracterização-de-campos-acústicos-ultrassônicos)
- [Autores](#-autores-pt)
- [Visão Geral](#-visão-geral-pt)
- [Arquitetura do Sistema](#-arquitetura-do-sistema-pt)
- [Hardware Utilizado](#-hardware-utilizado-pt)
- [Estrutura do Repositório](#-estrutura-do-repositório-pt)
- [Artigo do Projeto](#-artigo-do-projeto-pt)

---

## Desenvolvimento de uma Plataforma de Baixo Custo para Varredura 2D e Caracterização de Campos Acústicos Ultrassônicos

<a id="autores-pt"></a>
### Autores
- **Ana Laura Waideman de Oliveira** (DAELT - UTFPR)
- **Ana Clara Annunciato de Oliveira** (DAELT - UTFPR)
- **Alexia Marcon Watzlawick** (CPGEI-CT - UTFPR)
- **Gilson Maekawa Kanashiro** (CPGEI-CT - UTFPR / IFPR)
- **Joaquim Miguel Maia** (CPGEI-CT / DAELN - UTFPR)
- **Amauri Amorin Assef** (CPGEI-CT / DAELT - UTFPR)

<a id="visão-geral-pt"></a>
### Visão Geral
Este repositório contém o código-fonte, esquemáticos e documentação do desenvolvimento e validação experimental de uma plataforma de baixo custo para caracterização de transdutores ultrassônicos. O sistema integra um sistema de posicionamento mecânico bidimensional (eixos X-Z) baseado em microcontrolador, uma interface supervisória no LabVIEW e rotinas de processamento de sinais em MATLAB para mapeamento de pressão acústica e análise espectral.

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
