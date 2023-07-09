#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_LATCH 4


void setup() {

  // put your setup code here, to run once:
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);

  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, 0xff);

}

void loop() {
  // put your main code here, to run repeatedly:

}
