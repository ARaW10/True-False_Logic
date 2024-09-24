/*
  Title:          True/False Logic (LARGE VERSION)
  Creator:        ARaW
  Inspired from:  Imamid - Github
  Used Component: Arduino Uno, 4x PushButtons, 3x LED's, 3x 220Ω Resistor, LCD OLED 0.96 
                  Potentiometer, Servo, Buzzer
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// Define LED
#define LedRed    12
#define LedYellow 11
#define LedGreen  10

// Define Behavior Things
#define Buzzer    13
#define Potentio  A3
#define ServoPin  9

// Define Button
#define btnUp     2
#define btnDown   3
#define btnOk     4
#define btnBack   5

// IDK what is this
#define OLED_RESET -1 

// Define boolean data for LED
bool dataLED1 = false;
bool dataLED2 = false;
bool dataLED3 = false;

// Define boolean data for Additional Feature
bool dataBuzzer = false;
bool dataServo = false;
bool dataLED = false;

// Define boolean data for Button Status
boolean statusBtnUp   = false;
boolean statusBtnOk   = false;
boolean statusBtnDown = false;
boolean statusBtnBack = false;

// Define boolean data for Button Later Status
boolean lastStatusBtnUp   = false;
boolean lastStatusBtnOk   = false;
boolean lastStatusBtnDown = false;
boolean lastStatusBtnBack = false;

// Define boolean data for Navigation
boolean UP   = false;
boolean OK   = false;
boolean DOWN = false;
boolean BACK = false;

Servo servo;

// Define additional data
int dataPotent;
int page      = 1;
int menuItemA = 1;
int menuItemB = 1;

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

void setup() {
  pinMode(LedRed,     OUTPUT);
  pinMode(LedYellow,  OUTPUT);
  pinMode(LedGreen,   OUTPUT);
  pinMode(Buzzer,     OUTPUT);
  pinMode(Potentio,   INPUT);

  pinMode(btnUp,   INPUT_PULLUP);
  pinMode(btnOk,   INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnBack, INPUT_PULLUP);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    while (true) { // Loop forever if initialization fails
      // Optionally, you can flash an LED or print an error message over Serial
      digitalWrite(LedRed, HIGH); // Error indication (optional)
      delay(500);
      digitalWrite(LedRed, LOW);
      delay(500);
    }
  }

  display.clearDisplay();

  servo.attach(ServoPin);
}

void loop() {
  // Displaying Home
  homeDisplay();
  // Execute The Data
  execute();
  // Reading Button
  statusBtnUp   = digitalRead(btnUp);
  statusBtnOk   = digitalRead(btnOk);
  statusBtnDown = digitalRead(btnDown);
  statusBtnBack = digitalRead(btnBack);

  // Calling button function void
  saatUpDitekan();
  saatOkDitekan();
  saatDownDitekan();
  saatBackDitekan();

  // For button Up
  if (UP && page == 1) {
    UP = false;
    menuItemA --;
    if (menuItemA < 1)menuItemA = 3;
  }
  else if (UP && page == 3) {
    UP = false;
    menuItemB --;
    if (menuItemB < 1)menuItemB = 3;
  }
  // For button Down
  if (DOWN && page == 1) {
    DOWN = false;
    menuItemA ++;
    if (menuItemA > 3)menuItemA = 1;
  }
  else if (DOWN && page == 3) {
    DOWN = false;
    menuItemB ++;
    if (menuItemB > 3)menuItemB = 1;
  }
  // For button Ok
  if (OK) {
    OK = false;
    delay(100);
    if (page == 1 && menuItemA == 1) {
      page = 2;
    } else if (page == 1 && menuItemA == 2) {
      page = 3;
    } else if (page == 1 && menuItemA == 3) {
      page = 4;
    }

    if (page == 3 && menuItemB == 1) {
      dataBuzzer = !dataBuzzer;
    }
    else if (page == 3 && menuItemB == 2) {
      dataServo = !dataServo;
    }
    else if (page == 3 && menuItemB == 3) {
      dataLED = !dataLED;
    }
  }
  // For button Back
  if (BACK) {
    BACK = false;
    if (page == 2 || page == 3 || page == 4) {
      page = 1;
    }
  }
}

// ============= Button Execute Function ============= //

void saatUpDitekan() {
  if (statusBtnUp != lastStatusBtnUp) {
    if (statusBtnUp == 0) {
      UP = true;
    }
    delay(50);
  }
  lastStatusBtnUp = statusBtnUp;
}

void saatOkDitekan() {
  if (statusBtnOk != lastStatusBtnOk) {
    if (statusBtnOk == 0) {
      OK = true;
    }
    delay(50);
  }
  lastStatusBtnOk = statusBtnOk;
}

void saatDownDitekan() {
  if (statusBtnDown != lastStatusBtnDown) {
    if (statusBtnDown == 0) {
      DOWN = true;
    }
    delay(50);
  }
  lastStatusBtnDown = statusBtnDown;
}

void saatBackDitekan() {
  if (statusBtnBack != lastStatusBtnBack) {
    if (statusBtnBack == 0) {
      BACK = true;
    }
    delay(50);
  }
  lastStatusBtnBack = statusBtnBack;
}

// =============== Displaying Pages ================= //

void homeDisplay() {
  if(page == 1) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10,5);
    display.print("List Menu");

    if (menuItemA == 1) {
      display.setTextSize(1);
      display.setCursor(5, 27);
      display.print("> Check Status");
    } else {
      display.setTextSize(1);
      display.setCursor(5, 27);
      display.print("  Check Status");
    }

    if (menuItemA == 2) {
      display.setTextSize(1);
      display.setCursor(5, 37);
      display.print("> Feature Toggle");
    } else {
      display.setTextSize(1);
      display.setCursor(5, 37);
      display.print("  Feature Toggle");
    }

    if (menuItemA == 3) {
      display.setTextSize(1);
      display.setCursor(5, 47);
      display.print("> Credit");
    } else {
      display.setTextSize(1);
      display.setCursor(5, 47);
      display.print("  Credit");
    }

    border();
  }
  else if (page == 2) {
    dataBehavior();
  }
  else if (page == 3) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10,5);
    display.print("Feature");

    if (dataBuzzer == 1) {
      if (menuItemB == 1) {
        display.setTextSize(1);
        display.setCursor(5, 27);
        display.print("> Buzzer : On");
      } else {
        display.setTextSize(1);
        display.setCursor(5, 27);
        display.print("  Buzzer : On");
      }
    } else if (dataBuzzer == 0) {
      if (menuItemB == 1) {
        display.setTextSize(1);
        display.setCursor(5, 27);
        display.print("> Buzzer : Off");
      } else {
        display.setTextSize(1);
        display.setCursor(5, 27);
        display.print("  Buzzer : Off");
      }
    }

    if (dataServo == 1) {
      if (menuItemB == 2) {
        display.setTextSize(1);
        display.setCursor(5, 37);
        display.print("> Servo  : On");
      } else {
        display.setTextSize(1);
        display.setCursor(5, 37);
        display.print("  Servo  : On");
      }
    } else if (dataServo == 0) {
      if (menuItemB == 2) {
        display.setTextSize(1);
        display.setCursor(5, 37);
        display.print("> Servo  : Off");
      } else {
        display.setTextSize(1);
        display.setCursor(5, 37);
        display.print("  Servo  : Off");
      }
    }

    if (dataLED == 1) {
      if (menuItemB == 3) {
        display.setTextSize(1);
        display.setCursor(5, 47);
        display.print("> LED  : On");
      } else {
        display.setTextSize(1);
        display.setCursor(5, 47);
        display.print("  LED  : On");
      }
    } else if (dataLED == 0) {
      if (menuItemB == 3) {
        display.setTextSize(1);
        display.setCursor(5, 47);
        display.print("> LED  : Off");
      } else {
        display.setTextSize(1);
        display.setCursor(5, 47);
        display.print("  LED  : Off");
      }
    }
    border();
  }
  else if (page == 4) {
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10, 0);
    display.println(F("Credit to"));
    
    display.setTextSize(1);
    display.setCursor(0, 17);
    display.println(F("Designer, Coder, &"));
    display.setCursor(0, 27);
    display.println(F("Publisher => ARaW"));
    display.setCursor(0, 40);
    display.println(F("Special thank to     imamid-Github for    repository code"));
  }

  display.display();
}

// ============= Execute Function ============= //
void execute() {
  dataPotent = analogRead(Potentio);
  int Roll = map(dataPotent, 0,1023, 0,180);

  // Servo Function
  if (dataServo == 1) {
    servo.write(Roll);
  }

  // LED Function
  if (dataLED == 1) {
    if ((dataPotent >= 50) && (dataPotent <= 450)) {
      digitalWrite(LedRed, LOW);
      digitalWrite(LedYellow, LOW);
      digitalWrite(LedGreen, HIGH);
      dataLED1 = false;
      dataLED2 = false;
      dataLED3 = true;
      delay(500);
    }
    else if ((dataPotent > 450) && (dataPotent <= 950)) {
      digitalWrite(LedRed, LOW);
      digitalWrite(LedYellow, HIGH);
      digitalWrite(LedGreen, HIGH);
      dataLED1 = false;
      dataLED2 = true;
      dataLED3 = true;
      delay(250);
    } 
    else if (dataPotent > 950) {
      digitalWrite(LedRed, HIGH);
      digitalWrite(LedYellow, HIGH);
      digitalWrite(LedGreen, HIGH);
      dataLED1 = true;
      dataLED2 = true;
      dataLED3 = true;
      delay(100);
    } 
  } 

  // Buzzer Function
  if (dataBuzzer == 1) {
    if ((dataPotent >= 50) && (dataPotent <= 450)) {
      if (dataBuzzer == 1) {
        tone(Buzzer, 5000, 100);
      }
      delay(500);
    }
    else if ((dataPotent > 450) && (dataPotent <= 950)) {
      if (dataBuzzer == 1) {
        tone(Buzzer, 5000, 100);
      }
      delay(250);
    } 
    else if (dataPotent > 950) {
      if (dataBuzzer == 1) {
        tone(Buzzer, 5000, 100);
      }
      delay(100);
    } 
  } 
  
  else {
    digitalWrite(LedRed, LOW);    
    digitalWrite(LedYellow, LOW);
    digitalWrite(LedGreen, LOW);
    dataLED1 = false;
    dataLED2 = false;
    dataLED3 = false;
  }
}

void dataBehavior() {
  display.clearDisplay();
  dataPotent = analogRead(Potentio);
  int Roll = map(dataPotent, 0,1023, 0,180);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(F("ALL STATUS"));

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print(F("Status LED1 = "));
  display.println(dataLED1 ? F("On") : F("Off"));

  display.setCursor(0, 30);
  display.print(F("Status LED2 = "));
  display.println(dataLED2 ? F("On") : F("Off"));

  display.setCursor(0, 40);
  display.print(F("Status LED3 = "));
  display.println(dataLED3 ? F("On") : F("Off"));

  display.setCursor(0, 50);
  display.print(F("Status Servo = "));
  if (dataServo == 1) {
    display.print(Roll);
    display.print((char)248);
  } else {
    display.println(F("Off"));
  }

  border();

  display.display();
}

void border() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,60);
  display.print("---------------------");
  display.display();
}