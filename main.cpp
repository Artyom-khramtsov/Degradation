#include "Lib/TXLib.h"
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


int main()
{

    bool GameOver = false;
    txCreateWindow (1280, 895);

    HDC  pic1 = txLoadImage ("��������/������ ���.bmp");
    HDC  pic2 = txLoadImage ("��������/�����.bmp");
    HDC  pic3 = txLoadImage ("��������/������.bmp");
    HDC  pic4 = txLoadImage ("��������/������.bmp");
    HDC  pic5 = txLoadImage ("��������/��������.bmp");

    while(GameOver == false)
    {
        txSetFillColor(TX_BLACK);
        txClear();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);
        txRectangle (50, 50, 300, 490);


        txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);

    txRectangle (740, 190, 940, 320);
    txTransparentBlt (txDC(), 740, 190, 200, 157, pic2, 0, 0, TX_WHITE);

    txRectangle (990, 190, 1190, 320);
    txTransparentBlt (txDC(), 990, 190, 240,160, pic3, 0, 0, TX_WHITE);

    txRectangle (740, 390, 940, 620);
    txTransparentBlt (txDC(), 740, 390, 200,200, pic4, 0, 0, TX_WHITE);

    txRectangle (990, 590, 1190, 820);
    txTransparentBlt (txDC(), 990, 390, 180,160, pic5, 0, 0, TX_WHITE);



        txRectangle(880,460,992,509);
          //txRectangle(880,460,992,509);

         if(txMouseX() >= 880 &&
               txMouseY() >= 460 &&
               txMouseX() <= 992 &&
               txMouseY() <= 509 &&
               txMouseButtons()== 1)
            {
                txDisableAutoPause();
                 GameOver = true;
            }

            if(txMouseX() >= 740 &&
               txMouseY() >= 190 &&
               txMouseX() <= 740 + 200 &&
               txMouseY() <= 190 + 200 &&
               txMouseButtons()== 1)
            {
                        txBitBlt (txDC(), 229, 379, 275,419, pic2, 0, 0);

            }

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

           txDrawText(747,78,1242,100,"���� ��������� � ���������� ");

        Win32::RoundRect (txDC(), 100, 200, 400, 500, 30, 30);

        txSleep(20);

    }
    txDeleteDC(pic1);
  txDeleteDC(pic2);
    return 0;
}
