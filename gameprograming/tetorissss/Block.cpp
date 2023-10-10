#include  "Block.h"
#include "DxLib.h"
#include "InputControl.h"

#define FIELD_HEIGHT		(21)
#define FIELD_WIDTH				(12)
#define BLOCK_TROUT_SIZE	(4)
#define BLOCK_SIZE				(36)
#define BLOCK_TYPE_MAX			(7)
#define BLOCK_NEXT_POS_X	(700)
#define BLOCK_NEXT_POS_Y	(500)
#define BLOCK_STOCK_POS_X	(500)
#define BLOCK_STOCK_POS_Y	(350)
#define DROP_BLOCK_INIT_X	(4)
#define DROP_BLOCK_INIT_Y	(-1)
#define DROP_SPEED				(60)
#define TURN_CROCKWICE			(0)
#define TURN_ANTICROCKWICE	(1)

enum BLOCK_STATE
{
	E_BLOCK_EMPTY,
	E_BLOCK_LIGHT_BLUE,
	E_BLOCK_YELLOW_GREEN,
	E_BLOCK_YELLOW,
	E_BLOCK_ORANGE,
	E_BLOCK_BLUE,
	E_BLOCK_PINK,
	E_BLOCK_RED,
	E_BLOCK_GLAY,
	E_BLOCK_WALL,
	E_BLOCK_IMAGE_MAX
};

const int C_BLOCK_TABLE[BLOCK_TYPE_MAX][BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE] = {
	{
	{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}
},
{
	{0,0,0,0},
	{0,0,0,0},
	{2,2,2,2},
	{0,0,0,0}
},
{
	{0,0,0,0},
	{3,0,0,0},
	{3,3,3,0},
	{0,0,0,0}
},
{
	{0,0,0,0},
	{0,0,0,4},
	{0,4,4,4},
	{0,0,0,0}
},
{
	{0,0,0,0},
	{0,5,5,0},
	{0,0,5,5},
	{0,0,0,0}
},
{
	{0,0,0,0},
	{0,6,6,0},
	{6,6,0,0},
	{0,0,0,0}
},
{
	{0,0,0,0},
	{0,7,0,0},
	{7,7,7,0},
	{0,0,0,0}
},
};

int BlockImage[E_BLOCK_IMAGE_MAX];
BLOCK_STATE Field[FIELD_HEIGHT][FIELD_WIDTH];
BLOCK_STATE Next[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];
BLOCK_STATE Stock[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];
BLOCK_STATE DropBlock[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];

int DropBlock_X;
int DropBlock_Y;

int WaitTime;
int Stock_Flg;
int Generate_Flg;
int DeleteLine;
int SoundEffect[3];


void create_field(void);
void create_block(void);
void move_block(void);
void change_block(void);
void turn_block(int clockwise);
int check_overlap(int x, int y);
void lock_block(int x, int y);
void check_line(void);

int Block_Initialize(void)
{
	int ret = 0;
	int i = 0;

	ret = LoadDivGraph("images/block.png", E_BLOCK_IMAGE_MAX, 10, 1, 
		BLOCK_SIZE, BLOCK_SIZE, BlockImage);

	SoundEffect[0] = LoadSoundMem("sounds/SE3.mp3");
	SoundEffect[1] = LoadSoundMem("sounds/SE4.mp3");
	SoundEffect[2] = LoadSoundMem("sounds/SE5.wav");

	ChangeVolumeSoundMem(150, SoundEffect[0]);
	ChangeVolumeSoundMem(150, SoundEffect[1]);
	ChangeVolumeSoundMem(130, SoundEffect[2]);

	create_field();
	create_block();

	WaitTime = 0;

	Stock_Flg = FALSE;

	Generate_Flg = TRUE;

	DeleteLine = 0;

	for (i = 0; i < 3; i++)
	{
		if (SoundEffect[i] == -1)
		{
			ret = -1;
			break;
		}
	}
	return ret;
}


void Block_Update(void)
{
	move_block();

	if ((GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) == TRUE) ||
		(GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) == TRUE))
	{
		if (Generate_Flg == TRUE)
		{
			change_block();
		}
	}
	if ((GetButtonDown(XINPUT_BUTTON_A) == TRUE) ||
		(GetButtonDown(XINPUT_BUTTON_Y) == TRUE))
	{
		turn_block(TURN_ANTICROCKWICE);
	}
	if ((GetButtonDown(XINPUT_BUTTON_B) == TRUE) ||
		(GetButtonDown(XINPUT_BUTTON_X) == TRUE))
	{
		turn_block(TURN_CROCKWICE);
	}
	WaitTime++;
	if (WaitTime > DROP_SPEED)
	{
		if (check_overlap(DropBlock_X, DropBlock_Y + 1) == TRUE)
		{
			DropBlock_Y++;
		}
		else
		{
			lock_block(DropBlock_X, DropBlock_Y);

			check_line();

			create_block();
		}
		WaitTime = 0;
	}
}


void Block_Draw(void)
{
	int i, j;

	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++)
		{
			if (Field[i][j] != E_BLOCK_WALL)
			{
				DrawGraph(j * BLOCK_SIZE, i * BLOCK_SIZE, BlockImage[Field[i][j]],
					TRUE);
			}
		}
	}
	for (i = 0; i < BLOCK_TROUT_SIZE; i++)
	{
		for (j = 0; j < BLOCK_TROUT_SIZE; j++)
		{
			DrawGraph(BLOCK_SIZE * j + BLOCK_NEXT_POS_X, BLOCK_SIZE * i +
				BLOCK_NEXT_POS_Y, BlockImage[Next[i][j]], TRUE);
			DrawGraph(BLOCK_SIZE * j + BLOCK_STOCK_POS_X, BLOCK_SIZE * i +
				BLOCK_STOCK_POS_Y, BlockImage[Stock[i][j]], TRUE);
		}
	}
	for (i = 0; i < BLOCK_TROUT_SIZE; i++)
	{
		for (j = 0; j < BLOCK_TROUT_SIZE; j++)
		{
			DrawGraph((DropBlock_X + j) * BLOCK_SIZE, (DropBlock_Y + 1) * BLOCK_SIZE,
				BlockImage[DropBlock[i][j]], TRUE);
		}
	}

}

int Get_GenerateFlg(void)
{

}