
#include "GameMap2.h"
#include "GameMap.h"
#include <time.h>
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
        CGameStateInit(CGame* g);
        void OnInit();  								// �C������Ȥιϧγ]�w
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
        void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
    protected:
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
    private:
        CMovingBitmap logo;								// �C���}�l�e��
        CMovingBitmap   keyboard,instruction;
        bool IfKeyboard = false;
		bool IfInstruction = false;
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState {
    public:
        CGameStateRun(CGame* g);
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
        ShowNext shownext;
        Score score;
        Hold hold;
        ShowNext2 shownext2;
        Score2 score2;
        Hold2 hold2;
        const int		NUMBALLS;	// �y���`��
        int picX, picY, counter2 = 0;
        CMovingBitmap   backgroundcut;
        CMovingBitmap	background;	// �I����
        CMovingBitmap   player1win;
        CMovingBitmap   player2win;
        CMovingBitmap   tie;
        CMovingBitmap   combo1,combo2, combo3, combo4, combo5, combo6, combo7, combo8, combo9, combo10, combo11, combo12; //combo��
        CMovingBitmap	help;		// ������
        CMovingBitmap	corner;		// ������
        CMovingBitmap	corner2;	// ������
        CInteger		hits_left;	// �ѤU��������
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState {
    public:
        CGameStateOver(CGame* g);
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void OnInit();
    protected:
        void OnMove();		// ���ʹC������
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
    private:
        int counter;	// �˼Ƥ��p�ƾ�
        int p1 = 0;
};

}