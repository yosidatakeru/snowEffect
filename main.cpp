#include <Novice.h>

const char kWindowTitle[] = "LE2B_ヨシダ_タケル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	int SnowMax = 960;
	int coverSnowpPosx[960 ];
	int coverSnowpPosy[960];
	int coverSnowpSize[960];
	int coverSnowpDelete[960];
	int snowpilesup[960];
	int snowCoverMax = 690;
	int pushSnowPosx = 30;
	int pushSnowPosy = 3;
	int legPosx=0;
	int legPosy = 0;
	int legSize = 50;
	int speed = 5;
	int playerCenterPosx = 0;
	int playerCenterPosy = 0;
	int coverSnowpx = 0;
	int coverSnowpy = 0;
	int count = 0;
	
	for (int i = 0; i < SnowMax; i++)
	{
		coverSnowpPosx[i] = 0;
		coverSnowpPosy[i] = 720;
		coverSnowpSize[i] = 5;
		snowpilesup[i] = 0;
		coverSnowpDelete[i] = 0;
	}
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 800, 720);
	

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		
		playerCenterPosx = legPosx + 25;
		playerCenterPosy = legPosy + 25;
		//legPosy += 10;
		//足の操作
		if (legPosy + 50 > 720)
		{
			legPosy = 670;
		}
		if (keys[DIK_W])
		{

			legPosy-=speed;
		}
		if (keys[DIK_A])
		{

			legPosx -= speed;
		}
		if (keys[DIK_S])
		{

			legPosy += speed;
		}
		if (keys[DIK_D])
		{
			legPosx += speed;
		}

		

		for (int i = 0; i < SnowMax; i++)
		{
			//雪の最大積雪量
			if (coverSnowpPosy[i] < snowCoverMax)
			{
				coverSnowpPosy[i] += 9;
			}

			//雪とプレイヤーの当たり判定
			if (coverSnowpPosx[i] <= legPosx + legSize &&
				legPosx <= coverSnowpPosx[i] + coverSnowpSize[i] &&
				coverSnowpPosy[i] <= legPosy + legSize &&
				legPosy <= coverSnowpPosy[i] + coverSnowpSize[i])
			{
				
				
				//左
				if ( playerCenterPosx > coverSnowpPosx[i])
				{
					 coverSnowpPosx[i] -= pushSnowPosx;
					 coverSnowpPosy[i] -= pushSnowPosy;
				}
				//右
				if (playerCenterPosx < coverSnowpPosx[i])
			    {
					coverSnowpPosx[i] += pushSnowPosx;
					coverSnowpPosy[i] -= pushSnowPosy;
				}
				//真ん中
				if (playerCenterPosx == coverSnowpPosx[i])
				{
					coverSnowpDelete[i] = 1;
				}

			}
		}
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//雪の描画
		for (int i = 0; i < 960; i++)
		{
			
			if (snowpilesup[i] == 0)
			{
				coverSnowpPosx[i] += coverSnowpx;
				coverSnowpPosy[i] -= coverSnowpy ;
			}
			coverSnowpx += coverSnowpSize[i]  ;
			if (count >= 160)
			{
				coverSnowpy += coverSnowpSize[i];
				coverSnowpx = 0;
				count = 0;
			}
			count++;
			snowpilesup[i] =1;
			if (coverSnowpDelete[i] == 0) 
			{
				Novice::DrawBox(coverSnowpPosx[i], coverSnowpPosy[i], coverSnowpSize[i], coverSnowpSize[i], 0.0f, 0xFFFFFFFF, kFillModeSolid);
			}
			
		}

		Novice::DrawBox(legPosx, legPosy, legSize, legSize, 0.0f, RED, kFillModeSolid);
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
