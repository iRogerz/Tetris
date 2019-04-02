namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		bool check = true;
		int block0[4][4] = { { 0,3,3,0 },{ 0,0,3,0 },{ 0,0,3,0 },{ 0,0,0,0 } };// 7 個方塊 用數組表示 正「7」
		int block1[4][4] = { { 0,4,4,0 },{ 0,4,0,0 },{ 0,4,0,0 },{ 0,0,0,0 } };// 反「7」
		int block2[4][4] = { { 0,0,0,0 },{ 0,0,5,5 },{ 0,5,5,0 },{ 0,0,0,0 } };// 反「z」
		int block3[4][4] = { { 0,0,0,0 },{ 6,6,0,0 },{ 0,6,6,0 },{ 0,0,0,0 } };// 正「z」
		int block4[4][4] = { { 0,0,0,0 },{ 0,7,0,0 },{ 7,7,7,0 },{ 0,0,0,0 } };// 倒「T」
		int block5[4][4] = { { 0,0,0,0 },{ 0,8,8,0 },{ 0,8,8,0 },{ 0,0,0,0 } };// 正方形
		int block6[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 9,9,9,9 },{ 0,0,0,0 } };// 直條
		int BLOCK[4][4];//正在下落的方塊
		int block[4][4];//提示區的方塊
		int tem[4][4];//用4*4的方格來控制方塊的操作和顯示
		int scope[25][34] = { 0 };//操作的範圍 這裡要注意，一個方格是占兩個橫坐標單位的
		void random();
		void clear();
	protected:
		CAnimation animation;		// 擦子的動畫
		int x, y,time=0,i=0,j=0;	   // 擦子左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
	};
}