// Class to handle a blinking LED connected to a specific pin of a port
class Blinky {
  private:
    unsigned char *port;      // Pointer to the port (address)
    unsigned int pin;         // Pin number on the port
    int OFF;                  // OFF time duration (ms)
    int ON;                   // ON time duration (ms)
    unsigned char *port_Dir;  // Pointer to the port direction register
  
  public:
    // Constructor: Initializes the port, pin, and ON/OFF times
    Blinky(unsigned char* port_number, unsigned int pin_Number, int ON_time, int OFF_time) {
      ON = ON_time;          // Set the ON time
      OFF = OFF_time;        // Set the OFF time
      port = port_number;    // Set the port address
      pin = pin_Number;      // Set the pin number

      // Set the direction register (DDR) based on the port address
      if (port == (unsigned char*)0x25) {
        port_Dir = (unsigned char*)0x24;  // DDR for port 0x25
      } else if (port == (unsigned char*)0x28) {
        port_Dir = (unsigned char*)0x27;  // DDR for port 0x28
      } else {
        port_Dir = (unsigned char*)0x2A;  // Default DDR for other ports
      }

      // Set the entire port direction to output (0xFF)
      // You may want to only set the direction for the specific pin
      *port_Dir = 0xFF;
    }

    // Blink function: Turns the LED on and off with the specified ON/OFF times
    void Blink() {
      // Set the pin HIGH (turn on the LED)
      *port = (*port) | (1 << pin);
      delay(ON);  // Wait for the ON duration

      // Set the pin LOW (turn off the LED)
      *port = (*port) & ~(1 << pin);
      delay(OFF); // Wait for the OFF duration
    }
};

// Create two Blinky objects representing two LEDs connected to the same port but different pins
Blinky led1((unsigned char*)0x25, 0, 750, 350);  // LED on pin 0 of port 0x25
Blinky led2((unsigned char*)0x25, 1, 400, 600);  // LED on pin 1 of port 0x25

// Setup function (currently empty, but can be used for initialization)
void setup() {
  // No setup needed in this case
}

// Main loop: Continuously blink both LEDs
void loop() {
  led1.Blink();  // Blink LED1
  led2.Blink();  // Blink LED2
}
