#include"set.h"

int main(int argc, char *argv[]) {

	system("color 8F");  //控制台背景色和字体颜色 

	Boot_Program();  //引导游戏开始

	handle();	//捕获输入并处理

	score();  //积分系统

	close();	//释放媒体并关闭

	return 0;
}

//游戏引导程序
void Boot_Program() {

	SDL_Init(SDL_INIT_EVERYTHING);  //初始化

	//初始化窗口win
	win = SDL_CreateWindow("2048",   /*窗口名称*/
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  /*参数*/
		win_width, win_height,   /*窗口大小*/
		SDL_WINDOW_SHOWN);  /*参数*/

	//初始化渲染器surfase_render
	surfase_render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	//SDL_SetRenderDrawBlendMode(surfase_render, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(surfase_render, 250, 248, 238, 200);  //背景色
	SDL_RenderClear(surfase_render);   //清空Render

	//显示
	SDL_RenderPresent(surfase_render);

	//此处加入边界线,文字...     暂时跳过

	//TTF_Init();  //初始化ttf库
	//TTF_Font* surfase_font = NULL;  //字体
	//surfase_font = TTF_OpenFont("SIMYOU.TTF", 24);//打开SIMYOU.TTF字库，设字体为24号
	//if (surfase_font == NULL) {
	//	cout << "error" << endl;
	//	exit(-1);
	//}  //如果打开失败
	//SDL_Texture* surfacetexture = NULL;
	//SDL_Surface* surfasetext = NULL;  //文字表面
	//SDL_Color surfase_color = { 0,0,0 };  //字体颜色 R,G,B
	//SDL_Rect surfacetextload;
	//surfacetextload.x = 0;
	//surfacetextload.y = 0;
	//surfacetextload.w = 0;
	//surfacetextload.h = 0;
	//surfasetext = TTF_RenderText_Solid(surfase_font, "2048", surfase_color);
	//surfacetexture = SDL_CreateTextureFromSurface(surfase_render, surfasetext);
	//SDL_RenderCopy(surfase_render, surfacetexture, NULL, &surfacetextload);
	////SDL_RenderClear(surfase_render);
	////SDL_RenderPresent(surfase_render);

	//绘制矩形
	//提供起始坐标
	SDL_Rect gamerect;
	gamerect.x = (win_width - Length * 100) / 2 - 20;  //左右
	gamerect.y = (win_height - Length * 100) / 2 + 50 - 20;  //上下
	gamerect.w = Length * 100 + 30;
	gamerect.h = Length * 100 + 30;
	//绘制边界线 ,宽15
	SDL_SetRenderDrawColor(surfase_render, 185, 171, 158, 255);  //类似棕色
	SDL_Rect interval;
	interval.x = gamerect.x - 15;
	interval.y = gamerect.y - 15;
	interval.h = gamerect.h + 15 * 2;
	interval.w = gamerect.w + 15 * 2;
	SDL_RenderDrawRect(surfase_render, &interval);  //绘制矩形
	SDL_RenderFillRect(surfase_render, &interval);  //填充矩形
	//间隔线宽10; 填充数字显示区域,大小100*100
	SDL_Rect gamerect1;
	gamerect1.w = 100;
	gamerect1.h = 100;
	SDL_SetRenderDrawColor(surfase_render, 203, 190, 179, 200);  //设置颜色  类似黄色
	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			gamerect1.x = gamerect.x + i * 110;
			Coo_X[i][j] = gamerect1.x;
			gamerect1.y = gamerect.y + j * 110;
			Coo_Y[i][j] = gamerect1.y;
			SDL_RenderDrawRect(surfase_render, &gamerect1);  //绘制矩形
			SDL_RenderFillRect(surfase_render, &gamerect1);  //填充矩形
		}
	}
	SDL_RenderPresent(surfase_render);  //显示

	return;
}

//捕获输入并处理
void handle() {
	//产生第一个数
	int r, i, j;
	srand((int)time(0));
	r = rand() % 16;
	i = r / Length;
	j = r % Length;
	//如果该位置没有值,就产生2或4
	if (arr[i][j] == 0) {
		//控制频率
		if (r < 13) {
			arr[i][j] = 2;
			transfer(2, i, j);
		}
		else {
			arr[i][j] = 4;
			transfer(4, i, j);
		}
	}

	//消息循环
	bool quit = false;

	while (!quit) {
		while (SDL_PollEvent(&gameevent) != 0) {
			if (gameevent.type == SDL_QUIT)
				quit = true;
			else if (gameevent.type == SDL_KEYDOWN) {
				//键盘任意键
				//判断具体键位
				if (gameevent.key.keysym.sym == SDLK_a || gameevent.key.keysym.sym == SDLK_LEFT)
					core(2);   //左
				if (gameevent.key.keysym.sym == SDLK_w || gameevent.key.keysym.sym == SDLK_UP)
					core(1);   //上
				if (gameevent.key.keysym.sym == SDLK_s || gameevent.key.keysym.sym == SDLK_DOWN)
					core(4);   //下
				if (gameevent.key.keysym.sym == SDLK_d || gameevent.key.keysym.sym == SDLK_RIGHT)
					core(3);  //右
			}
		}
	}
	return;
}

//2048处理程序 
void core(int n) {

	//左
	if (n == 1) {
		for (int i = 0; i < Length; i++) {  //按行遍历整个数组
			for (int j = 0; j < Length - 1; j++) {	//按列遍历
				if (arr[i][j] != 0) {  //如果该位置有值
					for (int k = j + 1; k < Length; k++) {  //查看后一个
						if (arr[i][k] != 0) {  //如果该位置有值
							if (arr[i][j] == arr[i][k]) {  //如果两者相等,合并,计分,然后结束
								counts++;
								scores += arr[i][j];
								arr[i][j] *= 2;
								arr[i][k] = 0;
								//transfer(arr[i][j], i, j);
							}
							break;
						}
					}
				}
			}
			for (int j = 0; j < Length - 1; j++) {  //按列遍历
				if (arr[i][j] == 0) {  //如果该位置无值
					for (int k = j + 1; k < Length; k++) {  //查看后一个
						if (arr[i][k] != 0) {  //如果该位置有值,移动到此,结束
							arr[i][j] = arr[i][k];
							arr[i][k] = 0;
							//transfer(arr[i][j], i, j);
							break;
						}
					}
				}
			}
		}
	}

	//上
	if (n == 2) {
		for (int j = 0; j < Length; j++) {  //按列遍历整个数组
			for (int i = 0; i < Length - 1; i++) {  //按行遍历
				if (arr[i][j] != 0) {  //如果该位置有值
					for (int k = i + 1; k < Length; k++) {	//查看下一个
						if (arr[k][j] != 0) {	//如果该位置有值
							if (arr[i][j] == arr[k][j]) {	//如果两者相等,合并,计分,然后结束
								counts++;
								scores += arr[i][j];
								arr[i][j] *= 2;
								arr[k][j] = 0;
								//transfer(arr[i][j], i, j);
							}
							break;
						}
					}
				}
			}
			for (int i = 0; i < Length - 1; i++) {  //按行遍历
				if (arr[i][j] == 0) {	//如果该位置无值
					for (int k = i + 1; k < Length; k++) {	//查看下一个
						if (arr[k][j] != 0) {	//如果该位置有值,移动到此,结束
							arr[i][j] = arr[k][j];
							arr[k][j] = 0;
							break;
						}
					}
				}
			}
		}
	}

	//下
	if (n == 3) {
		for (int j = 0; j < Length; j++) {	//按列遍历整个数组
			for (int i = Length - 1; i >= 0; i--) {	//按行遍历
				if (arr[i][j] != 0) {	//如果该位置有值
					for (int k = i - 1; k >= 0; k--) {	//查看上一个
						if (arr[k][j] != 0) {	//如果该位置有值
							if (arr[i][j] == arr[k][j]) {	//如果两者相等,合并,计分,然后结束
								counts++;
								scores += arr[i][j];
								arr[i][j] *= 2;
								arr[k][j] = 0;
								//transfer(arr[i][j], i, j);
							}
							break;
						}
					}
				}
			}
			for (int i = Length - 1; i >= 0; i--) {	//按行遍历
				if (arr[i][j] == 0) {	//如果该位置无值
					for (int k = i - 1; k >= 0; k--) {	//查看上一个
						if (arr[k][j] != 0) {	//如果该位置有值,移动到此,结束
							arr[i][j] = arr[k][j];
							arr[k][j] = 0;
							break;
						}
					}
				}
			}
		}
	}

	//右
	if (n == 4) {
		for (int i = 0; i < Length; i++) {	//按行遍历整个数组
			for (int j = Length - 1; j >= 0; j--) {	//按列遍历
				if (arr[i][j] != 0) {	//如果该位置有值
					for (int k = j - 1; k >= 0; k--) {	//查看下一个
						if (arr[i][k] != 0) {	//如果该位置有值
							if (arr[i][j] == arr[i][k]) {	//如果两者相等,合并,计分,然后结束
								counts++;
								scores += arr[i][j];
								arr[i][j] *= 2;
								arr[i][k] = 0;
								//transfer(arr[i][j], i, j);
							}
							break;
						}
					}
				}
			}
			for (int j = Length - 1; j >= 0; j--) {	//按列遍历
				if (arr[i][j] == 0) {	//如果该位置无值
					for (int k = j - 1; k >= 0; k--) {	//查看下一个
						if (arr[i][k] != 0) {	//如果该位置有值,移动到此,结束
							arr[i][j] = arr[i][k];
							arr[i][k] = 0;
							break;
						}
					}
				}
			}
		}
	}

	//随机位置生成数和判断是否结束

	//读取位置空余多少
	int m = 0;
	/*for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			if (arr[i][j] != 0)
				m++;
		}
	}*/
	//如果位置全满,则结束游戏
	if (/*m == Length * Length*/counts == 0 && flag == 0) {
		transfer(0, 0, 0);
		return;
	}//game over
	if (flag == 1) {
		transfer(1, 0, 0);
		return;  //退出整个程序
	}//win
	//如果有空余位置,则生成一个2或4
	if (/*m != Length * Length*/counts != 0) {
		int i = 0, j = 0, r = 0;
		while (arr[i][j] >= 0) {
			srand((int)time(0));
			r = rand() % 16;
			i = r / Length;
			j = r % Length;
			//如果该位置没有值,就产生2或4
			if (arr[i][j] == 0) {
				counts--;
				//控制频率
				if (r < 13) {
					arr[i][j] = 2;
					//transfer(2, i, j);
				}
				else {
					arr[i][j] = 4;
					//transfer(4, i, j);
				}
				break;
			}
		}
	}
	output();
	return;
}

void output() {
	SDL_SetRenderDrawColor(surfase_render, 250, 248, 238, 200);  //背景色
	SDL_RenderClear(surfase_render);   //清空Render

	//显示
	SDL_RenderPresent(surfase_render);

	SDL_RenderClear(surfase_render);   //清空Render

		//绘制矩形
		//提供起始坐标
	SDL_Rect gamerect;
	gamerect.x = (win_width - Length * 100) / 2 - 20;  //左右
	gamerect.y = (win_height - Length * 100) / 2 + 50 - 20;  //上下
	gamerect.w = Length * 100 + 30;
	gamerect.h = Length * 100 + 30;
	//绘制边界线 ,宽15
	SDL_SetRenderDrawColor(surfase_render, 185, 171, 158, 255);  //类似棕色
	SDL_Rect interval;
	interval.x = gamerect.x - 15;
	interval.y = gamerect.y - 15;
	interval.h = gamerect.h + 15 * 2;
	interval.w = gamerect.w + 15 * 2;
	SDL_RenderDrawRect(surfase_render, &interval);  //绘制矩形
	SDL_RenderFillRect(surfase_render, &interval);  //填充矩形
	//间隔线宽10; 填充数字显示区域,大小100*100
	SDL_Rect gamerect1;
	gamerect1.w = 100;
	gamerect1.h = 100;
	SDL_SetRenderDrawColor(surfase_render, 203, 190, 179, 200);  //设置颜色  类似黄色
	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			gamerect1.x = gamerect.x + i * 110;
			Coo_X[i][j] = gamerect1.x;
			gamerect1.y = gamerect.y + j * 110;
			Coo_Y[i][j] = gamerect1.y;
			SDL_RenderDrawRect(surfase_render, &gamerect1);  //绘制矩形
			SDL_RenderFillRect(surfase_render, &gamerect1);  //填充矩形
		}
	}
	SDL_RenderPresent(surfase_render);  //显示


	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			if (arr[i][j] > 0) {
				transfer(arr[i][j], i, j);
			}
		}
	}
	return;
}

//图片调用
void transfer(int n, int i, int j) {
	SDL_Rect fillrectt;
	fillrectt.x = Coo_X[i][j];
	fillrectt.y = Coo_Y[i][j];
	fillrectt.w = 100;
	fillrectt.h = 100;

	//为提高程序运行速度,提前加载图片
	SDL_Surface *display_image_two = SDL_LoadBMP("two.bmp");  //2
	SDL_Texture *display_image_texture_two = SDL_CreateTextureFromSurface(surfase_render, display_image_two);
	SDL_Surface *display_image_four = SDL_LoadBMP("four.bmp");  //4
	SDL_Texture *display_image_texture_four = SDL_CreateTextureFromSurface(surfase_render, display_image_four);
	SDL_Surface *display_image_eight = SDL_LoadBMP("eight.bmp");  //8
	SDL_Texture *display_image_texture_eight = SDL_CreateTextureFromSurface(surfase_render, display_image_eight);
	SDL_Surface *display_image_sixteen = SDL_LoadBMP("sixteen.bmp");  //16
	SDL_Texture *display_image_texture_sixteen = SDL_CreateTextureFromSurface(surfase_render, display_image_sixteen);
	SDL_Surface *display_image_thirty_two = SDL_LoadBMP("thirty_two.bmp");  //32
	SDL_Texture *display_image_texture_thirty_two = SDL_CreateTextureFromSurface(surfase_render, display_image_thirty_two);
	SDL_Surface *display_image_sixty_four = SDL_LoadBMP("sixty_four.bmp");  //64
	SDL_Texture *display_image_texture_sixty_four = SDL_CreateTextureFromSurface(surfase_render, display_image_sixty_four);
	SDL_Surface *display_image_one_hundred_twenty_eight = SDL_LoadBMP("one_hundred_twenty_eight.bmp");  //128
	SDL_Texture *display_image_texture_one_hundred_twenty_eight = SDL_CreateTextureFromSurface(surfase_render, display_image_one_hundred_twenty_eight);
	SDL_Surface *display_image_two_hundred_fifty_six = SDL_LoadBMP("two_hundred_fifty_six.bmp");  //256
	SDL_Texture *display_image_texture_two_hundred_fifty_six = SDL_CreateTextureFromSurface(surfase_render, display_image_two_hundred_fifty_six);
	SDL_Surface *display_image_five_hundred_twelve = SDL_LoadBMP("five_hundred_twelve.bmp");  //512
	SDL_Texture *display_image_texture_five_hundred_twelve = SDL_CreateTextureFromSurface(surfase_render, display_image_five_hundred_twelve);
	SDL_Surface *display_image_one_thousand_zero_twenty_four = SDL_LoadBMP("one_thousand_zero_twenty_four.bmp");  //1024
	SDL_Texture *display_image_texture_one_thousand_zero_twenty_four = SDL_CreateTextureFromSurface(surfase_render, display_image_one_thousand_zero_twenty_four);
	SDL_Surface *display_image_two_thousand_zero_forty_eight = SDL_LoadBMP("two_thousand_zero_forty_eight.bmp");  //2048
	SDL_Texture *display_image_texture_two_thousand_zero_forty_eight = SDL_CreateTextureFromSurface(surfase_render, display_image_two_thousand_zero_forty_eight);

	//over
	if (n == 0) {
		fillrectt.x = 0;
		fillrectt.y = 0;
		fillrectt.w = win_width;
		fillrectt.h = win_height;
		SDL_Surface *display_image_over = SDL_LoadBMP("over.bmp");
		SDL_Texture *display_image_texture_over = SDL_CreateTextureFromSurface(surfase_render, display_image_over);
		SDL_RenderCopy(surfase_render, display_image_texture_over, NULL, &fillrectt);
		fillrectt.x = Coo_X[i][j];
		fillrectt.y = Coo_Y[i][j];
		fillrectt.w = 100;
		fillrectt.h = 100;
		SDL_FreeSurface(display_image_over);
		SDL_DestroyTexture(display_image_texture_over);
	}
	//win
	if (n == 1) {
		fillrectt.x = 0;
		fillrectt.y = 0;
		fillrectt.w = win_width;
		fillrectt.h = win_height;
		SDL_Surface *display_image_win = SDL_LoadBMP("win.bmp");
		SDL_Texture *display_image_texture_win = SDL_CreateTextureFromSurface(surfase_render, display_image_win);
		SDL_RenderCopy(surfase_render, display_image_texture_win, NULL, &fillrectt);
		fillrectt.x = Coo_X[i][j];
		fillrectt.y = Coo_Y[i][j];
		fillrectt.w = 100;
		fillrectt.h = 100;
		SDL_FreeSurface(display_image_win);
		SDL_DestroyTexture(display_image_texture_win);
	}
	if (n == 2) {
		SDL_RenderCopy(surfase_render, display_image_texture_two, NULL, &fillrectt);
	}
	if (n == 4) {
		SDL_RenderCopy(surfase_render, display_image_texture_four, NULL, &fillrectt);
	}
	if (n == 8) {
		SDL_RenderCopy(surfase_render, display_image_texture_eight, NULL, &fillrectt);
	}
	if (n == 16) {
		SDL_RenderCopy(surfase_render, display_image_texture_sixteen, NULL, &fillrectt);
	}
	if (n == 32) {
		SDL_RenderCopy(surfase_render, display_image_texture_thirty_two, NULL, &fillrectt);
	}
	if (n == 64) {
		SDL_RenderCopy(surfase_render, display_image_texture_sixty_four, NULL, &fillrectt);
	}
	if (n == 128) {
		SDL_RenderCopy(surfase_render, display_image_texture_one_hundred_twenty_eight, NULL, &fillrectt);
	}
	if (n == 256) {
		SDL_RenderCopy(surfase_render, display_image_texture_two_hundred_fifty_six, NULL, &fillrectt);
	}
	if (n == 512) {
		SDL_RenderCopy(surfase_render, display_image_texture_five_hundred_twelve, NULL, &fillrectt);
	}
	if (n == 1024) {
		SDL_RenderCopy(surfase_render, display_image_texture_one_thousand_zero_twenty_four, NULL, &fillrectt);
	}
	if (n == 2048) {
		flag = 1;
		SDL_RenderCopy(surfase_render, display_image_texture_two_thousand_zero_forty_eight, NULL, &fillrectt);
	}
	SDL_RenderPresent(surfase_render);
	//为了避免内存占用过多,释放加载的图片与texture
	SDL_FreeSurface(display_image_two);  //2
	SDL_DestroyTexture(display_image_texture_two);
	SDL_FreeSurface(display_image_four);  //4
	SDL_DestroyTexture(display_image_texture_four);
	SDL_FreeSurface(display_image_eight);  //8
	SDL_DestroyTexture(display_image_texture_eight);
	SDL_FreeSurface(display_image_sixteen);  //16
	SDL_DestroyTexture(display_image_texture_sixteen);
	SDL_FreeSurface(display_image_thirty_two);  //32
	SDL_DestroyTexture(display_image_texture_thirty_two);
	SDL_FreeSurface(display_image_sixty_four);  //64
	SDL_DestroyTexture(display_image_texture_sixty_four);
	SDL_FreeSurface(display_image_one_hundred_twenty_eight);  //128
	SDL_DestroyTexture(display_image_texture_one_hundred_twenty_eight);
	SDL_FreeSurface(display_image_two_hundred_fifty_six);  //256
	SDL_DestroyTexture(display_image_texture_two_hundred_fifty_six);
	SDL_FreeSurface(display_image_five_hundred_twelve);  //512
	SDL_DestroyTexture(display_image_texture_five_hundred_twelve);
	SDL_FreeSurface(display_image_one_thousand_zero_twenty_four);  //1024
	SDL_DestroyTexture(display_image_texture_one_thousand_zero_twenty_four);
	SDL_FreeSurface(display_image_two_thousand_zero_forty_eight);  //2048
	SDL_DestroyTexture(display_image_texture_two_thousand_zero_forty_eight);
	return;
}

//积分系统
void score() {
	//font = TTF_OpenFont("华文隶书.ttf", 100);

	//SDL_Color textcolor = { 120,173,20 };  //字体颜色

	//SDL_Surface* std = TTF_RenderText_Solid(font, "2048asdfggasdfggs...", textcolor);

	cout << "您本局的得分为:" << scores << endl;

	return;
}

//释放媒体并关闭
void close() {
	//关闭字体
	//TTF_CloseFont(font);
	//销毁图片
	//SDL_FreeSurface(imagebackground);


	//SDL_DestroyTexture(imageb);
	//imageb = NULL;

	//销毁表面
	//SDL_FreeSurface(screen_surface);

	SDL_DestroyRenderer(surfase_render);
	surfase_render = NULL;

	//销毁窗口
	SDL_DestroyWindow(win);
	win = NULL;

	//安全退出
	SDL_Quit();
	return;
}



/*
废弃代码暂存处
画一个黑色(0)的长方形(全屏)
SDL_FillRect(surface, NULL, 0);
窗口的持续时间
SDL_Delay(8000);
加载一个窗体的表面
SDL_Surface* surface = SDL_GetWindowSurface(win);
把图片贴上去   第一个NULL : 切割图片的起点　　　第二个NULL：把图片左上角贴到什么位置
SDL_BlitSurface(imagesurface, NULL, surface, NULL);
全部清空rend, 每次贴图之前
SDL_RenderClear(rend);
加载一张png格式图片
SDL_Surface* imagebackground = IMG_Load("back.png");
加载一张bmp格式的图片
SDL_Surface* coin = SDL_LoadBMP("image,bmp");
画点
SDL_RenderDrawPoint(rend, 10, 10);
const int s[20] = { 2,2,4,2,2,2,4,2,2,2,4,2,2,2,2,2,2,2,4,2 };
随机出现2或4
把某一种颜色设置为透明, 三个RGB值, 随意输入的
SDL_SetColorKey(imagebackground, SDL_TRUE, SDL_MapRGB(imagebackground->format, 255, 0, 255));
把图片设置成半透明
SDL_SetTextureBlendMode(imageb, SDL_BLENDMODE_BLEND);
调试半透明  0 - 255  0为全透明   设置透明度
SDL_SetTextureAlphaMod(imageb, 100);
else if (event.type == SDL_MOUSEMOTION) {
鼠标移动
int x = event.motion.x;  //当前鼠标的位置
int y = event.motion.y;
else if (event.type == SDL_MOUSEBUTTONDOWN) {
鼠标左键
if (event.button.button == SDL_BUTTON_LEFT) {
}
鼠标右键
else if (event.button.button == SDL_BUTTON_RIGHT) {
}
			}
关于随机数: rand产生一个伪随机数,
因此需要一个初始值, 即 : 种子;
不设置, rand默认种子为1;
void srand(unsigned int seed)
为其设置种子, seed便是种子,
切记seed需要输入


*/
