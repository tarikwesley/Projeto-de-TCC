// ========================================================================================================
// --- Adiciona as Bibliotecas Necessárias ---
#include <EmonLib.h>          //Biblioteca pra calcular valores de corrente e tensão RMS
#include <Wire.h>             //Biblioteca que permite enviar e receber dados por meio de uma interface TWI/I2C (interface a dois fios) em uma rede de dispositivos ou sensores.
#include <LiquidCrystal_I2C.h>  //Biblioteca para utilização do LCD

// ========================================================================================================
// --- Configuração do Display ---
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

// ========================================================================================================
// --- Declaração das Variáveis ---
  const int AmpIn=A1;          //Corrente de entrada
  float tensao = 127;          //Tensão de entrada
  float corrente;               
  float potencia; 
  float fatorCalibracao=9;     //Fator de Calibração= N° de espiras no secundario/resistência de carga --> 2000/220 = 9.09

// ========================================================================================================
// --- Instância do Objeto sensor ---
  EnergyMonitor sensor;
  
void setup() {  
  lcd.begin (16,2);        //Inicia o LDC
  sensor.current(AmpIn,fatorCalibracao);  //Calcula a corrente lida pelo sensor a partir do fator de calibração
  pinMode(A1,INPUT);                      //Coloca o pino analógico A1 como entrada
  Serial.begin(9600);                     //Inicia a comunicação serial e 9600
}

void loop() {
  corrente=sensor.calcIrms(2960);        //Cálcula o valor RMS de corrente usando 2960 amostras
   
// ========================================================================================================
// --- Controle de Isolamento ---
        
          if(corrente > 0.05){           
            corrente = corrente;
          }else{
            corrente=0;
          }
                   
          if(corrente > 0.05){
            potencia=tensao*corrente;
          }else{
            potencia=0;
            }

// ========================================================================================================
// --- Exibição no Monitor Serial e no LCD ---
           Serial.print("Corrente = ");
           Serial.print(corrente);
           Serial.println(" A");
            
           Serial.print("Potencia = ");
           Serial.print(potencia);
           Serial.println(" W");
           Serial.println("********************");

           lcd.clear(); 
           lcd.setBacklight(HIGH);
           lcd.setCursor(0,0);
           lcd.print("Corrente=");
           lcd.print(corrente);
           lcd.print("A");    
           lcd.setCursor(0,1);
           lcd.print("Potencia=");
           lcd.print(potencia);
           lcd.print("W");       
  delay(1000);

}
