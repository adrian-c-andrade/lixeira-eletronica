#include <Servo.h>

Servo emp;


int TRIG1= 12;
int ECHO1= 11;
int DURACAO1;
int DISTANCIA1;
int pinzinho=500;
int coisinha=2500;
unsigned long millisP= millis();


int TRIG2= 3;
int ECHO2= 2;
int DURACAO2;
int DISTANCIA2;
float FUNDO = 90; /// fundo do lixo
float centopor;
unsigned long millisL = millis();


int VERDE= 6;
int AMARELO= 5;
int VERMELHO= 4;
unsigned long millisB = millis();



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
}

void portinhola(){
	
	digitalWrite(TRIG1, HIGH);	
	digitalWrite(TRIG1, LOW);
	DURACAO1=pulseIn(ECHO1, HIGH);
	DISTANCIA1=DURACAO1/58.2;
	
	
	if (DISTANCIA1 <= 50)
	{
		
		emp.write(90); 
		millisP = millis(); 						//// TIMER RESETA QUANDO DETECTAR MOVIMENTO	

	} else if ( (millis() - millisP) > 5000) 		// DELAY DE 5 SEGUNDOS
	{
		
		if (DISTANCIA1 > 50) 
		{	
			emp.write(0);
		};
		
	};
	
}

void lixo(){
	
	if ( (millis() - millisP) > 5000) //// Essa função não roda enquanto a porta estiver aberta
	{
	
		if ( (millis() - millisL) > 3000) //// A cada 3 segundos,
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
				
				// Esse comando vai ser importante na hora de montar o lixo pra determinar o valor de FUNDO
				//Serial.Println(DISTANCIA2);
			};
			
			// 		^ ^ ^ ^
			
			
			
			millisL = millis();
			
		};
	};
}	

void leds(){
	
	if (centopor >= 90)
	{
			
		if ( (millis() - millisB) < 500)
		{
			digitalWrite(VERMELHO, HIGH);
			digitalWrite(AMARELO, HIGH);
			digitalWrite(VERDE, HIGH);
			
			if ( (millis() - millisB) > 250)
			{	
			digitalWrite(VERMELHO, LOW);
			digitalWrite(AMARELO, LOW);
			digitalWrite(VERDE, LOW);
			
			};
			
		} else
		{
			millisB = millis();
			
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
}