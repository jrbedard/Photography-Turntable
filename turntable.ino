/* turntable.ino
 by J.R. Bedard - @jrbedard - http://jrbedard.com
 Arduino code to control a 3D printed photography turntable.
 3D Model available on the SketchUp model warehouse.
*/

#include <Servo.h>


const int TURNTABLE_SERVO_PIN = 1; // input pin on your Arduino


class Turntable
{
  Servo servo;          // the servo
  int pos;              // current servo position 
  int increment;        // increment to move for each interval
  int  updateInterval;  // interval between updates
  unsigned long lastUpdate; // last update of position

public: 
  Turntable(int interval)
  {
    updateInterval = interval;
    increment = 1;
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      
      if((pos >= 180) || (pos <= 0)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
    }
  }
};


Turntable turntable(45); // turntable instance

void setup()
{
  turntable.Attach(TURNTABLE_SERVO_PIN);
}


void loop()
{
  turntable.Update();
}


