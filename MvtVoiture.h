#ifndef MvtVoiture_h
#define MvtVoiture_h
#include <Grove_I2C_Motor_Driver.h>

#include <Arduino.h>

/*This library is used to move an arduino with 2 engines
1 on the left, 1 on the right.
Can turn lef, right, go forward, pathfinding, recorrect his path,
stop and return the type of crossroads*/

class MvtVoitureD
{
private:
  int leftengpin;
  int rightengpin;
public:
  void forward(void);
  void left(void);
  void right(void);
  void stopCar(void);
  void seekingPath(void);
  void alignLeft(void);
  void alignRight(void);
  int crossroads(int inter);
};

extern MvtVoitureD MvtVoiture;
#endif
