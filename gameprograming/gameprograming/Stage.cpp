#include "Stage.h"
#include "DxLib.h"
#include "InputControl.h"
/*****
�}�N����`
*******/
#define HEIGHT				(12)
#define WIDTH				(12)
#define BLOCKSIZE			(48)
#define BLOCK_IMAGE_MAX		(10)

#define ITEM_MAX			(8)

#define SELECT_CURSOR		(0)
#define NEXT_CURSOR			(1)
#define TMP_CURSOR			(2)

/********
�^��`
********/
typedef struct
{
	int flg;
	int x, y;
	int width, height;
	int image;
	int backup;
}T_Object;
typedef struct
{
	int x;
	int y;
}T_CURSOR;
enum {
	E_NONE,
	E_ONCE,
	E_SECOND
};
/**********
�ϐ��錾
********/
T_Object Block[HEIGHT][WIDTH];
T_CURSOR Select[3];
int Item[ITEM_MAX];
int ClickStatus;
int Stage_State;
int Stage_Mission;
int Stage_Score;
int ClearFlag;

int BlockImage[BLOCK_IMAGE_MAX];
int StageImage;
int ClickSE;
int FadeOutSE;
int MoveBlockSE;
/*******
�v���g�^�C�v�錾
********/
int combo_check(int x, int y);
void combo_check_h(int y,int x, int* cnt, int* col);
void combo_check_w(int y,int x, int* cnt, int* col);
void save_block(void);
void restore_block(void);
/****
�X�e�[�W����@�\�F����������
�����F�Ȃ�
�߂�l�F�G���[���
******/
int StageInitialize(void)
{
	int ret = 0;
	int i;
	//�摜�ǂݍ���
	LoadDivGraph("images/block.png", BLOCK_IMAGE_MAX, BLOCK_IMAGE_MAX, 1,
		BLOCKSIZE, BLOCKSIZE, BlockImage);
	StageImage = LoadGraph("images/stage.png");

	//�����ǂݍ���
	ClickSE = LoadSoundMem("sounds/click_se.mp3");
	FadeOutSE = LoadSoundMem("sounds/fadeout_se.mp3");
	MoveBlockSE = LoadSoundMem("sounds/moveblock_se.mp3");
	//�u���b�N����
	CreateBlock();

	ClickStatus = E_NONE;
	Stage_State = 0;
	Stage_Score = 0;
	ClearFlag = FALSE;
	for (i = 0; i < 3; i++)
	{
		Select[i].x = 0;
		Select[i].y = 0;
	}
	//�G���[�`�F�b�N
	for (i = 0; i < BLOCK_IMAGE_MAX; i++)
	{
		if (BlockImage[i] == -1)
		{
			ret = -1;
			break;
		}
	}
	if (StageImage == -1)
	{
		ret = -1;
	}
	if (ClickSE == -1)
	{
		ret = -1;
	}
	if (FadeOutSE == -1)
	{
		ret = -1;
	}
	if (MoveBlockSE == -1)
	{
		ret = -1;
	}
	return ret;
}
/********
�X�e�[�W����@�\�F�X�e�[�W�̕`��
�����F�Ȃ�
�߂�l�F�Ȃ�
********/
void StageDraw(void) {
	DrawGraph(0, 0, StageImage, FALSE);
	//�A�C�e���̎擾����`��
	for (int i = 0; i < ITEM_MAX; i++)
	{
		DrawRotaGraph(540, 245 + i * 30, 0.5f, 0, BlockImage[i + 1], TRUE, 0);
		DrawFormatString(580, 235 + i * 30, 0xffffff, "%3d", Item[i]);
	}
	//�u���b�N��`��
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (Block[i][j].flg == TRUE && Block[i][j].image != NULL)
			{
				DrawGraph(Block[i][j].x, Block[i][j].y,
					BlockImage[Block[i][j].image], TRUE);
			}
		}
	}
	//�I���u���b�N��`��
	DrawGraph(Select[SELECT_CURSOR].x * BLOCKSIZE, Select[SELECT_CURSOR].y
		* BLOCKSIZE, BlockImage[9], TRUE);
	if (ClickStatus != E_NONE)
	{
		DrawGraph(Select[NEXT_CURSOR].x * BLOCKSIZE, Select[NEXT_CURSOR].y * 
			BLOCKSIZE, BlockImage[9], TRUE);
	}
	//�~�b�V����
	SetFontSize(20);
	DrawFormatString
	(590, 211, GetColor(255, 255, 255), "%3d", Stage_Mission);

	//�A�C�e��
	for (int i = 0; i < ITEM_MAX; i++)
	{
		DrawRotaGraph
		(540, 245 + i * 30, 0.5f, 0, BlockImage[i + 1], TRUE, 0);
		DrawFormatString
		(580, 235 + i * 30, GetColor(255, 255, 255), "%3d", Item[i]);
	}
}

void CreateBlock(void)
{
	int Check = 0;
	int i, j;

	do
	{
		Check = 0;
		for (i = 0; i < HEIGHT; i++)
		{
			for (j = 0; j < WIDTH; j++)
			{
				if (j == 0 || j == WIDTH - 1 || i == HEIGHT - 1 || i == 0)
				{
					Block[i][j].flg = FALSE;
					Block[i][j].image = NULL;
				}
				else
				{
					Block[i][j].flg = TRUE;
					Block[i][j].x = (j - 1) * BLOCKSIZE;
					Block[i][j].y = (i - 1) * BLOCKSIZE;
					Block[i][j].width = BLOCKSIZE;
					Block[i][j].height = BLOCKSIZE;
					Block[i][j].image = GetRand(7) + 1;
				}
			}
		}
		/*for (i = 1; i<HEIGHT - 1; i++)
		{
			for (j = 1; j < WIDTH - 1; j++)
			{
				if (Block[i][j].image == NULL)
				{
					Block[i][j].image = GetRand(7) + 1;
				}
			}
		}*/
		//�u���b�N�A��
		for (i = 1; i < HEIGHT - 1; i++)
		{
			for (j = 1; j < WIDTH - 1; j++)
			{
				Check += combo_check(i, j);
			}
		}
	} while (Check != 0);

	for (i = 0; i < ITEM_MAX; i++)
	{
		Item[i] = 0;
	}
}
void SelectBlock(void)
{
	int TmpBlock;
	int Result;

	//�J�[�\��
	Select[SELECT_CURSOR].x = GetMousePositionX() / BLOCKSIZE;
	Select[SELECT_CURSOR].y = GetMousePositionY() / BLOCKSIZE;

	if (Select[SELECT_CURSOR].x < 0)
	{
		Select[SELECT_CURSOR].x = 0;
	}
	if (Select[SELECT_CURSOR].x > WIDTH - 3)
	{
		Select[SELECT_CURSOR].x = WIDTH - 3;
	}
	if (Select[SELECT_CURSOR].y < 0)
	{
		Select[SELECT_CURSOR].y = 0;
	}
	if (Select[SELECT_CURSOR].y > HEIGHT - 3)
	{
		Select[SELECT_CURSOR].y = HEIGHT - 3;
	}

	//�N���b�N�Ԃ���� 
	if (GetKeyFlg(MOUSE_INPUT_LEFT)) {
		//�N���b�N��
		PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK);

		if (ClickStatus == E_NONE) {
			Select[NEXT_CURSOR].x = Select[SELECT_CURSOR].x;
			Select[NEXT_CURSOR].y = Select[SELECT_CURSOR].y;
			ClickStatus = E_ONCE;
		}
		else if(ClickStatus==E_ONCE&&
			((abs(Select[NEXT_CURSOR].x-Select[SELECT_CURSOR].x)
				==1&&
				(abs(Select[NEXT_CURSOR].y-Select[SELECT_CURSOR].y)
					==0))||
				(abs(Select[NEXT_CURSOR].x-Select[SELECT_CURSOR].x)
					==0&&
					abs(Select[NEXT_CURSOR].y-Select[SELECT_CURSOR].y)==1)))
		
		{
			Select[TMP_CURSOR].x = Select[SELECT_CURSOR].x;
			Select[TMP_CURSOR].y = Select[SELECT_CURSOR].y;
			ClickStatus = E_SECOND;
		}
	}
	//�I���u���b�N
	if (ClickStatus == E_SECOND)
	{
		TmpBlock = Block[Select[NEXT_CURSOR].y + 1][Select[NEXT_CURSOR].x + 1].image;
		Block[Select[NEXT_CURSOR].y + 1][Select[NEXT_CURSOR].x + 1].image =
		Block[Select[TMP_CURSOR].y + 1][Select[TMP_CURSOR].x + 1].image;
		Block[Select[TMP_CURSOR].y + 1][Select[TMP_CURSOR].x + 1].image = TmpBlock;


		//�A����3�ȏ�
		Result = 0;
		Result += combo_check(Select[NEXT_CURSOR].y + 1, Select[NEXT_CURSOR].x + 1);
		Result += combo_check(Select[TMP_CURSOR].y + 1, Select[TMP_CURSOR].x + 1);
		//�A��3����
		if (Result == 0)
		{
			int TmpBlock = Block[Select[NEXT_CURSOR].y +
				1][Select[NEXT_CURSOR].x + 1].image;
			Block[Select[NEXT_CURSOR].y + 1][Select[NEXT_CURSOR].x + 1].image =
				Block[Select[TMP_CURSOR].y + 1][Select[TMP_CURSOR].x + 1].image;
			Block[Select[TMP_CURSOR].y + 1][Select[TMP_CURSOR].x + 1].image = TmpBlock;
		}
		else
		{
			//�A��3�ȏ�u���b�N�ړ������ڍs
			Stage_State = 1;
		}
		//���ɃN���b�N�ł���悤�ɂ���
		ClickStatus = E_NONE;
	}
}

void FadeOutBlock(void)
{
	static int BlendMode = 255;
	int i, j;

	//�t�F�[�h�A�E�g��
	if (CheckSoundMem(FadeOutSE) == 0)
	{
		PlaySoundMem(FadeOutSE, DX_PLAYTYPE_BACK);
	}
	//�`��A���t�@�u�����h
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, BlendMode);
	for (i = 1; i < HEIGHT - 1; i++)
	{
		for (j = 1; j < WIDTH - 1; j++);
		{
			if (Block[i][j].image == 0)
			{
				DrawGraph(Block[i][j].x, Block[i][j].y,
					BlockImage[Block[i][j].backup], TRUE);
			}
		}
	}
	//�`�惂�[�h�m�[�u��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	BlendMode -= 5;

	if (BlendMode == 0)
	{
		BlendMode = 255;
		Stage_State = 2;
		StopSoundMem(FadeOutSE);
	}
}
/******
*****/
void MoveBlock(void)
{
	int i, j, k;
	//	�u���b�N�ړ���
	PlaySoundMem(MoveBlockSE, DX_PLAYTYPE_BACK);
	//���ړ�����
	for (i = 1; i < HEIGHT - 1; i++)
	{
		for (j = 1; j < WIDTH - 1; j++)
		{
			if (Block[i][j].image == 0)
			{
				for (k = i; k > 0; k--)
				{
					Block[k][j].image = Block[k - 1][j].image;
					Block[k - 1][j].image = 0;
				}
			}
		}
	}
	//��̃u���b�N��������
	for (i = 1; i < HEIGHT - 1; i++)
	{
		for (j = 1; j < WIDTH - 1; j++)
		{
				if (Block[i][j].image == 0)
				{
					Block[i][j].image = GetRand(7) + 1;
				}
		}
		//�A���`�F�b�N
		Stage_State = 3;
	}
}

/*****
******/
void CheckBlock(void)
{
	int Result = 0;
	int i, j;
	//�u���b�N�A��
	for (i = 1; i < HEIGHT - 1; i++)
	{
		for (j = 1; j < WIDTH - 1; j++)
		{
			Result += combo_check(i, j);
		}
	}
		//�A���������Ȃ�΃u���b�N�I��
		//�����łȂ���΃u���b�N�ړ��ֈڍs
	if (Result == 0)
		{
			//�N���A�`�F�b�N
			Stage_State = 4;
		}
		else
		{
			//�A��3�Ȃ�u���b�N�����ړ��ڍs
		Stage_State = 1;
	}

}
/***
****/
void CheckClear(void)
{
	int i;
	for (i = 0; i < ITEM_MAX; i++)
	{
		if (Item[i] >= Stage_Mission)
		{
			ClearFlag = TRUE;
			break;
		}
	}
	if (ClearFlag != TRUE)
	{
		Stage_State = 0;
	}
}
/******
*******/
int Get_StageState(void)
{
	return Stage_State;
}
/*******
********/
int Get_StageClearFlag(void)
{
	return ClearFlag;
}
/***
****/
int Get_StageScore(void)
{
	return Stage_Score;
}
/**
**/
void Set_StageMission(int mission)
{
	Stage_Mission += mission;
}
/**
***/
int combo_check(int y, int x)
{
	int ret = FALSE;
	//�c
	int CountH = 0;
	int ColorH = 0;
	save_block();
	combo_check_h(y, x, &CountH, &ColorH);
	if (CountH < 3)
	{
		restore_block();
	}
	//��
	int CountW = 0;
	int ColorW = 0;
	save_block();
	combo_check_w(y, x, &CountW, &ColorW);
	if (CountW < 3)
	{
		restore_block();
	}
	//3�ȏ�
	if ((CountH >= 3 || CountW >= 3))
	{
		if (CountH >= 3)
		{
			Item[ColorH - 1] += CountH;
			Stage_Score += CountH * 10;
		}
		if (CountW >= 3)
		{
			Item[ColorW - 1] += CountW;
			Stage_Score += CountW * 10;
		}
		ret = TRUE;
	}
	return ret;

}
/*
**/
void combo_check_h(int y, int x, int* cnt, int* col)
{
	int Color = 0;
	//�Ώۃu���b�N�O�g
	if (Block[y][x].image == 0)
	{
		return;
	}
	*col = Block[y][x].image;
	Color = Block[y][x].image;
	Block[y][x].image = 0;
	(*cnt)++;                                          

	if (Block[y + 1][x].image == Color)
	{
		combo_check_h(y + 1, x, cnt, col);
	}
	if (Block[y - 1][x].image == Color)
	{
		combo_check_h(y - 1, x, cnt, col);
	}
}
/**
***/
void combo_check_w(int y, int x, int* cnt, int* col)
{
	int Color = 0;
	//�Ώۃu���b�N�O�g
	if (Block[y][x].image == 0)
	{
		return;
	}
	*col = Block[y][x].image;
	Color = Block[y][x].image;
	Block[y][x].image = 0;
	(*cnt)++;

	if (Block[y][x + 1].image == Color)
	{
		combo_check_w(y, x + 1, cnt, col);
	}
	if (Block[y][x - 1].image == Color)
	{
		combo_check_w(y, x - 1, cnt, col);
	}
}
/**
**/
void save_block(void)
{
	int i, j;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			Block[i][j].backup = Block[i][j].image;
		}
	}
}
/**
***/
void restore_block(void)
{
	int i, j;
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			Block[i][j].image = Block[i][j].backup;
		}
	}
}



