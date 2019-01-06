
#include <SPI.h>
#include <SD.h>



/*
 * The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
 * 
 */

File myFile;
int times;
String incomingByte;
int input = 0;
int nocard = 0;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);

   Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    nocard = 1;
    return;
  }
  else{
    Serial.println("initialization done.");
    nocard = 0;
  }
  
  myFile = SD.open("sensor.txt", FILE_WRITE);
  // Open the file for writing. 
  if (myFile) {
    
    myFile.println("time,sensor");
    //myFile.close();
    Serial.println("First line done!");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening .txt");
  }
  
  
  times = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogSensor = analogRead(0);

  //Serial.print("Pin A0: ");
  Serial.print(times);
  Serial.print(": ");
  if (nocard==1){
    Serial.print(analogSensor);
    Serial.println("      -> No SD-card !!!");
  }
  else{
    Serial.println(analogSensor);
  }
  

  
  myFile.print(times);
  myFile.print(",");
  myFile.println(analogSensor);
    
  
  incomingByte = (Serial.read());
  //input = int(incomingByte);
  
  //Serial.println (incomingByte);
  if (incomingByte == "113"){//"q for quite - exlit the file writing
    myFile.close();
    Serial.println("Writing compleated...");
  }
  else if (incomingByte == "100"){// "d for delete
    myFile.close();
    SD.remove("test.txt");
    SD.remove("sensor.txt");
    Serial.println("File removed...");
  }
  
  delay(1000);
  times=times+1;
}
