   /* colors:
 * 0 = white
 * 1 = red
 * 2 = green
 * 3 = blue
 */

int len = 30;    // can be customized, length of session in seconds
float ex = 0.6;  // can be customized, length of exposure in seconds before scramble  

///////////////////////////////////////////////////////////////////////////////////////////o
unsigned long length_of_session = len*1000; // sec to ms
unsigned long exposure = ex*1000; // sec to ms
int missed_hits = 0;
int total_hits = 0;

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
unsigned long begin_time;

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
  randomSeed(analogRead(A5));
  Serial.println("Press all buttons that light up!"); Serial.println();
  begin_time = millis();
}

void loop() {
  delay(random(5000)+5000); //delays LED light up
  int ran;
  int random_LED;
  if (millis()-begin_time < length_of_session) {
    ran = random(1, 4);           
    random_LED = random(0, num_buttons);      // randomly generated LED
    setColor(random_LED, ran);
    ledColor[random_LED] = ran;
  }
  else {
    while (end_func() == false);
    return;
  }
  if (ran < 1000) {      // if correct color LED
      bool done = false;
    while(!done) {
      if ((millis()-initial_time) >= exposure) { 
        Serial.println("Missed!");
        missed_hits++;
        total_rxn_time += exposure;
        total_rxn_time += 100;
        break;
      }
      if (digitalRead(buttons[random_LED]) == LOW) {     // if button is pressed within three seconds, record correct hit
        Serial.print("Hit!   ");
        total_hits ++;
        time_elapsed();
        break;
      }
    }
      digitalWrite(redPins[random_LED], HIGH);
      digitalWrite(greenPins[random_LED], HIGH);
      digitalWrite(bluePins[random_LED], HIGH);
    reset();
  }
}

void time_elapsed() {
  final_time = millis();
  elapsed_time = final_time - initial_time;
  total_rxn_time += elapsed_time;
  Serial.print("Elapsed time = ");
  Serial.print(float(elapsed_time)/1000);
  Serial.println(" s");
}

bool end_func() {
    stopSign();
    Serial.println("");
    Serial.println("Results: ");
    Serial.print("   Average reaction time: "); Serial.print((float(total_rxn_time)/float(total_hits + missed_hits))/1000); Serial.println(" s");
    Serial.print("   Total buttons shown: "); Serial.println(total_hits + missed_hits);
    Serial.print("   Percent hit: "); Serial.print(float(float(total_hits)/float(total_hits + missed_hits))*100); Serial.println("%");
    delay(1500);
    setColor(14, 5); setColor(13, 1); setColor(12, 1); setColor(11, 1); setColor(10, 1); setColor(9, 1); setColor(8, 1);
    while(digitalRead(buttons[14]) == HIGH);
    setColor(14, 4); setColor(13, 4); setColor(12, 4); setColor(11, 4); setColor(10, 4); setColor(9, 4); setColor(8, 4);
    total_hits = 0; missed_hits = 0; total_rxn_time = 0;
    Serial.println(""); Serial.println("Resetting..."); Serial.println("");
    delay(2000);
    begin_time = millis();
    return true;
}

void rule(int color) {
  Serial.print("Only hit ");
  switch(color) {
    case 1: Serial.println("red"); break;
    case 2: Serial.println("green"); break;
    case 3: Serial.println("blue"); break;
  }
  Serial.println("");
}

void reset() {
  for (int i = 0; i < num_buttons; i++){
    buttonStates[i]=HIGH;
  }
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
