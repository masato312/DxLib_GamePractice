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
{	//�^�C�g����ύX
	SetMainWindowMode(TRUE);

	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);

	//Dx���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//�t���[�����䏈��
	FreamControl_Initialize();

	//�V�[���Ǘ�����
	SceneManager_Initialize(E_TITLE);

	//�`����ʁ@��
	SetDrawScreen(DX_SCREEN_BACK);

	//�����T�C�Y�ݒ�
	SetFontSize(FONT_SIZE);

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && GetExitButton() != TRUE && ErrorCheck() ==
		D_NORMALITY)
	{
		//�t���[�����䏈��
		FreamControl_Update();

		//��ʏ�����
		ClearDrawScreen();

		//���͐���X�V����
		InputControl_Update();

		//�V�[���Ǘ��@�\����
		SceneManager_Update();

		//�V�[���Ǘ��@�\�`��
		SceneManager_Draw();

		//����ʁ@�\���f
		ScreenFlip();
	}
	//DX���C�u�����g�p�̏I������
	DxLib_End();
	return 0;
}