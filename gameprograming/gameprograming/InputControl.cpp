#include "DxLib.h"
#include "inptControl.h"


int old_button;
int now_button;
int mouse_position_x;
int mouse_position_y;






void Input_Initialize(void)
{
	old_button = NULL;
	now_button = NULL;
	mouse_position_x = NULL;
	mouse_position_y = NULL;
}





void Input_Update(void)
{
	old_button = now_button;
	now_button = GetMouseInput();

	GetMousePoint(&mouse_position_x, &mouse_position_y);
}

int Input_Escape(void)
{
	int ret = FALSE;
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ret = TRUE;
	}
	return ret;
}




int GetOldKey(int key)
{
	int ret = FALSE;
	if ((key & old_button) != FALSE)
	{
		ret = TRUE;
	}
	return ret;

}



int GetNowKey(int key)
{
	int ret = FALSE;
	int keyflg = now_button & old_button;
	if ((key & keyflg) != FALSE)
	{
		ret = TRUE;
	}
	return ret;
}


int GetMousePositionX(void)
{
	return mouse_position_x;
}


int GetMousePositionY(void)
{
	return mouse_position_y;
}
