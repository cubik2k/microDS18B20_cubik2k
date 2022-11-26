// пример работы с датчиками без адресации с getResolution()
// один датчик - один пин

#include <microDS18B20.h>
// Датчики на D2 и D3
MicroDS18B20<2> sensor1;
MicroDS18B20<3> sensor2;

void setup() {
  Serial.begin(9600);


  delay(100);
  Serial.println("");
  Serial.println("------------------------");

  sensor1.setResolution(9);  // set resolution for example

  uint8_t res1 = sensor1.getResolution();  // read resolution
  Serial.print("Resolution sensor1: ");
  Serial.println(res1);

  if (res1 < 12) {  // if resolution is lower than 12 then set 12
    sensor1.setResolution(12);

    res1 = sensor1.getResolution();  // check resolution

    Serial.print("New resolution for sensor1: ");
    Serial.println(res1);
  }

  Serial.println("------------------------");
  delay(1000);

}

void loop() {
  // запрос температуры
  sensor1.requestTemp();
  sensor2.requestTemp();

  // вместо delay используй таймер на millis(), пример async_read
  delay(1000);

  // ПЕРВЫЙ ДАТЧИК
  Serial.print("t1: ");

  // просто выводим температуру первого датчика
  Serial.print(sensor1.getTemp());

  // ВТОРОЙ ДАТЧИК
  Serial.print(", t2: ");

  // проверяем успешность чтения и выводим
  if (sensor2.readTemp()) Serial.println(sensor2.getTemp());
  else Serial.println("error");
}