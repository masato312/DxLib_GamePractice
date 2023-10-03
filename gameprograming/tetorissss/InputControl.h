#pragma once

#include "InputControl.h"

void InputControl_Initialize(void);
void InputControl_Updata(void);

int GetButton(int button);
int GetButtonDown(int button);
int GetButtonUp(int button);

int GetExitButton(void);