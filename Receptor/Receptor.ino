#include <VirtualWire.h>
#include <stdio.h> // Para printf
#include <string.h> // Para strcmp y strlen
#include <ctype.h> // Para toupper

#define LONGITUD_MENSAJE 500
/**
 * Traductor de código Morse en C
 *
 * Basado en https://gist.github.com/parzibyte/2b9986ee3e820f61e4cadc64722da052
 *
 * @author parzibyte
 * https://parzibyte.me/blog
 *
 * */
// Código y signo iguales deben estar en el mismo índice
char *codigosMorse[] = {
        ".-", "-...", "-.-.", "-..",
        ".", "..-.", "--.", "....", "..",
        ".---", "-.-", ".-..", "--", "-.",
        "---", ".--.", "--.-", ".-.", "...",
        "-", "..-", "...-", ".--", "-..-",
        "-.--", "--..", "-----", ".----", "..---",
        "...--", "....-", ".....", "-....", "--...",
        "---..", "----.", ".-.-.-", "--..--", "---...",
        "..--..", ".----.", "-....-", "-..-.", ".--.-.",
        "-...-", ".-..-.", "-.-.--",};

char *simbolosAscii[] = {"A", "B", "C", "D",
                         "E", "F", "G", "H", "I",
                         "J", "K", "L", "M", "N",
                         "O", "P", "Q", "R", "S",
                         "T", "U", "V", "W", "X",
                         "Y", "Z", "0", "1", "2",
                         "3", "4", "5", "6", "7",
                         "8", "9", ".", ",", ":",
                         "?", "'", "-", "/", "@",
                         "=", "\"", "!",};

const int NUMERO_CODIGOS = sizeof(codigosMorse) / sizeof(codigosMorse[0]);

int buscarIndiceDeMorse(char *codigo) {
    for (int x = 0; x < NUMERO_CODIGOS; x++) {
        if (strcmp(codigosMorse[x], codigo) == 0) {
            return x;
        }
    }
    return -1;
}

int buscarIndiceDeAscii(char signo) {
    // Convertir char a string
    char cadenaTemporal[2];
    cadenaTemporal[0] = signo;
    cadenaTemporal[1] = '\0';
    for (int x = 0; x < NUMERO_CODIGOS; x++) {
        if (strcmp(simbolosAscii[x], cadenaTemporal) == 0) {
            return x;
        }
    }
    return -1;
}



void demostrarDecodificacionMorse(char* mensaje) {
//    char mensaje[] = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.. ----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----. .-.-.- --..-- ---... ..--.. .----. -....- -..-. .--.-. -...- .-..-. -.-.--";
    // Aquí define tu mensaje separado por espacios
    //Serial.print(mensaje);
    char delimitador[] = " ";
    // Separamos la cadena por espacios. Más información sobre strtok en https://parzibyte.me/blog/2018/11/13/separar-cadena-delimitadores-c-strtok/
    char *token = strtok(mensaje, delimitador);
    if (token != NULL) {
        while (token != NULL) {
            // Obtener cuál índice tiene este código
            int indice = buscarIndiceDeMorse(token);
            // Aquí puedes hacer lo que gustes con el ascii, yo simplemente lo imprimo
            char *ascii = simbolosAscii[indice];
            Serial.print(ascii);
            token = strtok(NULL, delimitador);
        }
    }
    Serial.println();
}

void setup()
{
    Serial.begin(9600);  // Debugging only
    Serial.println("Emisor: Setup");

    // Se inicializa el RF
    vw_setup(2000);  // velocidad: Bits per segundo
    vw_set_rx_pin(2);    //Pin 2 como entrada del RF
    vw_rx_start();       // Se inicia como receptor
}

void loop(){
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    //verificamos si hay un dato valido en el RF
    if (vw_get_message(buf, &buflen)) {
        int i;

        digitalWrite(13, true); // Parpadeamos  el led al recibir
        //verificamos si hay un dato valido en el RF

        String mensaje ;
        for (i = 0; i < buflen; i++){
            mensaje += (char)buf[i];
            
        }
        int n = mensaje.length();
        char char_array[n+1];
        strcpy(char_array,mensaje.c_str());

       
        demostrarDecodificacionMorse(char_array);
        //Serial.println("");
        
        digitalWrite(13, false);
    }
}
