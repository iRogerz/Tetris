#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include<ctime>
#include<time.h>
#include<conio.h>
#include <windows.h>
#include<stdio.h>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + animation.Width();
	}

	int CEraser::GetY2()
	{
		return y + animation.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 312;
		const int Y_POS = 98;
		//const int X_POS = 14;
		//const int Y_POS = 0;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{
		IDB_BLOCKBLUE;
		IDB_BLOCKGREEN;
		IDB_BLOCKLIGHTBLUE;
		IDB_BLOCKORANGE;
		IDB_BLOCKPURPLE;
		IDB_BLOCKRED;
		IDB_BLOCKYELLOW;
		animation.AddBitmap(IDB_BITMAP5);
		/*animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));*/
	}

	void CEraser::OnMove()
	{

		random();
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				BLOCK[i][j] = block[i][j];//�N���ܰϪ�����ƲնǨ�U���������
			}
		}
		const int STEP_SIZE = 30;
		animation.OnMove();
		if (isMovingLeft)
		{
			x -= STEP_SIZE;
			/*int i, j;

			for (i = 0; i < 3; i++)

				for (j = 0; j < 4; j++)

				{

					if (1 == BLOCK[j][i] && (x + 2 * i - 1 < 2 || 1 == scope[x / 2 + i - 1][y + j]))

					{

						return;//�p�G����t �Ϊ̬O����w�g���F���

					}

				}

			for (i = 0; i < 4; i++)

				for (j = 0; j < 4; j++)

					if (1 == BLOCK[i][j])

					{

						SetXY(x + j * 2, y + i);

						printf(" ");//�⤧�e������

					}

			x -= 2;*/
		}		
		if (isMovingRight)
		{
			x += STEP_SIZE;
			/*int i, j;

			for (i = 3; i > 0; i--)

				for (j = 0; j < 4; j++)

				{

					if (1 == BLOCK[j][i] && (x + 2 * i + 2 > 30 || 1 == scope[x / 2 + i + 1][y + j]))

					{

						return;//�p�G����t �Ϊ̬O�k��w�g���F���

					}

				}
			for (i = 0; i < 4; i++)

				for (j = 0; j < 4; j++)

					if (1 == BLOCK[i][j])

					{

						SetXY(x + j * 2, y + i);

						printf(" ");//�⤧�e������

					}

			x += 2;*/
		}	
		if (isMovingUp)
		{
			int i, j;

			for (i = 0; i < 4; i++)

			{

				for (j = 0; j < 4; j++)

				{

					tem[i][j] = BLOCK[i][j];

					if (1 == BLOCK[i][j])

					{

						SetXY(x + j * 2, y + i);

						printf(" ");

					}

				}

			}

			for (i = 0; i < 4; i++)

			{

				for (j = 0; j < 4; j++)

				{

					BLOCK[j][3 - i] = tem[i][j];

				}

			}

			//�H�W������C

			//�U������������W�X�ج[�d��

			for (j = 0; j < 2; j++)

			{

				for (i = 0; i < 4; i++)

				{

					if (1 == BLOCK[i][j] && x < 2)

					{

						x += 2;

					}

					else if (1 == BLOCK[i][3 - j] && x > 24)

					{

						x -= 2;

					}

				}

			}

			//my_printblock();//���ध��ߧY��ܥX��
		}	
		if (isMovingDown)
		{
			y += STEP_SIZE;
			/*int i, j;
			if (true == check)
			{
				return;//����U������������
			}

			SetXY(x, y);

			for (i = 3; i > 0; i--)//�˴��Ӥ���ٯण��U��

				for (j = 0; j < 4; j++)

					if (3 == BLOCK[i][j] || BLOCK[i][j]==4 || BLOCK[i][j]==5 || BLOCK[i][j]==6 || BLOCK[i][j]==7 || BLOCK[i][j]==8 || BLOCK[i][j]==9)

					{

						if () //��̤U��άO�U���w�g�����

						{

							check = true;

							return;

						}

					}

			for (i = 0; i < 4; i++)

				for (j = 0; j < 4; j++)

					if (1 == BLOCK[i][j])

					{

						SetXY(x + j * 2, y + i);

						printf(" ");//��U���A�����H�e�����

					}

			y++;

			//my_printblock();//�b�U�@�����
		}		
		/*if (true == check)//����U����

		{

			for (i = 0; i < 4; i++)

			{

				for (j = 0; j < 4; j++)

				{

					if (1 == BLOCK[i][j])
						scope[x / 2 + j][y + i] = BLOCK[i][j];//��U���������ȵ��ާ@�Ϫ��Ʋ�
															//�o�̪�point_x���H2�O�]���@�Ӥp��l�e��Ӿ��
				}

			}

			//my_printblock();

			//clear();//�p�G���Y�@�溡�F�N����*/

		}
		//random();*/
	
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::random()
	{
		int i, j;

		switch (rand() % 7)

		{

		case 0:for (i = 0; i < 4; i++)

			for (j = 0; j < 4; j++)

				block[i][j] = block0[i][j];

			break;

		case 1: for (i = 0; i < 4; i++)

			for (j = 0; j < 4; j++)

				block[i][j] = block1[i][j];

			break;

		case 2: for (i = 0; i < 4; i++)

			for (j = 0; j < 4; j++)

				block[i][j] = block2[i][j];

			break;

		case 3: for (i = 0; i < 4; i++)

			for (j = 0; j < 4; j++)

				block[i][j] = block3[i][j];

			break;

		case 4: for (i = 0; i < 4; i++)

			for (j = 0; j < 4; j++)

				block[i][j] = block4[i][j];

			break;

		case 5: for (i = 0; i < 4; i++)

			for (j = 0; j < 4; j++)

				block[i][j] = block5[i][j];

			break;

		case 6: for (i = 0; i < 4; i++)

			for (j = 0; j < 4; j++)

				block[i][j] = block6[i][j];

			break;

		default:;

		}

		for (i = 0; i < 4; i++)

		{

			for (j = 0; j < 4; j++)

			{

				tem[i][j] = block[i][j];

			}

		}

		switch (rand() % 4)//�A�]�m�H�����઺��V

		{

		case 0:

			break;

		case 1: for (i = 0; i < 4; i++)//���ɰw90��

		{

			for (j = 0; j < 4; j++)

			{

				block[j][3 - i] = tem[i][j];

			}

		}

				break;

		case 2: for (i = 0; i < 4; i++)//��180��

		{

			for (j = 0; j < 4; j++)

			{

				block[3 - i][3 - j] = tem[i][j];

			}

		}

				break;

		case 3: for (i = 0; i < 4; i++)//��270��

		{
			for (j = 0; j < 4; j++)

			{
				block[3 - j][i] = tem[i][j];
			}
		}
				break;
		default:;

		}
	}

	void CEraser::clear()
	{
		int i, j, k, m = 0;

		for (i = y + 3; i >= y; i--)

		{

			for (j = 1; j < 16; j++)

			{

				if (0 == scope[j][i])

				{

					break;

				}

			}

			if (16 == j)

			{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

				m++;

				for (k = i; k>3; k--)

				{

					for (j = 1; j < 16; j++)

					{

						scope[j][k] = scope[j][k - 1];

						SetXY(j * 2, k);

						if (1 == scope[j][k])

						{

							printf("��");

						}

						else

						{

							printf(" ");

						}

					}

				}

				for (j = 1; j < 16; j++)

				{

					scope[j][4] = 0;

				}

				i++;

			}

		}

	}

	void CEraser::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
		/*int i, j;

		for (i = 0; i < 4; i++)

		{

			for (j = 0; j < 4; j++)

			{

				if (x / 2 + j > 0)

				{

					if (1 == scope[x / 2 + j][y + i])

					{

						//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

						SetXY(x + j * 2, y + i);

						printf("��");

					}

					else if (1 == BLOCK[i][j])

					{

						//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

						SetXY(x + j * 2, y + i);

						printf("��");

					}

				}

			}

		}*/
	}
}