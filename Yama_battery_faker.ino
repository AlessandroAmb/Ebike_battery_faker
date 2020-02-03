
//255 255 14 6 26 25 1 110 2 199 42 248 1 24 17 192 0 110 7
int b1=255;
int b2=255;
int b3=14;
int b4=6;
int b5 = 100;//batt percent.
int b6=25;
int b7=1;
int b8=110; //??
int b9=2; //?? 2-3
int b10=199; // ?? 22-255
int b11=42;
int b12=248;
int b13=1;
int b14=24;
int b15=17;
int b16=240; //unusedled indicator 128-192-240-255
int b17=0; // 0-7 prob. power
int b18=110; // 0-255
int b19;

int b5t = 0;
int b5t2 = 0;
int index = 0;
boolean low = false;

void setup(){
  Serial.begin(2400,SERIAL_8E1);

}

void loop(){
    // this shit here is linear, dont expect a fancy li-ion charge algorithm.
    
    b5t = (int)map(analogRead(0),804,1023,0,100); 
    //calibrate here. 
    //804 = 3.93V Analog In = empty @ 33V batt 
    //1023 = 5V Analog In =  full @ 42V batt

    b5t2 = b5t2 + b5t;
    index = index + 1;
    
    // averaging, calc every 5 secs a new batt percentage.
    if(index > 20){ 
      b5 = (int)(b5t2 / 20);
      b5t2 = 0;
      index = 0;
    }
    if(b5 >= 100){ b5 = 100; }
    if(b5 <= 10 || low){ b5 = 10; low = true;} 
    //once it goes below 10% stay there until Arduino has been restarted.
    //voltage drop cause the motor to turn off on a hill.
    //this squeezes the last bit of juice out of your batt. 

  //crc sum dont change
  b19 = ((b1-b2-b3-b4-b5-b6-b7-b8-b9-b10-b11-b12-b13-b14-b15-b16-b17-b18)%256)+256;
  
 
  // 4x a sec, dont change or add any other delay.
  delay(250); 
  
  
  Serial.write(b1);
  Serial.write(b2);
  Serial.write(b3);
  Serial.write(b4);
  Serial.write(b5);
  Serial.write(b6);
  Serial.write(b7);
  Serial.write(b8);
  Serial.write(b9);
  Serial.write(b10);
  Serial.write(b11);
  Serial.write(b12);
  Serial.write(b13);
  Serial.write(b14);
  Serial.write(b15);
  Serial.write(b16);
  Serial.write(b17);
  Serial.write(b18);
  Serial.write(b19);
  
}
