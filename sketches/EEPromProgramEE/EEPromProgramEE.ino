#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_LATCH 4
#define EEPROM_D0 5
#define EEPROM_D7 12
#define WRITE_EN 13

void setAddress(int address, bool outputEnable) {
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (address >> 8 ) | (outputEnable ? 0x00 : 0x80));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);

  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}

byte readEEPROM(int address) {
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    pinMode(pin, INPUT);
  }

    setAddress(address, /*outputEnable*/ true);
    byte data = 0;
    for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin -= 1) {
      data = (data << 1) + digitalRead(pin);
    }
    return data;
  }

void writeEEPROM(int address, byte data) {
    for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
      pinMode(pin, OUTPUT);
    }

    setAddress(address, /*outputEnable*/ false);
    for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
      digitalWrite(pin, data & 1);
      data = data >> 1;
    }
    digitalWrite(WRITE_EN, LOW);
    delayMicroseconds(1);
    digitalWrite(WRITE_EN, HIGH);
    delay(10);
  }

  void printContents() {
    for (int base = 0; base <= 255; base += 16) {
      byte data[16];
      for (int offset = 0; offset <= 15; offset += 1) {
        data[offset] = readEEPROM(base + offset);
      }
  
      char buf[80];
      sprintf(buf, "%03x: %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
        base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7],
        data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
  
      Serial.println(buf);
    }  
  }

  void setup() {

    // put your setup code here, to run once:
    pinMode(SHIFT_DATA, OUTPUT);
    pinMode(SHIFT_CLK, OUTPUT);
    pinMode(SHIFT_LATCH, OUTPUT);
    digitalWrite(WRITE_EN, HIGH);
    pinMode(WRITE_EN, OUTPUT);
    Serial.begin(57600);

    for (int address = 0; address <= 255; address += 1) {
      writeEEPROM(address, 0x00);
    }
    printContents();
    
  }
  void loop() {
    // put your main code here, to run repeatedly:

  }
