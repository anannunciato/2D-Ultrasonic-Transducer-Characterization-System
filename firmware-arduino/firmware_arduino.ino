#include <AccelStepper.h>
#include <LiquidCrystal.h>

// --- CONFIGURAÇÕES ---
#define PASSOS_POR_MM 800.0   
#define LIMITE_MAX 100.0      

const int pinoTrigger = 50; 

// --- PINS DOS FINS DE CURSO ---
const int pinoFimDeCursoX = 48; // Fim de curso do Eixo X
const int pinoFimDeCursoZ = 49; // Fim de curso do Eixo Z

// RS:22, E:23, D4:24, D5:25, D6:26, D7:27
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
const int pinoBotoes = A8; 

AccelStepper stepperX(1, 2, 5); 
AccelStepper stepperZ(1, 4, 7); 
const int enPin = 8; 

int digitosX[6] = {0, 0, 0, 0, 0, 0}; 
int digitosZ[6] = {0, 0, 0, 0, 0, 0}; 
int cursorLocal = 0;   
bool editandoX = true; 
bool modoRemoto = false;

bool sistemaIniciouPulsos = false; 

unsigned long ultimaLeituraBotao = 0;
const int intervaloDebounce = 200; 

unsigned long ultimoPulsoMovimento = 0;

// Configurado para 10ms (Equivale a uma frequência de 100 Hz)
const int intervaloPulsoMovimento = 10; 

String comandoAcumulado = "";

void dispararPulso() {
  digitalWrite(pinoTrigger, HIGH);
  delayMicroseconds(50); // Pulso rápido estável para leitura TTL do Olympus
  digitalWrite(pinoTrigger, LOW);
}

int lerBotao(int valor) {
  if (valor < 60)  return 0; // RIGHT
  if (valor < 200) return 1; // UP
  if (valor < 400) return 2; // DOWN
  if (valor < 600) return 3; // LEFT
  if (valor < 850) return 4; // SELECT
  return -1;
}

float converterParaFloat(int d[]) {
  return (d[0] * 100.0) + (d[1] * 10.0) + d[2] + (d[3] * 0.1) + (d[4] * 0.01) + (d[5] * 0.001);
}

void imprimirLinha(int d[]) {
  lcd.print(d[0]); lcd.print(d[1]); lcd.print(d[2]);
  lcd.print(".");                  
  lcd.print(d[3]); lcd.print(d[4]); lcd.print(d[5]);
  lcd.print("mm"); 
}

void atualizarPainel() {
  lcd.setCursor(0, 0);
  lcd.print(editandoX ? ">X:" : " X:");
  imprimirLinha(digitosX);
  
  lcd.setCursor(0, 1);
  lcd.print(!editandoX ? ">Z:" : " Z:");
  imprimirLinha(digitosZ);
  
  int colFinal = 3 + cursorLocal; 
  if (cursorLocal > 2) colFinal++; 
  lcd.setCursor(colFinal, editandoX ? 0 : 1);
}

void movimentarEmTempoReal() {
  float valX = converterParaFloat(digitosX);
  float valZ = converterParaFloat(digitosZ);
  if (valX <= LIMITE_MAX) stepperX.moveTo(valX * PASSOS_POR_MM);
  if (valZ <= LIMITE_MAX) stepperZ.moveTo(valZ * PASSOS_POR_MM);
  
  sistemaIniciouPulsos = true; 
}

void enviarDadosSincronizacao() {
  float mmX = converterParaFloat(digitosX);
  float mmZ = converterParaFloat(digitosZ);
  
  long passosX = mmX * PASSOS_POR_MM;
  long passosZ = mmZ * PASSOS_POR_MM;

  Serial.print("POSX:"); 
  Serial.print(passosX);
  Serial.print(";POSZ:"); 
  Serial.print(passosZ);
  Serial.println(";"); 
  
  stepperX.moveTo(passosX);
  stepperZ.moveTo(passosZ);

  sistemaIniciouPulsos = true;

  lcd.setCursor(13, 0); 
  lcd.print("OK!");
  delay(300);
  atualizarPainel(); 
}

void processarComandoLabVIEW(String comando) {
  if (!modoRemoto) {
    modoRemoto = true;
    sistemaIniciouPulsos = false; 

    lcd.noCursor();
    lcd.noBlink();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MODO REMOTO");
    lcd.setCursor(0, 1);
    lcd.print("LABVIEW ATIVO");
  }

  int pinoDoisPontos = comando.indexOf(':');
  int pinoVirgula = comando.indexOf(',');
  
  if (pinoDoisPontos != -1 && pinoVirgula != -1) {
    long alvoX = comando.substring(pinoDoisPontos + 1, pinoVirgula).toInt();
    long alvoZ = comando.substring(pinoVirgula + 1).toInt();
    stepperX.moveTo(alvoX);
    stepperZ.moveTo(alvoZ);
    
    dispararPulso(); 
  }
}

void processarBotao(int b) {
  int* d = editandoX ? digitosX : digitosZ;
  switch(b) {
    case 0: // RIGHT
      if (cursorLocal < 5) cursorLocal++; 
      else if (editandoX) { editandoX = false; cursorLocal = 0; }
      break;
    case 3: // LEFT
      if (cursorLocal > 0) cursorLocal--; 
      else if (!editandoX) { editandoX = true; cursorLocal = 5; }
      break;
    case 1: // UP
      d[cursorLocal] = (d[cursorLocal] + 1) % 10;
      movimentarEmTempoReal();
      break;
    case 2: // DOWN
      d[cursorLocal] = (d[cursorLocal] - 1 + 10) % 10;
      movimentarEmTempoReal();
      break;
    case 4: // SELECT
      enviarDadosSincronizacao();
      break;
  }
}

void verificarFinsDeCurso() {
  if (digitalRead(pinoFimDeCursoX) == LOW) {
    stepperX.stop(); 
    stepperX.setCurrentPosition(stepperX.currentPosition()); 
  }

  if (digitalRead(pinoFimDeCursoZ) == LOW) {
    stepperZ.stop(); 
    stepperZ.setCurrentPosition(stepperZ.currentPosition()); 
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(pinoTrigger, OUTPUT);
  digitalWrite(pinoTrigger, LOW); 

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW); 

  
  pinMode(pinoFimDeCursoX, INPUT_PULLUP);
  pinMode(pinoFimDeCursoZ, INPUT_PULLUP);

  stepperX.setMaxSpeed(600.0);       
  stepperX.setAcceleration(400.0);  
  stepperZ.setMaxSpeed(600.0);     
  stepperZ.setAcceleration(400.0); 

  lcd.begin(16, 2);
  lcd.clear();
  lcd.cursor(); 
  lcd.blink();  
  atualizarPainel(); 
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') { 
      if (comandoAcumulado.startsWith("GOTO:")) {
        processarComandoLabVIEW(comandoAcumulado);
      }
      comandoAcumulado = ""; 
    } else {
      comandoAcumulado += c; 
    }
  }

  if (!modoRemoto) {
    if (millis() - ultimaLeituraBotao > intervaloDebounce) {
      int leitura = analogRead(pinoBotoes);
      int botao = lerBotao(leitura);
      
      if (botao != -1) {
        processarBotao(botao);
        atualizarPainel();
        ultimaLeituraBotao = millis();
      }
    }
  }

  verificarFinsDeCurso();

  stepperX.run();
  stepperZ.run();

  if (!modoRemoto && sistemaIniciouPulsos) {
    if (millis() - ultimoPulsoMovimento >= intervaloPulsoMovimento) {
      dispararPulso();
      ultimoPulsoMovimento = millis(); 
    }
  }
}
