/* colors:
 * 0 = white
 * 1 = red
 * 2 = green
 * 3 = blue
 */
int rightColor = 1;          // can be customized
int num_rightColor = 5;     // number of correct LEDs per session; can be customized
int delay_time = 1;          // random delay between each led in seconds, lower bound 0.5 seconds

////////////////////////////////////////////////////////////////////////////////////////

int distance = 1;                // "distance" between two correct LEDs
int incorrect_hits = 0;
unsigned long delayed = delay_time * 1000;    // delay converted to ms

const int num_right = num_rightColor;

const int num_buttons = 15;
const int redPins[] = {10, 6, 2, 17, 21, 29, 22, 37, 30, 45, 38, 53, 46, 69, 65};
const int greenPins[] = {11, 7, 3, 16, 20, 27, 24, 35, 32, 43, 40, 51, 48, 68, 64};
const int bluePins[] = {12, 8, 4, 15, 19, 25, 26, 33, 34, 41, 42, 49, 50, 67, 63};
const int buttons[] = {13, 9, 5, 14, 18, 23, 28, 31, 36, 39, 44, 47, 52, 66, 62};

int buttonStates[num_buttons];                     // array for storing button states (HIGH or LOW)
int ledColor[num_buttons];                         // array for storing colors of LEDs

unsigned long initial_time = 0;          // time led turns on
unsigned long final_time = 0;            // time button pressed
unsigned long elapsed_time = 0;          // reaction time
unsigned long total_rxn_time = 0;

void setup() {
  for (int i = 0; i < num_buttons; i++) {
    pinMode(buttons[i], INPUT);
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
    pinMode(bluePins[i], OUTPUT);
    buttonStates[i]=HIGH;
    setColor(i, 4);
  }
  Serial.begin(9600);
  randomSeed(analogRead(A7));
  rule(rightColor);
  colorIndicator();
}

void loop() {
  int ran;
  int random_LED;
  if (num_rightColor > 0) {
    delay(random(delayed) + 500); //delays LED light up
    ran = random(1, 4);            // random number to decide whether or not correct color will be displayed;
    if (ran == rightColor or distance == 0) {
      ran = rightColor;
      num_rightColor--;
      random_LED = random(0, num_buttons);      // randomly generated LED
      setColor(random_LED, rightColor);
      ledColor[random_LED] = rightColor;
      distance = random(1, 4);        // randomly generated "distance" to next LED
      distance--;
    }
    else {                          // sets random LED to wrong color
      distance--;
      random_LED = random(0, num_buttons);
      setColor(random_LED, ran);
      ledColor[random_LED] = ran;
    }
  }
  
  else {                             // if number of correct LEDs goes to zero, session over
    while (end_func()==false);
    return;
  }
  
  if (ran == rightColor) {      // if correct color LED
    while(digitalRead(buttons[random_LED]) == HIGH)     // wait until button corresponding to LED is pressed
    {
       buttonStates[random_LED] = LOW;
    }
    accuracy(random_LED);
    time_elapsed();
  }
  else {
    bool done = false;
    while(!done) {    // while no button is pressed
      if ((millis()-initial_time) >= 1500) {             // if three seconds go by and no button is pressed, exit while loop to turn off button
        //Serial.println("Good! You didn't press!");
        done = true;
        break;
      }
      if (digitalRead(buttons[random_LED]) == LOW) {     // if button is pressed within three seconds, record incorrect hit
        Serial.println("Incorrect!");
        incorrect_hits++;
        done = true;
        break;
      }
    }
    for (int i = 0; i < num_buttons; i++) {     // turn off LED
      digitalWrite(redPins[i], HIGH);
      digitalWrite(greenPins[i], HIGH);
      digitalWrite(bluePins[i], HIGH);
    }
  }
}

void accuracy(int led) {
  if (ledColor[led] == rightColor && buttonStates[led] == LOW)
      Serial.print("Correct! ");
  else
    Serial.print("Incorrect! ");
  for (int i = 0; i < num_buttons; i++){
    buttonStates[i]=HIGH;
  }
}

void time_elapsed() {
  final_time = millis();
  for (int i = 0; i < num_buttons; i++) {
    digitalWrite(redPins[i], HIGH);
    digitalWrite(greenPins[i], HIGH);
    digitalWrite(bluePins[i], HIGH);
  }
  elapsed_time = final_time - initial_time;
  total_rxn_time += elapsed_time;
  Serial.print("Elapsed time = ");
  Serial.print(float(elapsed_time)/1000);
  Serial.println(" s");
}

bool end_func(){
  stopSign();
  Serial.println();Serial.println("Results: ");
  Serial.print("   Average reaction time: "); Serial.print(float(float(total_rxn_time)/float(num_right))/1000); Serial.println(" s");
  Serial.print("   Incorrect hits: "); Serial.println(incorrect_hits);
  delay(1500);
  setColor(14, 5); setColor(13, 1); setColor(12, 1); setColor(11, 1); setColor(10, 1); setColor(9, 1); setColor(8, 1);
  while(digitalRead(buttons[14]) == HIGH);
  setColor(14, 4); setColor(13, 4); setColor(12, 4); setColor(11, 4); setColor(10, 4); setColor(9, 4); setColor(8, 4);
  Serial.println(""); Serial.println("Resetting..."); Serial.println("");
  delay(1000);
  rightColor = random(1, 4); rule(rightColor); num_rightColor = num_right; total_rxn_time = 0; Serial.println(num_rightColor);
  delay(1000);
  colorIndicator();
  return true;
}

void rule(int color) {
  Serial.print("Only hit ");
  switch(color) {
    case 1: Serial.print("red\n");  break;
    case 2: Serial.println("green");  break;
    case 3: Serial.println("blue");  break;
  }
  Serial.println("");
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
