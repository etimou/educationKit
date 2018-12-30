 
boolean blink_led_status = 0;
boolean blink_var_led_status = 0;
boolean ledState = 0;
unsigned long last_blink_time = 0;
unsigned long last_blink_var_time = 0;
unsigned long lastDebounceTime = 0; 
boolean buttonState;
boolean lastButtonState = 0;

boolean Aval,Bval,Cval,Dval,Eval,Fval,Gval;

char counter = 0;

void printchar(char num)
{
  #define seg_A 11
  #define seg_B 12
  #define seg_C 13
  #define seg_D 5
  #define seg_E 6
  #define seg_F 7
  #define seg_G 8

  if (num==0)
  {
    Aval=1;Bval=1;Cval=1;Dval=1;Eval=1;Fval=1;Gval=0;
  }
  else if (num==1)
  {
    Aval=0;Bval=1;Cval=1;Dval=0;Eval=0;Fval=0;Gval=0;
  }
  else if (num==2)
  {
    Aval=1;Bval=1;Cval=0;Dval=1;Eval=1;Fval=0;Gval=1;
  }
  else if (num==3)
  {
    Aval=1;Bval=1;Cval=1;Dval=1;Eval=0;Fval=0;Gval=1;
  }  
  else if (num==4)
  {
    Aval=0;Bval=1;Cval=1;Dval=0;Eval=0;Fval=1;Gval=1;
  }    
  else if (num==5)
  {
    Aval=1;Bval=0;Cval=1;Dval=1;Eval=0;Fval=1;Gval=1;
  }
  else if (num==6)
  {
    Aval=1;Bval=0;Cval=1;Dval=1;Eval=1;Fval=1;Gval=1;
  }
  else if (num==7)
  {
    Aval=1;Bval=1;Cval=1;Dval=0;Eval=0;Fval=0;Gval=0;
  }
  else if (num==8)
  {
    Aval=1;Bval=1;Cval=1;Dval=1;Eval=1;Fval=1;Gval=1;
  }   
  else if (num==9)
  {
    Aval=1;Bval=1;Cval=1;Dval=1;Eval=0;Fval=1;Gval=1;
  }
  else if (num==10)
  {
    Aval=1;Bval=1;Cval=1;Dval=0;Eval=1;Fval=1;Gval=1;
  }
  else if (num==11)
  {
    Aval=0;Bval=0;Cval=1;Dval=1;Eval=1;Fval=1;Gval=1;
  }  
  else if (num==12)
  {
    Aval=1;Bval=0;Cval=0;Dval=1;Eval=1;Fval=1;Gval=0;
  }    
  else if (num==13)
  {
    Aval=0;Bval=1;Cval=1;Dval=1;Eval=1;Fval=0;Gval=1;
  }
  else if (num==14)
  {
    Aval=1;Bval=0;Cval=0;Dval=1;Eval=1;Fval=1;Gval=1;
  }
  else if (num==15)
  {
    Aval=1;Bval=0;Cval=0;Dval=0;Eval=1;Fval=1;Gval=1;
  }    

  digitalWrite(seg_A, Aval);
  digitalWrite(seg_B, Bval);
  digitalWrite(seg_C, Cval);
  digitalWrite(seg_D, Dval);
  digitalWrite(seg_E, Eval);
  digitalWrite(seg_F, Fval);
  digitalWrite(seg_G, Gval);


}

void computechar(int val)
{
  if (val<100)
  {
    printchar(0);
    return;
  }
  else if (val<200)
  {
    printchar(1);
    return;
  }
  else if (val<300)
  {
    printchar(2);
    return;
  }
  else if (val<400)
  {
    printchar(3);
    return;
  }
  else if (val<500)
  {
    printchar(4);
    return;
  }
  else if (val<600)
  {
    printchar(5);
    return;
  }
  else if (val<700)
  {
    printchar(6);
    return;
  }
  else if (val<800)
  {
    printchar(7);
    return;
  }
  else if (val<900)
  {
    printchar(8);
    return;
  }
  else
  {
    printchar(9);
  }
}

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(2, OUTPUT);//toggle led
  pinMode(3, OUTPUT);//intensity led
  pinMode(1, OUTPUT);//frequency led
  pinMode(0, OUTPUT);//usual 0.5Hz blink
  pinMode(9, OUTPUT);//buzzer
  pinMode(10, OUTPUT);//led used with photocell
  
  pinMode(5, OUTPUT);//7-segment 
  pinMode(6, OUTPUT);//7-segment 
  pinMode(7, OUTPUT);//7-segment 
  pinMode(8, OUTPUT);//7-segment 
  pinMode(11, OUTPUT);//7-segment 
  pinMode(12, OUTPUT);//7-segment 
  pinMode(13, OUTPUT);//7-segment 
}

void loop() {
  
  ////////////////////////////////////////////////////
  if (millis()-last_blink_time>1000)
  {
    last_blink_time = millis();
    blink_led_status = !blink_led_status;
  }
  digitalWrite(0, blink_led_status);   // set the LED on
  ////////////////////////////////////////////////////
  int val = analogRead(A5);
  int val_intensity = map(val, 0, 1023, 0, 255);//when using potentiometer
  analogWrite(3, val_intensity);
  
  int val2 =val;
  if (val2>512)
  {
    val2=512;
  }
  int val_intensity2 = map(val2, 0, 512, 255, 0);//when using photocell
  analogWrite(10, val_intensity2);
  ////////////////////////////////////////////////////
  int val_frequency = map(val, 0, 1023, 20, 1000); 
  if (millis()-last_blink_var_time>val_frequency)
  {
    last_blink_var_time = millis();
    blink_var_led_status = !blink_var_led_status;
  }
  digitalWrite(1, blink_var_led_status);   // set the LED on
  ////////////////////////////////////////////////////
  int reading = digitalRead(18);
  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > 50) {
    if ((buttonState==0) && (reading==1))
    {
      ledState = !ledState;
      if (counter == 15)
      {
        counter = 0;
      }
      else
      {
        counter++;
      }
    }
    buttonState = reading;
  }
  digitalWrite(2, ledState);
  lastButtonState = reading;
  ////////////////////////////////////////////////////
  if (!reading)
  {
    analogWrite(9, 127);
  }
  else
  {
    digitalWrite(9,0);
  }
  /////////////////////////////////////////////////////
  if (digitalRead(A3))
  {
    computechar(val);
  }
  else
  {
    printchar(counter);
  }
  
}
