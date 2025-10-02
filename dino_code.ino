#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  

// --- Pines ---
int buzzer = 11;   // Pin del buzzer activo

// Caracteres Dino y obstáculos
byte DINO_PARADO_PARTE_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00001}; 
byte DINO_PARADO_PARTE_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B01000};
byte DINO_PIE_DERE_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00001};
byte DINO_PIE_DERE_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B00000};
byte DINO_PIE_IZQU_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00000};
byte DINO_PIE_IZQU_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B01000};
byte DOS_RAMAS_PART_1[8] = {B00000, B00100, B00100, B10100, B10100, B11100, B00100, B00100};
byte DOS_RAMAS_PART_2[8] = {B00100, B00101, B00101, B10101, B11111, B00100, B00100, B00100};
byte AVE_ALAS_PART1[8] = {B00001, B00001, B00001, B00001, B01001, B11111, B00000, B00000};
byte AVE_ALAS_PART2[8] = {B00000, B10000, B11000, B11100, B11110, B11111, B00000, B00000};

// Variables Dino
int columna_dino1 = 1;
int columna_dino2 = 2;
int fila_dino = 1;
unsigned long reloj=0;
int periodo=100;
int flag=1;

// Variables obstáculos
int fila_rama=0;
int columna_rama=13;
int periodo2=100;
unsigned long reloj2=0;
int a=0;
int b=1;
int c=2;
int d=0;
unsigned long reloj3=0;
int periodo3=100; 
int puntos =0;
int punto2 =0;
int numerorandom=0;
int columnaave= 13;
int fila_ave=1;
int senalactual=0;
int senalantigua=0;
int f=13;
int aceleracion=1;

// Variables para salto automático
bool saltando = false;
unsigned long tiempoSalto = 0;
int duracionSalto = 400;   // tiempo total del salto (ms)
int mitadSalto = 200;      // momento en que baja

// --- MELODÍA "Time To Level Up" simplificada ---
int melodia[] = {523, 659, 784, 659, 880, 784, 659, 523}; // notas (C5, E5, G5, etc.)
int duraciones[] = {200, 200, 200, 200, 300, 200, 200, 400}; // ms cada nota
int totalNotas = 8;
int indiceNota = 0;
unsigned long tiempoNota = 0;

void setup() {
  lcd.begin(16, 2);               
  lcd.createChar(0,DINO_PARADO_PARTE_1);      
  lcd.createChar(1,DINO_PARADO_PARTE_2);               
  lcd.createChar(2,DINO_PIE_DERE_PART_1);      
  lcd.createChar(3,DINO_PIE_DERE_PART_2);          
  lcd.createChar(4,DINO_PIE_IZQU_PART_1);      
  lcd.createChar(5,DINO_PIE_IZQU_PART_2);          
  lcd.createChar(6,DOS_RAMAS_PART_1);      
  lcd.createChar(7,DOS_RAMAS_PART_2);

  pinMode(13, INPUT); // pulsador
  pinMode(buzzer, OUTPUT); // buzzer
} 

void loop() {
  // --- Música de fondo ---
  if (millis() - tiempoNota > duraciones[indiceNota]) {
    tiempoNota = millis();
    tone(buzzer, melodia[indiceNota], duraciones[indiceNota] * 0.9);
    indiceNota++;
    if (indiceNota >= totalNotas) indiceNota = 0; // repetir loop
  }

  // --- Animación del Dino caminando ---
  if(millis()>reloj+periodo){		
    reloj=millis();
    if(flag==1){ flag=2; }
    else if(flag==2){ flag=1; }  
  }  
  
  // --- Movimiento de obstáculos ---
  if(millis()>reloj2+periodo2){			
    reloj2=millis();
    columna_rama=columna_rama-1;
    if(columna_rama<0){
      columna_rama=13;  
      periodo2=periodo2-aceleracion;
      numerorandom=random(0,3);
    }
      
    f=columna_rama+1;
    lcd.setCursor(f,1); lcd.print(" ");    
    lcd.setCursor(f,0); lcd.print(" ");   
    lcd.setCursor(0,1); lcd.print(" ");
    lcd.setCursor(0,0); lcd.print(" ");
    a=1;
  }

  // --- Dibujar Dino en piso ---
  if(!saltando){
    if(flag==1){  
      lcd.setCursor(columna_dino1,fila_dino); lcd.write(byte(2));
      lcd.setCursor(columna_dino2,fila_dino); lcd.write(byte(3));
    }
    if(flag==2){
      lcd.setCursor(columna_dino1,fila_dino); lcd.write(byte(4));
      lcd.setCursor(columna_dino2,fila_dino); lcd.write(byte(5));
    }
  }
  
  // --- Dibujar obstáculos ---
  if(a==1){
    if(numerorandom == 1){
      fila_rama = 1;
      lcd.createChar(6,DOS_RAMAS_PART_1);
      lcd.setCursor(columna_rama,fila_rama); 
      lcd.write(byte(6));
    }
    else if(numerorandom == 2){
      fila_rama = 1;
      lcd.createChar(7,DOS_RAMAS_PART_2);
      lcd.setCursor(columna_rama,fila_rama);
      lcd.write(byte(7));
    }
    else{	// ave
      columnaave=columna_rama-1;
      fila_rama = 0;
      lcd.createChar(6,AVE_ALAS_PART1);
      lcd.setCursor(columnaave,fila_rama); lcd.write(byte(6));
      lcd.createChar(7,AVE_ALAS_PART2);  
      lcd.setCursor(columna_rama,fila_rama); lcd.write(byte(7));   
    }
    a=0;
  }
  
  // --- Condiciones de colisión ---
  if(saltando==true && (columna_rama==1||columna_rama==2||columnaave==1||columnaave==2) && fila_rama==0 ){
    lcd.clear();
    lcd.setCursor(5, 0); lcd.print("GAME OVER");
    tone(buzzer, 200, 800); // beep largo grave
    delay(2000);
    lcd.clear();
    columna_rama=15;
    periodo2=100;
    puntos=0;
    punto2=0;
  }
  
  if((columna_rama==b||columna_rama==c) && fila_rama==1 && !saltando){    
    lcd.clear();
    lcd.setCursor(5, 0); lcd.print("GAME OVER");
    tone(buzzer, 200, 800); // beep largo grave
    delay(2000);
    lcd.clear();
    columna_rama=15;
    periodo2=100;
    puntos=0;
    punto2=0;
  }
  
  // --- SALTO AUTOMÁTICO ---
  senalactual = digitalRead(13);

  if (senalactual == HIGH && senalantigua == LOW && !saltando) {
    saltando = true;
    tiempoSalto = millis();

    // Sonido de salto
    tone(buzzer, 800, 150); 

    lcd.setCursor(columna_dino1, 1); lcd.print(" ");
    lcd.setCursor(columna_dino2, 1); lcd.print(" ");

    lcd.setCursor(columna_dino1, 0); lcd.write(byte(2));
    lcd.setCursor(columna_dino2, 0); lcd.write(byte(3));
  }

  if (saltando) {
    unsigned long tiempoEnAire = millis() - tiempoSalto;

    if (tiempoEnAire > mitadSalto) {
      lcd.setCursor(columna_dino1, 0); lcd.print(" ");
      lcd.setCursor(columna_dino2, 0); lcd.print(" ");

      if (flag == 1) {
        lcd.setCursor(columna_dino1, 1); lcd.write(byte(2));
        lcd.setCursor(columna_dino2, 1); lcd.write(byte(3));
      } else {
        lcd.setCursor(columna_dino1, 1); lcd.write(byte(4));
        lcd.setCursor(columna_dino2, 1); lcd.write(byte(5));
      }
    }

    if (tiempoEnAire > duracionSalto) {
      saltando = false;
    }
  }

  senalantigua = senalactual;

  // --- Puntaje ---
  if(millis()>reloj3+periodo3){		
    reloj3=millis();
    lcd.setCursor(14, 1); lcd.print(puntos);
    puntos=puntos+1;
    if(puntos==100){
      puntos=0;
      punto2=punto2+1;
      if(punto2==100){ punto2=0; }
    }
  }  
  lcd.setCursor(14, 1); lcd.print(puntos);
  lcd.setCursor(14, 0); lcd.print(punto2);
}
