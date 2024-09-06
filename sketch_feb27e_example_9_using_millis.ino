// Class to handle a non-blocking blinking LED connected to a specific pin of a port
class Blinky {
  private:
    unsigned char *port;       // Pointer to the port (address)
    unsigned int pin;          // Pin number on the port
    int OFF;                   // OFF time duration (ms)
    int ON;                    // ON time duration (ms)
    unsigned char *port_Dir;   // Pointer to the port direction register (DDR)
    unsigned long previousTime; // Stores the last time the LED state changed

  public:
    // Constructor: Initializes the port, pin, and ON/OFF times
    Blinky(unsigned char* port_number, unsigned int pin_Number, int ON_time, int OFF_time) {
      ON = ON_time;           // Set the ON time
      OFF = OFF_time;         // Set the OFF time
      port = port_number;     // Set the port address
      pin = pin_Number;       // Set the pin number

      // Determine the corresponding DDR (Data Direction Register) based on the port address
      if (port == (unsigned char*)0x25) {
        port_Dir = (unsigned char*)0x24;  // DDR for port 0x25
      } else if (port == (unsigned char*)0x28) {
        port_Dir = (unsigned char*)0x27;  // DDR for port 0x28
      } else {
        port_Dir = (unsigned char*)0x2A;  // Default DDR for other ports
      }

      // Set the entire port direction to output (0xFF)
      *port_Dir = 0xFF;
      
      previousTime = 0;  // Initialize previous time to 0
    }

    // Blink function: Turns the LED on and off using a non-blocking approach
    void Blink() {
      unsigned long currentTime = millis();  // Get the current time

      // Check if the LED is currently off
      if (((*port) & (1 << pin)) == 0) {
        // If enough time has passed, turn the LED on
        if (currentTime - previousTime >= OFF) {
          *port = (*port) | (1 << pin);  // Set the pin HIGH (turn on the LED)
          previousTime = currentTime;    // Update the previous time
        }
      } else {
        // If the LED is on, check if enough time has passed to turn it off
        if (currentTime - previousTime >= ON) {
          *port = (*port) & ~(1 << pin);  // Set the pin LOW (turn off the LED)
          previousTime = currentTime;     // Update the previous time
        }
      }
    }
};

// Example 9: Instantiating multiple Blinky objects for different pins on the same port
Blinky led1((unsigned char*)0x25, 0, 781, 515);  // LED on pin 0 of port 0x25
Blinky led2((unsigned char*)0x25, 1, 2014, 1348); // LED on pin 1 of port 0x25
Blinky led3((unsigned char*)0x25, 2, 343, 1348);  // LED on pin 2 of port 0x25
Blinky led4((unsigned char*)0x25, 3, 678, 1839);  // LED on pin 3 of port 0x25
Blinky led5((unsigned char*)0x25, 4, 342, 534);   // LED on pin 4 of port 0x25
Blinky led6((unsigned char*)0x25, 5, 1478, 326);  // LED on pin 5 of port 0x25
Blinky led7((unsigned char*)0x25, 6, 1859, 351);  // LED on pin 6 of port 0x25
Blinky led8((unsigned char*)0x25, 7, 777, 888);   // LED on pin 7 of port 0x25

// Setup function (currently empty, but can be used for initialization)
void setup() {
  // No setup needed in this case
}

// Main loop: Continuously blink all LEDs using the non-blocking approach
void loop() {
  led1.Blink();  // Blink LED1
  led2.Blink();  // Blink LED2
  led3.Blink();  // Blink LED3
  led4.Blink();  // Blink LED4
  led5.Blink();  // Blink LED5
  led6.Blink();  // Blink LED6
  led7.Blink();  // Blink LED7
  led8.Blink();  // Blink LED8
}
