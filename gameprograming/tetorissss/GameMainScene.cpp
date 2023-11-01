#include "GameMainScene.h"
#include "DxLib.h"
#include "Block.h"
#include "SceneManager.h"

int BackGround_image;		//背景画像イメージ
int BackGround_sound;		//BGM
int GameOver_sound;			//ゲームオーバーSE
int Score;					//スコア

int GameMainScene_Initialize(void)
{
	int ret = 0;

	ret = Block_Initialize();
	BackGround_image = LoadGraph("images/stage.png");
	BackGround_sound = LoadSoundMem("sounds/BGM017.ogg");
	GameOver_sound = LoadSoundMem("sounds/GameOver.mp3");

	if (BackGround_image == -1)
	{
		ret = -1;
	}
	if (BackGround_sound == -1)
	{
		ret = -1;
	}
	return ret;
}

void GameMainScene_Update(void)
{
	PlaySoundMem(BackGround_sound, DX_PLAYTYPE_LOOP, FALSE);

	Block_Update();

	Score = Get_Line() * 50;

	if (Get_GenerateFlg() != TRUE)
	{
		PlaySoundMem(GameOver_sound, DX_PLAYTYPE_BACK, FALSE);
		Change_Scene(E_RANKING);
		StopSoundMem(BackGround_sound);
	}
}

void GameMainScene_Draw(void)
{
	DrawGraph(0, 0, BackGround_image, TRUE);

	Block_Draw();
	SetFontSize(100);

	DrawFormatString(800, 100, GetColor(255, 255, 255), "%d", Score);
	SetFontSize(20);
}

int Get_Score(void)
{
	return Score;
}