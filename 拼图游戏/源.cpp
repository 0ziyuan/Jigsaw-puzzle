/*����ƴͼ��һ���������Ϸ����һ��ͼ����Ϊ��ȵ�����������С���飬ȡ������һ��������λ��
���ö���Ŀո񻬶�����С���飬����ͼ���γ�ƴͼ����λʱ������ȡ���κ�С���飬����ȱ�ٵĿ�λ
����ͼ���е�С����ʹ�临ԭ��*/
/*�������к���������ң�Ȼ�������������ƴͼ��ԭ�����ֻ�ֱܷ������ո����ڵ��������ҵ�
�������ո�λ�ƶ����ж�ͼƬ��ԭ����ʾƴͼ���*/

/*Ԥ����ָ���ȡͷ�ļ�*/
#include"acllib.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*�궨����*/
#define WNDWIDTH 800
#define WNDHEIGHT 600
#define SIZE 200
#define ROW WNDHEIGHT/SIZE
#define COL WNDHEIGHT/SIZE

/*ȫ�ֱ�������*/
ACL_Image img[ROW* COL],preimg;
ACL_Sound clicksonud[ROW * COL], winsound;
int map[ROW][COL];
int r0,c0,temp;
char img_name[] = "1.jpg";
char son_name[] = "1.mp3";
boolean suc = true;

/*��������*/
void loadImages();//ͼƬ����
void loadSounds();//��Ч����
void initPos();//������Һ���
void MouseEvent(int x, int y, int button, int event);//��Ϸ����

/*������*/
int Setup()
{
    initWindow("ƴͼ��Ϸ", 0, 0, WNDWIDTH, WNDHEIGHT);
    loadSounds();//��Ч����
    loadImages();//ͼƬ����
    initPos();//������Һ���
    registerMouseEvent(MouseEvent);//��Ϸ����
    return 0;
}

/*ͼƬ����*/
void loadImages()
{
    loadImage("ԭͼƬ.jpg", &preimg);
	for (int i = 0; i < ROW * COL; ++i)
	{
		img_name[0] = i + 1 + '0';
		loadImage(img_name, &img[i]);
	}
//��ʼ��map�������飬ӳ��9��λ��
//֮���ͼƬ��������ֻ�ý���map�����е�ֵ������ʱȡ��ֵ����
    for (int i = 0; i <  ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            map[i][j] = i + j*ROW;
        } 
    }
}

/*��Ч����*/
void loadSounds()
{
    loadSound("��ĺ��.mp3",&winsound);
    for (int i = 0; i < ROW * COL; ++i)
    {
        son_name[0] = i + 1 + '0';
        loadSound(son_name, &clicksonud[i]);
    }
}

/*������Һ���*/
void initPos()
{
    srand((unsigned)time(NULL));
    int pos = 0;
    int i;
        r0=2,c0=2;
//�����������������switch�жϣ�ʹ�ÿհ׿�����Χ��Ӧ�Ŀ齻��
    for (i = 0; i < 100; i++)
    {
            pos = rand() % 4;
            switch (pos)
            {
            case 0:
                if ( (r0-1) >= 0)
                {
                    temp = map[r0][c0];
                    map[r0][c0] = map[r0-1][c0];
                    map[r0-1][c0] = temp;
                    r0--;
                    break;
                }
            case 1:
                if ((r0 + 1) <= 2)
                {
                    temp = map[r0][c0];
                    map[r0][c0] = map[r0 + 1][c0];
                    map[r0 + 1][c0] = temp;
                    r0++;
                    break;
                }
            case 2:
                if ((c0-1) >= 0)
                {
                    temp = map[r0][c0];
                    map[r0][c0] = map[r0][c0-1];
                    map[r0][c0-1] = temp;
                    c0--;
                    break;
                }
            case 3:
                if ((c0 + 1) <= 2)
                {
                    temp = map[r0][c0];
                    map[r0][c0] = map[r0][c0+1];
                    map[r0][c0+1] = temp;
                    c0++;
                    break;
                }
            default:
                break;
            }
    }
    beginPaint();
    putImageScale(&preimg, 600, 200, SIZE, SIZE);
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            putImageScale(&img[map[i][j]], i * SIZE, j * SIZE, SIZE, SIZE);
        }

    }
    endPaint();
}

/*��Ϸ����*/
void MouseEvent(int x, int y, int button, int event)
{
    int r, c;
    if (x<(WNDWIDTH-SIZE)&&(button == LEFT_BUTTON && event == BUTTON_DOWN))
    {
        c = y / SIZE;
        r = x / SIZE;
        if ((r==r0&&c==c0-1)||(r==r0&&c==c0+1)||   //ͨ�������ʱ��������հ׿�����ȶԣ��ж��Ƿ�ɽ���
            (c==c0&&r==r0-1)||(c==c0&&r==r0+1))
        {
            playSound(clicksonud[map[r][c]], 0);
            map[r0][c0] = map[r][c];
            map[r][c] = ROW*COL -1;
        beginPaint();
            putImageScale(&img[map[r0][c0]], r0 * SIZE, c0 * SIZE, SIZE, SIZE);
            putImageScale(&img[map[r][c]], r * SIZE,c  * SIZE, SIZE, SIZE);
        endPaint();
            r0 = r;
            c0 = c;
        }
    }
    //�ж�ƴͼ�Ƿ�ԭ
    int count = 0;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if (map[i][j] == i + j * ROW)//��map�����е�ֵ���ʼֵ�Ƚϣ��Ӷ��ж�
                count++;
    if (count == ROW * COL)
    {
        if (suc)
        {
            char str[50];
            playSound(winsound, 1);
            sprintf_s(str, 50, "ƴͼ���");
            beginPaint();
            setTextSize(40);
            paintText(WNDWIDTH - 180, 20, str);//��������
            endPaint();
            suc = false;
        }
    }
}