//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//		ACIONANDO UM DISPLAY DE CRISTAL LIQUIDO DE 16x2									//
//																						//
//				Interface de dados de 4 bits											//
//=====================================================================================	//

#include "def_principais.h"			//inclusão do arquivo com as principais definições 
#include "LCD.h"

//definiçao para acessar a memória flash 
PROGMEM const char mensagem[1][16] = " DADOS DE 4BITS!\0"; //mensagem armazenada na memória flash

char line_data[6][16]= 
{
{'M','E','N','U',' ','1','#','#','#','#','#','#','#','#','#','#'},
{'E','N','T','E','R',' ','S','U','B',' ','M','E','N','U','#','#'},
{'M','E','N','U',' ','3','#','#','#','#','#','#','#','#','#','#'},
{'M','E','N','U',' ','4','#','#','#','#','#','#','#','#','#','#'},
{'M','E','N','U',' ','5','#','#','#','#','#','#','#','#','#','#'},
{'M','E','N','U',' ','6','#','#','#','#','#','#','#','#','#','#'} 
};


//--------------------------------------------------------------------------------------
int main()
{	
    DDRD = 0xFF;					//PORTD como saída
	DDRC = 0x00;
	PORTC = 0xFF;  // PORT C ENTRADA
	DDRB = 0xFF;

	inic_LCD_4bits();				//inicializa o LCD
	escreve_LCD("  INTERFACE DE");	//string armazenada na RAM
	cmd_LCD(0xC0,0); 				//desloca cursor para a segunda linha
	escreve_LCD_Flash(mensagem[0]);	//string armazenada na flash



	while(1) {						//laço infinito
		
	
		if(!tst_bit(PINC,0))			//se o botão for pressionado executa o if
		{
		cmd_LCD(0xC0,0); 		
		escreve_LCD("1");
		}	
			
		if(!tst_bit(PINC,1))			//se o botão for pressionado executa o if
		{
		cmd_LCD(0xC1,0); 		
		escreve_LCD("2");
		}	
		
	    if(!tst_bit(PINC,2))			//se o botão for pressionado executa o if
		{
		//cmd_LCD(0xC2,0); 		
		//escreve_LCD("3");
		
			cmd_LCD(0x18,0); 
		_delay_ms(200);	
		
		}	
					
	    if(!tst_bit(PINC,3))			//se o botão for pressionado executa o if
		{
	//	cmd_LCD(0xC0,0); 		
		//escreve_LCD("    ");
		cmd_LCD(0x1C,0); 
		_delay_ms(200);	
		}	
			
				cmd_LCD(0xCf,0); 					
				
			
		}			
				
}
//======================================================================================	