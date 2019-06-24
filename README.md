# Arduino-Acoustic-Control-for-RGB-LED-Strip
Acoustic Control for RGB LED Strips in Arduino using a Sound sensor and a RGB Led strip that changes color with the frequency of the sound, music is used as an example 

 ******** BRAIN SMASH ******** 
 
 ****** AUTHOR: DAEDALUS   6/2019 ******
 
 **** Github.com/BrainSmash ****
 
 You may use or modify this code for any and all of your projects whitout any restrictions
 If you use any fragment of this code we will be happy if you could send a message ;)
 Brain Smash nor the Author are hold responsible for any misuse partially or complete of this code 

   Acoustic Control for RGB LED Strips
  
   Change the color of a LED strip based on the signal value that is received from a Sound sensor,
   the signal is filtered using a First Order Low pass IIR Digital filter with a cutoff frequency 
   of 900Hz the filtered signal is compared with a threshold value that is used to determine
   which color will be displyed based on the frequency of the sound catched by the sensor, 
   the frequency of the sound that is sensed by the sensor represent the voltage output of the sensor,
   low frequency or intensity equal 1023 bits of output of the sensor,
   high frequency or intensity equal close to 0 bits of output of the sensor.
   
   MainFunction()
   
   This method read the value of the output of the Sound sensor with "sensorValue" 
   as a float & substracts 1023 to it since the sound sensor gives an output of 1023 or 5V 
   when is not sensing any sound, this way we have a value of 0 when not sensing sound  
   & values up to 1023 when it senses sound (vibrations in air), we convert the signal
   to volts.
   
   FilterSignal()
   
   Filter the signal using a First Order IIR Low Pass Digital Filter created in Matlab
   and assigned the value to the variable "filteredSignal"
  
   CompareSignalFiltered()
   
   Compare the "filteredSignal" variable with "filteredSignalValues" array 
   to determine where our compared variable value is less, more or in between, our 
   treshold values to assign a color to the LED Strip and print the color that represents 
   what we set. 
   
   RGBColor()
   
   Send to the defined pins for each RGB color a value from 0 to 255 that represent the color 
   that we want; Search on Google RGB Color Wheel to help you learn how colors are created. 
  
