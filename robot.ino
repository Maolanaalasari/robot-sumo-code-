// Pin Ultrasonic
const int trigPin = 2;
const int echoPin = 4;

// Pin Sensor Warna (Analog Input)
const int colorSensorPin = 3;

// Pin Motor Driver (L298N)
const int motor1Pin1 = 7; // IN1
const int motor1Pin2 = 8; // IN2
const int motor2Pin1 = 9; // IN3
const int motor2Pin2 = 10; // IN4

// Variabel
long duration;
float distance;
int colorValue;

void setup() {
  // Inisialisasi serial monitor
  Serial.begin(9600);

  // Konfigurasi pin ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Konfigurasi pin motor driver
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Awal motor dimatikan
  stopMotors();
}

void loop() {
  // Mengukur jarak dengan sensor ultrasonik
  distance = readUltrasonic();
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Membaca nilai sensor warna
  colorValue = analogRead(colorSensorPin);
  Serial.print("Nilai Warna: ");
  Serial.println(colorValue);

  // Logika Perilaku Robot
  if (distance < 10) { 
    // Jika jarak kurang dari 10 cm, dorong lawan
    Serial.println("Lawan terdeteksi, mendorong lawan.");
    moveForwardFast();
  } else if (colorValue < 500) { 
    // Jika permukaan hitam, berjalan cepat
    Serial.println("Permukaan: Hitam, bergerak cepat.");
    moveForwardFast();
  } else { 
    // Jika permukaan putih, berhenti
    Serial.println("Permukaan: Putih, berhenti.");
    stopMotors();
  }

  delay(100); // Delay untuk pembaruan data
}

// Fungsi membaca sensor ultrasonik
float readUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  float distanceCm = duration * 0.034 / 2; // Menghitung jarak dalam cm
  return distanceCm;
}

// Fungsi menggerakkan motor maju dengan kecepatan tinggi
void moveForwardFast() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Fungsi menghentikan motor
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
