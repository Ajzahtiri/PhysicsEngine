#include		"input.h"		

Input::Input()
{

}

keyEvent Input::checkUserInput(HWND hWnd)
{
	keyEvent event;

	if (IS_KEY_DOWN(VK_ESCAPE))
	{
		event = QUIT;
		PostMessage(hWnd, WM_DESTROY, 0, 0);
	}

	else if (IS_KEY_DOWN(VK_UP))
	{
		event = UP;
	}

	else if (IS_KEY_DOWN(VK_DOWN))
	{
		event = DOWN;
	}

	else if (IS_KEY_DOWN(VK_LEFT))
	{
		event = LEFT;
	}

	else if (IS_KEY_DOWN(VK_RIGHT))
	{
		event = RIGHT;
	}

	else if (IS_KEY_DOWN(0x5A))
	{
		event = Z;
	}

	else if (IS_KEY_DOWN(0x58))
	{
		event = X;
	}

	else if (IS_KEY_DOWN(0x43))
	{
		event = C;
	}
	
	else if (IS_KEY_DOWN(0x56))
	{
		event = V;
	}

	else if (IS_KEY_DOWN(0x41))
	{
		event = A;
	}

	else if (IS_KEY_DOWN(0x44))
	{
		event = D;
	}

	else if (IS_KEY_DOWN(0x53))
	{
		event = S_DOWN;
	}

	else if (IS_KEY_UP(0x53))
	{
		event = S_UP;
	}		

	else 
	{
		event = QUIET;
	}

	return event;
}

