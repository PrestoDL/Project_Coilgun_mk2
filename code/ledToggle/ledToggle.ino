// input
const int bt_charger = 0;
const int sens1 = 1;
const int sens2 = 2;
const int sens3 = 3;
const int bt_reload = 4;
const int bt_expand = 5;
const int bt_trigger = 6;
const int bt_laser = 7;

// output
const int charger = 8;
const int coil1 = 9;
const int coil2 = 10;
const int coil3 = 11;
const int laser = 12;

// analog
const int mt_gunstock = A0;
const int mt_expand = A1;
const int mt_reload = A2;
// const int SDA = A4;
// const int SCL = A5;



/*
bool status = false;
bool buttonNow = true;
bool buttonLast = true;

unsigned long lastDebounceTime = 0;   // 마지막으로 버튼이 눌린 시간 저장
unsigned long debounceDelay = 100;    // 디바운스 시간 지연
*/

void setup() {
  pinMode(bt_charger, INPUT_PULLUP);
  pinMode(sens1, INPUT);
  pinMode(sens2, INPUT);
  pinMode(sens3, INPUT);
  pinMode(bt_reload, INPUT_PULLUP);
  pinMode(bt_expand, INPUT_PULLUP);
  pinMode(bt_trigger, INPUT_PULLUP);
  pinMode(bt_laser, INPUT_PULLUP);

  pinMode(charger, OUTPUT);
  pinMode(coil1, OUTPUT);
  pinMode(coil2, OUTPUT);
  pinMode(coil3, OUTPUT);
  pinMode(laser, OUTPUT);


  // pinMode(led, OUTPUT);
  // pinMode(button, INPUT_PULLUP);      // 풀업 저항을 사용하여 버튼이 눌리지 않았을 때 HIGH
  // digitalWrite(led, status);          // 초기 LED 상태
}

void loop() {
  if (digitalRead(sens1) == 1) {
    digitalWrite(coil1, 1);
  }

  else {
    digitalWrite(coil1, 0);
  }


  /*
  buttonNow = digitalRead(button);

  // 버튼의 상태가 변했는지 확인 (떨림 가능성 존재)
  if (buttonNow != buttonLast) {
    // 디바운스 지연 시간 동안 상태가 변하지 않으면 안정된 것으로 간주
    if ((millis() - lastDebounceTime) > debounceDelay) {
      // 버튼이 눌렸을 때(LOW)만 토글
      if (buttonNow == LOW) {
        status = !status;
        digitalWrite(led, status);
      }
    }
    // 마지막 디바운스 시간을 현재 시간으로 갱신
    lastDebounceTime = millis();
  }

  // 이전 버튼 상태 업데이트
  buttonLast = buttonNow;
  */
}
