#include <Servo.h>

Servo emp;


int TRIG1= 12;
int ECHO1= 11;
int pinzinho=500;
int coisinha=2500;
int DURACAO1, DISTANCIA1;


unsigned long millisP, millisL, millisB;

unsigned long currentMillis;


int TRIG2= 3;
int ECHO2= 2;
int DURACAO2, DISTANCIA2;
float FUNDO = 25; /// fundo do lixo
float centopor;


int VERDE= 6;
int AMARELO= 5;
int VERMELHO= 4;



void setup(){
	
	Serial.begin(9600);
	
	pinMode(TRIG1, OUTPUT);
	pinMode(ECHO1, INPUT);
	
	emp.attach(13,pinzinho,coisinha);		//	Servo motor no pino 13
	emp.write(0);
	
	pinMode(TRIG2, OUTPUT);
	pinMode(ECHO2, INPUT);
	
	pinMode(VERDE, OUTPUT);
	pinMode(AMARELO, OUTPUT);
	pinMode(VERMELHO, OUTPUT);
	
	digitalWrite(VERMELHO, LOW);
	digitalWrite(AMARELO, LOW);
	digitalWrite(VERDE, LOW);
	
	centopor = 0;
  

  millisP = millis();
  millisL = millis();
  millisB = millis();
  
}

void portinhola(){

	digitalWrite(TRIG1, HIGH);	
	digitalWrite(TRIG1, LOW);
	DURACAO1=pulseIn(ECHO1, HIGH);
	DISTANCIA1=DURACAO1/58.2;

	if (DISTANCIA1 <= 0)
	{									//	Se ficar recebendo só 99 ou 98 de Distância,
		DISTANCIA1 = 98;				//	significa que tem um problema de 
	};									// 	mal contato com os sensores
	if (DISTANCIA1 >=331)
	{
		DISTANCIA1 = 99;
	};
	
	
	if (DISTANCIA1 <= 25)
	{
		emp.write(180); //Servo gira 180 graus
		millisP = currentMillis; // TIMER RESETA QUANDO DETECTAR MOVIMENTO	

	} else if ( (currentMillis - millisP) >= 4000) // DELAY DE 4 SEGUNDOS

	  {
			emp.write(0);
	  };

	
}

void lixo(){
	
  
			
	if (DISTANCIA2 >= 331)
	{
		DISTANCIA2 = 99;
	};

	if (DISTANCIA2 <= -200)
	{
		DISTANCIA2 = 98;
	};

	if ( (currentMillis - millisP) >= 6000)
	{

  
	
		if ( (currentMillis - millisL) > 3000)
		{
			
			digitalWrite(TRIG2, HIGH);
	    digitalWrite(TRIG2, LOW);
	
		
	    DURACAO2=pulseIn(ECHO2, HIGH); 
	    DISTANCIA2=DURACAO2/58.2;

	    DISTANCIA2 -= 10;     // offset em cm pra determinar onde seria o ponto 0
			
		
			//pega a porcentagem entre 0 e 100 com FUNDO e DISTANCIA2	
			float porcento = constrain( ((DISTANCIA2 * 100) / FUNDO), 0, 100); 
			centopor = 100 - porcento;	
			
			
			// PLACEHOLDER ATÉ O APLICATIVO FICAR PRONTO
			// 		V V V V V
			
			
			if (centopor < 90)
			{
				Serial.print("lixeira: ");
				Serial.print(int(centopor));
				Serial.println("% cheia");
				Serial.println();
				
			} else
			{ 
				Serial.print("!!!ALERTA!!!");
				Serial.print("\t");
				Serial.println("!!!LIXEIRA CHEIA!!!");
				
				Serial.print("lixeira: ");
				Serial.print(int(centopor));
				Serial.println("% cheia");
				Serial.println();
			};
			
			// 		^^^^^^^^^
			
			millisL = currentMillis;
		};
  };
}	

void leds(){
	
	if (centopor >= 70)
	{

    digitalWrite(VERMELHO, HIGH);
    digitalWrite(AMARELO, LOW);
    digitalWrite(VERDE, LOW);

		/*if ( ((currentMillis - millisB) >= 0) && ( (currentMillis - millisB) < 450))
		{
			
			digitalWrite(VERMELHO, HIGH);
			digitalWrite(AMARELO, HIGH);
			digitalWrite(VERDE, HIGH);

		};
		if ( (currentMillis - millisB) >= 675)
		{	
			digitalWrite(VERMELHO, LOW);
			digitalWrite(AMARELO, LOW);
			digitalWrite(VERDE, LOW);

			if ( (currentMillis - millisB) >= 900)
			{
				millisB = currentMillis;
			};
		};*/
    
    
		
	} else if (centopor >= 50)
	{
    digitalWrite(VERDE, LOW);
    digitalWrite(AMARELO, HIGH);
	  digitalWrite(VERMELHO, LOW);
		
	} else if (centopor >= 25)
	{
		digitalWrite(VERMELHO, LOW);
		digitalWrite(AMARELO, LOW);
		digitalWrite(VERDE, HIGH);
		
	} else
	{
		if ((currentMillis - millisB) < 1000)
		{
			digitalWrite(VERDE, LOW);
			digitalWrite(AMARELO, LOW);
			digitalWrite(VERMELHO, LOW);
			
		} else
		{
			digitalWrite(VERDE, HIGH);
			digitalWrite(AMARELO, LOW);
			digitalWrite(VERMELHO, LOW);
			
			if ((currentMillis - millisB) >= 2000)
			{
				millisB = currentMillis;
			};
			
		};
		
	};
}
void loop(){
	
	portinhola();
	lixo();
	leds();

	currentMillis = millis();
	
	////	IMPRIME VALORES DOS SENSORES E DOS MILLIS
	////	PARA DEBUGGING;
	////	DESLIGUE ISSO NA HORA DE APRESENTAR
	Serial.print(DISTANCIA1);
	Serial.print("\t");
  
	Serial.print(DISTANCIA2);
	Serial.print("\t");

	Serial.print(currentMillis - millisP);
	Serial.print("\t"); Serial.print("\t");
	
	Serial.print(currentMillis - millisL);
	Serial.print("\t");

	Serial.print(currentMillis - millisB);
	Serial.print("\t"); Serial.print("\t");

	Serial.print(millisP);
	Serial.println("\t");

  

}

// https://www.norwegiancreations.com/2017/09/arduino-tutorial-using-millis-instead-of-delay/

//https://community.appinventor.mit.edu/t/bluetooth-hc-06-arduino-send-receive-send-text-file-multitouch-image/9518/15
		// 		14. Where do we connect the Bluetooth module in Arduino UNO?


    // HC 05      BLUETOOTH

//https://www.youtube.com/watch?v=0zz1n6wVoz0&t=390s
