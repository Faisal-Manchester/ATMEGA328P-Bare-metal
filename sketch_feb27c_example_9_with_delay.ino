class Blinky

{
 private:
  unsigned char *port;
  unsigned int pin;
  int OFF;
  int ON;
  unsigned char *port_Dir;
  
  
  public:
    Blinky(unsigned char* port_number,unsigned int pin_Number, int ON_time,int OFF_time)
    
    { 
     //#define BIT(pin_Number) (1 << (pin_Number))
     ON=ON_time;
     OFF=OFF_time;
     port=port_number;
     pin=pin_Number;
    // pin=pin_Number;
   if(port==(unsigned char*)0x25)
     {
     port_Dir =(unsigned char*)0x24;
     }
     else if(port ==(unsigned char*)0x28)
     {
       port_Dir=(unsigned char*)0x27;
     }
     else 
     {
      port_Dir=(unsigned char*)0x2A;
     }
    // pin=1<<pin;
    // port_Dir =(unsigned char*)0x24;
    
    //*port_Dir=(*port_Dir)&BIT(pin_Number);
     *port_Dir=0xFF;
    
    }
  
 void Blink()


{
 *port=(*port)|(1<<pin);
 //*port=0xFF;
  delay(ON);
 *port=(*port)&~(1<<pin);
 //*port=0x00;
delay(OFF);


}










  
  
  










};
////// Example 9
Blinky led1((unsigned char*)0x25,0,781,515);
Blinky led2((unsigned char*)0x25,1,2014,1348);
Blinky led3((unsigned char*)0x25,2,343,1348);
Blinky led4((unsigned char*)0x25,3,678,1839);
Blinky led5((unsigned char*)0x25,4,342,534);
Blinky led6((unsigned char*)0x25,5,1478,326);
Blinky led7((unsigned char*)0x25,6,1859,351);
Blinky led8((unsigned char*)0x25,7,777,888);


void setup() 
{
  

}

void loop() 
{
  led1.Blink();
  led2.Blink();
  led3.Blink();
  led4.Blink();
  led5.Blink();
  led6.Blink();
  led7.Blink();
  led8.Blink();
    

}
