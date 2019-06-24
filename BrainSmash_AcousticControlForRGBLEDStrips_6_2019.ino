/**********************************
* ******** BRAIN SMASH ******** 
* ****** AUTHOR: DAEDALUS   6/2019 ******
* **** Visit us at: Youtube.com/BrainSmash ****
* ** Github.com/BrainSmash **
* You may use or modify this code for any and all of your projects whitout any restrictions
* If you use any fragment of this code we will be happy if you could drop us a message ;)
* Brain Smash nor the Author are hold responsible for any misuse partially or complete of this code 
*/

/*
 *  Acoustic Control for RGB LED Strips
 *  
 *  Change the color of a LED strip based on the signal value that is received from a Sound sensor,
 *  the signal is filtered using a First Order Low pass IIR Digital filter with a cutoff frequency 
 *  of 900Hz the filtered signal is compared with a threshold value that is used to determine
 *  which color will be displyed based on the frequency of the sound catched by the sensor, 
 *  the frequency of the sound that is sensed by the sensor represent the voltage output of the sensor,
 *  low frequency or intensity equal 1023 bits of output of the sensor,
 *  high frequency or intensity equal close to 0 bits of output of the sensor.
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

#define Rpin 11
#define Gpin 10
#define Bpin 9
#define delayLEDS 3
#define sensorPin A0

float sensorValue = 0, filteredSignal = 0,
      filteredSignalValues[] = {0.4, 0.9, 1.3, 1.7, 2.1, 2.4, 2.7, 3.1, 3.4};

void setup () {

  Serial.begin (9600);
}

void loop () {

  MainFunction();
}

void MainFunction() {

  sensorValue = (float)(1023.0 - analogRead(sensorPin)) * (5.0 / 1024.0);

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

  if (filteredSignal < filteredSignalValues[0]) {
    RGBColor(0, 0, 255);
    Serial.println("Blue");
  } else if (filteredSignal >= filteredSignalValues[0] && filteredSignal < filteredSignalValues[1]) {
    Serial.println("Azure");
    RGBColor(0, 255, 255);
  } else if (filteredSignal >= filteredSignalValues[1] && filteredSignal < filteredSignalValues[2]) {
    RGBColor(0, 127, 255);
    Serial.println("Cyan");
  } else if (filteredSignal >= filteredSignalValues[2] && filteredSignal < filteredSignalValues[3]) {
    RGBColor(0, 255, 127);
    Serial.println("Aqua marine");
  } else if (filteredSignal >= filteredSignalValues[3] && filteredSignal < filteredSignalValues[4]) {
    RGBColor(0, 255, 0);
    Serial.println("Green");
  } else if (filteredSignal >= filteredSignalValues[4] && filteredSignal < filteredSignalValues[5]) {
    RGBColor(127, 255, 0);
    Serial.println("Chartreuse");
  } else if (filteredSignal >= filteredSignalValues[5] && filteredSignal < filteredSignalValues[6]) {
    RGBColor(255, 255, 0);
    Serial.println("Yellow");
  } else if (filteredSignal >= filteredSignalValues[6] && filteredSignal < filteredSignalValues[7]) {
    RGBColor(255, 0, 255);
    Serial.println("Magenta");
  } else if (filteredSignal >= filteredSignalValues[7] && filteredSignal < filteredSignalValues[8]) {
    RGBColor(255, 0, 127);
    Serial.println("Rose");
  } else if (filteredSignal >= filteredSignalValues[8] && filteredSignal < filteredSignalValues[9]) {
    RGBColor(255, 127, 0);
    Serial.println("Orange");
  } else if (filteredSignal >= filteredSignalValues[9]) {
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
