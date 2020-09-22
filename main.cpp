#include "Lib/TXLib.h"
#include "windows.h"

struct Picture
{
    int x;
    int y;
    int width;
    int height;
    HDC pic;
    bool visible;
};

bool GameOver = false;
bool click (int x1, int x2)
{
    if (txMouseX
        () > x1 &&
        txMouseX()< x2)
{
return true;
}
else
    return false;
}
void exit ()
{

    if(GetAsyncKeyState(VK_MENU) &&  GetAsyncKeyState(VK_F4))
    {
         txDisableAutoPause();
         GameOver = true;
    }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
         txDisableAutoPause();
         GameOver = true;
        }
}
void menu ()
{
}    //���� �� ������������



int main()
{
    txCreateWindow (1280, 895);

    HDC  pic1 = txLoadImage ("��������/������ ���.bmp");

    Picture variants[10];
    variants[0] = {740, 190, 200,157, txLoadImage("��������/�����.bmp")};
    variants[1] = {990, 190, 267,287, txLoadImage("��������/������.bmp")};
    variants[2] = {740, 390, 234,234, txLoadImage("��������/������.bmp")};
    variants[3] = {990, 390, 252,189, txLoadImage("��������/��������.bmp")};
    variants[4] = {740, 590, 248,248, txLoadImage("��������/���� ������.bmp")};

    Picture centr[10];
    centr[0] = {458, 608, 200,157, txLoadImage("��������/�����.bmp"), false};
    centr[1] = {229, 379, 267,287, txLoadImage("��������/������.bmp"), false};
    centr[2] = {609, 479, 234,234, txLoadImage("��������/������.bmp"), false};
    centr[3] = {229, 379, 252,189, txLoadImage("��������/��������.bmp"), false};
    centr[4] = {320, 787, 248,248, txLoadImage("��������/���� ������.bmp"), false};


    while (GameOver == false)
    {
        txSetFillColor(TX_BLACK);
        txClear();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);
        txRectangle (50, 50, 300, 490);


        txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);

        txTransparentBlt (txDC(), variants[0].x, variants[0].y, variants[0].width, variants[0].height, variants[0].pic, 0, 0, TX_WHITE);

         for (int nomer = 0; nomer < 5; nomer = nomer + 1)
         {
            Win32::TransparentBlt (txDC(), variants[nomer].x,   variants[nomer].y, 100, 100, variants[nomer].pic, 0, 0, variants[nomer].width, variants[nomer].height, TX_WHITE);
         }


        txRectangle(933,638,1042,687);    // �����

          txDrawText(940,653,1031,676, "�����");
         if(txMouseX() >= 933 &&
               txMouseY() >= 638 &&
               txMouseX() <= 1042 &&
               txMouseY() <= 687 &&
               txMouseButtons()== 1)
            {
                txDisableAutoPause();
                 GameOver = true;
            }
         // ��������� ������ �� ����� (pic2)
         for (int nomer = 0; nomer < 5; nomer = nomer + 1)
         {

            if (txMouseX() >= variants[nomer].x &&
               txMouseY() >= variants[nomer].y &&
               txMouseX() <= variants[nomer].x + 100 &&
               txMouseY() <= variants[nomer].y + 100 &&
               txMouseButtons()== 1)
            {
                centr[nomer].visible = !centr[nomer].visible;
                txSleep(100);
            }
        }


         for (int nomer = 0; nomer < 5; nomer = nomer + 1)
         {
            if (centr[nomer].visible)

                Win32::TransparentBlt (txDC(), centr[nomer].x,   centr[nomer].y, 100, 100, variants[nomer].pic, 0, 0, variants[nomer].width, centr[nomer].height, TX_WHITE);
         }


           txDrawText(747,78,1242,100,"���� ��������� � ���������� ");

           txDrawText(885,146,1195,179,"������ ���������");

        txSleep(20);
        exit();

    }

        for (int nomer = 0; nomer < 5; nomer = nomer + 1)
         {
        txDeleteDC(variants[nomer].pic);
         }

        for(int nomer = 0; nomer < 5; nomer = nomer + 1)
         {
        txDeleteDC(centr[nomer].pic);
         }

         txDeleteDC(pic1);



    return 0;
}
