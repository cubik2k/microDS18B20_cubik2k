[![latest](https://img.shields.io/github/v/release/GyverLibs/microDS18B20.svg?color=brightgreen)](https://github.com/GyverLibs/microDS18B20/releases/latest/download/microDS18B20.zip)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/microDS18B20?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# microDS18B20
Легкая библиотека для работы с 1-Wire (OneWire) термометрами Dallas DS18B20
- Работа с несколькими датчиками на одном пине (режим адресации)
- Хранение массива адресов в PROGMEM памяти
- Работа с одним датчиком на пине (без использования адресации)
- Расчет температуры в целых числах и с плавающей точкой
- Чтение сырых данных для случаев сильной экономии памяти
- Проверка корректности полученной температуры
- Настраиваемое разрешение преобразования
- Проверка подлинности данных
- Проверка корректности работы датчика

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)
- Не работает на Digispark, какой то конфликт с компилятором. Используй ядро [ATTInyCore Universal](https://github.com/SpenceKonde/ATTinyCore) с настройкой ATtiny85 + Micronucleous (Digispark) вместо стандартного Digi-ядра

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Подключение](#wiring)
- [Примеры](#examples)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **microDS18B20** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/microDS18B20/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="init"></a>
## Инициализация
```cpp
// один датчик на пине без адресации
MicroDS18B20<uint8_t pin> ds;

// несколько датчиков на пине с адресацией, указываем адрес (адрес - массив uint8_t)
MicroDS18B20<uint8_t pin, uint8_t *address> ds;

// указываем, что будем работать с адресацией. Сам адрес передадим позже (в setAddress())
MicroDS18B20<uint8_t pin, DS_ADDR_MODE>;

// указываем, что будем работать с адресацией, и на линии будет несколько (amount) датчиков
// см. пример async_read_many_bus
MicroDS18B20<uint8_t pin, DS_ADDR_MODE, uint8_t amount>;

// указываем, что будем работать с адресацией, на линии будет несколько (amount) датчиков, а адреса будем хранить в PROGMEM
// см. пример async_read_many_bus_pgm
MicroDS18B20<uint8_t pin, DS_ADDR_MODE, uint8_t amount, DS_PROGMEM>;
```

<a id="usage"></a>
## Использование
```cpp
// ============= МЕТОДЫ КЛАССА =============
bool readAddress(uint8_t *addressArray);    // Прочитать уникальный адрес термометра в массив. [true, если успешно]
void setAddress(uint8_t *addr);             // установить (сменить) адрес
void setResolution(uint8_t resolution);     // Установить разрешение 9-12 бит
bool online();                              // проверить связь с датчиком (true - датчик онлайн). Шина должна быть подтянута

void requestTemp();                         // Запросить новое преобразование температуры
bool readTemp();                            // прочитать температуру с датчика. [true если успешно]

float getTemp();                            // получить значение температуры в float
int16_t getTempInt();                       // получить значение температуры в int
int16_t getRaw();                           // получить "сырое" значение температуры (в 16 раз больше, чем реальная температура)

// ======= МЕТОДЫ ДЛЯ ШИНЫ ДАТЧИКОВ =======
// см. примеры async_read_many_bus и async_read_many_bus_pgm
void setResolutionAll(uint8_t res);                     // Установить разрешение 9-12 бит у всех датчиков на линии
void setResolution(uint8_t resolution, uint8_t idx);    // Установить разрешение 9-12 бит (датчик под номером idx)
bool online(uint8_t idx);                               // проверить связь (датчик под номером idx)
uint8_t getResolution(uint8_t idx = 0)                  // прочитать разрешение датчикa (датчик под номером idx)
void getResolutionAll()                                 // прочитать разрешение у всех датчиков на линии

void requestTempAll();                                  // запрос температуры у всех датчиков на линии
void requestTemp(uint8_t idx);                          // Запросить новое преобразование температуры (датчик под номером idx)
bool readTemp(uint8_t idx);                             // прочитать температуру с датчика (датчик под номером idx)

float getTemp(uint8_t idx);                             // получить значение температуры в float (датчик под номером idx)
int16_t getTempInt(uint8_t idx);                        // получить значение температуры в int (датчик под номером idx)
int16_t getRaw(uint8_t idx);                            // получить "сырое" значение температуры (датчик под номером idx)

// =========== ФУНКЦИИ ВНЕ КЛАССА ===========
int DS_rawToInt(int data);                  // преобразовать raw данные в температуру int
float DS_rawToFloat(int data);              // преобразовать raw данные в температуру float

// ============ ДЕФАЙНЫ НАСТРОЕК ============
// прописывать перед подключением библиотеки
#define DS_CHECK_CRC [true / false]         // Проверка подлинности данных. При отключении будет выдавать некорректное значение при сбое передачи (умолч. true)
#define DS_CRC_USE_TABLE [true / false]     // Использовать таблицу для CRC. Быстрее, но +256 байт flash (<1мкс VS ~6мкс) (умолч. false)

// ================== ИНФО ==================
// Время преобразования от точности
точность | время
12 бит   | 750 мс
11 бит   | 375 мс
10 бит   | 187 мс
9 бит    | 93 мс
```

### Работа с датчиком
#### Без адресации
В этом режиме на один пин МК подключается один датчик, для работы с ним не требуется предварительного чтения адреса и записи его в программу. 
Можно подключить несколько датчиков, каждому указать свой пин, см. пример *one_pin_one_sensor*.
```cpp
MicroDS18B20<пин1> sensor1;
MicroDS18B20<пин2> sensor2;
// ... и так далее
```

#### С адресацией
В этом режиме можно подключить сколько угодно датчиков на один пин МК, но для работы с ними понадобится занести в программу уникальные адреса датчиков. 
В момент чтения адреса к пину должен быть подключен только один датчик! Пример - *address_read*.  
Для дальнейшей работы адреса хранятся в массивах на стороне программы и передаются датчикам при инициализации, пин указывается один и тот же:
```cpp
uint8_t addr1[] = {0x28, 0xFF, 0xCD, 0x59, 0x51, 0x17, 0x4, 0xFE};
uint8_t addr2[] = {0x28, 0xFF, 0x36, 0x94, 0x65, 0x15, 0x2, 0x80};

MicroDS18B20<пин, addr1> sensor1;
MicroDS18B20<пин, addr2> sensor2;
// ... и так далее
```
Также адрес можно сменить во время работы программы, см. документацию выше.

#### Чтение температуры
Чтение температуры делится на два этапа - запрос и получение данных. Запрос делается функцией `requestTemp()`. После получения запроса 
датчик начинает измерение температуры, которое длится от 90 до 750 мс в зависимости от настроенной точности *(по умолчанию точность максимальная, 
преобразование длится 750 мс)*. Если прочитать температуру до окончания преобразования - датчик вернёт результат предыдущего измерения, 
поэтому в примерах используется задержка или опрос по таймеру на 1 секунду. Получить температуру можно при помощи `getTemp()` [float] или `getTempInt()` [int]. 
Если принятые данные повреждены или датчик отсутствует на линии - функция вернёт предыдущее успешно прочитанное значение температуры.  
**Примечание:** при повторных вызовах `getTemp()` не запрашивает с датчика новую температуру (долгое выполнение функции), 
вместо этого она просто возвращает предыдущий результат до тех пор, пока не будет сделан новый запрос `requestTemp()`.  

В версии библиотеки 3.5 появилась возможность отдельно запросить температуру и определить корректность полученных данных, чтобы только после этого их прочитать 
и применить в программе - функция `readTemp()`. Также это позволяет определить состояние подключения и всё ли в порядке с датчиком. 
Для чтения температуры рекомендуется использовать конструкцию вида:
```cpp
if (sensor.readTemp()) value = sensor.getTemp();
// else отработка ошибки
```
где `readTemp()` запрашивает данные с датчика и возвращает `true`, если они прочитаны корректно. После этого можно забрать текущую температуру из `getTemp()`, 
которая уже не запрашивает температуру с датчика, а отдаёт прочитанный в `readTemp()` результат.

#### Подключаем много датчиков на один объект
В версии библиотеки 3.9 появилась возможность подключить сколько угодно датчиков на один объект MicroDS18B20, не создавая массива объектов (как в старых версиях). 
Нужно создать двумерный массив адресов и передать его в библиотеку, также указав количество датчиков на линии (можно максимальное, если оно будет меняться в процессе работы программы). 
Это позволяет сэкономить немного памяти, но можно пойти дальше - засунуть массив адресов датчиков в PROGMEM, чтобы они не висели в оперативной памяти.  
Инициализация в этом случае выглядит так: `MicroDS18B20<пин, DS_ADDR_MODE, колич-во>;` или `MicroDS18B20<пин, DS_ADDR_MODE, колич-во, DS_PROGMEM>;` для PROGMEM режима.  
Адреса передаются в `setAddress()`, а для опроса просто передаём индекс датчика в те же функции что и раньше. Смотри примеры *async_read_many_bus*, *async_read_many_bus_pgm* и раздел документации *МЕТОДЫ ДЛЯ ШИНЫ ДАТЧИКОВ*.

<a id="wiring"></a>
## Подключение
![scheme](/doc/scheme.png)
P.S. Вместо резистора на 4.7к можно использовать параллельно два по 10к =)

<a id="examples"></a>
Остальные примеры смотри в **examples**!
## Один датчик без адресации
```cpp
// один датчик лучше читать без адресации, это сильно экономит память
#include <microDS18B20.h>
MicroDS18B20<2> sensor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // запрос температуры  
  sensor.requestTemp();
  
  // вместо delay используй таймер на millis(), пример async_read
  delay(1000);
  
  // проверяем успешность чтения и выводим
  if (sensor.readTemp()) Serial.println(sensor.getTemp());
  else Serial.println("error");
}
```

## Несколько датчиков без адресации
```cpp
// 2 и более датчиков НЕВЫГОДНО использовать в таком режиме! Но можно

#include <microDS18B20.h>
// Датчики на D2 и D3
MicroDS18B20<2> sensor1;
MicroDS18B20<3> sensor2;

void setup() {
  Serial.begin(9600);
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
```

## Чтение адреса
```cpp
#include <microDS18B20.h>

// на пин подключен только один датчик!
MicroDS18B20 <2> sensor;  // Создаем термометр без адреса на пине D2
uint8_t address[8];       // Создаем массив для адреса

void setup() {
  Serial.begin(9600);
}

void loop() {
  // читаем адрес термометра в указанный массив
  if (sensor.readAddress(address)) {  // если успешно, выводим
    Serial.print('{');
    for (uint8_t i = 0; i < 8; i++) {
      Serial.print("0x");
      Serial.print(address[i], HEX);  // Выводим адрес
      if (i < 7) Serial.print(", ");
    }
    Serial.println('}');

  } else Serial.println("Not connected");
  delay(1000);
}
```

## Несколько датчиков с адресацией
```cpp
// 2 и более датчиков выгоднее использовать с адресацией на одном пине
#include <microDS18B20.h>
#define DS_PIN 2 // пин для термометров

// Уникальные адреса датчиков - считать можно в примере address_read
uint8_t s1_addr[] = {0x28, 0xFF, 0xCD, 0x59, 0x51, 0x17, 0x4, 0xFE};
uint8_t s2_addr[] = {0x28, 0xFF, 0x36, 0x94, 0x65, 0x15, 0x2, 0x80};

MicroDS18B20<DS_PIN, s1_addr> sensor1;  // Создаем термометр с адресацией
MicroDS18B20<DS_PIN, s2_addr> sensor2;  // Создаем термометр с адресацией

void setup() {
  Serial.begin(9600);
}

void loop() {
  // асинхронное чтение нескольких датчиков смотри в примере async_read_many
  sensor1.requestTemp();      // Запрашиваем преобразование температуры
  sensor2.requestTemp();

  delay(1000);          // ожидаем результат 
  
  Serial.print("t1: ");
  if (sensor1.readTemp()) Serial.println(sensor1.getTemp());
  else Serial.println("error");

  Serial.print("t2: ");
  if (sensor2.readTemp()) Serial.println(sensor2.getTemp());
  else Serial.println("error");
}
```

## Асинхронный опрос пачки датчиков
```cpp
// пример компактного асинхронного опроса датчиков на программном таймере
// https://alexgyver.ru/lessons/time/

// количество датчиков для удобства
#define DS_SENSOR_AMOUNT 5

// создаём двухмерный массив с адресами
uint8_t addr[][8] = {
  {0x28, 0xFF, 0x78, 0x5B, 0x50, 0x17, 0x4, 0xCF},
  {0x28, 0xFF, 0x99, 0x80, 0x50, 0x17, 0x4, 0x4D},
  {0x28, 0xFF, 0x53, 0xE5, 0x50, 0x17, 0x4, 0xC3},
  {0x28, 0xFF, 0x42, 0x5A, 0x51, 0x17, 0x4, 0xD2},
  {0x28, 0xFF, 0xCD, 0x59, 0x51, 0x17, 0x4, 0xFE},
};

#include <microDS18B20.h>
// указываем DS_ADDR_MODE для подключения блока адресации
// и создаём массив датчиков на пине D2
MicroDS18B20<2, DS_ADDR_MODE> sensor[DS_SENSOR_AMOUNT];

void setup() {
  Serial.begin(9600);
  // устанавливаем адреса
  for (int i = 0; i < DS_SENSOR_AMOUNT; i++) {
    sensor[i].setAddress(addr[i]);
  }
}

void loop() {
  // конструкция программного таймера на 1c
  static uint32_t tmr;
  if (millis() - tmr >= 1000) {
    tmr = millis();

    // выводим показания в порт
    for (int i = 0; i < DS_SENSOR_AMOUNT; i++) {
      Serial.print(sensor[i].getTemp());
      Serial.print(',');
    }
    Serial.println();

    // запрашиваем новые
    for (int i = 0; i < DS_SENSOR_AMOUNT; i++) {
      sensor[i].requestTemp();
    }
  }
}
```

## Чтение разрешенa датчикa
```cpp
#include <microDS18B20.h>

// на пин подключен только один датчик!
MicroDS18B20 <2> sensor;  // Создаем термометр без адреса на пине 2

void setup() {
  Serial.begin(9600);
  uint8_t res = sensor.getResolution();  // Чтение разрешенa датчикa
  Serial.print("Resolution: ");
  Serial.println(res);  
}

void loop() {
}
```

<a id="versions"></a>
## Версии
- v3.0 - Библиотека переехала на шаблон! Старые примеры НЕСОВМЕСТИМЫ. Оптимизация, новые трюки.
- v3.0.1 - добавлен пример
- v3.1 - добавлена возможность смены адреса на лету
- v3.1.1 - microOneWire разбит на .h и .cpp
- v3.2 - исправлены отрицательные температуры
- v3.3 - разбил на файлы
- v3.4 - добавлена проверка онлайна датчика и буфер, при ошибке чтения возвращается последнее прочитанное значение
- v3.5 - оптимизация, повышение стабильности, проверка правильности чтения, online() работает с адресацией, добавлен метод getTempInt() и readTemp(), упразднён DS_TEMP_TYPE
- v3.6 - исправлена ошибка компиляции, добавлена поддержка GyverCore (спасибо ArtemiyKolobov)
- v3.7 - исправлена ошибка readTemp() при 0 градусов
- v3.8 - небольшая оптимизация. Совместимость с ESP32
- v3.9 - добавил расширенный режим адресации и хранение адресов в PROGMEM
- v3.10 - оптимизация, увеличена стабильность
- v3.10.1 - added getResolution()

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
