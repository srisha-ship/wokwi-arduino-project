
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

// Servo motor
Servo myServo;

// Pin definitions
const int button1Pin = 2;
const int button2Pin = 3;
const int redLedPin = 6;
const int greenLedPin = 7;
const int buzzerPin = 8;
const int servoPin = 9;

// Function to display a message on OLED
void showMessage(const char *line1, const char *line2) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    display.println(line1);
    display.setCursor(0, 35);
    display.println(line2);
    display.display();
}

void setup() {
    // Configure buttons
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);

    // Configure outputs
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

    // Initialize outputs
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(buzzerPin, LOW);

    // Initialize servo
    myServo.attach(servoPin);
    myServo.write(0);

    // Initialize OLED
    if (!display.begin(
            SSD1306_SWITCHCAPVCC,
            0x3C
        )) {
        for (;;) {
            // Stop if OLED initialization fails
        }
    }

    showMessage("System Initialized", "Ready for input");
    delay(1500);
}

void loop() {
    // Button 1: Access granted
    if (digitalRead(button1Pin) == LOW) {
        digitalWrite(greenLedPin, HIGH);
        digitalWrite(redLedPin, LOW);

        showMessage("ACCESS GRANTED", "Welcome!");

        myServo.write(90);

        tone(buzzerPin, 1000, 200);

        delay(200);

        // Wait until button is released
        while (digitalRead(button1Pin) == LOW) {
            delay(10);
        }

        delay(2000);

        // Return to locked state
        myServo.write(0);
        digitalWrite(greenLedPin, LOW);

        showMessage("System Ready", "Waiting for input");
    }

    // Button 2: Access denied
    if (digitalRead(button2Pin) == LOW) {
        digitalWrite(redLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);

        showMessage("ACCESS DENIED", "Try again!");

        myServo.write(0);

        tone(buzzerPin, 500, 200);
        delay(300);
        tone(buzzerPin, 500, 200);

        delay(200);

        // Wait until button is released
        while (digitalRead(button2Pin) == LOW) {
            delay(10);
        }

        delay(1500);

        digitalWrite(redLedPin, LOW);

        showMessage("System Ready", "Waiting for input");
    }

    delay(20);
}

