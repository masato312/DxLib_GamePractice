#include "SceneManager.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "RankingScene.h"
#include "EndScene.h"
#include "DxLib.h"

GAME_MODE game_mode;
GAME_MODE next_mode;
int read_error;

void SceneManager_Initialize(GAME_MODE mode)
{
	read_error = D_NORMALITY;
	switch (mode)
	{
	case E_TITLE:
		read_error = TitleScene_Initialize();
		break;
	case E_GAMEMAIN:
		read_error = GameMainScene_Initialize();
		break;
	case E_RANKING:
		if (game_mode == E_GAMEMAIN)
		{
			Set_RankingMode(RANKING_INPUT_MODE);
			Set_RankingScore(Get_Score());
		}
		else {
			Set_RankingMode(RANKING_DISP_MODE);
		}
		read_error = RankingScene_Initialize();
		break;
	case E_END:
	default:
		EndScene_Initialize();
		break;
	}
	game_mode = mode;
	next_mode = game_mode;
}
void SceneManager_Update(void)
{
	if (game_mode != next_mode)
	{
		SceneManager_Initialize(next_mode);
	}
	switch (game_mode)
	{
	case E_TITLE:
		TitleScene_Update();
		break;
	case E_GAMEMAIN:
		GameMainScene_Update();
		break;
	case E_RANKING:
		RankingScene_Update();
		break;
	case E_END:
	default:
		EndScene_Update();
		break;
	}
}
void SceneManager_Draw(void)
{
	switch (game_mode)
	{
	case E_TITLE:
		TitleScene_Draw();
		break;
	case E_GAMEMAIN:
		GameMainScene_Draw();
		break;
	case E_RANKING:
		RankingScene_Draw();
		break;
	case E_END:
	default:
		EndScene_Draw();
		break;
	}
}
void Change_Scene(GAME_MODE mode)
{
	next_mode = mode;
}

int ErrorCheck(void)
{
	if (Get_EndTime() == TRUE)
	{
		read_error = D_ERROR;
	}
	return read_error;
}