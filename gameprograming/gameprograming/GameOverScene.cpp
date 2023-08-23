#include"GameOverScene.h"
#include"DxLib.h"
#include"SceneManager.h"
/***
*変数宣言
****/
int GameOverImage;
int GameOverSE;
int GameOverFlag;
/***
プロトタイプ宣言
***/

int GameOverScene_Initialize(void)
{
	int ret = 0;
	//画像読み込み
	GameOverImage = LoadGraph("images/gameover.png");
	//音源読み込み
	GameOverSE = LoadSoundMem("sounds/gameover_se.mp3");
	GameOverFlag = FALSE;
	//エラーチェック
	if (GameOverImage == -1)
	{
		ret = -1;
	}
	if (GameOverSE == -1)
	{
		ret = -1;
	}
	return ret;
}

void GameOverScene_Update(void)
{
	if (CheckSoundMem(GameOverSE) == 0)
	{
		if (GameOverFlag == TRUE)
		{
			Change_Scene(E_GAME_OVER);
		}
		else
		{
			PlaySoundMem(GameOverSE, DX_PLAYTYPE_BACK);
			GameOverFlag = TRUE;
		}
	}
}
void GameOverScene_Draw(void)
{
	DrawGraph(0, 0, GameOverImage, FALSE);
}