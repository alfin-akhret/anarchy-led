// SETTING PIN
int cl = 13; // clock
int ds = 11; // serial
int la = 8; // latch

void setup() {
  // put your setup code here, to run once:
  pinMode(ds, OUTPUT);
  pinMode(cl, OUTPUT);
  pinMode(la, OUTPUT);
}

int seq[8] = {1,2,4,8,16,32,64,128};

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(la, LOW);
  shiftOut(ds, cl, MSBFIRST, seq[0]); 
  digitalWrite(la, HIGH);

  digitalWrite(la, LOW);
  shiftOut(ds, cl, MSBFIRST, seq[1]); 
  digitalWrite(la, HIGH);

}
