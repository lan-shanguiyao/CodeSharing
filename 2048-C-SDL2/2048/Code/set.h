#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include"SDL.h" 
#include<Windows.h>
#include<time.h>

using namespace std;

//一些数值的初定义
extern const int Length = 4;
extern const int win_width = 600;  //窗口的宽度(左右)
extern const int win_height = 800;  //窗口的高度(上下)
int arr[Length][Length], Coo_X[Length][Length], Coo_Y[Length][Length];
int scores, counts = Length * Length - 1, flag;

extern SDL_Window*  win = NULL;  //窗口
extern SDL_Renderer* surfase_render = NULL;  //渲染器
//extern SDL_Texture* imageb = NULL;  //纹理 调用GPU
SDL_Event gameevent;  //事件声明

//x和y是矩形的左上角坐标。x从左到右增加；y从上到下增加。
//左上角的坐标就是(0,0)——SDL中就是这样的。w是矩形的宽，h是矩形的高。

//游戏引导程序
void Boot_Program();

//释放媒体并关闭
void close();

//捕获输入并处理
void handle();

//积分系统
void score();

//2048处理程序
void core(int n);

void output();

//图片调用
void transfer(int n, int i, int j);

#endif // !GAME_H
