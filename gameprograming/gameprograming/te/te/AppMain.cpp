#include "DxLib.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE Hprevinstance, _In_
	LPSTR lpCmdLINE, _In_ int nShowCmd)
{

	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);


	//Dx���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return -1;
	}


	//���͑ҋ@
	WaitKey();


	//DX���C�u�����g�p�̏I������
	DxLib_End();
	return 0;

}