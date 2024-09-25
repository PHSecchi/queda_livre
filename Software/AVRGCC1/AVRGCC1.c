#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>	
#include <avr/interrupt.h>
#include "def_principais.h"	
#include "LCD.h"
#include "LCD_4bits_messagens.h"

    ISR(INT0_vect);
	ISR(INT1_vect);
	ISR(TIMER1_OVF_vect);
	

// variaveis
    float tempo=0;
	unsigned int tm1=0;
	unsigned long queda=0;
	unsigned char  estado=0;	//declara variável global
	
	#define BT1 PD0
	#define BT2 PD1
	#define SS1 PD2
	#define SS2 PD3
	#define BBN PD4
	
	
//--------------------------------------------------------------------------------------
int main()
{	unsigned char digitos[tam_vetor];	//declaração da variável para armazenagem dos digitos
	

	DDRD = 0b11110000;          //Pinos de entrada
	PORTD= 0b00000011;			//habilita o pull-up		 
	DDRB=  0b00111111;				//PORTD como saída (display)
	PORTB= 0b00000000;				//desliga o display
	    
	inic_LCD_4bits();				//inicializa o LCD
	cmd_LCD(0x01,0); 				//desloca cursor para a segunda linha
	
   
   
   //Interrupção INT0 e INT1
   EICRA= 0b00001010;
   EIMSK= 0b00000011;
   
   //Timer 1
   TCCR1A= 0b00000000;
   TCCR1B= 0b00000101;
   TIMSK1= 0b00000000;
    
   
	while (1)
	{
	 switch(estado)
 {   
   case 0:{cmd_LCD(0x84,0);	
		  escreve_LCD_Flash(msg_bem);
		  cmd_LCD(0xC5,0);	
		  escreve_LCD_Flash(msg_vindo);
		  _delay_ms(2000);
		   estado=1; cmd_LCD(0x01,0);	  
		  break;}
		
   
   case 1:{cli();
	       queda=0;
          cmd_LCD(0x80,0); 
		  escreve_LCD_Flash(msg_pronto);
		  cmd_LCD(0xc0,0); 
		  escreve_LCD_Flash(msg_limp);
		  set_bit(PORTD, BBN);						//Ativa a bobina
          if(!tst_bit(PIND,BT1)) { while(!tst_bit(PIND,BT1)); estado=2;}	//Testa o botão de inicio
			  break;}
                                
									 
   case 2:{cmd_LCD(0x80,0);	
		  escreve_LCD_Flash(msg_cronometrando);
		  sei();	                            //Habilita as Interrupições
		  clr_bit(PORTD,BBN);
		   if(!tst_bit(PIND,BT2)) {while(!tst_bit(PIND,BT1)); estado=1;}    	//Testa o botão de Reset*/					//Desativa a bobina
		  break;}
		 
			  
   case 3:{cmd_LCD(0x80,0); 	 cli();
                                 escreve_LCD_Flash(msg_tqueda);
                                 ident_num(queda,digitos);
			                     cmd_LCD(0xC6,0);			//desloca o cursor para que os 3 digitos fiquem a direita do LCD
			                     cmd_LCD(digitos[4],1);
			                     cmd_LCD(digitos[3],1);							 
								 cmd_LCD(digitos[2],1);
			                     cmd_LCD(digitos[1],1);
								 cmd_LCD('.',1);
			                     cmd_LCD(digitos[0],1);
								 cmd_LCD(' ',1);
			                     cmd_LCD('m',1);
			                     cmd_LCD('s',1);
     
		  if(!tst_bit(PIND,BT2)) { while(!tst_bit(PIND,BT1));estado=1;}
		  break;}		//Testa o botão de Reset
		  
		  
  		  	  
                                 
 }   // fim switch
        	
		
		
	}
		
}
//======================================================================================	

ISR(INT0_vect)
{ TCNT1=0;}	

ISR(INT1_vect)
{//tm1=TCNT1;
 tm1 = 5550
 tempo = ((float)TCNT1*0,000064);
 queda = tempo*10000;
 estado=3;	
}

