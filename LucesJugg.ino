/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#define Tcambio 3000 //milisegundos que tarda la transición
#define Npasos 200 //pasos en los que realizamos la transición

  int counter = 0;
  double Tactual, Tinicio;
  int cr, cg, cb;
  int cr_old, cg_old, cb_old;
  double ir, ig, ib;
  
  
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  //long Tactual;
  Tinicio = millis();
  
  Serial.begin(9600);
  
  analogWrite(3, 20);  
  analogWrite(5, 0);
  analogWrite(6, 0);

  delay(500);
  analogWrite(3, 0);  
  analogWrite(5, 200);
  analogWrite(6, 0);
  
  delay(500);
  analogWrite(3, 0);  
  analogWrite(5, 0);
  analogWrite(6, 200);

  delay(500);
  analogWrite(3, 207);  
  analogWrite(5, 212);
  analogWrite(6, 2);
  
  delay(500);
  analogWrite(3, 145);  
  analogWrite(5, 46);
  analogWrite(6, 201);

  delay(500);
}

// the loop function runs over and over again forever
void loop() {
  
  Tactual = millis()-Tinicio;
  
  if (Tactual>=(Tcambio))
  {
    
    cr_old = cr;
    cg_old = cg;
    cb_old = cb;
    
    
    if (random(15) == 3)
        {
          cr = 255;
          cg = 0;
          cb = 0;
        }
    else if (random(30) == 5)
       {
         cr = 207;
         cg = 212;
         cb = 85;
       }
    else if (random(30) == 5)
       {
         cr = 145;
         cg = 46;
         cb = 201;
       }  
    else 
    {
       while (abs((cr+cg+cb)-(cr_old+cg_old+cb_old))<=100)
        {
          cr = random(255);
          cg = random(255);
          cb = random(200);
          while (abs(cr-cr_old)<=20){cr = random(255);}
          while (abs(cg-cg_old)<=20){cg = random(255);}
          while (abs(cb-cb_old)<=20){cb = random(200);}
        }
    }
    
    ir = double(double(cr - cr_old) / double(Npasos));
    ig = double(double(cg - cg_old) / double(Npasos));
    ib = double(double(cb - cb_old) / double(Npasos));
    
    Serial.print(ir);Serial.print(ig);Serial.println(ib);
    
    counter = 0;
    
    Tinicio = millis();
  }
  
  else
  {
    
  analogWrite(3, int((ir*counter)+cr_old));  
  analogWrite(5, int((ig*counter)+cg_old));
  analogWrite(6, int((ib*counter)+cb_old));

  counter = counter + 1;
  
  delay(Tcambio/(Npasos));
  
  }  

}
