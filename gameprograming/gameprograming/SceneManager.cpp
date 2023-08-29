#include"SceneManager.h"
#include"TitleScene.h"
#include"GameMainScene.h"
#include"GameClearScene.h"
#include"GameOverScene.h"







GAME_MODE Game_Mode;
GAME_MODE Next_Mode;








int SceneManager_Initialize(GAME_MODE mode)
{
	int Read_Error;
	//�V�[���ǂݍ���
	//�^�C�g�����
	Read_Error = TitleScene_Initialize();
	if (Read_Error == D_ERROR)
	{
		return D_ERROR;
	}
	//�Q�[�����C����� 
	Read_Error = GameMainScene_Initialize();
	if (Read_Error == D_ERROR)
	{
		return D_ERROR;
	}
	//�Q�[���N���A���
	Read_Error = GameClearScene_Initialize();
	if (Read_Error == D_ERROR)
	{
		return D_ERROR;
	}
	//�Q�[�����[�Ή��
	Read_Error = GameOverScene_Initialize();
	if (Read_Error == D_ERROR)
	{
		return D_ERROR;
	}

	Game_Mode = mode;
	Next_Mode = Game_Mode;
	return Read_Error;
}


void SceneManager_Update(void)
{
	if (Game_Mode != Next_Mode)
	{
		SceneManager_Initialize(Next_Mode);


	}



	//�e��ʂ̍X�V
	switch (Game_Mode)
	{
	case E_TITLE:
		TitleScene_Update();
		break;
	case E_GAMEMAIN:
		GameMainScene_Update();
		break;
	case E_GAME_CLEAR:
		GameClearScene_Update();
		break;
	case E_GAME_OVER:
		GameOverScene_Update();
		break;
	default:
		break;
	}
}


void SceneManager_Draw(void)
{
	switch (Game_Mode)
	{
	case E_TITLE:
		TitleScene_Draw();
		break;
	case E_GAMEMAIN:
		GameMainScene_Draw();
		break;
	case E_GAME_CLEAR:
		GameClearScene_Draw();
		break;
	case E_GAME_OVER:
		GameOverScene_Draw();
		break;
	default:
		break;
	}
}




void Change_Scene(GAME_MODE mode)
{
	Next_Mode = mode;
}

