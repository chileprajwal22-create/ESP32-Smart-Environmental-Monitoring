
#include <DHT.h>

// Hardware configuration
#define DHTPIN 4
#define DHTTYPE DHT22
#define LED_PIN 2

DHT dht(DHTPIN, DHTTYPE);

// Timing configuration
const unsigned long SENSOR_INTERVAL_MS = 2000;
const float TEMP_THRESHOLD_C = 30.0f;

unsigned long previousSensorMillis = 0;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  Serial.println("ESP32 Environmental Monitor");
  Serial.println("Debug mode started");
}

void loop() {
  const unsigned long currentMillis = millis();

  // Read the sensor at fixed intervals without blocking delay()
  if (currentMillis - previousSensorMillis >= SENSOR_INTERVAL_MS) {
    previousSensorMillis = currentMillis;

    const float temperature = dht.readTemperature();
    const float humidity = dht.readHumidity();

    // Detect invalid sensor readings before using the values
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("[ERROR] DHT22 reading failed");
      digitalWrite(LED_PIN, LOW);
      return;
    }

    // Print validated readings for debugging
    Serial.print("[OK] Temperature: ");
    Serial.print(temperature, 1);
    Serial.print(" C | Humidity: ");
    Serial.print(humidity, 1);
    Serial.println(" %");

    // Update the alert output
    const bool highTemperature =
        temperature >= TEMP_THRESHOLD_C;

    digitalWrite(LED_PIN, highTemperature ? HIGH : LOW);

    Serial.print("[DEBUG] LED alert: ");
    Serial.println(highTemperature ? "ON" : "OFF");
  }
}

    Serial.println("------------------------------");
  }
}
