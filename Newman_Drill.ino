/* colors:
 * 1 = red
 * 2 = green
 * 3 = blue
 * 4 = off
 */
int rightColor = 3;  // can be customized
unsigned long len = 30; // can be customized, length of session in milliseconds
                                         // seconds x 1000
float exposure_time = 0.7;  // can be customized, length of exposure in seconds before scramble                                         

///////////////////////////////////////////////////////////////////////////////

unsigned long exposure = exposure_time*1000;    // ms to s
unsigned long length_of_session = len*1000;     // ms to s
int num_incorrect = 0;
int num_correct = 0;
int total_incorrect = 0;
int total_correct = 0;
int correct = 0;
int tot_run = 0;
int correct_leds = 0;
int tot_correct_shown = 0;
int tpast = 0;                          // for check_button()

const int num_buttons = 15;
const int redPins[] = {10, 6, 2, 17, 21, 29, 22, 37, 30, 45, 38, 53, 46, 69, 65};
const int greenPins[] = {11, 7, 3, 16, 20, 27, 24, 35, 32, 43, 40, 51, 48, 68, 64};
const int bluePins[] = {12, 8, 4, 15, 19, 25, 26, 33, 34, 41, 42, 49, 50, 67, 63};
const int buttons[] = {13, 9, 5, 14, 18, 23, 28, 31, 36, 39, 44, 47, 52, 66, 62};

int buttonStates[num_buttons];                     // array for storing states of buttons
int ledColor[num_buttons];                     // array for storing colors of LEDs

unsigned long initial_time = 0;          // time led turns on
unsigned long final_time = 0;            // time button pressed
unsigned long elapsed_time = 0;          // reaction time
unsigned long begin_session= 0;


void setup() {
  for (int i = 0; i < num_buttons; i++) {
    buttonStates[i] = HIGH;
    pinMode(buttons[i], INPUT);
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
    pinMode(bluePins[i], OUTPUT);
    setColor(i, 4);
  }
  Serial.begin(9600);
  randomSeed(analogRead(A5));
  rule(rightColor);
  Serial.print(len); Serial.println(" second session");
  Serial.print(exposure_time); Serial.println(" second exposure"); Serial.println();
  colorIndicator();
  begin_session=millis();
}

void loop() {
  if (millis() - begin_session < length_of_session) {
    tot_run++;
    delay(100);                    //delays LED light up
    correct_leds = 1;                            // every run has at least one correct led
    //sets random LED to be the correct color
    int number = random(0, num_buttons);
    setColor(number, rightColor);
    ledColor[number] = rightColor;
    tot_correct_shown ++;
    //sets the other LEDs to random colors
    for (int i = 0; i < num_buttons; i++){
      if (i == number)
        continue;
      int color = random(1, 4); 
      if (color == rightColor){
        correct_leds++;
        tot_correct_shown++;
      }
      setColor(i, color);
      ledColor[i] = color;
    }
    reset();
    //delay(10);
    
    tpast = millis();        // for check_button()
    while (correct_leds > 0 && (millis()-initial_time < exposure)) {  //runs until all correct leds are turned off
      correct_leds = check_button();
    }
    reset();
  }
  else {
    while (end_func() == false);
    begin_session = millis();
    return;
  }
}

int check_button() {
  int tnow = millis();
  int time_diff = tnow - tpast;                   // how long until last call of function
  
  for (int i = 0; i < num_buttons; i ++) {                   // reads and records button states
    buttonStates[i] = digitalRead(buttons[i]);
  }
  for (int i = 0; i < num_buttons; i++) {
    if ((buttonStates[i] == LOW) && (ledColor[i] == rightColor) && time_diff > 70){  // if button pressed was correct button
      digitalWrite(redPins[i], HIGH);
      digitalWrite(greenPins[i], HIGH);
      digitalWrite(bluePins[i], HIGH);
      ledColor[i] = 4;     // turn color to off-state so led will not be counted twice
      correct_leds--; correct++; num_correct++; total_correct ++;
      buttonStates[i] == HIGH;
    }
    if ((buttonStates[i] == LOW) && !(ledColor[i] == rightColor) && !(ledColor[i] == 4) && time_diff > 150) { // if button pressed was incorrect
      delay(100);
      num_incorrect++; total_incorrect++;
      buttonStates[i] == HIGH;
    }
  }
  //Serial.print(total_incorrect);
  reset();
  return correct_leds;
}

bool end_func() {
  for(int i = 0; i < num_buttons; i++){
    setColor(i, 4);
  }
  stopSign();
  Serial.println("Results:");
    Serial.print("   Total hits = "); Serial.println(total_incorrect + total_correct);
    Serial.print("      Correct = "); Serial.print(total_correct); Serial.print("/"); Serial.println(tot_correct_shown);
    Serial.print("      Incorrect hits = "); Serial.println(total_incorrect);
    Serial.print("      Percentage = "); Serial.print(float(float(total_correct-total_incorrect)/float(tot_correct_shown))*100); Serial.println("%");
    setColor(14, 5);
    while(digitalRead(buttons[14]) == HIGH);
    setColor(14, 4);
    tot_run = 0; correct=0; total_incorrect = 0; total_correct = 0; tpast = 0; tot_correct_shown = 0;
    reset();
    Serial.println(); Serial.println("Resetting"); Serial.println();
    delay(1000);
    rightColor = random(1, 4); rule(rightColor);
    delay(1000);
    colorIndicator();
    return true;
}

void colorIndicator() {
  setColor(0, rightColor); setColor(1, rightColor); setColor(2, rightColor); setColor(3, rightColor); setColor(4, rightColor); setColor(5, rightColor); setColor(6, rightColor); setColor(7, rightColor);
  delay(1000);
  setColor(0, 4); setColor(2, 4); setColor(3, 4); setColor(4, 4); setColor(5, 4); setColor(6, 4); setColor(7, 4); setColor(1, 4);
  setColor(8, rightColor); setColor(9, rightColor); setColor(10, rightColor); setColor(11, rightColor); setColor(12, rightColor); setColor(13, rightColor);
  delay(1000);
  setColor(8, 4); setColor(9, 4); setColor(10, 4); setColor(11, 4); setColor(12, 4); setColor(13, 4);
  setColor(14, rightColor);
  delay(1000);
  setColor(14, 4);
  delay(1000);
}

void reset() {
  for (int i = 0; i < num_buttons; i++) {
    buttonStates[i]=HIGH;
  }
}

void rule(int color) {
  Serial.print("Only hit ");
  switch(color) {
    case 1: Serial.print("red\n"); break;
    case 2: Serial.println("green"); break;
    case 3: Serial.println("blue"); break;
  }
  Serial.println();
}

void stopSign() {
  delay(500);
  for (int i = 8; i<num_buttons; i++) {
    setColor(i, 1);
  }
  delay(500);
  for (int i = 8; i<num_buttons; i++) {
    setColor(i, 4);
  }
  delay(500);
  for (int i = 8; i<num_buttons; i++) {
    setColor(i, 1);
  }
  delay(500);
  for (int i = 8; i<num_buttons; i++) {
    setColor(i, 4);
  }
  delay(500);
  for (int i = 8; i<num_buttons; i++) {
    setColor(i, 1);
  }
  delay(500);
  for (int i = 8; i<num_buttons; i++) {
    setColor(i, 4);
  }
}

void setColor(int led, int color) {
  initial_time = millis();
  if (color == 1) {
    digitalWrite(redPins[led], LOW);
    digitalWrite(greenPins[led], HIGH);
    digitalWrite(bluePins[led], HIGH);
  }
  else if (color == 2) {
    digitalWrite(redPins[led], HIGH);
    digitalWrite(greenPins[led], LOW);
    digitalWrite(bluePins[led], HIGH);
  }
  else if (color == 3) {
    digitalWrite(redPins[led], HIGH);
    digitalWrite(greenPins[led], HIGH);
    digitalWrite(bluePins[led], LOW);
  }
  else if (color == 4) {
    digitalWrite(redPins[led], HIGH);
    digitalWrite(greenPins[led], HIGH);
    digitalWrite(bluePins[led], HIGH);
  }
  else if (color == 5) {
    digitalWrite(redPins[led], HIGH);
    digitalWrite(greenPins[led], LOW);
    digitalWrite(bluePins[led], LOW);
  }
}
