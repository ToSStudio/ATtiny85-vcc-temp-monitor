// ATtiny85 measuring its own power supply and
// ambient temperature w/o external hardware
// it implements an exponential moving average algorithm
// with integer-math to display smooth output
// adjust the next two values until you get good results

// This holds the Temp-correction-coefficient
// common values: 300 - 318. The lower the value the higher the output
#define TEMP_REF 308      // Temp coefficient

// adjust ADC_REF. The higher the value the higher the output
#define ADC_REF 988       // 1.1V internal reference in mV

// ===============
#define VBG_CHANNEL  0x0E // Bandgap reference channel
#define TEMP_CHANNEL 0x0F // Temperature sensor channel

// ---------- EMA CONFIGURATION ----------
// The smoothing factor determines how "slow" the value reacts.
// Higher divisor = smoother but slower response.
// Common values: 4, 8, 16 (must be a power of 2 for efficiency)
const uint8_t EMA_DIVISOR = 8;  // Equivalent to alpha = 1/8

// This holds the ADC-values
int tempRaw, vbgRaw;

// This holds the filtered value (start at your first ADC read)
int filteredTempRaw, filteredVbgRaw;


void setup() {

  pinMode (4, OUTPUT);
  analogReference(INTERNAL);  // Use internal 1.1V reference
  Serial.begin(9600);

  Serial.print ("\nATTiny showing Vcc");
  Serial.print ("\nand Temp in °C");
  Serial.print ("\npriming the EMA .");

  // prime the values
  for (int i = 0; i < 40; i++)  {
    tempRaw = analogRead(TEMP_CHANNEL);
    vbgRaw  = analogRead(VBG_CHANNEL);
    // === EMA updates ===
    filteredTempRaw = (filteredTempRaw * (EMA_DIVISOR - 1) + tempRaw) / EMA_DIVISOR;
    filteredVbgRaw  = (filteredVbgRaw  * (EMA_DIVISOR - 1) + vbgRaw ) / EMA_DIVISOR;
    delay (80);
    if (!(i % 5)) Serial.print (".");
  }

  for (int i = 0; i < 3; i++)  {
    // Flash LED on Pin 4 thrice
    delay(85);
    digitalWrite (4, HIGH);
    delay(85);
    digitalWrite (4, LOW);
  }
  delay (300);

}

void loop() {

  // === Raw ADC readings ===
  tempRaw = analogRead(TEMP_CHANNEL);
  vbgRaw  = analogRead(VBG_CHANNEL);

  // === EMA updates ===
  filteredTempRaw = (filteredTempRaw * (EMA_DIVISOR - 1) + tempRaw) / EMA_DIVISOR;
  filteredVbgRaw  = (filteredVbgRaw  * (EMA_DIVISOR - 1) + vbgRaw ) / EMA_DIVISOR;

  float temperatureC = (filteredTempRaw - TEMP_REF) / 1.1 + 25;  // estimation
  float vcc = (ADC_REF * 1024.0) / filteredVbgRaw;  // in mV

  // === Output ===
  Serial.print("\nTemp: ");
  Serial.print(temperatureC, 1);
  Serial.print(" °C | Vcc: ");
  Serial.print(vcc / 1000.0, 3);
  Serial.print(" V");

  // Flash LED on Pin 4
  delay(1000);
  digitalWrite (4, HIGH);
  delay(85);
  digitalWrite (4, LOW);

}

