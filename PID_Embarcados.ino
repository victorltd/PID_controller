// Contador de RPM  by: http://elprofegarcia.com
// Conexion de la entrada de la interrupcion 0  por el PIN 2
// Configurar el monitor serial a 57600 Baudios para visualizar los RPM
// Tienda para comprar Materiales http://dinastiatecnologica.com

volatile int contador = 0;   // Variable entera que se almacena en la RAM del Micro

#include <Servo.h>  //Vou usar a biblioteca de servo pra controlar o esc

Servo esc; //Criei uma classe servo com o nome esc
 
void setup() {
  Serial.begin(9600);
  //sensor optico
  attachInterrupt(0,interrupcion0,RISING);  // Interrupcion 0 (pin2) 

  //motor
  esc.attach(8); //Estou dizendo para o arduino onde está conectado o pino de sinal do esc
  esc.writeMicroseconds(1000); //Iniciaalizar o sinal em 1000, estará desligado o meu motor

  delay(7000);

}                                          
int throttle= 1130; //valor inicial do sinal pwm do motor
float pwmMotor;
double error=0;
double rotacao;
double lastRotacao;

double kP= 1.0, 
       kI= 0.0,
       kD= 0.0;

double P=0,
       I=0,
       D=0;

double PID=0;

double setPoint=1500;  //defino o valor de rpm que eu quero
long lastProcess;



 
void loop() {
  rotacao=contador*30;

  //Implementação PID
  error= setPoint - rotacao;
  float deltaTime= (millis() - lastProcess) / 1000.0;
  lastProcess= millis();

  //P
  P= error * kP;

  //I
  I+= (error *kI) * deltaTime;

  D= (lastRotacao - rotacao) * kD * deltaTime;
  lastRotacao= rotacao;


  PID= P + I + D;

  pwmMotor = throttle + PID;

  esc.writeMicroseconds(pwmMotor);

  
}
 
void interrupcion0()    // Funcion que se ejecuta durante cada interrupion
{
  contador++;           // Se incrementa en uno el contador
}
