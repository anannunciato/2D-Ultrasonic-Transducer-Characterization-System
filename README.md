# Low-cost-2D-HYDROPHONE-SCANNING-TANK-WITH-LABVIEW-and-ARDUINO

# Sistema de Varredura 2D para Mapeamento Acústico

Este repositório contém o código-fonte e a documentação do sistema automatizado de baixo custo para o posicionamento preciso de um hidrofone em tanques acústicos.

## 🛠️ Hardware Utilizado
* Arduino Mega 2560
* CNC Shield V3 + Drivers DRV8825 (Configurados em 1/32 de passo)
* Motores de Passo NEMA 17
* LCD Keypad Shield (IHM Física Modificada)

## Estrutura do Repositório

```text
.
├── documentacao/
│   ├── artigo.pdf                 # Artigo do projeto
│   ├── lista_de_materiais.pdf     # Relação detalhada de componentes de hardware
│
├── firmware-arduino/
│   └── firmware_arduino/          # Código-fonte principal em C/C++ (Arduino IDE)
│       └── firmware_arduino.ino   # Firmware de controle dos eixos X/Z e sincronismo (100 Hz)
│
├── software-labview/
│   ├── bibliotecas/               # Dependências e drivers VISA do LabVIEW
│   └── Varredura_2D.vi            # Interface principal de automação de malha em zigue-zague
│
└── README.md                      # Documentação geral do projeto

##  Como Executar o Projeto
1. Carregue o arquivo contido na pasta `/firmware-arduino` no Arduino Mega.
2. Faça o ajuste manual dos limites espaciais no LCD Shield.
3. Abra o software no LabVIEW, configure a porta COM correta e inicie a varredura automática.


