#pragma once

class InputManager
{
public:

	// Function that processes incoming bool values with SDL events and checks whether they are printed or not.
	void KeyControl(bool& _running, bool& _ButtonOneUp, bool& _ButtonOneDown, bool& _ButtonTwoUp, bool& _ButtonTwoDown);
};

