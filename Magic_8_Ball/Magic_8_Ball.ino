// Dane Bik
// Magic 8 Ball
// TEC 284

// Include libraries for communication over I2C, 3-Axis accelerator, and OLED display
#include "LIS3DHTR.h"
#include <U8g2lib.h>
#include <Wire.h>

// Declare object for 3-Axis accelerator
LIS3DHTR<TwoWire> lis;

// Declare object for OLED display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R2, // Rotates text to line up with other text on the board
  SCL,
  SDA,
  U8X8_PIN_NONE
);

// Create an array listing the answers that the 8 Ball/screen will display when shaken
const char* answers[] = {"Yes", "No", "Ask again", "Probably", "Unclear", "Doubtful", "Absolutely", "Not sure", "Try later"};

// Store the number of answers into an int variable
int a = sizeof(answers) / sizeof(answers[0]);

void setup() {
  // Start I2C communication and OLED display
  Wire.begin();
  u8g2.begin();

// Start accelerator
  lis.begin(Wire, 0x19);
  lis.setOutputDataRate(LIS3DHTR_DATARATE_50HZ); // Reads the sensor
  lis.setFullScaleRange(LIS3DHTR_RANGE_2G); // Sensitivity

  // Display a startup message to signal that the 8 Ball is working and ready to be used
  u8g2.firstPage();	
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr); // Font selected
    u8g2.drawStr(0,35,"Shake me!");	// Message displayed
  }	while (u8g2.nextPage());

  // Delay to let user see the first message before it is shaken
  delay(1500);  
}

void loop() {
  // Get the acceleration of the X, Y, and Z axis
  float x = lis.getAccelerationX();
  float y = lis.getAccelerationY();
  float z = lis.getAccelerationZ();

  // Calculate the strength of the motion in a float variable
  float motion = sqrt(x*x + y*y + z*z);

  // Check if the Arduino was shaken at all
  if(motion > 1.5) {
    int rand = random(a); // Picks a random answer from the array

    // Display an answer given from shaking the device
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_ncenB08_tr);	// Font selected
      u8g2.drawStr(0,35, answers[rand]); // Random answer displayed
    } while (u8g2.nextPage());

    // Delay to let user see answer given by 8 Ball
    delay(1500);
  }
}
