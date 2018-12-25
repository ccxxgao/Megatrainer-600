# Megatrainer-6000

## Yale Athletics Department, Yale Lacrosse——Reaction Training Board

This code was created for a reaction training board with 15 buttons capable of displaying RGB LEDs.
The board was created to train the reaction times of various Yale athletes and create an environment conducive to simulating psychologic stressors an athlete can encounter during a game.
The multiple game modes offer a high degree of customizability by the user and target different aspects of human reaction (time, accuracy, stamina).
This project was given credit for Yale Lacrosse's historic 2018 National Championship win.

Article: [*Engineering a Championship*](https://news.yale.edu/2018/12/07/engineering-championship)

[Demos ft. Yale Athletics and Yale SEAS](https://drive.google.com/open?id=1kIcDlqelc1zpJhlsuj2p-aEHg2j-pehl)

**Color Code:**

| **Value** | **Color** |       
| ----- |:-----:|
| 1     | red   |
| 2     | green |
| 3     | blue  |
| 4     | off   |

**Single Light** = one button flashes at a time

**Light Array** = all 15 buttons flash at a time

### Disappearing Whack-a-Mole (Single Light)
Buttons are exposed only for a set time before they disappear

Customizable frequency, useful for stamina training

``` C++
int len = 30;               // can be customized, length of session in seconds
float ex = 0.6;             // can be customized, length of exposure in seconds before scramble  
```

_**Recorded:** reaction time and hit rate_

### Whack-a-Mole with Dummies (Single Light)
One correct color; “dummy” buttons thrown in

``` C++
int rightColor = 1;         // can be customized
int num_rightColor = 5;     // number of correct LEDs per session; can be customized
int delay_time = 1;         // random delay between each led in seconds, lower bound 0.5 seconds
```

_**Recorded:** reaction time and accuracy_

### All-At-Once (Light Array)
One correct color, all lights go off

``` C++
int rightColor = 2;         // can be customized
int runs = 10;              // total amount of times to display light arra
```

_**Recorded:** time taken to hit all correct buttons in a light array and incorrect hits_

### Scramble (Light Array)
Correct light; if incorrect button is hit, lights are scrambled

``` C++
int rightColor = 2;         // can be customized
int session_length = 20;    // can be customized, length of session in seconds
```

_**Recorded:** average reaction time, total hits, and accuracy_

### D-Line Drill (Light Array)
Must hit *x* amount of correct buttons in a row

If incorrect button is hit, light array is scrambled, and button count starts from 0

``` C++
int rightColor = 2;         // can be customized
int hits = 40;              // can be customized, the number of correct hits in a row needed to finish the session
```

_**Recorded:** total time taken to hit x correct buttons in a row and incorrect hits_

### Newman Drill (Light Array)
*Known to bring any athlete——from tennis players to football stars——to tears. Named in honor of the Yale Strength Coach, Thomas Newman.*

One correct color, runs for *x* seconds

Light array is exposed for a customizable time (e.g. 0.4 s) before scrambling

``` C++
int rightColor = 3;         // can be customized
unsigned long len = 30;     // can be customized, length of session in seconds
float exposure_time = 0.7;  // can be customized, length of exposure in seconds before scramble
```

_**Recorded:** correct and incorrect hits, accuracy_
