#include <Vector.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> 
#endif
#define LED_PIN    5
#define LED_COUNT 300
Adafruit_NeoPixel *strip = new Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#include "Style.h"
#include "Solid.h"
#include "Rainbow.h"
#include "Breathe.h"
#include "Gradient.h"

#define DATA_SIZE 54

Style *style;
int data[DATA_SIZE];
uint8_t styletype;

void setup()
{
Serial.begin(9600);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip->begin();
  strip->setBrightness(25);
}

void loop()
{
  if (Serial && Serial.available()){
    delete(style);
    style = NULL;
    
    GetSerialData();

    //SOLID
    if (styletype == 1){
      styletype = -1;
      if (hasData(2)){
        Serial.println("SOLID R:" + String(data[0]) + " G:" + String(data[1]) + " B:" + String(data[2]));
        style = new Solid(strip->Color(data[0], data[1], data[2]));
        style->start(strip);
      }else{
        Serial.println("Failed");
      }
    }
    
    //BREATHE
    if (styletype == 2){
      styletype = -1;
      if (hasData(4)){
        Serial.println("BREATHE");//Serial.println("BREATHE R:" + String(data[0]) + " G:" + String(data[1]) + " B:" + String(data[2]) + " Dur:" + String(data[3]) + " Rep:" + String(data[4]));
        style = new Breathe(strip->Color(data[0], data[1], data[2]), data[3], data[4]);
        style->start(strip);
      }else{
        Serial.println("Failed");
      }
    }

    //GRADIENT
    if (styletype == 3){
      styletype = -1;
      int dl = dataLength();
      if (dl <= 0 || dl % 3 != 0){ Serial.println("Failed"); return; }
      uint32_t colours[dl / 3];
      for(int i = 0; i < sizeof(colours); i++){
        colours[i] = -1;
      }
      for(int i = 0; i < dl; i += 3){
        if (hasData(i + 2)){
          Serial.println("Gradient " + String(i / 3) + "R:" + String(data[i]) + " G:" + String(data[i + 1]) + " B:" + String(data[i + 2]));
          colours[i / 3] = strip->Color(data[i], data[i + 1], data[i + 2]);
        }else{
          Serial.println("Failed");
        }
      }
      style = new Gradient(colours, dl / 3, 1);
      style->start(strip);
    }

    //RAINBOW
    if (styletype == 4){
      styletype = -1;
      if (hasData(1)){
        delete(style);
        style = new Rainbow(data[0], data[1]);
        Serial.println("RAINBOW");
      }else{
        Serial.println("Failed");
      }
    }

    if(styletype == 0){
      styletype = -1;
      if (hasData(0)){
        strip->setBrightness(data[0]);
        strip->show();
      }
    }
  }

  if (style != NULL){
    style->execute(strip);
  }
}

void GetSerialData(){
  char input[320];
  
  String inputstring = "";

  inputstring = Serial.readString();
  Serial.flush();

  inputstring.toCharArray(input, 320);

  styletype = -1;
 
  int index = 0;
  
  // Get the style type
  char stylename[] = {'0', '0'};
  uint8_t cindex = 0;
  while(input[index] != NULL){
    char c = input[index];
    index++;
    if (cindex < 2){
      stylename[cindex] = c;
      cindex++;
    }
    if (cindex >= 2){
      break;
    }
  }
  styletype = StrToHex(stylename);

  //Reset data
  for(int i = 0; i < DATA_SIZE; i++){
    data[i] = -1.0;
  }
  
//int dataIndex = 0;
//String datastring = "";
//  // Get the data
//  while(input[index] != NULL){
//    char c = input[index];
//    index++;
//    if (c == ',' || c == ')'){
//      data[dataIndex] = datastring.toInt();
//      datastring = "";
//      dataIndex++;
//    }else{
//      datastring.concat(c);
//    }
//  }

  int dataIndex = 0;
  cindex = 0;
  char datastring[] = {'0', '0'};
  // Get the data
  while(input[index + 1] != NULL){
    char c = input[index];
    index++;
    datastring[cindex] = c;
    cindex = (cindex + 1) % 2;
    if (cindex == 0){
      data[dataIndex] = StrToHex(datastring);
      dataIndex++;
    }
  }

//  Serial.println(stylename);
  for(int i = 0; i < DATA_SIZE; i++){
    //Serial.print(String(data[i]) + ",");
    Serial.print(String(data[i]) + ",");
  }
  Serial.println();
}

bool hasData(int index){
  bool has = true;
  for(int i = 0; i <= index; i++){
    if (data[i] == -1){
      has = false;
    }
  }
  return has;
}

int dataLength(){
  int amount = 0;
  for(int i = 0; i <= DATA_SIZE; i++){
    if (data[i] >= 0){
      amount++;
    }else{
      break;
    }
  }
  return amount;
}

int StrToHex(char str[2])
{
  return (uint8_t) strtol(str, 0, 16);
}
