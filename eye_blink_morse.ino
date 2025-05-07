// Morse Code Translator using Eye Blinks with Arduino

const int blinkSensorPin = 2;  // Digital input from Eye Blink sensor
const int ledPin = 13;         // LED for feedback (optional)

unsigned long blinkStart = 0;
unsigned long blinkDuration = 0;
bool blinkActive = false;

void setup() {
  pinMode(blinkSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Morse Code Translator Initialized");
}

void loop() {
  int sensorValue = digitalRead(blinkSensorPin);

  if (sensorValue == LOW && !blinkActive) {
    // Blink started
    blinkActive = true;
    blinkStart = millis();
    digitalWrite(ledPin, HIGH);  // Visual feedback
  }

  if (sensorValue == HIGH && blinkActive) {
    // Blink ended
    blinkActive = false;
    blinkDuration = millis() - blinkStart;
    digitalWrite(ledPin, LOW);

    if (blinkDuration < 500) {
      Serial.print(".");
    } else {
      Serial.print("-");
    }
  }

  // Add delay between letters (optional, 2s gap for testing)
  static unsigned long lastBlinkTime = 0;
  if (!blinkActive && millis() - blinkStart > 2000 && blinkStart > 0) {
    Serial.print(" "); // Represents a space between letters
    blinkStart = 0;
  }
}
