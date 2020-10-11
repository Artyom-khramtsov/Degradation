#include "Lib/TXLib.h"
#include "windows.h"
#include "Picture.cpp"
#include "Stoly.cpp"

const char* active_category;

bool GameOver = false;

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




        txRectangle(1033,638,1242,687);    // выход

        txDrawText (1040,653,1231,676, "Выход");
        if(txMouseX() >= 1033 &&
               txMouseY() >= 638 &&
               txMouseX() <= 1242 &&
               txMouseY() <= 687 &&
               txMouseButtons()== 1)
        {
            txDisableAutoPause();
             GameOver = true;
        }
}
void menu ()
{
}    //пока не используется

void select_category()
{

            if (txMouseX() >= 1114 &&
               txMouseY() >= 180 &&
               txMouseX() <= 1269 &&
               txMouseY() <= 222 &&
               txMouseButtons()== 1)
            {
                active_category = "Учителя" ;
            }

            if (txMouseX() >= 736 &&
               txMouseY() >= 184 &&
               txMouseX() <= 885 &&
               txMouseY() <= 221 &&
               txMouseButtons()== 1)
            {
                active_category = "Ученики" ;
            }


            if (active_category == "Учителя")
                txSetFillColor(TX_BLUE);
            else
                txSetFillColor(TX_WHITE);
            txSetColor(TX_BLACK);
            Win32::RoundRect(txDC(), 1114, 180, 1269, 222, 50, 50);
            txDrawText(1114,180,1269,222,"Учителя");


            if (active_category == "Ученики")
                txSetFillColor(TX_BLUE);
            else
                txSetFillColor(TX_WHITE);
            txSetColor(TX_BLACK);
            Win32::RoundRect(txDC(), 728, 180, 883, 222, 50, 50);
           txDrawText(736,184,885,221,"Ученики");
}
void teleport_na_party(Picture* centr, Objects* mesto, int n_active)
{
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


}

int select_active(Picture* centr, int n_pics, int pic_width, int pic_height, int n_active)
{
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

    return n_active;
}

void del_pic (Picture* centr, Picture* variants, HDC  pic1, int N_VARS )
{
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
}
void dvizhenie(Picture* centr, int speed_x, int speed_y, int n_active)
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
void teleport_na_stol_uchitela(Objects* stol_ychitela, Picture* centr, int n_active)
{
    if (txMouseX() >= stol_ychitela[0].x &&  // телепорт на стол учителя
       txMouseY() >= stol_ychitela[0].y &&
       txMouseX() <= stol_ychitela[0].x + 30  &&
       txMouseY() <= stol_ychitela[0].y + 30 &&
       txMouseButtons()== 1 && centr[n_active].visible)
    {
       centr[n_active].x  = stol_ychitela[0].x ;
       centr[n_active].y = stol_ychitela[0].y ;
    }
}
void draw_text()
{
txDrawText(747,78,1242,100,"Игра находится в разработке ");
txDrawText(885,146,1195,179,"Выбери персонажа");
}
void draw_centr_pic(Picture* centr, int n_pics, int pic_width, int pic_height)
{
for (int nomer = 0; nomer < n_pics; nomer = nomer + 1)
        {
            if (centr[nomer].visible)
            {
                Win32::TransparentBlt (txDC(), centr[nomer].x,   centr[nomer].y, pic_width, pic_height, centr[nomer].pic, 0, 0, centr[nomer].width, centr[nomer].height, TX_WHITE);
            }
        }

}
int risovanie_po_categorii(Picture* variants, Picture* centr, int N_VARS, int n_pics)
{
 for (int nomer = 0; nomer < N_VARS; nomer = nomer + 1)
         {
            if (txMouseX() >= variants[nomer].x &&
               txMouseY() >= variants[nomer].y &&
               txMouseX() <= variants[nomer].x + 100 &&
               txMouseY() <= variants[nomer].y + 100 &&
               txMouseButtons() == 1 && variants[nomer].category == active_category)
            {
                //Добавляется новая центральная картинка
                centr[n_pics] = {458, 608, 100,100, variants[nomer].pic, true, active_category};
                n_pics++;
                txSleep(100);
            }
        }

        return n_pics;
}
int main()
{
    txTextCursor (false);

    txCreateWindow (1280, 895);
    HDC  pic1 = txLoadImage ("Картинки/задний фон.bmp");
    const int speed_x = 1;
    const int speed_y = 1;
    const int pic_width = 75;
    const int pic_height = 75;


    const int N_VARS = 6;
    Picture variants[N_VARS];
    variants[0] = {780, 240, 100, 100, txLoadImage("Картинки/ботан.bmp"),false, "Ученики"};
    variants[1] = {920, 250, 100, 100, txLoadImage("Картинки/фанера.bmp"),false, "Ученики"};
    variants[2] = {780, 410, 100, 100, txLoadImage("Картинки/бревно.bmp"),false, "Ученики"};
    variants[3] = {920, 410, 100, 100, txLoadImage("Картинки/картошка.bmp"),false, "Ученики"};
    variants[4] = {780, 240, 100, 100, txLoadImage("Картинки/злая училка.bmp"),false,"Учителя"};
    variants[5] = {930, 230, 100, 100, txLoadImage("Картинки/Учитель по труду.bmp"),false,"Учителя"};

    Picture centr[1000];
    int n_pics = 0;
    int n_active = 0;


    mesto[0] = {247, 352};
    mesto[1] = {322, 344};
    mesto[2] = {383, 356};
    mesto[3] = {449, 356};
    mesto[4] = {246, 490};
    mesto[5] = {309, 488};
    mesto[6] = {385, 490};
    mesto[7] = {449, 491};


    stol_ychitela[0]  = {412, 115};



    while (GameOver == false)
    {
        txBegin();
        txSetFillColor(TX_BLACK);
        txClear();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);


        txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);

        exit();
        n_active = select_active(centr, n_pics,pic_width, pic_height, n_active);
        draw_variants(variants, N_VARS, active_category);

        // окно подсказки
        txDrawText(710, 480, 890, 640, "Выбранный персонаж");
        txRectangle(702, 550, 930, 800);
        if (n_active >= 0)
        Win32::TransparentBlt (txDC(), 702,  550, 228, 250, centr[n_active].pic, 0, 0, centr[n_active].width, variants[n_active].height, TX_WHITE);


        select_category();
        teleport_na_party(centr, mesto, n_active);
        dvizhenie(centr, speed_x, speed_y, n_active);
        teleport_na_stol_uchitela(stol_ychitela, centr, n_active);
        draw_text();
        draw_centr_pic(centr, n_pics, pic_width, pic_height);

        txRectangle (stol_ychitela[0].x, stol_ychitela[0].y, stol_ychitela[0].x + 30, stol_ychitela[0].y + 30);
        n_pics = risovanie_po_categorii(variants, centr, N_VARS, n_pics);


         // рисование ботана по клику (pic2)



        txEnd();
        txSleep(20);
    }

    del_pic(centr,variants, pic1, N_VARS);
    return 0;
}
