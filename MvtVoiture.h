#ifndef MvtVoiture_h
#define MvtVoiture_h
#include <Grove_I2C_Motor_Driver.h>

#include <Arduino.h>

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
