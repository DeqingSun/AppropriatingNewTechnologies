unsigned long previousMillis = 0;
unsigned long sample_time;
unsigned char v,i,k;
unsigned char sensor_raw[4];
unsigned int sensor_value[4];
unsigned char bit_count[4];
//unsigned int sensor1;
boolean sample=false;
boolean sensorValue;
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  i=0;
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >=1) {
    previousMillis=currentMillis;
    for (i=0;i<4;i++){
      sensorValue = digitalRead(2+i);
      sensor_raw[i]<<=1;
      sensor_raw[i]+=sensorValue;
      v=sensor_raw[i];

      for (bit_count[i] = 0; v; v >>= 1)
      {
        bit_count[i] += v & 1;
      }
    }
  }
  if (sample){
    if (currentMillis>=sample_time){
      k++;
      sample=false;
      for (i=0;i<4;i++){
        sensor_value[i]<<=1;


        if (bit_count[i]<6){
          sensor_value[i]|=1;
          //  Serial.print("D\n");
        }
        else{
          //  Serial.print("d\n");
        }
      }
      Serial.print("d\n");
    } 

  }


  // Serial.println(sensorValue);
  if (Serial.available() > 0) {
    unsigned char inByte = Serial.read();
    if (inByte=='G'){
      sample=true;
      sample_time=currentMillis+100;
    }
    else if(inByte=='S'){
      //sensor1=1022;
      //Serial.println(sensor_value[0]);
      for (i=0;i<4;i++){
        Serial.print(sensor_value[i]);
        if (i<4-1){
         Serial.print(',');
        }else{
         Serial.print('\n'); 
        }
      }
      /*      for (i=0;i<10;i++){
       if (sensor1&(1<<(9-i))){
       Serial.print(1); 
       }
       else{
       Serial.print(0);
       }
       }
       
       Serial.print('\n');
       Serial.print(k);
       Serial.print('\n');*/
    }
    else if(inByte=='R'){
      for (i=0;i<4;i++){
        sensor_value[i]=0;
      }
      k=0;
    }
  }
}















