#include "RankingScene.h"
#include "DxLib.h"
#include "InputControl.h"
#include "SceneManager.h"

#define RANKING_FILE		("dat/rankingdata.csv")
#define RANKING_MAX				(10)
#define RANKING_NAME_LEN	(11)

typedef struct
{
	int rank;
	char name[RANKING_NAME_LEN];
	int score;
}T_RANKING;

typedef struct
{
	int x;
	int y;
}T_CURSOR;

T_RANKING Ranking_Data[RANKING_MAX];
T_RANKING New_Score;
int DispMode;

T_CURSOR Cursor;
int name_num;

void file_read(void);
void file_write(void);
void ranking_sort(void);
void ranking_input_name(void);
void ranking_input_name_draw(void);

int RankingScene_Initialize(void)
{
	int ret = 0;

	file_read();

	switch (DispMode)
	{
	case RANKING_INPUT_MODE:
		Cursor.x = 0;
		Cursor.y = 0;
		name_num = 0;
		break;
	case RANKING_DISP_MODE:
	default:

		break;
	}
	return ret;
}

void RankingScene_Update(void)
{
	switch (DispMode)
	{
	case RANKING_INPUT_MODE:
		ranking_input_name();
		break;
	case RANKING_DISP_MODE:
	default:
		if (GetButtonDown(XINPUT_BUTTON_B))
		{
			Change_Scene(E_TITLE);
		}
		break;
	}
}

void RankingScene_Draw(void)
{
	int i;

	switch (DispMode)
	{
	case RANKING_INPUT_MODE:
		ranking_input_name_draw();
		break;
	case RANKING_DISP_MODE:
	default:
		for (i = 0; i < RANKING_MAX; i++)
		{
			DrawFormatString(20, 10 + (i * 25), GetColor(255, 255, 255),
				"%2d,%10s,%10d", Ranking_Data[i].rank, Ranking_Data[i].name,
				Ranking_Data[i].score);
		}
		break;
	}
}

void Set_RankingMode(int mode)
{
	DispMode = mode;
}


void Set_RankingScore(int score)
{
	New_Score.score = score;
}

void file_read(void)
{
	FILE* fp = NULL;
	int i;

	OutputDebugString("�t�@�C����ǂ݂��݂܂�");
	fopen_s(&fp, RANKING_FILE, "r");

		if (fp == NULL)
		{
			OutputDebugString("�t�@�C����ǂݍ��߂܂���");
			OutputDebugString("�t�@�C���𐶐����܂�");
			file_write();
		}
		else
		{
			for (i = 0; i < RANKING_MAX; i++)
			{
				fscanf_s(fp, "%2d,%[^,],%10d\n", &Ranking_Data[i].rank,
					Ranking_Data[i].name, RANKING_NAME_LEN, &Ranking_Data[i].score);

			}
			fclose(fp);
	}
}

void file_write(void)
{
	FILE* fp = NULL;
	int i;

	OutputDebugString("�t�@�C�����������݂܂�");
	fopen_s(&fp, RANKING_FILE, "w");

	if (fp == NULL)
	{
		OutputDebugString("�t�@�C�����������߂܂���");
	}
	else{
		for (i = 0; i < RANKING_MAX; i++)
		{
			fprintf(fp, "%2d,%s,%10d\n", Ranking_Data[i].rank,
				Ranking_Data[i].name, Ranking_Data[i].score);
		}
		fclose(fp);
	}
}
void ranking_sort(void)
{
	int i, j;
	T_RANKING tmp;

	Ranking_Data[RANKING_MAX - 1] = New_Score;

	for (i = 0; i < RANKING_MAX; i++) {
		for (j = i + 1; j < RANKING_MAX; j++) {
			if (Ranking_Data[i].score < Ranking_Data[j].score) {
				tmp = Ranking_Data[i];
				Ranking_Data[i] = Ranking_Data[j];
				Ranking_Data[j] = tmp;
			}
		}
	}
	for (i = 0; i < RANKING_MAX; i++) {
		Ranking_Data[i].rank = i + 1;
	}
	file_write();
}

void ranking_input_name(void) {
	int c;

	if (GetButtonDown(XINPUT_BUTTON_DPAD_LEFT) == TRUE) {
		if (Cursor.x > 0) {
			Cursor.x--;
		}
	}
	if (GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT) == TRUE) {
		if (Cursor.x < 12) {
			Cursor.x++;
		}
	}
	if (GetButtonDown(XINPUT_BUTTON_DPAD_UP) == TRUE) {
		if (Cursor.y > 0) {
			Cursor.y--;
		}
	}
	if (GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) == TRUE) {
		if (Cursor.y < 4) {
			Cursor.y++;
		}
	}
	if (GetButtonDown(XINPUT_BUTTON_B) == TRUE) 
	{
		if (Cursor.y < 2) 
		{
			c = 'a' + Cursor.x + (Cursor.y * 13);
			New_Score.name[name_num++] = c;
		}
		else if (Cursor.y < 4)
		{
			c = 'A' + Cursor.x + ((Cursor.y - 2) * 13);
			New_Score.name[name_num++] = c;
		}
		else
		{
			if (Cursor.x < 10)
			{
				c = '0' + Cursor.x;
				New_Score.name[name_num++] = c;
			}
			else if (Cursor.x == 10)
			{
				name_num--;
				New_Score.name[name_num] = '\n';
			}
			else
			{
				DispMode = RANKING_DISP_MODE;
				ranking_sort();
			}
		}
	}
}

void ranking_input_name_draw(void)
{
	int i;

	SetFontSize(40);
	DrawFormatString(300, 150, GetColor(255, 255, 255), "���O����͂��Ă�������");
	for (i = 0; i < 26; i++)
	{
		DrawFormatString((i % 13 * 50) + 300, (i / 13 * 50) + 330, GetColor(255, 255,
			255), "%-3c", 'a' + i);
		DrawFormatString((i % 13 * 50) + 300, (i / 13 * 50) + 430, GetColor(255, 255,
			255), "%-3c", 'A' + i);
	}
	for (i = 0; i < 10; i++)
	{
		DrawFormatString((i % 13 * 50) + 300, (i / 13 * 50) + 530, GetColor(255, 255,
			255), "%-3c", '0' + i);
	}
	DrawFormatString(300, 220, GetColor(255, 255, 255), ">%s", New_Score.name);
	SetFontSize(20);

	DrawBox((Cursor.x * 50) + 290, (Cursor.y * 50) + 330,
		(Cursor.x * 50) + 330, (Cursor.y * 50) + 370,
		GetColor(255, 255, 255), FALSE);
}