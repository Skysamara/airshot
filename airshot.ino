// Работает
// Выводит микросекунды
// https://alexgyver.ru/lessons/pointers/ - Указатели. Переписать


const int pinLL = D5;
const int pinLH = D6;
const int pinRL = D7;
const int pinRH = D8; // на плате - D3



//volatile boolean isTimeOn = false;
volatile boolean isShotInProgress = false;
volatile unsigned long timeShot = 0;
volatile unsigned long maxTimeShot = 500000; //1000 микросекунд

volatile unsigned long tickLL = 0;
volatile unsigned long tickLH = 0;
volatile unsigned long tickRL = 0;
volatile unsigned long tickRH = 0;

volatile boolean isComletedLL = false;
volatile boolean isComletedLH = false;
volatile boolean isComletedRL = false;
volatile boolean isComletedRH = false;


void setup() {
  Serial.begin(9600);
  //  pinMode(LED_BUILTIN, OUTPUT);

  // pinmode
  pinMode(pinLL, INPUT_PULLUP);
  pinMode(pinLH, INPUT_PULLUP);
  pinMode(pinRL, INPUT_PULLUP);
  pinMode(pinRH, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinLL), shotLL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinLH), shotLH, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinRL), shotRL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinRH), shotRH, CHANGE);

  timeShot = micros();
  printResult();
}

void loop() {
  if (isShotInProgress) {
    if ((micros() - timeShot) > maxTimeShot) { // Время истекло
      isShotInProgress = false;
      printResult();
      resetPins();
    }
  }
}

void printResult() {
  Serial.print("tickLL - ");
  Serial.println(tickLL);

  Serial.print("tickLH - ");
  Serial.println(tickLH);

  Serial.print("tickRL - ");
  Serial.println(tickRL);

  Serial.print("tickRH - ");
  Serial.println(tickRH);

  Serial.println(micros());
  Serial.println("---------------");
}

// ICACHE_RAM_ATTR void https://randomnerdtutorials.com/interrupts-timers-esp8266-arduino-ide-nodemcu/
//IRAM_ATTR void shotLH() {


ICACHE_RAM_ATTR void shotLL() {
  if (!isShotInProgress) {
    isShotInProgress = true;  // Сработал первый датчик, считаем время
    timeShot = micros();
  }

  if (!isComletedLL) {  // Если это первая волна, запоминаем время
    tickLL = micros();
    isComletedLL = true;
  }
}

ICACHE_RAM_ATTR void shotLH() {
  if (!isShotInProgress) {
    isShotInProgress = true;  // Сработал первый датчик, считаем время
    timeShot = micros();
  }

  if (!isComletedLH) {  // Если это первая волна, запоминаем время
    tickLH = micros();
    isComletedLH = true;
  }
}

ICACHE_RAM_ATTR void shotRL() {
  if (!isShotInProgress) {
    isShotInProgress = true;  // Сработал первый датчик, считаем время
    timeShot = micros();
  }

  if (!isComletedRL) {  // Если это первая волна, запоминаем время
    tickRL = micros();
    isComletedRL = true;
  }
}

ICACHE_RAM_ATTR void shotRH() {
  if (!isShotInProgress) {
    isShotInProgress = true;  // Сработал первый датчик, считаем время
    timeShot = micros();
  }

  if (!isComletedRH) {  // Если это первая волна, запоминаем время
    tickRH = micros();
    isComletedRH = true;
  }
}

void resetPins() {
  isComletedLL = false;
  isComletedLH = false;
  isComletedRL = false;
  isComletedRH = false;

  tickLL = 0;
  tickLH = 0;
  tickRL = 0;
  tickRH = 0;
}
