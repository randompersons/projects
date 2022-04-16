//Current code for Purdue Engineering Projects in Community Service Music Tuner. Code has been passed down through multiple teams and is currently in a testing phase 
//with our physical model

#include "arduinoFFT.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <math.h> 

#define SAMPLES 8192             //Must be a power of 2 cant be greater than 8192 due to ram
#define SAMPLING_FREQUENCY 10000 //Hz, must be less than 10000 due to ADC
#define LED_LEFT 4
#define LED_CENTER 3
#define LED_RIGHT 2
#define KERNEL_SIZE 3 // size of window for filtering

const char* commands[] = {"0.WAV", "1.WAV", "2.WAV", "3.WAV", "4.WAV", "5.WAV", "6.WAV", "7.WAV", "8.WAV", "9.WAV", "10.WAV", "11.WAV", "12.WAV"};
arduinoFFT FFT = arduinoFFT();


AudioPlaySdWav           playWav1;
AudioOutputAnalog        audioOutput;


AudioConnection          patchCord2(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord3(playWav1, 1, audioOutput, 1);

#define SDCARD_CS_PIN    BUILTIN_SDCARD
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];
int sens = 200; //level that note must reach to be recorded
 
void setup() {
    pinMode(LED_LEFT, OUTPUT);
    pinMode(LED_CENTER, OUTPUT);
    pinMode(LED_RIGHT, OUTPUT);
    Serial.begin(115200);
    AudioMemory(40);
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
    if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while(1){
    Serial.println("Unable to access the SD card");
    delay(500);
    }
    }
}

void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  while (playWav1.isPlaying()) {
   
  }
}




void loop() {
   
    /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(2);
        Serial.println(vReal[i]);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }

    /*FILTERING*/
    double vRealFiltered[SAMPLES];
    int sum; // sum of neighboring values
    for(int j = 0; j < SAMPLES; j++) // duplicates vReal to vRealFiltered (needed for edge values where averaging cannot be done since window would exceed boundaries)
    {
        vRealFiltered[j] = vReal[j];
    }
    for(int k = KERNEL_SIZE / 2; k < SAMPLES - KERNEL_SIZE / 2; k++) // runs through all values far away enough from edges where the window doesn't exceed boundary
    {
        sum = 0; // reinitialize
        for(int m = k - KERNEL_SIZE / 2; m <= k + KERNEL_SIZE / 2; m++) // runs through all values of the window (should have kernelSize number of iterations)
        {
            sum += vReal[m];
        }
        vRealFiltered[k] = sum / KERNEL_SIZE; // average of surrounding window is the new value at that point
    }
    
    /*FFT*/
    FFT.Windowing(vRealFiltered, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vRealFiltered, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vRealFiltered, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vRealFiltered, SAMPLES, SAMPLING_FREQUENCY);
    
    /*PRINT RESULTS*/
    Serial.println(peak);     //Print out what frequency is the most dominant.
    int note = (int) peak;
    double freq;
    //Serial.println();
    //Serial.print("Loudness is ");
    //Serial.println(vReal[note]); 

    double b;
    double a; 
    int d;
   if (vReal[note] > sens)   //add back in!
    {
    Serial.println();
    Serial.print("Freq is ");
    Serial.print(peak);
    //Serial.print(vRealFiltered);
    Serial.println();
    freq = peak;
    b = freq;
    }
    else {
    a = 0;
    b = 0;
    d = 0;
   }

 

    
    
    //IF STATEMENTS

    if (113.3 < b && b <= 120) { //Update lower bound
    a = 130.81; //B2
    d = 12;
    }
    
    if (120 < b && b <= 134.7){ //Update lower bound
    a = 130.81; //C3
    d = 1;
    }
    else if (134.7 < b && b <= 142.71){ 
    a = 138.59; //C3#
    d = 2;
    }
    else if (142.71 < b && b <= 151.195){ 
    a = 146.83; //D3
    d = 3;
    }
    else if (151.195 < b && b <= 160.185){ 
    a = 155.56; //D3#
    d = 4;
    }
    else if (160.185 < b && b <= 169.71){ 
    a = 164.81; //E3
    d = 5;
    }
    else if (169.71 < b && b<= 179.805){ 
    a = 174.61; //F3
    d = 6;
    }
    else if (179.805 < b && b <= 190.5){ 
    a = 185.00; //F3#
    d = 7;
    }
    else if (190.5 < b && b <= 201.825){ 
    a = 196.00;//G3
    d = 8;
    }
    else if (201.825 < b && b <= 213.825){ 
    a = 207.65; //G3#
    d = 9;
    }
    else if (213.825 < b && b <= 226.54){ 
    a = 220.00; //A3
    d = 10;
    }
    else if (226.54 < b && b <= 240.01){
    a = 233.08; //A3# 
    d = 11;
    }
    else if (240.01 < b && b <= 254.285){
    a = 246.94; //B3
    d = 12;
    }
    else if (254.285 < b && b <= 269.405){
    a = 261.63; //C4
    d = 1;
    }
    else if (269.405 < b && b <= 285.42){
    a = 277.18; //C4#
    d = 2;
    }
    else if (285.42 < b && b <= 302.395){
    a = 293.66; //D4
    d = 3;
    }
    else if (302.395 < b && b <= 320.38){
    a = 311.13; //D4#
    d = 4;
    }
    else if (320.38 < b && b <= 339.43){
    a = 329.63; //E4
    d = 5;
    }
    else if (339.43 < b && b <= 359.61){
    a = 349.23; //F4 
    d = 6;
    }
    else if (359.61 < b && b <= 380.995){
    a = 369.99; //F#4
    d = 7;
    }
    else if (380.995 < b && b <= 403.65){
    a = 392; //G4
    d = 8;
    }
    else if (403.65 < b && b <= 427.65){
    a = 415.30; //G4#
    d = 9;
    }
    else if (427.65 < b && b <= 453.08){
    a = 440; //A4
    d = 10;
    }
    else if (453.08 < b && b <= 480.02){ 
    a = 466.16; //A4#
    d = 11;
    }
    else if (480.02 < b && b <= 508.565){ 
    a = 493.88; //B4
    d = 12;
    }
    else if (508.565 < b && b <= 538.81){ 
    a = 523.25; //C5
    d = 1;
    }
    else if (538.81 < b && b <= 570.85){ 
    a = 554.37; //C5#
    d = 2;
    }
    else if (570.85 < b && b <= 604.79){ 
    a = 587.33; //D5
    d = 3;
    }
    else if (604.79 < b && b <= 640.75){ 
    a = 622.25; //D5#
    d = 4;
    }
    else if (640.75 < b && b <= 678.855){ 
    a = 659.25; //E5
    d = 5;
    }
    else if (678.855 < b && b <= 719.225){ 
    a = 698.46; //F5
    d = 6;
    }
    else if (719.225 < b && b <= 761.99){ 
    a = 739.99; //F5#
    d = 7;
    }
    else if (761.99 < b && b <= 807.3){ 
    a = 783.99; //G5
    d = 8;
    }
    else if (807.3 < b && b <= 855.305){ 
    a = 830.61; //G5#
    d = 9;
    }
    else if (855.305 < b && b <= 906.165){ 
    a = 880.00; //A5
    d = 10;
    }
    else if (906.165 < b && b <= 960.05){ 
    a = 932.33; //A5#
    d = 11;
    }
   // else if (960.05 < b && b <= 1017.135){ 
   // a = 987.77; //B5
    //d = 12;
    //}
    else if (1017.135 < b && b < 1100){ //change upper bound
    a = 1046.50; //C6
    d = 1;
    }
    else {
    a = 1; //Out of range
    d = 0;
    }
    
    double c = 1200 * (log(b/a) / log(2));
    
    
    //LED code
    if (-53 < c && c <= -8.3){
    //left led
    digitalWrite(LED_LEFT, HIGH);
    digitalWrite(LED_CENTER, LOW);
    digitalWrite(LED_RIGHT, LOW);
    }
    else if (-8.3 < c && c <= 8.3){
    //center led
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_CENTER, HIGH);
    digitalWrite(LED_RIGHT, LOW);
    }
    else if (8.3 < c && c <= 53){
    //right led
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_CENTER, LOW);
    digitalWrite(LED_RIGHT, HIGH);
    }
    //else {
    //}


    //Code for what wav file to play

    
    if (-53 < c && c <= -41.6){
    delay(500);
    playFile(commands[d]); 
    delay(200);
    playFile("fiftyf.WAV"); 
    delay(200);
    }    
    else if (-41.6 < c && c <= -33.3){
      delay(500);
    playFile(commands[d]); 
    delay(200);    
    playFile("fourtyf.WAV"); 
    delay(200);
    }
    else if (-33.3 < c && c <= -25){
      delay(500); 
      playFile(commands[d]); 
      delay(200);
      playFile("thirtyf.WAV"); 
      delay(200);
    }
    else if (-25 < c && c <= -16.6){
      delay(500);
      playFile(commands[d]); 
      delay(200);
      playFile("twentyf.WAV"); 
      delay(200);
    }    
    else if (-16.6 < c && c <= -8.3){
      delay(500);
      playFile(commands[d]); 
      delay(200);
      playFile("tenf.WAV"); 
      delay(200);
    }
    else if (-8.3 < c && c <= 0){
      delay(500);
    playFile(commands[d]); //CHANGE THIS BACK
    delay(200);
    }
    else if (0 < c && c <= 8.3){
      delay(500);
    playFile(commands[d]); //CHANGE THIS BACK
    delay(200);
    }
    else if (8.3 < c && c <= 16.6){
      delay(500);
      playFile(commands[d]); 
      delay(200);
      playFile("tens.WAV"); 
      delay(200);
    }
    else if (16.6 < c && c <= 25){
      delay(500);
      playFile(commands[d]); 
      delay(200);
      playFile("twentys.WAV"); 
      delay(200);
    } 
    else if (25 < c && c <= 33.3){
      delay(500);
      playFile(commands[d]); 
      delay(200);
      playFile("thirtys.WAV"); 
      delay(200);
    } 
    else if (33.3 < c && c <= 41.6){
      delay(500);
    playFile(commands[d]); 
    delay(200);
    playFile("fourtys.WAV"); 
    delay(200);
    }  
    else if (41.6 < c && c <= 53){
      delay(500);
    playFile(commands[d]); 
    delay(200);
    playFile("fiftys.WAV"); 
    delay(200);
    }  
    else{
    }



    /*
    //Debug code
    Serial.println();
    Serial.print("Note is ");
    Serial.print(b);
    Serial.println();
    Serial.print("Cents is ");
    Serial.print(c);
    Serial.print("a is ");
    Serial.print(a);
    Serial.print("d is ");
    Serial.print(d);
    //delay(1000);  //Repeat the process every second OR:
    */
    
}
