#include <Servo.h>

Servo emp;


int TRIG1= 12;
int ECHO1= 11;
int DURACAO1;
int DISTANCIA1;
int pinzinho=500;
int coisinha=2500;


unsigned long millisP;
unsigned long millisL;
unsigned long millisB;

unsigned long currentMillis;


int TRIG2= 3;
int ECHO2= 2;
int DURACAO2;
int DISTANCIA2;
float FUNDO = 30; /// fundo do lixo
float centopor;


int VERDE= 6;
int AMARELO= 5;
int VERMELHO= 4;



void setup(){
	
	Serial.begin(9600);
	
	pinMode(TRIG1, OUTPUT);
	pinMode(ECHO1, INPUT);
	
	emp.attach(13,pinzinho,coisinha);
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

	if (DISTANCIA1 == 0)
	{
		DISTANCIA1 = 999;
	};
	
	
	if (DISTANCIA1 <= 5)
	{
		emp.write(180); 
		millisP = currentMillis; 						//// TIMER RESETA QUANDO DETECTAR MOVIMENTO	

	} else if ( (currentMillis - millisP) >= 6000) 		// DELAY DE 6 SEGUNDOS

	  {
			emp.write(0);
	  };

	
}

void lixo(){
	

	if ( (currentMillis - millisP) >= 7000)
	{

  
	
		if ( (currentMillis - millisL) > 3000) //// A cada 3 segundos,
		{
			
			digitalWrite(TRIG2, HIGH);
			digitalWrite(TRIG2, LOW);
	
		
			DURACAO2=pulseIn(ECHO2, HIGH); 
			DISTANCIA2=DURACAO2/58.2;
		
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
			
			// 		^ ^ ^ ^
			
			millisL = currentMillis;
		};
  };
}	

void leds(){
	
	if (centopor >= 90)
	{

		if ( ((currentMillis - millisB) >= 0) && ( (currentMillis - millisB) < 450))
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
		};
    
    
		
	} else if (centopor >= 60)
	{
		digitalWrite(VERMELHO, LOW);
		digitalWrite(AMARELO, HIGH);
		digitalWrite(VERDE, HIGH);
		
	} else if (centopor >= 30)
	{
		digitalWrite(VERMELHO, LOW);
		digitalWrite(AMARELO, LOW);
		digitalWrite(VERDE, HIGH);
		
	} else
	{
		digitalWrite(VERMELHO, LOW);
		digitalWrite(AMARELO, LOW);
		digitalWrite(VERDE, LOW);
		
	}
}
void loop(){
	
	portinhola();
	lixo();
	leds();

	currentMillis = millis();

	//if ( (currentMillis - millisP) >= 20000)
	//{
	//	millisP = currentMillis;
	//	millisP += 1000;
	//};

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

	Serial.println(millisP);

}

// https://www.norwegiancreations.com/2017/09/arduino-tutorial-using-millis-instead-of-delay/