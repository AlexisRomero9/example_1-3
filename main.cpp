#include "mbed.h"
#include "arm_book_lib.h"
#include "hal/gpio_api.h"

#define PROG_LANG_C (0) //Se utiliza C para la declaración de las variables
#define PROG_LANG_CPP (1) //Se utiliza C++ para la declaración de variables
#define PROG_LANG_USED(PROG_LANG_C) //Se define qué lenguaje de programación voy a utilizar

#if (PROG_LANG_USED == PROG_LANG_C)
    
    gpio_t gasDetector;
    gpio_t overTempDetector;
    gpio_t alarmOffButton;
    gpio_t alarmLed;

    void inicializarGPIO(){
        gpio_init_in_ex(&gasDetector,D2,PullDown);
        gpio_init_in_ex(&overTempDetector,D3,PullDown);
        gpio_init_in(&alarmOffButton,BUTTON1);
        gpio_init_out(&alarmLed,LED1);
    }
    

    int gasDetectorState(){return gpio_read(&gasDetector);}
    int overTempDetectorState(){return gpio_read(&overTempDetector);}
    int alarmOffButtonState() {return gpio_read(&alarmOffButton);}
    void changeAlarmState(bool alarmState) {gpio_write(&alarmLed,alarmState);}

#endif

#if (PROG_LANG_USED == PROG_LANG_CPP)

    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);
    DigitalIn alarmOffButton(BUTTON1);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);
    alarmLed = OFF;

    int gasDetectorState(){return gasDetector;}
    int overTempDetectorState(){return overTempDetector;}
    int alarmOffButtonState(){return alarmOffButton;}
    void changeAlarmState(bool alarmState){alarmLed = alarmState;}



#endif


int main()
{

    bool alarmState = OFF;

    while (true) {

        if ( gasDetectorState() || overTempDetectorState() ) {
            printf("El sensor de gas está %s\n", gasDetectorState() ? "ACTIVADO" : "DESACTIVADO");
            printf("El sensor de temperatura está %s\n", overTempDetectorState() ? "ACTIVADO" : "DESACTIVADO");
            alarmState = ON;
            printf("La alarma está activada");
        }

        changeAlarmState(alarmState);

        if ( alarmOffButtonState() ) {
            alarmState = OFF;
            printf("La alarma está desactivada");
        }
    }
}


/*9b -Una ventaja es que se trabaja a más bajo nivel, dando más detalle de lo que estamos haciendo dentro del microcontrolador.
Y Las desventajas son código un poco mas complejo de interpretar, una mayor cantidad de instrucciones para hacer cada cosa.
Al trabajar con objetos, se puede agrupar mejor las propiedades y metodos asociados con una clase, que resulta mas simple
que utilizar estructuras en C.

*/