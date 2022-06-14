const int pulse_y_axis = 7; const int dir_y_axis = 6; const int pulse_x_axis = 9; const int dir_x_axis = 10; //motor driver's pins
int delayM = 50; // frequency of motor to control speed
double setpoint_y; // as degree // -ccw + cw  
double setpoint_x; // as degree // - cw(left)+ ccw(right)
double temp_x;double temp_y; // temporary value for x and y axis coordinates
double a_x = 113.2; // 40752/360   at 800 resolution   // 113 pulses for 1 degree  for x axis stepper motor 
long int a_y=112;//         40600/360   at 800 resolution   // 112 pulses for 1 degree  for y axis stepper motor   
long int pulseCount_y;
long int pulseCount_x;
long int biggerPulseCount; long int smallerPulseCount; // using bigger one/smaller one 2nd for loop and smaller one 1st for loop
int biggerpulse; int smallerpulse;
long int stepMissed; // variable to calculate how many step missed
long int sa[2]; int r=0; int t=0; // parsing value as x axis and y axis
double y; double x;
void setup() {
  Serial.begin(9600);   
  pinMode(pulse_y_axis, OUTPUT); pinMode(dir_y_axis, OUTPUT); pinMode(pulse_x_axis, OUTPUT); pinMode(dir_x_axis, OUTPUT);
   runMotors(360,0);  
}
void loop() {
    if(Serial.available()){
      String inp = Serial.readString();
      setpoint_x=(inp.toInt()/100000)/100;
//2lasers_system // taking coordinate of the target from Qt desktop application
      setpoint_y=90-abs((inp.toInt()%100000)/100);
      x=setpoint_x-temp_x;  y=setpoint_y-temp_y;  
      runMotors(-x,y);
      temp_x=setpoint_x;    temp_y=setpoint_y; 
//taking point of the target from Qt desktop application
//      setpoint_y=(inp.toInt()%100000)/100;
//      x=setpoint_x-temp_x;   y=setpoint_y-temp_y;
//      runMotors(-x,-y);
//      temp_x=setpoint_x;    temp_y=setpoint_y;
    }
}
void runMotors(long int x, long int y) {
  delay(200);
  if(y>160){ //determination of the boundary
    y=10;
  }else if(y<-160){
    y=-10;
  }
  
  pulseCount_y = abs(a_y*y);
  pulseCount_x = abs(a_x*x); 
  if (pulseCount_y > pulseCount_x) {
        biggerPulseCount = pulseCount_y;
        biggerpulse = pulse_y_axis;
        smallerPulseCount = pulseCount_x;
        smallerpulse = pulse_x_axis;
      } else if(pulseCount_y < pulseCount_x){
        biggerPulseCount = pulseCount_x;
        biggerpulse = pulse_x_axis;
        smallerPulseCount = pulseCount_y;
        smallerpulse = pulse_y_axis;
      }else{
        biggerPulseCount = pulseCount_y;
        biggerpulse = pulse_y_axis;
        smallerPulseCount = pulseCount_x;
        smallerpulse = pulse_x_axis;
      }
  if ( x >= 0 && y >= 0) {
    digitalWrite(dir_y_axis, HIGH); delay(200);
    digitalWrite(dir_x_axis, HIGH); delay(200);
    for (long int i = 0; i < smallerPulseCount; i++) {
      digitalWrite(smallerpulse, HIGH); delayMicroseconds(delayM); digitalWrite(smallerpulse, LOW); delayMicroseconds(delayM);
      if (x == 0 || y == 0) {
        for (long int j = 0; j < biggerPulseCount; j++) {
          digitalWrite(biggerpulse, HIGH); delayMicroseconds(delayM); digitalWrite(biggerpulse, LOW); delayMicroseconds(delayM);
        }
      } else {
        for (long int j = 0; j < biggerPulseCount / smallerPulseCount; j++) {
          digitalWrite(biggerpulse, HIGH); delayMicroseconds(delayM); digitalWrite(biggerpulse, LOW); delayMicroseconds(delayM);
        }
      }
    }
    
  } else if (x >= 0 && y <= 0) {
    digitalWrite(dir_y_axis, LOW); delay(200);
    digitalWrite(dir_x_axis, HIGH); delay(200);
    for (long int i = 0; i < smallerPulseCount; i++) {
      digitalWrite(smallerpulse, 255); delayMicroseconds(delayM); digitalWrite(smallerpulse, 0); delayMicroseconds(delayM);
      if (x == 0 || y == 0) {
        for (long int j = 0; j < biggerPulseCount; j++) {
          digitalWrite(biggerpulse, 255); delayMicroseconds(delayM); digitalWrite(biggerpulse, 0); delayMicroseconds(delayM);
        }
      } else {
        for (long int j = 0; j < biggerPulseCount / smallerPulseCount; j++) {
          digitalWrite(biggerpulse, 255); delayMicroseconds(delayM); digitalWrite(biggerpulse, 0); delayMicroseconds(delayM);
        }
      }
    }

  } else if (x <= 0 && y >= 0) {
    digitalWrite(dir_y_axis, HIGH); delay(200);
    digitalWrite(dir_x_axis, LOW); delay(200);
    for (long int i = 0; i < smallerPulseCount; i++) {
      digitalWrite(smallerpulse, 255); delayMicroseconds(delayM); digitalWrite(smallerpulse, 0); delayMicroseconds(delayM);
      if (x == 0 || y == 0) {
        for (long int j = 0; j < biggerPulseCount; j++) {
          digitalWrite(biggerpulse, 255); delayMicroseconds(delayM); digitalWrite(biggerpulse, 0); delayMicroseconds(delayM);
        }
      } else {
        for (long int j = 0; j < biggerPulseCount / smallerPulseCount; j++) {
          digitalWrite(biggerpulse, 255); delayMicroseconds(delayM); digitalWrite(biggerpulse, 0); delayMicroseconds(delayM);
        }
      }
    }

  } else if (x <= 0 && y <= 0) {
    digitalWrite(dir_y_axis, LOW); delay(200);
    digitalWrite(dir_x_axis, LOW); delay(200);
    for (long int i = 0; i < smallerPulseCount; i++) {
      digitalWrite(smallerpulse, 255); delayMicroseconds(delayM); digitalWrite(smallerpulse, 0); delayMicroseconds(delayM);
      if (x == 0 || y == 0) {
        for (long int j = 0; j < biggerPulseCount; j++) {
          digitalWrite(biggerpulse, 255); delayMicroseconds(delayM); digitalWrite(biggerpulse, 0); delayMicroseconds(delayM);
        }
      } else {
        for (long int j = 0; j < biggerPulseCount / smallerPulseCount; j++) {
          digitalWrite(biggerpulse, 255); delayMicroseconds(delayM); digitalWrite(biggerpulse, 0); delayMicroseconds(delayM);
        }
      }
    }
  }
    stepMissed = biggerPulseCount - (smallerPulseCount * (int)(biggerPulseCount / smallerPulseCount));
    if(x != 0 || y != 0 ){
        for (long int i = 0; i < stepMissed; i++) {
        digitalWrite(biggerpulse, 255); delayMicroseconds(delayM); digitalWrite(biggerpulse, 0); delayMicroseconds(delayM);
      }
    }
   
}
void parsing(String s){
     for (int i=0; i < s.length(); i++){ 
       if(s.charAt(i) == ','){ 
          sa[t] = s.substring(r, i).toInt(); 
          r=(i+1); 
          t++; 
        }
     }
}
