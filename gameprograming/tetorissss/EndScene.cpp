#include "EndScene.h"
#include "DxLib.h"




int wait_count;

int EndScene_Initialize(void)
{
	int ret = 0;

	wait_count = 0;

	return ret;
}

void EndScene_Update(void)
{
	wait_count++;
}


void EndScene_Draw(void)
{
	DrawString(10, 10, "ƒGƒ“ƒh‰æ–Ê‚Å‚·", GetColor(255, 255, 255));
}


int Get_EndTime(void)
{
	if (wait_count > 300)
	{
		return TRUE;
	}
	return FALSE;
}