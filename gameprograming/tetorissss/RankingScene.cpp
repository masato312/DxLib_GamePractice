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
	defaule:

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

void Set_rankingMode(int mode)
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

	OutputDebugString("ファイルを読みこみます");
	fopen_s(&fp, RANKING_FILE, "r")

		if (fp == NULL)
		{
			OutputDebugString("ファイルを読み込めません");
			OutputDebugString("ファイルを生成します");
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

page 4 hanbun