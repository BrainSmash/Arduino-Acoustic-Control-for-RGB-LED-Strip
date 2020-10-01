/**********************************
* ******** BRAIN SMASH ******** 
* ****** AUTHOR: DAEDALUS   7/2019 ******
* **** Visit us at: Youtube.com/BrainSmash ****
* ** Github.com/BrainSmash **
* You may use or modify this code for any and all of your projects whitout any restrictions
* If you use any fragment of this code we will be happy if you could drop us a message ;)
* Brain Smash nor the Author are hold responsible for any misuse partially or complete of this code 
*/

/*
 *  Acoustic Control for RGB LED Strips
 *  
 * How to build your own Music Visualizer with Arduino for RGB LED Strips 
 * This is a video that teaches you how to change the color of a LED strip 
 * based on the value that is obtianed from a Sound sensor, the signal is 
 * filtered using a First Order Low pass IIR Digital filter with a cutoff 
 * frequency of 900Hz the filtered signal is compared with several threshold 
 * values that are used to determine which color will be displyed based on the 
 * frequency of the sound that is sensed by the sensor, low frequency sounds 
 * (barely audible) are displayed as Blue in the LED Strip, all the way to 
 * high frequency sounds (highly audible) wich are displayed as Red in the strip.
 *  
 *  MainFunction() 
 *  This method read the value of the output of the Sound sensor with "sensorValue" 
 *  as a float & substracts 1023 to it since the sound sensor gives an output of 1023 or 5V 
 *  when is not sensing any sound, this way we have a value of 0 when not sensing sound  
 *  & values up to 1023 when it senses sound (vibrations in air), we convert the signal
 *  to volts.
 *  
 *  FilterSignal()
 *  Filter the signal using a First Order IIR Low Pass Digital Filter created in Matlab
 *  and assigned the value to the variable "filteredSignal"
 *  
 *  CompareSignalFiltered()
 *  Compare the "filteredSignal" variable with "filteredSignalValues" array 
 *  to determine where our compared variable value is less, more or in between, our 
 *  treshold values to assign a color to the LED Strip and print the color that represents 
 *  what we set. 
 *  
 *  RGBColor()
 *  Send to the defined pins for each RGB color a value from 0 to 255 that represent the color 
 *  that we want; Search on Google RGB Color Wheel to help you learn how colors are created. 
 */ 

/*
 * VERSION 1.2
 * Changed the order of numbers in "filteredSignalValues" array from highest to lowest, was reversed and changed 
 * the equation from the "sensorValue" variable, from 1023 - "analogRead(A0)" to just "analogRead(A0)" to make it
 * easier to read.
 * Sound Sensor outputs 5V or 1023 when read as input from the Arduino when there is no sound and with a high sound it ouputs 0v
 * The Sensor has inverse output logic.
 */

#define Rpin 11
#define Gpin 10
#define Bpin 9
#define delayLEDS 3
#define sensorPin A0

float sensorValue = 0, filteredSignal = 0,
    filteredSignalValues[] = {3.4, 3.1, 2.7, 2.4, 2.1, 1.7, 1.3, 0.9, 0.4};

void setup () {

  Serial.begin (9600);
}

void loop () {

  MainFunction();
}

void MainFunction() {

  sensorValue = (float) analogRead(sensorPin) * (5.0 / 1024.0);

  FilterSignal(sensorValue);

  Serial.print(sensorValue);
  Serial.print(" ");
  Serial.println(filteredSignal);

  CompareSignalFiltered(filteredSignal);
}

void FilterSignal(float sensorSignal) {

  filteredSignal = (0.945 * filteredSignal) + (0.0549 * sensorSignal);
}

void CompareSignalFiltered(float filteredSignal) {

  if (filteredSignal > filteredSignalValues[0]) {
    RGBColor(0, 0, 255);
    Serial.println("Blue");
  } else if (filteredSignal <= filteredSignalValues[0] && filteredSignal > filteredSignalValues[1]) {
    Serial.println("Azure");
    RGBColor(0, 255, 255);
  } else if (filteredSignal <= filteredSignalValues[1] && filteredSignal > filteredSignalValues[2]) {
    RGBColor(0, 127, 255);
    Serial.println("Cyan");
  } else if (filteredSignal <= filteredSignalValues[2] && filteredSignal > filteredSignalValues[3]) {
    RGBColor(0, 255, 127);
    Serial.println("Aqua marine");
  } else if (filteredSignal <= filteredSignalValues[3] && filteredSignal > filteredSignalValues[4]) {
    RGBColor(0, 255, 0);
    Serial.println("Green");
  } else if (filteredSignal <= filteredSignalValues[4] && filteredSignal > filteredSignalValues[5]) {
    RGBColor(255, 255, 0);
    Serial.println("Yellow");
  } else if (filteredSignal <= filteredSignalValues[5] && filteredSignal > filteredSignalValues[6]) {
    RGBColor(255, 0, 255);
    Serial.println("Magenta");
  } else if (filteredSignal <= filteredSignalValues[6] && filteredSignal > filteredSignalValues[7]) {
    RGBColor(255, 0, 127);
    Serial.println("Rose");
  } else if (filteredSignal <= filteredSignalValues[7] && filteredSignal > filteredSignalValues[8]) {
    RGBColor(255, 127, 0);
    Serial.println("Orange");
  } else if (filteredSignal <= filteredSignalValues[8]) {
    RGBColor(255, 0, 0);
    Serial.println("Red");
  } else {
    RGBColor(0, 0, 255);
    Serial.println("Default: Blue");
  }
}

void RGBColor(int Rcolor, int Gcolor, int Bcolor) {

  analogWrite(Rpin, Rcolor);
  analogWrite(Gpin, Gcolor);
  analogWrite(Bpin, Bcolor);

  delay(delayLEDS);
} 
