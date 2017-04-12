
int input_H;              // integer for storing high time
int input_L;              // integer for storing low time
float period;             // float for storing total time of a cycle
float frequency;          // float storing frequency
float offsetF[20];
float calF = 100.0;
int numCalPoints = 20;
float calPoints[20];

void setup(){
  
    pinMode(8,INPUT);
    Serial.begin(115000);
 
}


float getData(){
	
    input_H = pulseIn(8,HIGH);      // count micros input is high
    input_L = pulseIn(8,LOW);     	// count micros input is low
    
    period = input_H + input_L;		// calc period
	
    frequency = 1000000/period;    	// covert period to frequency & scale
	
	
    return(frequency);
}

float tempData = 0.0;
float floatAvgSum = 0.0; 
float tempAvg = 0.0;

float getoffset(){
  
  for(int i=0;i<numCalPoints;i++){      // collect numCalPoints worth of deltas
    
    tempData = getData();
    offsetF[i] = abs(tempData - calF); 
    
  }
  
  for(int y=0;y<numCalPoints;y++){
	  
    floatAvgSum += offsetF[y];			// total sum for average
    
  }
  
  tempAvg = floatAvgSum/(float(numCalPoints)); // calc average
  floatAvgSum =0.0;							   // reset average for next collection

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
	
}
