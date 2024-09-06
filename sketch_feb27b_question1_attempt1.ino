#define BIT(x) (1 << (x))

class Blinky
{
  private:
    unsigned char *port;
    unsigned int pin;
    int OFF;
    int ON;
    unsigned char *port_Dir;
  
  public:
    Blinky(unsigned char* port_number, unsigned int pin_Number, int ON_time, int OFF_time)
    {
      ON = ON_time;
      OFF = OFF_time;
      port = port_number;
      pin = pin_Number;

      if(port == (unsigned char*)0x25)
      {
        port_Dir = (unsigned char*)0x24;  // DDR for port 0x25
      }
      else if(port == (unsigned char*)0x28)
      {
        port_Dir = (unsigned char*)0x27;  // DDR for port 0x28
      }
      else
      {
        port_Dir = (unsigned char*)0x2A;  // Default DDR
      }

      // Set the specific pin as output
      *port_Dir |= BIT(pin);
    }
  
    void Blink()
    {
      *port |= BIT(pin);    // Set pin HIGH
      delay(ON);            // Wait for ON duration
      *port &= ~BIT(pin);   // Set pin LOW
      delay(OFF);           // Wait for OFF duration
    }
};

// Example usage
Blinky led1((unsigned char*)0x25, 0, 750, 350);
Blinky led2((unsigned char*)0x25, 1, 400, 600);

void setup() 
{
  // Any setup code if needed
}

void loop() 
{
  led1.Blink();
  led2.Blink();
}
