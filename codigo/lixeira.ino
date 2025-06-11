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
float FUNDO = 25; // Onde seria o fundo do lixo, determinado pelo valor que DISTANCIA2 retorna quando a lixeira estiver vazia.
float centopor;


int VERDE= 6;
int AMARELO= 5;
int VERMELHO= 4;



void setup(){
	
	Serial.begin(9600);
	
	pinMode(TRIG1, OUTPUT);
	pinMode(ECHO1, INPUT);
	
	emp.attach(13,pinzinho,coisinha); //Servo motor no pino 13
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
	{								// Se ficar recebendo só 99 ou 98 de Distância,
		DISTANCIA1 = 98;					// significa que tem um problema de 
	};								// mal contato com os sensores
	
	if (DISTANCIA1 >=150)
	{
		DISTANCIA1 = 150;
	};
	
	
	if (DISTANCIA1 <= 25)
	{
		emp.write(180); 					// ABRE A LIXEIRA,
		millisP = currentMillis; 				// RESETA O TIMER,

	} else if ( (currentMillis - millisP) >= 4000) 			// ESPERA 4 SEGUNDOS ENQUANTO NÃO TIVER NADA PERTO

	{
		emp.write(0);						// FECHA A LIXEIRA.
	};

	
}

void lixo(){
	
  
			
	if (DISTANCIA2 >= 331)
	{
		DISTANCIA2 = 101;
	};

	if ( (currentMillis - millisP) >= 6000)
	{
		
  		if ( (currentMillis - millisL) > 3000)
		{
			
			digitalWrite(TRIG2, HIGH);
	    		digitalWrite(TRIG2, LOW);
	    		DURACAO2=pulseIn(ECHO2, HIGH); 
	    		DISTANCIA2=DURACAO2/58.2;

	    		DISTANCIA2 -= 10; // offset em cm pra determinar a altura onde seria o 100%. Quando maior o valor, menor a altura.
			
		
			// Faz uma porcentagem usando DISTANCIA2 e FUNDO, e inverte,
			//Assim, quanto mais perto do sensor, maior a porcentagem
			float centopor = 100 - constrain( ((DISTANCIA2 * 100) / FUNDO), 0, 100); 
			
			
			// PLACEHOLDER ATÉ O APLICATIVO FICAR PRONTO
			// 		V V V V V
			
			
			if (centopor < 70)
			{
				for (int loop = 0; loop<=10; loop++) { Serial.println(); };
				
				Serial.print("lixeira: ");
				Serial.print(int(centopor));
				Serial.println("% cheia");
				
			} else
			{
				for (int loop = 0; loop<=10; loop++) { Serial.println(); };
				
				Serial.print("!!!ALERTA!!!");
				Serial.print("\t");
				Serial.println("!!!LIXEIRA CHEIA!!!");
				
				Serial.print("lixeira: ");
				Serial.print(int(centopor));
				Serial.println("% cheia");
				
			};
			
			// 		^ ^ ^ ^ ^
			
			millisL = currentMillis;
		};
  	};
}	

void leds(){

	// Ascende um led conforme a porcentagem
	if (centopor >= 70)
	{

    		digitalWrite(VERMELHO, HIGH);
    		digitalWrite(AMARELO, LOW);
    		digitalWrite(VERDE, LOW);
		
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
			digitalWrite(VERDE, HIGH);
			digitalWrite(AMARELO, LOW);
			digitalWrite(VERMELHO, LOW);
			
		} else
		{
			digitalWrite(VERDE, LOW);
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
	
	if ( ((currentMillis - millisP) <= 3500) || ((currentMillis - millisP) >= 4010) )
	{
		portinhola();
	};
	
	lixo();
	leds();

	currentMillis = millis();
	
	
	
	////	IMPRIME VALORES DOS SENSORES E DOS MILLIS
	////	PARA DEBUGGING;
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
