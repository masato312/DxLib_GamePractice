#include <DxLib.h>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE Hprevinstance, _In_
	LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)

	{
		return -1;
	}

	//äÁñ //
	DrawCircle(320, 240, 100, GetColor(20, 100, 190), TRUE);


	//äÁÇÃîíÇ¢ïîï™ÇÃÇ‚Ç¬//
	DrawCircle(320, 260, 82, GetColor(255, 255, 255), TRUE);


	//ê^Ç¡ê‘Ç»Ç®ï@//
	DrawCircle(320, 220, 10, GetColor(255, 0, 0), TRUE);

	//îíñ⁄
	DrawOval(305, 200, 10, 20, GetColor(255, 255, 225), TRUE);
	DrawOval(335, 200, 10, 20, GetColor(255, 255, 225), TRUE);
	//çïñ⁄
	DrawOval(310, 200, 5, 10, GetColor(0, 0, 0), TRUE);
	DrawOval(330, 200, 5, 10, GetColor(0, 0, 0), TRUE);

	DrawOval(312, 200, 2, 5, GetColor(255, 255, 225), TRUE);
	DrawOval(328, 200, 2, 5, GetColor(255, 255, 225), TRUE);



	WaitKey();


	DxLib_End();


	return 0;

}