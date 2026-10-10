#include <DHT.h>

// Sensor and LED pin configuration
#define DHTPIN 4
#define DHTTYPE DHT22
#define LED_PIN 2

DHT dht(DHTPIN, DHTTYPE);

// Sensor reading interval
unsigned long previousSensorMillis = 0;
const unsigned long sensorInterval = 2000;

// Temperature alert threshold
const float TEMP_THRESHOLD = 30.0;

void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  dht.begin();

  Serial.println("Smart Environmental Monitoring System");
  Serial.println("-------------------------------------");
  Serial.println("Temperature alert threshold: 30 C");
}

void loop() {
  unsigned long currentMillis = millis();

  // Read sensor every 2 seconds
  if (currentMillis - previousSensorMillis >= sensorInterval) {
    previousSensorMillis = currentMillis;

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Check whether sensor readings are valid
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("ERROR: Sensor reading failed!");
      digitalWrite(LED_PIN, LOW);
      return;
    }

    // Display sensor readings
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Activate LED if temperature is too high
    if (temperature >= TEMP_THRESHOLD) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("ALERT: High temperature!");
    } else {
      digitalWrite(LED_PIN, LOW);
      Serial.println("Temperature normal.");
    }

    Serial.println("------------------------------");
  }
}
