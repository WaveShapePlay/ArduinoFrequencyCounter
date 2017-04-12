
int Htime;              //integer for storing high time
int Ltime;                //integer for storing low time
float Ttime;            // integer for storing total time of a cycle
float frequency;        //storing frequency
float offsetF[20];
float calF = 100.0;
int numCalPoints = 20;
float calPoints[20];
void setup(){
  
    pinMode(8,INPUT);
    Serial.begin(115000);
 
}


float getData(){
    Htime=pulseIn(8,HIGH);      //read high time
    Ltime=pulseIn(8,LOW);        //read low time
    
    Ttime = Htime+Ltime;
    frequency=1000000/Ttime;    //getting frequency with Ttime is in Micro seconds
    
    return(frequency);
}
float tempData = 0.0;
float floatAvgSum = 0.0; 
float tempAvg = 0.0;
float getoffset(){
  
  for(int i=0;i<numCalPoints;i++){
    
    tempData = getData();
    offsetF[i] = abs(tempData - calF); 
    
  }
  
  for(int y=0;y<numCalPoints;y++){
    floatAvgSum += offsetF[y];
    
  }
  tempAvg =floatAvgSum/(float(numCalPoints));
  floatAvgSum =0.0; // reset avg count

return tempAvg;
}
  
float rawData = 0.0;
float offset = 0.0;
float offset_cal_data = 0.0;

void loop(){
    
    rawData = getData();
    offset = getoffset();
    
    Serial.println(rawData);
    Serial.print("Average Offset: ");
    Serial.println(offset);
    offset_cal_data = abs(rawData - offset);
    Serial.print("Data with offset Cal: ");
    Serial.println(offset_cal_data);
    //delay(500);
}
