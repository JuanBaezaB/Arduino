#include <VirtualWire.h>

void setup()
{
    Serial.begin(9600);  // Debugging only
    Serial.println("Emisor: Setup");

    // Se inicializa el RF
    vw_setup(2000);  // velocidad: Bits per segundo
    vw_set_rx_pin(2);    //Pin 2 como entrada del RF
    vw_rx_start();       // Se inicia como receptor
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    //verificamos si hay un dato valido en el RF
    if (vw_get_message(buf, &buflen)) 
    {
  int i;

        digitalWrite(13, true); // Parpadeamos  el led al recibir
  //verificamos si hay un dato valido en el RF
  Serial.print("Mensaje: ");
  
  for (i = 0; i < buflen; i++)
  {
      Serial.print((char)buf[i]);
  }
  Serial.println("");
        digitalWrite(13, false);
    }
}
