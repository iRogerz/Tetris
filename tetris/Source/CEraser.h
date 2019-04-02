namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		bool check = true;
		int block0[4][4] = { { 0,3,3,0 },{ 0,0,3,0 },{ 0,0,3,0 },{ 0,0,0,0 } };// 7 �Ӥ�� �μƲժ�� ���u7�v
		int block1[4][4] = { { 0,4,4,0 },{ 0,4,0,0 },{ 0,4,0,0 },{ 0,0,0,0 } };// �ϡu7�v
		int block2[4][4] = { { 0,0,0,0 },{ 0,0,5,5 },{ 0,5,5,0 },{ 0,0,0,0 } };// �ϡuz�v
		int block3[4][4] = { { 0,0,0,0 },{ 6,6,0,0 },{ 0,6,6,0 },{ 0,0,0,0 } };// ���uz�v
		int block4[4][4] = { { 0,0,0,0 },{ 0,7,0,0 },{ 7,7,7,0 },{ 0,0,0,0 } };// �ˡuT�v
		int block5[4][4] = { { 0,0,0,0 },{ 0,8,8,0 },{ 0,8,8,0 },{ 0,0,0,0 } };// �����
		int block6[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 9,9,9,9 },{ 0,0,0,0 } };// ����
		int BLOCK[4][4];//���b�U�������
		int block[4][4];//���ܰϪ����
		int tem[4][4];//��4*4�����ӱ��������ާ@�M���
		int scope[25][34] = { 0 };//�ާ@���d�� �o�̭n�`�N�A�@�Ӥ��O�e��Ӿ�г�쪺
		void random();
		void clear();
	protected:
		CAnimation animation;		// ���l���ʵe
		int x, y,time=0,i=0,j=0;	   // ���l���W���y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	};
}