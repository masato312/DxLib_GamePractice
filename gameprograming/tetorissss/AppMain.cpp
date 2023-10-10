#include "DxLib.h"
#include "FreamControl.h"
#include "sceneManager.h"
#include "InputControl.h"


#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280
#define SCREEN_COLORBIT		(32)
#define FONT_SIZE	(20)


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE Hprevinstance, _In_
	LPSTR lpCmdLINE, _In_ int nShowCmd)
{	//タイトルを変更
	SetMainWindowMode(TRUE);

	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	//ウィンドウサイズ
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);

	//Dxライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//フレーム制御処理
	FreamControl_Initialize();

	//シーン管理処理
	SceneManager_Initialize(E_TITLE);

	//描画先画面　裏
	SetDrawScreen(DX_SCREEN_BACK);

	//文字サイズ設定
	SetFontSize(FONT_SIZE);

	//ゲームループ
	while (ProcessMessage() == 0 && GetExitButton() != TRUE && ErrorCheck() ==
		D_NORMALITY)
	{
		//フレーム制御処理
		FreamControl_Update();

		//画面初期化
		ClearDrawScreen();

		//入力制御更新処理
		InputControl_Update();

		//シーン管理機能処理
		SceneManager_Update();

		//シーン管理機能描画
		SceneManager_Draw();

		//裏画面　表反映
		ScreenFlip();
	}
	//DXライブラリ使用の終了処理
	DxLib_End();
	return 0;
}