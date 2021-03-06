///\file Picture.cpp
#pragma once
#include "TXLib.h"
#include "Stoly.cpp"
#include "dirent.h"

const char* active_category;

///��������� "�������"
struct Picture
{
    ///����� �������� (������ bmp-����!!)
    string adres;
    bool visible;
    const char* category;
    ///������� ���������� ������� (������ ����� ��� ����� � �������� �������� ����� _)
    int otstalost;
    HDC pic;
    int width;
    int height;
    int x;
    int y;
};

/// ��������� ������������ ������
void drawkrugbutton(int x, int y, int x1, int y1, const char* text)
{
    Win32::RoundRect(txDC(), x,y,x1,y1, 50, 50);
    txDrawText (x,y,x1,y1, text);
}

/// ��������� ������������ ������ (������� 160*60)
void drawkrugbutton(int x, int y,const char* text)
{
    drawkrugbutton(x, y, x + 160, y + 60, text);
}

///��������� ��������� ��� ������ ��������/��������
///\param N_VARS ���������� ���������
void draw_variants(Picture* variants, int N_VARS, const char* active_category)
{
    for (int nomer = 0; nomer < N_VARS; nomer++)
    {
        if (variants[nomer].category == active_category){
            Win32::TransparentBlt (txDC(), variants[nomer].x, variants[nomer].y, 100, 100, variants[nomer].pic, 0, 0, variants[nomer].width, variants[nomer].height, TX_WHITE);
        }
    }
}


///�������� ��������� ��������
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

/// �������������� �������� �������� �� ����������� ������
///\param N_VARS ���������� ���������
///\param n_pics ���������� ��������
///\param HDC pic �������� ���
void del_pic (Picture* centr, int n_pics, Picture* variants, int N_VARS, Plan* plans)
{
    for (int nomer = 0; nomer < N_VARS; nomer++)
    {
        txDeleteDC(variants[nomer].pic);
    }

    for(int nomer = 0; nomer < n_pics; nomer++)
    {
        txDeleteDC(centr[nomer].pic);
    }
     for(int i = 0; i<= 3; i++)
     {

    txDeleteDC(plans[i].pic);
    }
}

/// ����� ��������� (����������) ���������
///\param n_pics ���������� ��������
int select_active(Picture* centr, int n_pics, int pic_width, int pic_height, int n_active)
{
    for (int nomer = 0; nomer < n_pics; nomer++)
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
/// ��������� ����������
///\param n_pics ���������� ��������
///\param pic_width ������ ��������
///\param pic_height ������ ��������
///�� ����� �� �������, �������� ������ ��������� � ������
///\param n_pics ���-�� ��������
void draw_centr_pic(Picture* centr, int n_pics, int pic_width, int pic_height)
{
    for (int nomer = 0; nomer < n_pics; nomer++)
    {
        if (centr[nomer].visible)
        {
            Win32::TransparentBlt (txDC(), centr[nomer].x,   centr[nomer].y, pic_width, pic_height, centr[nomer].pic, 0, 0, centr[nomer].width, centr[nomer].height, TX_WHITE);
        }
    }
}





/// ��������� �������� �� ����� �� �������� � ������� ���������
int newCenterPic(Picture* variants, Picture* centr, int N_VARS, int n_pics, int N_MEST)
{
    for (int nomer = 0; nomer < N_VARS; nomer++)
    {
        if (txMouseX() >= variants[nomer].x &&
           txMouseY() >= variants[nomer].y &&
           txMouseX() <= variants[nomer].x + 100 &&
           txMouseY() <= variants[nomer].y + 100 &&
           txMouseButtons() == 1 && variants[nomer].category == active_category && n_pics < N_MEST)
        {

            ///����������� ����� ����������� ��������
            centr[n_pics] = { variants[nomer].adres, true, active_category, variants[nomer].otstalost,
                            variants[nomer].pic, variants[nomer].width, variants[nomer].height,458, 608};
            n_pics++;
            txSleep(100);
        }


        if (txMouseX() >= variants[nomer].x &&
           txMouseY() >= variants[nomer].y &&
           txMouseX() <= variants[nomer].x + 100  &&
           txMouseY() <= variants[nomer].y + 100 &&
           variants[nomer].category == active_category && active_category == "�������")
        {
            char str[100];
            sprintf(str, "���������� ��������� %d", variants[nomer].otstalost);
            txTextOut(850, variants[nomer].y + 100, str);
        }
    }

    return n_pics;
}
/// �������� ���������� �� ������ Delete
int deleteCenterPic(Picture* centr, int n_pics, int n_active)
{
    if (GetAsyncKeyState(VK_DELETE))
    {
        if(n_pics>0)
        {
            n_pics--;
            centr[n_active].x = centr[n_pics].x;
            centr[n_active].y = centr[n_pics].y;
            centr[n_active].pic = centr[n_pics].pic;
            txSleep(100);
        }
    }

    return n_pics;
}


 /// ��������
inline int GetFilePointer(HANDLE FileHandle){
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}


bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height){
    bool Success=0;
    HDC SurfDC=NULL;
    HBITMAP OffscrBmp=NULL;
    HDC OffscrDC=NULL;
    LPBITMAPINFO lpbi=NULL;
    LPVOID lpvBits=NULL;
    HANDLE BmpFile=INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return 0;
    if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
        return 0;
    HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
    BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return 0;
    ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
    lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SelectObject(OffscrDC, OldBmp);
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
        return 0;
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((BmpFile = CreateFile(filename,
                        GENERIC_WRITE,
                        0, NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL)) == INVALID_HANDLE_VALUE)
        return 0;
    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;
    if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return 0;
    if (Written < sizeof(BITMAPINFOHEADER))
        return 0;
    int PalEntries;
    if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
                      (int)(1 << lpbi->bmiHeader.biBitCount) : 0;
    if(lpbi->bmiHeader.biClrUsed)
    PalEntries = lpbi->bmiHeader.biClrUsed;
    if(PalEntries){
    if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
        return 0;
        if (Written < PalEntries * sizeof(RGBQUAD))
            return 0;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);
    if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
        return 0;
    if (Written < lpbi->bmiHeader.biSizeImage)
        return 0;
    bmfh.bfSize = GetFilePointer(BmpFile);
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;
    return 1;
}
bool ScreenCapture(int x, int y, int width, int height, char *filename){

    HDC hDC = GetDC(txWindow());
    HDC hDc = CreateCompatibleDC(hDC);

    HBITMAP hBmp = CreateCompatibleBitmap(hDC, width, height);

    HGDIOBJ old= SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, hDC, x, y, SRCCOPY);

    bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);

    SelectObject(hDc, old);
    DeleteObject(hBmp);

    DeleteDC (hDc);
    ReleaseDC (txWindow(), hDC);

    return ret;
}



///������� ��� �������� � ������ �� ������� ������ "������� ���!"
int del_all (int n_pics)
{
    txSetFillColour(TX_WHITE);
    drawkrugbutton(922,187,1075,230,"������� ���!");
    if (txMouseX() >= 922 &&
       txMouseY() >= 187 &&
       txMouseX() <= 1075 &&
       txMouseY() <= 230 &&
       txMouseButtons() == 1 )
    {
       n_pics = 0;
    }

    return n_pics;
}


/// ������ ������ �������� �� �����
int fillVariants(const char* address, Picture* variants, int N, const char* category)
{
    setlocale(LC_ALL, "Russian");
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (address)) !=NULL) {
        while((ent = readdir (dir)) !=NULL) {
            string str = ent->d_name;

            //���� ���������� �������� �� ������� _
            int pos = str.find("_", 0);
            string str1 = str.substr(0,pos);


            string folder = address;
            str = folder + "/" + str;

            if(str.find(".bmp") != -1)
            {
                variants[N] = {str,false, category, 0};
                variants[N].otstalost = atoi(str1.c_str()) ;
                N++;
            }

        }
        closedir (dir);
    }

    return N;
}
