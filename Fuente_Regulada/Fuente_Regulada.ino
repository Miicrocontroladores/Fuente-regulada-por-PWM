/*
R=100k
C=100nF
RC=10ms retrasar la descarga el maximo posible
*/

#define PWM 3
#define BTN 2

int cont=0;

//========================================================
//    INTERRUPT SERVICE ROUTINE
//========================================================

void interrupcion(){
      cont++;
      if(cont>=8){
        cont=0;
      }
      Serial.println(cont);
}

//========================================================
//    SETUP
//========================================================

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),interrupcion,FALLING); //Activa la interrupcion del pin 2
                                                                  //Indica que la interrupcion es en flanco de bajada (por pull-up)
                                                                  //Identifica la funcion "interrupion" como el vector de interrupcion

  TCCR2B = TCCR2B & B11111000 | B00000001; //maxima frecuencia de PWM en D3 y D11
                                           // 31372.55 Hz; 31.87us
                                           // Se escoge maxima para evitar rizado en RC del OPAMP

  pinMode(PWM,OUTPUT);                     //Se establece como salida el pin D3 (donde irá el PWM)
  pinMode(BTN,INPUT_PULLUP);               //Se establece como entrada con pull-up el pin del boton
}

//========================================================
//    MAIN
//========================================================

void loop() {
  
  if (cont==0)              //ciclo de 1.3%
  {
    analogWrite(PWM,0); 
    Serial.println("1.25v");
  }
  else if(cont==1)         //ciclo de 3.1%
  {
    analogWrite(PWM,5); 
    Serial.println("1.5v");
  }
  else if(cont==2)          //ciclo de 13.5%
  {
    analogWrite(PWM,32);
    Serial.println("3v");
  }
  else if(cont==3)          //ciclo de 15.6%
  {
    analogWrite(PWM,37);
    Serial.println("3.3v");
  }
  else if(cont==4)          //ciclo de 27.5%
  {
    analogWrite(PWM,67);
    Serial.println("5v");
  }
  else if(cont==5)          //ciclo de 34.5%
  {
    analogWrite(PWM,85);
    Serial.println("6v");
  }
  else if(cont==6)          //ciclo de 55,4%
  {
    analogWrite(PWM,138);   // Vavg = 2.77v
    Serial.println("9v");
  }
  else if(cont==7)           //ciclode 66%
  {
    analogWrite(PWM,168);     // Vavg = 3.3v
    Serial.println("10.5v");
  }
  
}
