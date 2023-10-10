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
int DropBlock_y;

int WaitTime;
int Stock_Flg;
int Generate_Flg;
int DeleteLine;
int SoundEffect[3];
