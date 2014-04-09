#include		"input.h"		

Input::Input()
{

}

Input::~Input()
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

	else 
	{
		event = QUIET;
	}

	return event;
}

