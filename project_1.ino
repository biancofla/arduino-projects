#include <SPI.h>
#include <SD.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

size_t DISPLAY_COLUMNS = 16;
size_t DISPLAY_ROWS    = 2;

LiquidCrystal_I2C lcd(0x3f, DISPLAY_COLUMNS, DISPLAY_ROWS);

File myFile;
int *fileContent = NULL;
int size = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  lcd.init();
  lcd.backlight();

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("test.txt", FILE_READ);
  if (myFile) {
    while (myFile.available()) {
      size += 1;
      fileContent = (int*) realloc(fileContent, size * sizeof(int));
      fileContent[size - 1] = myFile.read();
    }
    myFile.close();
  }

  lcd.setCursor(0, 0);
  for (size_t i = 0; i < size - 2; i++) {
    char c = char(fileContent[i]);
    lcd.print(c);
  }

  free(fileContent);
}

void loop() {
  lcd.scrollDisplayLeft();
  delay(500);
}
