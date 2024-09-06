// Class to handle button functionality with debounce and optional pull-up configuration
class Button {

  private:
    unsigned char *port;             // Pointer to the port (address)
    unsigned int pin;                // Pin number on the port
    unsigned int debounce_period;    // Debounce time (in milliseconds)
    bool normally_high_low;          // Button type: normally high (1) or low (0)
    unsigned char *port_Dir = (unsigned char*)0x24; // Direction register for the port
    bool pull_up;                    // Internal pull-up resistor enabled or disabled
    unsigned int count;              // Press count
    bool previous = 1;               // Store the previous button state (initially set to high)
    unsigned char *reader = (unsigned char*)0x23;   // Pointer to the PIN register (for reading button state)
    
  public:
    // Constructor to initialize the button with port, pin, debounce time, type, and pull-up option
    Button(unsigned char* port_number, unsigned int pin_Number, unsigned int debounce_time, bool button_type, bool internal_pull_up) { 
      debounce_period = debounce_time;     // Set debounce period
      normally_high_low = button_type;     // Set button type (normally high or low)
      pull_up = internal_pull_up;          // Set if pull-up resistor is enabled
      port = port_number;                  // Set port address
      pin = pin_Number;                    // Set pin number
    
      *port_Dir = 0x00;                    // Configure pin as input by setting direction to 0
     
      // Configure pull-up resistor based on internal_pull_up flag
      if (pull_up == 1) {
        *port = (*port) | (1 << pin);      // Enable pull-up resistor
      } else {
        *port = (*port) & ~(1 << pin);     // Disable pull-up resistor
      }
    }

    // Method to handle button press with debounce
    void onPress() {
      bool current;

      // If button is normally high
      if (normally_high_low == 1) {
        current = (((*reader) & (1 << pin)) != 0);  // Read current button state (high)

        // Check if button was pressed (transition from high to low)
        if (current && !previous) {
          delay(debounce_period);  // Wait for debounce period

          // Check if button is still pressed after debounce delay
          if (((*reader) & (1 << pin)) != 0) {
            count++;               // Increment press count
            Serial.println("A has been pressed once");
          }
        }
        previous = current;        // Update the previous state with the current state
      }

      // If button is normally low
      if (normally_high_low == 0) {
        current = (((*reader) & (1 << pin)) == 0);  // Read current button state (low)

        // Check if button was pressed (transition from low to high)
        if (current && !previous) {
          delay(debounce_period);  // Wait for debounce period

          // Check if button is still pressed after debounce delay
          if (((*reader) & (1 << pin)) == 0) {
            Serial.println("A has been pressed once");
          }
        }
        previous = current;        // Update the previous state with the current state
      }
    }

    /* Uncomment to add onRelease functionality
    void onRelease() {
      bool current;

      // If button is normally high
      if (normally_high_low == 1) {
        current = (((*reader) & (1 << pin)) == 0);  // Read current button state (low)

        // Check if button was released (transition from low to high)
        if (current && !previous) {
          delay(debounce_period);  // Wait for debounce period

          // Check if button is still released after debounce delay
          if (((*reader) & (1 << pin)) == 0) {
            Serial.println("A has been released");
          }
        }
        previous = current;        // Update previous state with current state
      }

      // If button is normally low
      if (normally_high_low == 0) {
        current = (((*reader) & (1 << pin)) != 0);  // Read current button state (high)

        // Check if button was released (transition from high to low)
        if (current && !previous) {
          delay(debounce_period);  // Wait for debounce period

          // Check if button is still released after debounce delay
          if (((*reader) & (1 << pin)) != 0) {
            Serial.println("A has been released");
          }
        }
        previous = current;        // Update previous state with current state
      }
    }
    */

    // Function pointer to handle button events (e.g., onPress, onRelease)
    void (*fptr)();
};

// Sample function to be called on button press
void onPressA() {
  Serial.println("A has been pressed");
}

// Create Button object with port 0x25, pin 0, debounce time of 3ms, normally high button, and pull-up enabled
Button Button1((unsigned char*)0x25, 0, 3, 1, 1);

// Setup function to initialize the serial communication and assign the onPress method to the function pointer
void setup() {
  Serial.begin(9600);               // Initialize serial communication at 9600 baud rate
  Button1.fptr = &Button::onPress;  // Set the function pointer to onPress method
}

// Main loop to continuously check the button state
void loop() {
  // Button1.onPress();  // Uncomment this to check for button press
  // Button1.onRelease(); // Uncomment this to check for button release
}
