#include"GameClearScene.h"
#include"DxLib.h"
#include"SceneManager.h"






int GameClearImage;
int GameClearSE;
int GameClearFlag;




int GameClearScene_Initialize(void)
{
	int ret = 0;

	GameClearImage = LoadGraph("images/gameclear.png");

	GameClearSE = LoadSoundMem("sounds/gameclear_se.mp3");

	GameClearFlag = 0;


	if(GameClearImage==-1)
{
	ret = -1;
}

if (GameClearSE == -1)
{
	ret = -1;
}
return ret;
}


void GameClearScene_Update(void)
{
	if (CheckSoundMem(GameClearSE) == 0)
	{
		if (GameClearFlag == TRUE)
		{
			Change_Scene(E_GAMEMAIN);
		}
		else
		{
			PlaySoundMem(GameClearSE, DX_PLAYTYPE_BACK);
			GameClearFlag = TRUE;
		}
	}
}


void GameClearScene_Draw(void)
{
	DrawGraph(0, 0, GameClearImage, FALSE);
}