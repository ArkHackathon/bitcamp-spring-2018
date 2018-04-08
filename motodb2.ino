const int analog0 = A3; // rpm
const int analog1 = A2; // coolant
const int analog2 = A1; // oil temp
const int analog3 = A0; // pedal pos
const int digital0 = 2; // veh power
const int digital1 = 3; // brake
const int digital2 = 4; // engine light
bool d0v = false;
bool d1v = false;
bool d2v = false;
bool d0w = false;
bool d1w = false;
bool d2w = false;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(digital0, INPUT);
pinMode(digital1, INPUT);
pinMode(digital2, INPUT);
}

bool checkButton(int pin,bool* was, bool* v){
  bool is = digitalRead(pin);
  if(!*was && is){
    *was = true;
    *v = !*v;
  }else if(!is && *was){
    *was = false;
  }

  return *v;  
}

void loop() {
  char a0s[9];
  char a1s[9];
  char a2s[9];
  char a3s[9];
  char d0s[9];
  char d1s[9];
  char d2s[9];
  sprintf(a0s,",a0,%04d",analogRead(analog0));
  sprintf(a1s,",a1,%04d",analogRead(analog1));
  sprintf(a2s,",a2,%04d",analogRead(analog2));
  sprintf(a3s,",a3,%04d",analogRead(analog3));
  sprintf(d0s,",d0,%04d",checkButton(digital0,&d0w,&d0v));
  sprintf(d1s,",d1,%04d",checkButton(digital1,&d1w,&d1v));
  sprintf(d2s,",d2,%04d",checkButton(digital2,&d2w,&d2v));
  char message[56];
  memcpy(message,a0s,8);
  memcpy(message+8,a1s,8);
  memcpy(message+8*2,a2s,8);
  memcpy(message+8*3,a3s,8);
  memcpy(message+8*4,d0s,8);
  memcpy(message+8*5,d1s,8);
  memcpy(message+8*6,d2s,8);
  //Serial.print("s");
  Serial.write(message,56);

  //Serial.print("e");
  
  delay(500);
}
