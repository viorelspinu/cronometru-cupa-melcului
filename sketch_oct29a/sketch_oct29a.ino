#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


#define IDLE_STATE  0
#define RACING_STATE  1
#define AFTER_RACING_STATE 2

int state = IDLE_STATE;
long timeStart = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(8, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

}

void loop() {

  int pressureSensor = digitalRead(8);

  if (IDLE_STATE == state) {    
    if (pressureSensor) {
      lcd.clear();
      state = RACING_STATE;
      timeStart = millis();
    }
  }
  if (RACING_STATE == state) {
    long elapsedTime = millis() - timeStart;
    lcd.setCursor(0, 0);
    lcd.print((float)elapsedTime / 1000);
    if (pressureSensor) {
      if (elapsedTime > 5000) {
        state = AFTER_RACING_STATE;
        lcd.setCursor(0, 1);
        lcd.print("REZULTAT FINAL");
        lcd.setCursor(0, 0);
        lcd.print((float)elapsedTime / 1000);
        lcd.print(" sec");
      }
    }
  }

  if (AFTER_RACING_STATE == state){
    int resetButton = digitalRead(10);
    if (resetButton){
      lcd.clear();
      lcd.print("RACE !");
      state = IDLE_STATE;
    }
  }


}

