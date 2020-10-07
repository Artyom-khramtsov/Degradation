#include "Lib/TXLib.h"
#include "windows.h"
int n_active ;
struct Picture
{
    int x;
    int y;
    int width;
    int height;
    HDC pic;
    bool visible;
    const char* category;
};
struct Objects
{
    int x;
    int y;

};

bool GameOver = false;
/*bool click (int x1, int x2 , int y1, int y2)
{
   if ( txMouseX() >= x1 &&
               txMouseY() >= y1 &&
               txMouseX() <= x2 &&
               txMouseY() <= y2 &&
               txMouseButtons()== 1);
               {
               })
{
*/

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
}    //пока не используется



int main()
{
    txTextCursor (false);

    txCreateWindow (1280, 895);
    const char* active_category;
    HDC  pic1 = txLoadImage ("Картинки/задний фон.bmp");
    const int speed_x = 1;
    const int speed_y = 1;
    const int pic_width = 30;
    const int pic_height = 30;


    const int N_VARS = 6;
    Picture variants[N_VARS];
    variants[0] = {780, 240, 200,157, txLoadImage("Картинки/ботан.bmp"),false, "Ученики"};
    variants[1] = {920, 250, 267,287, txLoadImage("Картинки/фанера.bmp"),false, "Ученики"};
    variants[2] = {780, 410, 234,234, txLoadImage("Картинки/бревно.bmp"),false, "Ученики"};
    variants[3] = {920, 410, 252,189, txLoadImage("Картинки/картошка.bmp"),false, "Ученики"};
    variants[4] = {780, 240, 248,248, txLoadImage("Картинки/злая училка.bmp"),false,"Учителя"};
    variants[5] = {930, 230, 225,225, txLoadImage("Картинки/Учитель по труду.bmp"),false,"Учителя"};

    Picture centr[1000];
    int n_pics = 0;


    Objects mesto [8];
    mesto[0] = {247, 352};
    mesto[1] = {322, 344};
    mesto[2] = {383, 356};
    mesto[3] = {449, 356};
    mesto[4] = {246, 490};
    mesto[5] = {309, 488};
    mesto[6] = {385, 490};
    mesto[7] = {449, 491};

    /*Objects parta [5];
    parta[0] = {219, 330, 353,377};
    parta[1] = {218, 466, 352,515};
    parta[2] = {217, 467, 354,515};
    parta[4] = {357, 467, 491,515};
*/
    Objects stol_ychitela [0];
    stol_ychitela[0]  = {412, 115};



    while (GameOver == false)
    {

        txSetFillColor(TX_BLACK);
        txClear();
        txBegin();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);
        txRectangle (50, 50, 300, 490);



        txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);
        for (int nomer = 0; nomer < n_pics; nomer = nomer + 1)   // определение активного персонажа
        {
            if (txMouseX() >= centr[nomer].x &&
               txMouseY() >= centr[nomer].y &&
               txMouseX() <= centr[nomer].x + pic_width  &&
               txMouseY() <= centr[nomer].y + pic_height &&
               txMouseButtons()== 1)
            {
                n_active = nomer;
            }
        }

        for (int nomer = 0; nomer < 8; nomer = nomer + 1)   // телепорт на парту
        {
            txRectangle (mesto[nomer].x, mesto[nomer].y, mesto[nomer].x + 30, mesto[nomer].y + 30);

            if (txMouseX() >= mesto[nomer].x &&
               txMouseY() >= mesto[nomer].y &&
               txMouseX() <= mesto[nomer].x + 30  &&
               txMouseY() <= mesto[nomer].y + 30 &&
               txMouseButtons()== 1 && centr[n_active].visible)
            {
               centr[n_active].x  = mesto[nomer].x ;
               centr[n_active].y = mesto[nomer].y ;
            }
        }


        txRectangle (stol_ychitela[0].x, stol_ychitela[0].y, stol_ychitela[0].x + 30, stol_ychitela[0].y + 30);

            if (txMouseX() >= stol_ychitela[0].x &&  // телепорт на стол учителя
               txMouseY() >= stol_ychitela[0].y &&
               txMouseX() <= stol_ychitela[0].x + 30  &&
               txMouseY() <= stol_ychitela[0].y + 30 &&
               txMouseButtons()== 1 && centr[n_active].visible)
            {
               centr[n_active].x  = stol_ychitela[0].x ;
               centr[n_active].y = stol_ychitela[0].y ;
            }

        //Движение
        {
        if(GetAsyncKeyState(VK_LEFT) && centr[n_active].visible)
        {
            centr[n_active].x = centr[n_active].x  -speed_x;
        }

        if(GetAsyncKeyState(VK_RIGHT) && centr[n_active].visible)
        {
            centr[n_active].x = centr[n_active].x  +speed_x;
        }

        if(GetAsyncKeyState(VK_UP) && centr[n_active].visible )
        {
            centr[n_active].y = centr[n_active].y  -speed_y;
        }

        if(GetAsyncKeyState(VK_DOWN) && centr[n_active].visible  )
        {
            centr[n_active].y = centr[n_active].y  +speed_y;
        }
        }

        //Рисование вариантов
         for (int nomer = 0; nomer < N_VARS; nomer = nomer + 1)
         {
             if (variants[nomer].category == active_category){
                Win32::TransparentBlt (txDC(), variants[nomer].x,   variants[nomer].y, 100, 100, variants[nomer].pic, 0, 0, variants[nomer].width, variants[nomer].height, TX_WHITE);
             }
        }

        txRectangle(933,638,1042,687);    // выход

          txDrawText(940,653,1031,676, "Выход");
         if(txMouseX() >= 933 &&
               txMouseY() >= 638 &&
               txMouseX() <= 1042 &&
               txMouseY() <= 687 &&
               txMouseButtons()== 1)
            {
                txDisableAutoPause();
                 GameOver = true;
            }


        //Рисование центральных картинок
        for (int nomer = 0; nomer < n_pics; nomer = nomer + 1)
        {
            if (centr[nomer].visible)
            {
                Win32::TransparentBlt (txDC(), centr[nomer].x,   centr[nomer].y, pic_width, pic_height, centr[nomer].pic, 0, 0, centr[nomer].width, centr[nomer].height, TX_WHITE);
            }
        }

           txDrawText(747,78,1242,100,"Игра находится в разработке ");

           txDrawText(885,146,1195,179,"Выбери персонажа");



            if (active_category == "Учителя")
                txSetColor(TX_BLUE);
            else
                txSetColor(TX_WHITE);
            txDrawText(1114,180,1269,222,"Учителя");


            if (active_category == "Ученики")
                txSetColor(TX_BLUE);
            else
                txSetColor(TX_WHITE);
           txDrawText(736,184,885,221,"Ученики");


            if(txMouseX() >= 1107 &&    //(1107, 24, 1241, 66  // ñïðàâêà
               txMouseY() >= 24 &&
               txMouseX() <= 1241 &&
               txMouseY() <= 66 &&
               txMouseButtons()== 1)
            {

            }


            //Выбор категории
            if (txMouseX() >= 1114 &&
               txMouseY() >= 180 &&
               txMouseX() <= 1269+30 &&
               txMouseY() <= 222+30 &&
               txMouseButtons()== 1)
            {
                active_category = "Учителя" ;
            }

            if (txMouseX() >= 736 &&
               txMouseY() >= 184 &&
               txMouseX() <= 885+30 &&
               txMouseY() <= 221+30 &&
               txMouseButtons()== 1)
            {
                active_category = "Ученики" ;
            }

         // рисование ботана по клику (pic2)
         for (int nomer = 0; nomer < N_VARS; nomer = nomer + 1)
         {
            if (txMouseX() >= variants[nomer].x &&
               txMouseY() >= variants[nomer].y &&
               txMouseX() <= variants[nomer].x + 100 &&
               txMouseY() <= variants[nomer].y + 100 &&
               txMouseButtons()== 1 && centr[nomer].visible)
            {
                //Добавляется новая центральная картинка
                centr[n_pics] = {458, 608, 100,100, variants[nomer].pic, true, "Учителя"};
                n_pics++;
                txSleep(100);
            }
        }

        exit();
        txEnd();
        txSleep(20);
    }

    //Удаление картинок
    for (int nomer = 0; nomer < N_VARS; nomer = nomer + 1)
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
