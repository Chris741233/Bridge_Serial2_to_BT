/******************************************************************
Created with PROGRAMINO IDE for Arduino - 10.07.2023 13:48:50

Author      : Chris74

Description : Bridge Serial2 to Bluethoot serial 

Example for Smart-BMS SZLLT (same JBD or Xiaoxiang) with  PC app JBDtools
work maybe also on Daly BMS with their PC soft ?? to be tested
- Tested  with BMS SZLLT SP15S001-P13S-40A and JBDTools v.1.6

Board       : ESP32 dev. / ESP32 M5Stamp Pico

Github (see diagram and note)  : https://github.com/Chris741233/Bridge_Serial2_to_BT

License     : MIT


M5Stamp Pico 
doc :  https://docs.m5stack.com/en/core/stamp_pico?id=program-download 
shop : https://shop.m5stack.com/products/m5stamp-pico-diy-kit

******************************************************************/


#include <HardwareSerial.h>

#include <BluetoothSerial.h>  // Header File for Serial Bluetooth


#define USE_M5PICO 0   // use M5stamp PICO ? 1=yes, 0= no (for Pico fastLed and button)


// --- INIT OBJECT and GPIO ----

HardwareSerial SerialBMS(2);  // init Serial2 (SerialBMS)

BluetoothSerial SerialBT;     // init Serial Bluetooth (SerialBT)


const int RX2_PIN    = 18;  // RX Serial2 (ESP32 default=16) - M5 Pico=18
const int TX2_PIN    = 19;  // TX Serial2 (ESP32 default=17) - M5 Pico=19


// if use M5Stamp Pico 
#if USE_M5PICO
    #include <FastLED.h>
    #define NUM_LEDS 1      // How many leds
    #define DATA_PIN 27
    CRGB leds[NUM_LEDS];    // Define the array of leds
    #define BRIGHTNESS  100 // max 255
    //CRGB::Red             // Red and Green inversed ?!
    //CRGB::Gray            // 'white' is too bright compared to red and blue
    //CRGB::Blue
    //CRGB::Black           // = Led Off
    
    const int BUTTON_PIN = 39;
#endif


// --- GLOBAL var ---

//  Message buffer design
#define MSGBUFFERSIZE 80    // 80 default 
byte pData[MSGBUFFERSIZE];
byte pData2[MSGBUFFERSIZE];



// --- MAIN ---

void setup() 
{
    // -- Serial console (USB) 
    Serial.begin(115200);
    Serial.println("Start serial USB");
    
    // -- Serial2 Smart-BMS (9600 Bd max)
    SerialBMS.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
    
    // -- Bluetooth serial
    SerialBT.begin("ESP32_SMART_BMS"); //Name of your Bluetooth Signal
    Serial.println("Bluetooth Device is Ready to Pair");
    
    
    // -- if M5Stamp pico, init Led and button  
    #if USE_M5PICO
        FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
        FastLED.setBrightness( BRIGHTNESS );
        leds[0] = CRGB::Red;  // Red and Green inversed ! 
        // (Black=off)
        FastLED.show();
        
        // Button
        pinMode(BUTTON_PIN,INPUT);
    #endif
    
} //end setup

void loop() 
{
    // & = pointer memory adress
    int nBytes = comportReceive(&pData[0], MSGBUFFERSIZE, 1);    // READ numCom1  (serialBMS)
    if(nBytes > 0) comportTransmit(&pData[0], nBytes, 2);        // WRITE numCom2 (serialBT)
    
    int nBytes2 = comportReceive(&pData2[0], MSGBUFFERSIZE, 2);  // READ numCom2  (serialBT)
    if(nBytes2 > 0) comportTransmit(&pData2[0], nBytes2, 1);     // WRITE numCom1 (serialBMS) 
}


// --------------------------------- FUNCTIONS --------------------------------------------------

// --- comportReceive
// pMsg = Message buffer
// nLen = Message buffer length
int comportReceive(byte* pMsg, int nLen, int numCom)
{
    int nBytes = 0;
    
    // Read serial data 
    // --- Com1
    if (numCom == 1) {
        while(SerialBMS.available() > 0)
        {
            pMsg[nBytes++] = (byte)SerialBMS.read();
            if(nBytes >= nLen)
                break;
        } // end while
    }
    // --- Com2
    else if (numCom == 2) {
        while(SerialBT.available() > 0)
        {
            pMsg[nBytes++] = (byte)SerialBT.read();
            if(nBytes >= nLen)
                break;
        } // end while
    }     
    else {
        //
    }
    
    return nBytes;
} // endfunc  


// --- comportTransmit
// pMsg = Message buffer
// nMsgLen = Message buffer length
void comportTransmit(byte* pMsg, int nMsgLen, int numCom)
{
    // Transmit the data
    if (numCom == 1) {
        SerialBMS.write(pMsg, nMsgLen); // 1
    }
    else if (numCom == 2) {
        SerialBT.write(pMsg, nMsgLen); // 2
    }
    else {
        //
    }
    
} // endfunc


