class Blinky

{
 private:
  unsigned char *port;
  unsigned int pin;
  int OFF;
  int ON;
  unsigned char *port_Dir;
  unsigned long previousTime;
  
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
  
  unsigned long currentTime=millis();
  
  if(((*port)&(1<<pin))==0)
  {
  
   if(currentTime-previousTime>=OFF)
  
  {
  
  *port=(*port)|(1<<pin);
  previousTime=currentTime;
   
  
  }
  
  
  
  
  }
  
  else
  {
  
   if(currentTime-previousTime>=ON)
  {
    *port=(*port)&~(1<<pin);
    previousTime=currentTime;
    
  }
  
  }
 //*port=(*port)|(1<<pin);
 //*port=0xFF;
  //delay(ON);
// *port=(*port)&~(1<<pin);
 //*port=0x00;
//delay(OFF);


}










  
  
  










};
////// Example 7
Blinky led1((unsigned char*)0x25,0,750,350);
Blinky led2((unsigned char*)0x25,1,400,600);


void setup() 
{
  

}

void loop() 
{
  led1.Blink();
  led2.Blink();
  

}
