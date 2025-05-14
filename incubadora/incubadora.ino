#define ledPin 4 
#define fanPin 6 

int contLedInterval = 0;
int contLedDuration = 0;
int ledState = 1;

int contFanInterval = 0;
int contFanDuration = 0;
int fanState = 1;

//configuración de los tiempos
int ledInterval = 24;  // En horas
int ledDuration = 12;  // En horas
int fanInterval = 2.4;  // En horas
int fanDuration = 3;   // En minutos

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);

  // Configuração do timer1 
  TCCR1A = 0;                        // El registro de control A queda todo en 0, pines OC1A y OC1B deshabilitados
  TCCR1B = 0;                        //limpia el registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = 0xC2F8;                    // inicia timer para desbordamiento 1 segundo
                                     // 65536-(16MHz/1024/1Hz - 1) = 49912 = 0xC2F8
  
  TIMSK1 |= (1 << TOIE1);           // habilita la interrupcion del TIMER1

  digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  digitalWrite(fanPin, digitalRead(fanPin) ^ 1);
}


void loop()
{
  //loop principal.
}


ISR(TIMER1_OVF_vect)                              //interrupcion del TIMER1 
{
  TCNT1 = 0xC2F7;                                 // Renicia TIMER
  
  contLedInterval++;
  contLedDuration++;
  
  contFanInterval++;
  contFanDuration++;
  
  if(contLedInterval==ledInterval*60*60){
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1); //invierte el estado do led
    contLedInterval = 0;
    contLedDuration = 0;  
    ledState = 1;  
  }  
  
  if(ledState && contLedDuration==ledDuration*60*60){
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1); //invierte el estado do led
    contLedDuration = 0;
    ledState = 0;
  } 

  if(contFanInterval==fanInterval*60*60){
    digitalWrite(fanPin, digitalRead(fanPin) ^ 1); //invierte el estado del ventilador
    contFanInterval = 0;
    contFanDuration = 0;  
    fanState = 1;  
  }  
  
  if(fanState && contFanDuration==fanDuration*60){
    digitalWrite(fanPin, digitalRead(fanPin) ^ 1); //invierte el estado del ventilador
    contFanDuration = 0;
    fanState = 0;
  } 
  
}
