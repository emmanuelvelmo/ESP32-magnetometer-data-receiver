#include <Arduino.h>
#include <Wire.h>

#define HMC5883L_ADDR 0x1E  // Dirección I2C del HMC5883L

void setup() {
  Serial.begin(115200);  // Inicia la comunicación serial
  Wire.begin();          // Inicia la comunicación I2C

  // Configura el HMC5883L
  Wire.beginTransmission(HMC5883L_ADDR);
  Wire.write(0x02);  // Selecciona el registro de modo
  Wire.write(0x00);  // Modo de medición continua
  Wire.endTransmission();
}

void loop() {
  int x, y, z;

  // Lee los datos del magnetómetro
  Wire.beginTransmission(HMC5883L_ADDR);
  Wire.write(0x03);  // Selecciona el registro de datos
  Wire.endTransmission();

  Wire.requestFrom(HMC5883L_ADDR, 6);  // Solicita 6 bytes de datos (x, y, z)
  if (Wire.available() >= 6) {
    x = Wire.read() << 8 | Wire.read();  // Lee el valor de X
    z = Wire.read() << 8 | Wire.read();  // Lee el valor de Z
    y = Wire.read() << 8 | Wire.read();  // Lee el valor de Y
  }

  // Muestra los valores en el monitor serial
  Serial.print("X: "); Serial.print(x);
  Serial.print("  Y: "); Serial.print(y);
  Serial.print("  Z: "); Serial.println(z);

  delay(500);  // Espera 500 ms antes de la siguiente lectura
}