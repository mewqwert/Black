int a = 2;


void test(int* x) {
  *x = *x+2;
}

void setup() {
  Serial.begin (115200);
}

void loop() {
  test(&a);
  Serial.println(a);
  delay(100);
}
