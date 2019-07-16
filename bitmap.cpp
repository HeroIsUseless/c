#include <stdio.h>
#include "bitmap.h"
#include "stdlib.h"
#include "math.h"
#include <iostream>
 
#define PI 3.14159//圆周率宏定义
#define LENGTH_NAME_BMP 30//bmp图片文件名的最大长度
 
using namespace std;
  
class Bitmap{
    BitmapFileHeader bfHeader;
    BitmapInfoHeader biHeader;
    RGBPalette palet[256];     //256色调色板
    int width,height;          //图片的宽度和高度
	ImageData *imagedata = NULL;//原图片的像素信息，一个二维数组
    public:
    Bitmap(char* filepath){
        FILE *fp;
	    fp=fopen(filepath,"rb");
        	if(fp != NULL){
            WORD bfType; // 先读取文件类型
            fread(&bfType,1,sizeof(WORD),fp);
            if(0x4d42!=bfType){cout<<"the file is not a bmp file!"<<endl; return;}
            //读取bmp文件的文件头和信息头
            fread(&bfHeader,1,sizeof(BitmapFileHeader),fp); //showBitmapFileHeader();//显示文件头
            fread(&biHeader,1,sizeof(BitmapInfoHeader),fp); //showBitmapInforHeader();//显示文件信息头
            //读取调色板
            for(int i=0;i<biHeader.biClrUsed;i++)
            { //存储的时候，一般去掉保留字rgbReserved
                fread((char *)&palet[i].rgbBlue,1,sizeof(BYTE),fp);
                fread((char *)&palet[i].rgbGreen,1,sizeof(BYTE),fp);
                fread((char *)&palet[i].rgbRed,1,sizeof(BYTE),fp);
            }
            width = biHeader.biWidth;
            height = biHeader.biHeight;
            //初始化图片的像素数组
            imagedata = (ImageData*) new ImageData[width*height]; 
            for(int i = 0;i < height;++i)
            {
                for(int j = 0;j < width;++j)
                {
                    (*(imagedata + i * width + j)).blue = 0;
                    (*(imagedata + i * width + j)).green = 0;
                    (*(imagedata + i * width + j)).red = 0;
                }
            }
            fread(imagedata,sizeof(ImageData)*width,height,fp); //读出图片的像素数据
            fclose(fp);
        }
        else
        {cout<<"file open error!"<<endl; return;}
    }
    ~Bitmap(){}

    void showBitmapFileHeader(){
        cout<<"bfSize: "<<bfHeader.bfSize<<endl;
        cout<<"bfReserved1: "<<bfHeader.bfReserved1<<endl;
        cout<<"bfReserved2: "<<bfHeader.bfReserved2<<endl;
        cout<<"bfOffBits: "<<bfHeader.bfOffBits<<endl<<endl;
    }
 
    void showBitmapInforHeader(){
        cout<<"biSize: "<<biHeader.biSize<<endl;
        cout<<"biWidth: "<<biHeader.biWidth<<endl;
        cout<<"biHeight: "<<biHeader.biHeight<<endl;
        cout<<"biPlanes: "<<biHeader.biPlanes<<endl;
        cout<<"biBitCount: "<<biHeader.biBitCount<<endl;
        cout<<"biCompression: "<<biHeader.biCompression<<endl;
        cout<<"biSizeImage: "<<biHeader.biSizeImage<<endl;
        cout<<"biXPelsPerMeter: "<<biHeader.biXPelsPerMeter<<endl;
        cout<<"biYPelsPerMeter: "<<biHeader.biYPelsPerMeter<<endl;
        cout<<"biClrUsed: "<<biHeader.biClrUsed<<endl;
        cout<<"biClrImportant: "<<biHeader.biClrImportant<<endl;
    }

    void showImageData(int n){
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                if(n>0){
                    cout << "{" << (*(imagedata + i * width + j)).blue+0; 
                    cout <<", "<<(*(imagedata + i * width + j)).red+0<<", ";
                    cout <<(*(imagedata + i * width + j)).green+0<<"}"<<endl;
                }
                n--;
            }
        }
    }

    void turnToBlue(char* filepath){
        ImageData *tid = new ImageData[width*height];
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                (*(tid + i * width + j)).red=(*(imagedata + i * width + j)).red;
                (*(tid + i * width + j)).green=(*(imagedata + i * width + j)).green;
                (*(tid + i * width + j)).blue=(*(imagedata + i * width + j)).blue;

            }
        }
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                if((*(imagedata + i * width + j)).red<=250 && 
                   (*(imagedata + i * width + j)).blue<=250 &&
                   (*(imagedata + i * width + j)).green<=250){
                       (*(tid + i * width + j)).red=0;
                       (*(tid + i * width + j)).green=0;
                       int color_t = (*(imagedata + i * width + j)).blue+200;
                       if(color_t < 255)
                        (*(tid + i * width + j)).blue=color_t;
                        else
                        {
                            (*(tid + i * width + j)).red=(*(imagedata + i * width + j)).red;
                            (*(tid + i * width + j)).green=(*(imagedata + i * width + j)).green;
                            (*(tid + i * width + j)).blue=255;
                        }
                        
                }
            }

//0->200 黑色-深蓝-浅蓝

//155->255 深蓝-浅蓝

        }
        FILE* fp;
        if((fp=fopen(filepath,"wb"))==NULL)
        {cout<<"create the bmp file error!"<<endl;return;}
        WORD bfType_w=0x4d42;
        fwrite(&bfType_w,1,sizeof(WORD),fp); // 写入文件头
        fwrite(&bfHeader,1,sizeof(BitmapFileHeader),fp); 
        fwrite(&biHeader,1,sizeof(BitmapInfoHeader),fp);
        //保存调色板数据
        for(unsigned int i=0;i<biHeader.biClrUsed;i++)
        {
            fwrite(&palet[i].rgbBlue,1,sizeof(BYTE),fp);
            fwrite(&palet[i].rgbGreen,1,sizeof(BYTE),fp);
            fwrite(&palet[i].rgbRed,1,sizeof(BYTE),fp);
        }
        //保存像素数据
        for(int i =0;i < height; i++)
        {
            for(int j = 0;j < width; j++)
            { 
                fwrite( &(*(tid + i * width + j)).blue,1,sizeof(BYTE),fp);
                fwrite( &(*(tid + i * width + j)).green,1,sizeof(BYTE),fp);
                fwrite( &(*(tid + i * width + j)).red,1,sizeof(BYTE),fp);
            }
        }
        fclose(fp);
    }
};
 
int main(){
	char filepath[200] = "e:\\1.bmp";//bmp文件名
    Bitmap bm(filepath);
    bm.showBitmapFileHeader();
    bm.showBitmapInforHeader();
    bm.showImageData(100);
    char tfp[200] = "e:\\b.bmp";
    bm.turnToBlue(tfp);
    return 0;
}