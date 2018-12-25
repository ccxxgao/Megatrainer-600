# **Megatrainer-6000**

## **Yale Athletics Department, Yale Lacrosse——Reaction Training Board**

This code was created for a reaction training board with 15 buttons capable of displaying RGB LEDs.
The board was created to train the reaction times of various Yale athletes and create an environment conducive to simulating psychologic stressors an athlete can encounter during a game.
The multiple game modes offer a high degree of customizability by the user and target different aspects of human reaction (time, accuracy, stamina).
This project was given credit for Yale Lacrosse's historic 2018 National Championship win.

Article: [*Engineering a championship*](https://news.yale.edu/2018/12/07/engineering-championship)

[Demos ft. Yale Athletics and Yale SEAS](https://drive.google.com/open?id=1kIcDlqelc1zpJhlsuj2p-aEHg2j-pehl)



**Single Light = one button flashes at a time**

**Light Array = all 15 buttons flash at a time**

### **Disappearing Whack-a-Mole (Single Light)**
Buttons are exposed only for a set time before they disappear

Customizable frequency, useful for stamina training

_**Recorded:** reaction time and hit rate_

### Whack-a-Mole with Dummies (Single Light)
One correct color; “dummy” buttons thrown in

_**Recorded:** reaction time and accuracy_

### All-At-Once (Light Array)
One correct color, all lights go off

_**Recorded:** time taken to hit all correct buttons in a light array and incorrect hits_

### Scramble (Light Array)
Correct light; if incorrect button is hit, lights are scrambled

_**Recorded:** average reaction time, total hits, and accuracy_

### D-Line Drill (Light Array)
Must hit *x* amount of correct buttons in a row

If incorrect button is hit, light array is scrambled, and button count starts from 0

_**Recorded:** total time taken to hit x correct buttons in a row and incorrect hits_

### Newman Drill (Light Array)
*Known to bring any athlete——from tennis players to football stars——to tears. Named in honor of the Yale Strength Coach, Thomas Newman.*

One correct color, runs for x seconds

Light array is exposed for a customizable time (e.g. 0.4 s) before scrambling

_**Recorded:** correct and incorrect hits, accuracy_
