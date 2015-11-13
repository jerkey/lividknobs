#define COL1 2 // JP1-1
#define COL2 3 // JP1-2
#define COL4 4 // JP1-3
#define COL8 5 // JP1-4
#define BR1  6 // JP1-9
#define BR2  7 // JP1-10
#define BR3  8 // JP1-11
#define BR4  9 // JP1-12
#define BR5 10 // JP1-13
#define BR6 11 // JP1-14
#define BR7 12 // JP1-15
#define BR8 13 // JP1-16

byte bits[16]; // stores the bit states
byte lastBits[16]; // stores the bit states

void setup() {
  Serial.begin(115200);
  Serial.println("livid knobs");
  pinMode(COL1, OUTPUT);
  pinMode(COL2, OUTPUT);
  pinMode(COL4, OUTPUT);
  pinMode(COL8, OUTPUT);
}

void loop() {
  pollBits();
  for (byte i = 0; i < 16; i++) {
    for (byte j = 0; j < 8; j++) {
      if ((lastBits[i] & (1 << j)) ^ bits[i] & (1 << j)) { // compare all the bits
        Serial.println("bit "+String(i*8+j));
      }
    }
    lastBits[i] = bits[i]; // store the new state now that we've compared
  }
}

void pollBits() {
  for (byte col = 0; col < 16; col++) {
    digitalWrite(COL1,col & 1);
    digitalWrite(COL2,col & 2);
    digitalWrite(COL4,col & 4);
    digitalWrite(COL8,col & 8);
    delay(5);
    for (byte row = 0; row < 8; row++) {
      bits[col]=0;
      if (digitalRead(BR1)) bits[col] += 1;
      if (digitalRead(BR2)) bits[col] += 2;
      if (digitalRead(BR3)) bits[col] += 4;
      if (digitalRead(BR4)) bits[col] += 8;
      if (digitalRead(BR5)) bits[col] += 16;
      if (digitalRead(BR6)) bits[col] += 32;
      if (digitalRead(BR7)) bits[col] += 64;
      if (digitalRead(BR8)) bits[col] += 128;
    }
  }
}
