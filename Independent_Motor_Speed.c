// Velocidad de los Motores de Manera Independiente | Independent Motor Speed 

// librerias | Libraries
#include <16f877A.h>
#fuses XT, NOWDT, NOLVP, NOPROTECT
#use delay(clock = 4000000)
#use rs232(baud = 9600, xmit = pin_c6, rcv = pin_c7, bits = 8, parity = N)
#include <lcd.c>

// Variables globales | Global Variables
char characters[2];
char option, speedRead, c = '%';
int percentage1, percentage2, speedInt;
int16 speedMotor1, speedMotor2;

// Funcion para imprimir en la pantalla | Function to print on the screen
void imprimir()
{
    printf("\f.: Control de Velocidad de 2 Motores de CD Mediante La PC :.\n\n\r");
    printf("     .: Ingrese la Velocidad Deseada para Cada Motor :.\n\n\r");
    printf(":: Comandos para Aumentar la Velocidad \n\n\r");
    printf(":: X = Numero de Motor (1-2)\n\n\r");
    printf(":: V = Velocidad del Motor (0-9)\n\n\r");
    printf(":: Ingrese el comando -> Ejemplo (XV = 19) \n\n\r");
    printf(":: Motor 1 a el 90%c de Velocidad  \n\n\r", c);
    printf(":: Ingrese el comando: ");
}

// Funcion de Interrupcion para recibir datos | Interrupt function to receive data
#int_rda
void motor()
{
    // Recibe los datos | Receive the data
    gets(characters);
    option = characters[0];
    speedRead = characters[1];
    speedInt = speedRead - 48;

    // Opcciones para el motor 1 | Options for motor 1
    if (option == '1')
    {
        percentage1 = speedInt * 10;
        speedMotor1 = speedInt * 10;
    }
    // Opcciones para el motor 2 | Options for motor 2
    else if (option == '2')
    {
        percentage2 = speedInt * 10;
        speedMotor2 = speedInt * 10;
    }

    // Imprimir en la pantalla | print on the screen
    imprimir();
}

// Funcion principal | Main function
void main()
{
    // Configuracion de las Interrupciones | Interrupt Configuration
    enable_interrupts(int_rda);
    enable_interrupts(global);
    // Inicializacion de la Pantalla LCD | LCD Screen Initialization
    lcd_init();
    // Imprimir en la pantalla | print on the screen
    imprimir();

    // Ciclo infinito | Infinite cycle
    while (true)
    {
        // Motor 1 | Motor 1
        output_high(PIN_B1);
        delay_ms(speedMotor1);
        output_low(PIN_B1);
        delay_ms(100 - speedMotor1);

        // Motor 2 | Motor 2
        output_high(PIN_B4);
        delay_ms(speedMotor2);
        output_low(PIN_B4);
        delay_ms(100 - speedMotor2);

        // Imprimir en la pantalla | print on the screen
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "Motor 1: %i%c  ", percentage1, c);
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "Motor 2: %i%c  ", percentage2, c);
    }
}
