#include "HX711.h"
#include "math.h"

#define calibration_factor -48100 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2
int A = 1;
float B = 0;
float C = 0;
float D = 0;
int drinks = 0;
float E[13][13] = { 
  {0, 1.1, 2.1, 3.2, 4.2, 5.3, 6.3, 7.7, 8.8, 9.9, 11, 12.1, 13.2},
  {0.8, 1.9, 2.9, 4.1, 5.2, 6.3, 7.1, 8.3, 9.6, 10.7, 11.8, 12.9, -1},
  {1.6, 2.7, 3.7, 4.9, 6, 6.9, 7.9, 9.1, 10.4, 11.5, 12.6, -1,-1},
  {2.4, 3.5, 4.5, 5.7, 6.8, 7.7, 8.5, 10.1, 11.2, 12.3, -1,-1,-1},
  {3.2, 4.3, 5.3, 6.5, 7.6, 8.7, 9.8, 10.9, 12, -1,-1,-1,-1},
  {4, 5.1, 6.1, 7.3, 8.4, 9.5, 10.6, 11.7, -1,-1,-1,-1,-1},
  {4.8, 5.9, 6.9, 8.1, 9.2, 10.3, 11.4, -1,-1,-1,-1,-1,-1},
  {5.6, 6.7, 7.7, 8.9, 10, 11.1, -1,-1,-1,-1,-1,-1,-1},
  {6.4, 7.5, 8.5, 9.7, 10.8, -1,-1,-1,-1,-1,-1,-1,-1},
  {7.2, 8.3, 9.3, 10.5, -1,-1,-1,-1,-1,-1,-1,-1,-1},
  {8, 9.1, 10.1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {8.8, 9.9, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {9.6, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
};

HX711 scale;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("HX711 scale demo");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");

}

void loop() {
  B = round(scale.get_units()/0.925);
  D = (scale.get_units());
  float x1 = (float)D*10;   
  x1 = x1 + 0.5;              
  int y = (int)x1;            
  float D = (float)y/10.0;  
  if(B == 0 & A == 1) {
    Serial.print("0"); //scale.get_units() returns a float
    Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
    Serial.println();
    Serial.print("No drinks, refill needed");
    Serial.println();
    A = 0;
    C = 0;
  }
  if(B >= 1 & B != C) {
    if(D == E[1][0] or D == E[0][1]){
    drinks = 1;
    }
    else if(D == E[2][0] or D == E[0][2] or D == E[1][1]){
    drinks = 2;
    }
    else if(D == E[3][0] or D == E[0][3] or D == E[2][1] or D == E[1][2]){
    drinks = 3;
    }
    else if(D == E[4][0] or D == E[0][4] or D == E[3][1] or D == E[2][2] or D == E[1][3] or D == 3.9){
    drinks = 4;
    }
    else if(D == E[5][0] or D == E[0][5] or D == E[4][1] or D == E[1][4] or D == E[2][3] or D == E[3][2] or D == 4.7 or D == 5.0 or D == 4.8){
    drinks = 5;
    }
    else if(D == E[6][0] or D == E[0][6] or D == E[5][1] or D == E[1][5] or D == E[2][4] or D == E[4][2] or D == E[3][3] or D == 5.5 or D == 5.8 or D == 5.6 or D==5.3){
    drinks = 6;
    }
    else if(D == E[7][0] or D == E[0][7] or D == E[6][1] or D == E[1][6] or D == E[2][5] or D == E[5][2] or D == E[4][3] or D == E[3][4] or D == 6.6 or D == 6.4 or D == 6.9){
    drinks = 7;
    }
    else if(D == E[8][0] or D == E[0][8] or D == E[7][1] or D == E[1][7] or D == E[2][6] or D == E[6][2] or D == E[5][3] or D == E[3][5] or D == E[4][4] or D == 7.4 or D == 7.2){
    drinks = 8;
    }
    else if(D == E[9][0] or D == E[0][9] or D == E[8][1] or D == E[1][8] or D == E[2][7] or D == E[7][2] or D == E[6][3] or D == E[3][6] or D == E[4][5] or D == E[5][4] or D == 8.2 or D == 7.9 or D==8.7){
    drinks = 9;
    }
    else if(D == E[10][0] or D == E[0][10] or D == E[9][1] or D == E[1][9] or D == E[2][8] or D == E[8][2] or D == E[7][3] or D == E[3][7] or D == E[4][6] or D == E[6][4] or D == E[5][5] or D == 8.7 or D == 9.3 or D==9){
    drinks = 10;
    }
    else if(D == E[11][0] or D == E[0][11] or D == E[10][1] or D == E[1][10] or D == E[2][9] or D == E[9][2] or D == E[8][3] or D == E[3][8] or D == E[4][7] or D == E[7][4] or D == E[6][5] or D == E[5][6]){
    drinks = 11;
    }
    else if(D == E[12][0] or D == E[0][12] or D == E[11][1] or D == E[1][11] or D == E[2][10] or D == E[10][2] or D == E[9][3] or E[3][9] or D == E[4][8] or D == E[8][4] or D == E[7][5] or D == E[5][7] or D == E[6][6]){
     if(D >= 10){
    drinks = 12;
     }
     else{
       drinks = B;
     }
    }
    else{
    drinks = B;
    }
    Serial.println();
    Serial.print(D);
    Serial.print(" lbs"); 
    Serial.println();
    Serial.print(drinks);
    if(B==1){
      Serial.print(" drink");
    }
    else{
      Serial.print(" drinks");
    }    
    Serial.println();
    A = 1;
    C = B;
  }
  delay(5000);
}