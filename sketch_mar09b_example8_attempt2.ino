class Button

{
 private:
  unsigned char *port;
  unsigned int pin;
  unsigned int debounce_period;
  bool normally_high_low;
  unsigned char *port_Dir=(unsigned char*)0x24;
  bool pull_up;
  unsigned int count;
  bool previous=1;
  unsigned char *reader =(unsigned char*)0x23;
  //unsigned long previousTime;
  
  public:
    Button(unsigned char* port_number,unsigned int pin_Number, unsigned int debounce_time,bool button_type,bool internal_pull_up)
    
    { 
     
     debounce_period=debounce_time;
     normally_high_low=button_type;
     pull_up=internal_pull_up;
     port=port_number;
     pin=pin_Number;
    
    
     *port_Dir=0x00;
     
     
     if(pull_up==1)
     {
     *port=(*port)|(1<<pin);
     
     
     }
     else 
     {
        *port=(*port)&~(1<<pin);
       
       
       
     }
    
    }
 void onPress()
 {
   bool current;
  if(normally_high_low==1)
   {
    current =(((*reader)&(1<<pin))!=0);
  if(current&&!previous)  
  {
    delay(debounce_period);
    if (((*reader)&(1<<pin))!=0)
    {
    count++;
    //Serial.print(count);
    Serial.println("A has been pressed once");
    }
    }
  previous=current;     
   }
  // previous=current;
      if(normally_high_low==0)
   {
    current =(((*reader)&(1<<pin))==0);
  if(current&&!previous)
    {
    delay(debounce_period);
    if (((*reader)&(1<<pin))==0)
    {
    ///count++;
    Serial.println("A has been pressed once");
    }
  } 
  previous=current;
  
   }
  }




/*void onRelease()
 {
   bool current;
  if(normally_high_low==1)
   {
    current =(((*reader)&(1<<pin))==0);
  if(current&&!previous)  
  {
    delay(debounce_period);
    if (((*reader)&(1<<pin))==0)
    {
    Serial.println("A has been released");
    
    }
  
   }
   }
   previous=current;
      if(normally_high_low==0)
   {
    current =(((*reader)&(1<<pin))==0);
  if(current&&!previous)  
  {
    delay(debounce_period);
    if (((*reader)&(1<<pin))!=0)
    {
    Serial.println("A has been released");
    
    }
  
   }
  
   }

   }*/



















void (*fptr)();




};


void onPressA()
{
Serial.println("A has been pressed");

}

Button Button1((unsigned char*)0x25,0, 3,1,1);


void setup() 
{
  Serial.begin(9600);
  Button1.fptr=&Button::onPress;

}

void loop() 
{
  
    //Button1.onPress();
  
    //Button1.onRelease();
  
  

}
