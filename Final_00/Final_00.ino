

// the final code 

#include <SoftwareSerial.h>
#include <Wire.h>

// General command to get the sensor id : 0xFE 0x03 0x02 0x00 0x00 0x01 0x91 0xBD

/* 
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            ## NPK sensor ##
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!            
ID                 : 01 
number of readings : 3 
number of commands : 3
General command    : 0x01 0x03 0x00 0x1E 0x00 0x03 0xE4 0x0C
*/

const byte CMD_Nitrogen   [] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte CMD_Phosphorus [] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte CMD_Potassuim[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};


/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
            ## PH sensor ##
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
ID                 : 02 
number of readings : 2 
number of commands : 3
General command    : 0x01 0x03 0x00 0x00 0x00 0x03 0x05 0xCB
*/

const byte CMD_PH      [] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
const byte CMD_TEMP_PH [] = {0x02, 0x03, 0x00, 0x02, 0x00, 0x01, 0x25, 0xCA};

/* 
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            ## MOIS sensor ##
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!            
ID                 : 03 
number of readings : 4 
number of commands : 5
General command    : 0x01 0x03 0x00 0x00 0x00 0x04 0x44 0x09
*/

const byte CMD_MOIS [] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
const byte CMD_TEMP [] = {0x02, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0xCA};
const byte CMD_EC   [] = {0x02, 0x03, 0x00, 0x02, 0x00, 0x01, 0x25, 0xCA};
const byte CMD_SL   [] = {0x02, 0x03, 0x00, 0x03, 0x00, 0x01, 0x74, 0x0A};



// define serial pins transmitter receiver Enables 
// "RE & DE" ->  HIGH  -> transmit 
// "RE & DE" ->  LOW  -> receive 


// for NANO
#define RE  8
#define DE  7


// storing reading values 
byte values[13];

// for arduino nano & uno
SoftwareSerial mod(2, 3);

//for arduino mega
// SoftwareSerial mod(10, 11);



// initialize your variables for each reading
uint16_t Value_Nitrogen ,Value_Potassuim, Value_Phosphorus, Value_PH, Value_TEMP_PH, Value_Mois, Value_Temp, Value_EC, Value_SL;


void setup() 
{
// initialize serial Comm -> 9600
  Serial.begin(9600);

// initialize mod bus ->9600
  mod.begin(9600);
 
// set pins RE , DE for mod bus as output 
// Define pin modes for RE and DE-
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  delay(500);
}

void loop() {

  // get the read from the function then display it on the serial monitor 
  Value_Nitrogen = HAL_u16Get_Sensor_Read(CMD_Nitrogen);
  Serial.print("Nitrogen Read is : ");
  Serial.print(Value_Nitrogen);
  delay(1000);

  Value_Phosphorus = HAL_u16Get_Sensor_Read(CMD_Phosphorus);
  Serial.print("Phosphorus Read is : ");
  Serial.print(Value_Phosphorus);
  delay(1000);

  Value_Potassuim = HAL_u16Get_Sensor_Read(CMD_Potassuim);
  Serial.print("Potassuim Read is : ");
  Serial.print(Value_Potassuim);
  delay(1000);  

  Value_PH = HAL_u16Get_Sensor_Read(CMD_PH);
  Serial.print("PH Read is : ");
  Serial.print(Value_PH);
  delay(1000);  

  Value_TEMP_PH = HAL_u16Get_Sensor_Read(CMD_TEMP_PH);
  Serial.print("Temprature_PH Read is : ");
  Serial.print(Value_TEMP_PH);
  delay(1000);

  Value_Mois = HAL_u16Get_Sensor_Read(CMD_MOIS);
  Serial.print("Moisture Read is : ");
  Serial.print(Value_Mois);
  delay(1000);

  Value_Temp = HAL_u16Get_Sensor_Read(CMD_TEMP);
  Serial.print("Temprature Read is : ");
  Serial.print(Value_Temp);
  delay(1000);  

  Value_EC = HAL_u16Get_Sensor_Read(CMD_EC);
  Serial.print("Elecrical Conductivity Read is : ");
  Serial.print(Value_EC);
  Serial.write((char)(Value_EC * 100/2000));
  delay(1000);

  Value_SL = HAL_u16Get_Sensor_Read(CMD_SL);
  Serial.print("Salinity Read is : ");
  Serial.print(Value_SL);
  delay(1000);

}


// function takes pionter to the command array then return the reading value 

uint16_t HAL_u16Get_Sensor_Read(const byte * COMMAND)
{
  uint16_t Local_u16Read;

  // trasmit 
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);

  if(mod.write(COMMAND,sizeof(COMMAND))==8)
  {
    // recieve 
  digitalWrite(DE,LOW);
  digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++)
    {
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.println(values[i],HEX);
    }    
    Serial.println();
  }

Local_u16Read = (uint16_t)((values[3]&0x00ff)<<8 | (values[4]&0xff));
return Local_u16Read;

}