

#include <Ultrasonic.h>
#include <AFMotor.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(53,52,51,50,49,48);

#define pulsadoram 45
#define pulsadorro 43
#define pulsadoracep 41
int valorlong = 1;
int valorlongitudinalelegido;
int valortrans = 1;
int valortransversalelegido;

Ultrasonic sensorlong(22,23); // trig , echo
Ultrasonic sensortransversal(24,25);


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


int cmlong;
int cmtrans;
int cmmoverlong;
int cmmovertrans;


void setup() {
  motor3.run(RELEASE);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor4.run(RELEASE);
  Serial.begin(9600);
  lcd.clear();
  lcd.begin(16, 2);
  pinMode(pulsadoram, INPUT);
  pinMode(pulsadorro, INPUT);
  pinMode(pulsadoracep, INPUT);
}

void loop() {
  Menu1();
}

void Menu1 (){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A - Mover Carros");
  lcd.setCursor(0,1);
  lcd.print("B - Mover Gancho");
  while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW){}

  if(digitalRead(pulsadoram) == HIGH){
    
    lcd.clear();
    MovimientoCarros1();
    cmmovertrans = ElegirMovimientoTransversal();
    cmtrans = sensortransversal.read();
    MovimientoTransversal();
    //--------------------
    MoverCarros2();
    cmmoverlong = ElegirMovimientoLongitudinal();
    cmlong = sensorlong.read();
    MovimientoLongitudinal();
  }

  if(digitalRead(pulsadorro) == HIGH){
    
    lcd.clear();
    MoverGanchos();

  }
}

void BajarGancho(){
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  delay(9000);
  motor3.run(RELEASE);
}

void SubirGancho(){
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  delay(10000);
  motor3.run(RELEASE);
}

void MoverCarros(){
  cmmovertrans = ElegirMovimientoTransversal();
  cmtrans = sensortransversal.read();
  cmmoverlong = ElegirMovimientoLongitudinal();
  cmlong = sensorlong.read();
  MovimientoTransversal();
  MovimientoLongitudinal();
}

int ElegirMovimientoLongitudinal(){

    switch (valorlongitudinalelegido){
      case 1:
      return 2;
      break;

      case 2:

      return 7;
      break;

      case 3:

      return 17;
      break;

      case 4:

      return 27;
      break;

      case 5:

      return 37;
      break;

      case 6:

      return 47; //f
      break;

      case 7:

      return 57;
      break;

      case 8:

      return 68;
      break;

      case 9:

      return 77;
      break;
    }
}

int ElegirMovimientoTransversal(){


    switch (valortransversalelegido){
      case 1:
      return 0;
      break;

      case 2:
      Serial.println("2");
      return 7;
      break;

      case 3:
      Serial.println("3");
      return 16;
      break;

      case 4:
      Serial.println("4");
      return 28;
      break;

      case 5:
      Serial.println("5");
      return 39;
      break;

      case 6:
      Serial.println("6");
      return 44;
      break; 
    }
}

void MovimientoLongitudinal(){

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("En movimiento...");
  
   if(cmlong > cmmoverlong){
    while(sensorlong.read() > cmmoverlong){
      motor1.setSpeed(255);
      motor2.setSpeed(255);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      delay(100);
    }
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }

  if(cmlong < cmmoverlong){
    while(sensorlong.read() < cmmoverlong){
      motor1.setSpeed(255);
      motor2.setSpeed(255);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(100);
    }
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }

}

void MovimientoTransversal(){
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("En movimiento...");

    do{
      motor4.setSpeed(255);
      motor4.run(BACKWARD);
      delay(100);
    }while(sensortransversal.read() > cmmovertrans);
    motor4.run(RELEASE);
  

  if(cmtrans < cmmovertrans){
    while(sensortransversal.read() < cmmovertrans){
      motor4.setSpeed(255);
      motor4.run(FORWARD);
      delay(100);
    }
    motor4.run(RELEASE);
  }
}

void MovimientoCarros1(){

  lcd.setCursor(0,0);
  lcd.print("Eje transversal:");

  switch (valortrans){
    case 1:
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje transversal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print(valortrans);
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      if(valortrans = 1){
        valortrans = 6;
      }
    
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valortrans = valortrans + 1;
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valortransversalelegido = valortrans;

    }

    break;

    case 2:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje transversal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print(valortrans);
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valortrans = valortrans - 1;
    
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valortrans = valortrans + 1;
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valortransversalelegido = valortrans;

    }

    break;

    case 3:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje transversal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print(valortrans);
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valortrans = valortrans - 1;
    
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valortrans = valortrans + 1;
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valortransversalelegido = valortrans;

    }

    break;

    case 4:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje transversal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print(valortrans);
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valortrans = valortrans - 1;
    
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valortrans = valortrans + 1;
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valortransversalelegido = valortrans;

    }

    break;

    case 5:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje transversal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print(valortrans);
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valortrans = valortrans - 1 ;
    
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valortrans = valortrans + 1;
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valortransversalelegido = valortrans;

    }

    break;

    case 6:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje transversal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print(valortrans);
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valortrans = valortrans -1;
    
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valortrans = 1;
      
      lcd.clear();
      MovimientoCarros1();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valortransversalelegido = valortrans;

    }

    break;


  }
}

void MoverCarros2(){
  lcd.setCursor(0,0);
  lcd.print("Eje longitudinal:");

  switch (valorlong){

    case 1:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje longitudinal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print("A");
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      if(valorlong = 1){
        valorlong = 9;
      }
    
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valorlong = valorlong + 1;
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valorlongitudinalelegido = valorlong;

    }

    break;

    case 2:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje longitudinal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print("B");
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valorlong = valorlong - 1;
    
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valorlong = valorlong + 1;
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valorlongitudinalelegido = valorlong;

    }

    break;

    case 3:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje longitudinal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print("C");
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valorlong = valorlong - 1;
    
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valorlong = valorlong + 1;
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valorlongitudinalelegido = valorlong;

    }

    break;

    case 4:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje longitudinal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print("D");
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valorlong = valorlong - 1;
    
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valorlong = valorlong + 1;
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valorlongitudinalelegido = valorlong;

    }

    break;

    case 5:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje longitudinal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print("E");
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valorlong = valorlong - 1;
    
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valorlong = valorlong + 1;
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valorlongitudinalelegido = valorlong;

    }

    break;

    case 6:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje longitudinal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print("F");
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valorlong = valorlong - 1;
    
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valorlong = valorlong + 1;
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valorlongitudinalelegido = valorlong;

    }

    break;

    case 7:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje longitudinal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print("G");
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valorlong = valorlong - 1;
    
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valorlong = valorlong + 1;
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valorlongitudinalelegido = valorlong;

    }

    break;

    case 8:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje longitudinal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print("H");
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valorlong = valorlong - 1;
    
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadorro) == HIGH){
    
      valorlong = valorlong + 1;
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valorlongitudinalelegido = valorlong;

    }

    break;

    case 9:

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eje longitudinal:");
    lcd.setCursor(0,1);
    lcd.print("Elegir con C > ");
    lcd.print("I");
    delay(500);
    while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW && digitalRead(pulsadoracep) == LOW){}

    if(digitalRead(pulsadoram) == HIGH){

      valorlong = valorlong - 1;
    
      lcd.clear();
      MoverCarros2();
    }

    if(digitalRead(pulsadorro) == HIGH){

      if(valorlong = 9){
        valorlong = 1;
      }
      lcd.clear();
     MoverCarros2();
    }

    if(digitalRead(pulsadoracep) == HIGH){
      valorlongitudinalelegido = valorlong;

    }

    break;


  }
}

void MoverGanchos(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A - Subir Gancho");
  lcd.setCursor(0,1);
  lcd.print("B - Bajar Gancho");
  delay(1000);
  while(digitalRead(pulsadoram) == LOW && digitalRead(pulsadorro) == LOW){}

  if(digitalRead(pulsadorro) == HIGH){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bajando gancho");
    BajarGancho();
    Menu1();
  }

  if(digitalRead(pulsadoram) == HIGH){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Subiendo gancho");
    SubirGancho();
    Menu1();
  }
}



