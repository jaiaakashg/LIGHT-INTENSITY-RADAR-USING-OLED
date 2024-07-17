#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LDR_PIN 34 

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }
  
  display.display();
  delay(2000);
  display.clearDisplay();

  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  int barWidth = map(ldrValue, 0, 4095, 0, SCREEN_WIDTH - 20);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("LDR Value: ");
  display.print(ldrValue);
  
  display.drawRect(10, 20, SCREEN_WIDTH - 20, 20, SSD1306_WHITE);
  display.fillRect(10, 20, barWidth, 20, SSD1306_WHITE);

  display.display();

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  delay(500);
}

