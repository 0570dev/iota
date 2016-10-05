#include "OneButton.h"
#define BUTTONPIN 0 // D3
OneButton button(BUTTONPIN, true);

void setupButton() {
  pinMode(BUTTONPIN, INPUT);
  button.setClickTicks(200);
  button.setPressTicks(400);
  button.attachClick(doBuild);
}

void loopButton() {
  button.tick();
}
