#ifndef MvtVoiture_h
#define MvtVoiture_h

#include <Arduino.h>

class MvtVoiture
{
private:
  int leftengpin;
  int rightengpin;  
  MvtVoiture _mvtVoiture;
public: 
  MvtVoiture_(int pin1, int pin2);
  void forward(void);
  void left(void);
  void right(void);
  void stopCar(void);
  void seekingPath(void);
};

#endif
