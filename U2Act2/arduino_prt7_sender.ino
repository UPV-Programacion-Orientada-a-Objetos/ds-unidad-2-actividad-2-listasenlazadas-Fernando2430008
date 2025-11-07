// Ejemplo de emisor PRT-7 en Arduino (real)
// Envía una línea por segundo con el formato esperado por el decodificador C++

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  delay(1000);
}

void loop() {
  const char* frames[] = {
    "L,H",
    "L,O",
    "L,L",
    "M,2",
    "L,A",
    "L,Space",
    "L,W",
    "M,-2",
    "L,O",
    "L,R",
    "L,L",
    "L,D"
  };
  for (unsigned i = 0; i < sizeof(frames)/sizeof(frames[0]); ++i) {
    Serial.println(frames[i]);
    delay(1000);
  }
  // Detenerse
  while (true) { delay(1000); }
}
