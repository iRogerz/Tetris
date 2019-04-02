

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// csie��logo
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void GetY();
		void gotoxy(int x,int y);
		int map[20][10];
		bool check = false;
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
		void OnKeyDown(UINT);
		void random();
		void clear();
	protected:
		CMovingBitmap gray1, gray2,blue,green,lightblue,orange,purple,red,yellow;
		int x=0, y=4;
		const int X, Y;
		const int MW, MH;
	};
	class CGameMap2
	{
	public:
		CGameMap2();
		void LoadBitmap();
		void OnShow();
	protected:
		CMovingBitmap gray10, gray20;
		int map[20][10];
		const int X, Y;
		const int MW, MH;
	};
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);    // �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CGameMap  gamemap;
		CGameMap2 gamemap2;
		const int		NUMBALLS;	// �y���`��
		CMovingBitmap   practice;
		int picX, picY;
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CBall			*ball;		// �y���}�C
		CMovingBitmap	corner;		// ������
		CMovingBitmap	corner2;	// ������
		CEraser			eraser;		// ��l
		CInteger		hits_left;	// �ѤU��������
		CBouncingBall   bball;		// ���мu�����y
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};

}