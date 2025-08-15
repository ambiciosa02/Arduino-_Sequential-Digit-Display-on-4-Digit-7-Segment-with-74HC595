int latch = 4; // STCP (pin 12 du 74HC595)
int clock = 5; // SHCP (pin 11)
int data = 3;  // DS (pin 14)
int digitPins[] = {8, 9, 10, 11}; // Afficheurs de droite à gauche

// Table pour anode commune (valeurs inversées)
unsigned char table[] = {
  ~0xC0, // 0
  ~0xF9, // 1
  ~0xA4, // 2
  ~0xB0, // 3
  ~0x99, // 4
  ~0x92, // 5
  ~0x82, // 6
  ~0xF8, // 7
  ~0x80, // 8
  ~0x90  // 9
};

void setup() {
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW); // Éteindre tous les afficheurs au début
  }
}

void loop() {
  for (int chiffre = 0; chiffre <= 9; chiffre++) {
    for (int digit = 0; digit < 4; digit++) {
      afficherChiffre(chiffre, digit);
      delay(500); // Attendre un peu avant le suivant
    }
  }
}

void afficherChiffre(unsigned char chiffre, int afficheur) {
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, table[chiffre]);
  digitalWrite(latch, HIGH);

  // Éteindre tous les afficheurs
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], LOW);
  }

  // Allumer l’afficheur ciblé
  digitalWrite(digitPins[afficheur], HIGH);

  delay(5); // court affichage visible
  digitalWrite(digitPins[afficheur], LOW); // désactiver après
}
