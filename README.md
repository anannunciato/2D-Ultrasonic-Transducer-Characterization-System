# Low-cost-3D-HYDROPHONE-SCANNING-TANK-WITH-LABVIEW-and-ARDUINO

# Sistema de Varredura Tridimensional para Mapeamento Acústico

Este repositório contém o código-fonte e a documentação do sistema automatizado de baixo custo para o posicionamento preciso de um hidrofone em tanques acústicos.

## 🛠️ Hardware Utilizado
* Arduino Mega 2560
* CNC Shield V3 + Drivers DRV8825 (Configurados em 1/32 de passo)
* Motores de Passo NEMA 17
* LCD Keypad Shield (IHM Física Modificada)

## 💻 Software e Arquiteturas
* **Firmware (Arduino):** Desenvolvido utilizando as bibliotecas `AccelStepper` e `LiquidCrystal` de forma não-bloqueante.
* **Interface (LabVIEW):** Desenvolvido no LabVIEW Community 2026 Q1 utilizando arquitetura de Máquina de Estados Finitos (MEF).

## 🚀 Como Executar o Projeto
1. Carregue o arquivo contido na pasta `/firmware-arduino` no Arduino Mega.
2. Faça o ajuste manual dos limites espaciais no LCD Shield.
3. Abra o software no LabVIEW, configure a porta COM correta e inicie a varredura automática.

## 📄 Documentação Completa
O artigo científico contendo o manual detalhado de instalação, remapeamento de pinos e calibração do sistema pode ser baixado diretamente na pasta de documentação ou pelo link abaixo:

* [Clique aqui para acessar o Manual de Instalação (PDF)](documentacao/artigo_manual.pdf)
