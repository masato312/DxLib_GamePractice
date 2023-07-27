#include "GameMainScene.h"
#include "DxLib.h"
#include "Stage.h"
#include "SceneManager.h"

/*****
*�}�N����`
******/

#define TIMELIMIT			(3600*3)	//��������
#define NUMBER_IMAGE_MAX	(10)		//�����摜��

/**********
*�^��`
********/

/********
���ϐ��錾
********/
int GameScore;
int GameLevel;
int GameMission;
int GameTime;
int GameCount;				//����������Ȃ��悤�ɂ��邽�߂̃J�E���g
int ReStartFlag;
int NumberImage[NUMBER_IMAGE_MAX];


/********
�v���g�^�C�v
**********/


/***********
*�Q�[�����C���摜�F����������
*�����F�Ȃ�
*�߂�l�F�G���[���
******************/

int GameMainScene_Initialize(void)
{
	int ret = 0;
	int i;


	//�摜�ǂݍ���
	LoadDivGraph("images/number.png", NUMBER_IMAGE_MAX,
		NUMBER_IMAGE_MAX, 1, 60, 120, NumberImage);

	//�X�e�[�W�@�\������
	ret = StageInitialize();

	//�G���[�`�F�b�N
	for (i = 0; i < NUMBER_IMAGE_MAX; i++)
	{
		if(NumberImage[i]==D_ERROR)
		{
			ret = D_ERROR;
			break;
		}
	}

	//�Q�[���v���C�����񂩂ǂ����H
	if (GameCount == 0)
	{
		GameScore = 0;
		GameLevel = 1;
		Set_StageMission(3);
		GameCount++;
	}
	else
	{
		GameLevel++;
		Set_StageMission(3);
	}
	GameTime = TIMELIMIT;

	return ret;
}
/*****
���Q�[�����C���摜�F�X�V����
*�����F�Ȃ�
���߂�l�F�Ȃ�
******/
void GameMainScene_Update(void)
{
	switch (Get_StageState())
	{
	case 0:
		SelectBolck();
		break;
	case 2:
		MoveBlock();
		break;
	case 3:
		CheckBlock();
		break;
	case 4:
		CheckClear();
		break;
	default:
		break;
	}
	//�������Ԃ̍X�V
	GameTime--;

	//�������Ԃ������Ȃ�����A�Q�[���I�[�o�[�ɂ���
	if (GameTime < 0)
	{
		Change_Scene(E_GAME_OVER);
	}
	if (Get_StageClearFlag())
	{
		Change_Scene(E_GAME_CLEAR);
	}

}

/*********
�Q�[�����C���摜�F�`�揈��
*�����F�Ȃ�
*�߂�l�F�Ȃ�
****************/

void GameMainScene_Draw(void)
{
	int PosX = 600;
	int tmp_level = GameLevel;
	int tmp_score = Get_StageScore();

	//�X�e�[�W�`��
	StageDraw();

	//	�t�F�[�h�A�E�g��Ԃ��H
	if (Get_StageState() == 1)
	{
		FadeOutBlock();				//�t�F�[�h�A�E�g����B
	}
	//���x����`��
	do {
		DrawRotaGraph(PosX, 80, 0.5f, 0, NumberImage[tmp_level % 10], TRUE);
		tmp_level /= 10;
		PosX -= 30;
	} while (tmp_level > 0);

	//�X�R�A�̕`��
	PosX = 620;
	do {
		DrawRotaGraph(PosX, 160, 0.3f, 0, NumberImage[tmp_level % 10], TRUE);
		tmp_score /= 10;
		PosX -= 20;
	} while (tmp_score > 0);

	//�������Ԃ̕`��
	DrawBox(491, 469, 509, 469 - GameTime / 60 * 2, 0x0033ff, TRUE);
}
