#include"set.h"

int main(int argc, char *argv[]) {

	system("color 8F");  //����̨����ɫ��������ɫ 

	Boot_Program();  //������Ϸ��ʼ

	handle();	//�������벢����

	score();  //����ϵͳ

	close();	//�ͷ�ý�岢�ر�

	return 0;
}

//��Ϸ��������
void Boot_Program() {

	SDL_Init(SDL_INIT_EVERYTHING);  //��ʼ��

	//��ʼ������win
	win = SDL_CreateWindow("2048",   /*��������*/
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  /*����*/
		win_width, win_height,   /*���ڴ�С*/
		SDL_WINDOW_SHOWN);  /*����*/

	//��ʼ����Ⱦ��surfase_render
	surfase_render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	//SDL_SetRenderDrawBlendMode(surfase_render, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(surfase_render, 250, 248, 238, 200);  //����ɫ
	SDL_RenderClear(surfase_render);   //���Render

	//��ʾ
	SDL_RenderPresent(surfase_render);

	//�˴�����߽���,����...     ��ʱ����

	//TTF_Init();  //��ʼ��ttf��
	//TTF_Font* surfase_font = NULL;  //����
	//surfase_font = TTF_OpenFont("SIMYOU.TTF", 24);//��SIMYOU.TTF�ֿ⣬������Ϊ24��
	//if (surfase_font == NULL) {
	//	cout << "error" << endl;
	//	exit(-1);
	//}  //�����ʧ��
	//SDL_Texture* surfacetexture = NULL;
	//SDL_Surface* surfasetext = NULL;  //���ֱ���
	//SDL_Color surfase_color = { 0,0,0 };  //������ɫ R,G,B
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

	//���ƾ���
	//�ṩ��ʼ����
	SDL_Rect gamerect;
	gamerect.x = (win_width - Length * 100) / 2 - 20;  //����
	gamerect.y = (win_height - Length * 100) / 2 + 50 - 20;  //����
	gamerect.w = Length * 100 + 30;
	gamerect.h = Length * 100 + 30;
	//���Ʊ߽��� ,��15
	SDL_SetRenderDrawColor(surfase_render, 185, 171, 158, 255);  //������ɫ
	SDL_Rect interval;
	interval.x = gamerect.x - 15;
	interval.y = gamerect.y - 15;
	interval.h = gamerect.h + 15 * 2;
	interval.w = gamerect.w + 15 * 2;
	SDL_RenderDrawRect(surfase_render, &interval);  //���ƾ���
	SDL_RenderFillRect(surfase_render, &interval);  //������
	//����߿�10; ���������ʾ����,��С100*100
	SDL_Rect gamerect1;
	gamerect1.w = 100;
	gamerect1.h = 100;
	SDL_SetRenderDrawColor(surfase_render, 203, 190, 179, 200);  //������ɫ  ���ƻ�ɫ
	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			gamerect1.x = gamerect.x + i * 110;
			Coo_X[i][j] = gamerect1.x;
			gamerect1.y = gamerect.y + j * 110;
			Coo_Y[i][j] = gamerect1.y;
			SDL_RenderDrawRect(surfase_render, &gamerect1);  //���ƾ���
			SDL_RenderFillRect(surfase_render, &gamerect1);  //������
		}
	}
	SDL_RenderPresent(surfase_render);  //��ʾ

	return;
}

//�������벢����
void handle() {
	//������һ����
	int r, i, j;
	srand((int)time(0));
	r = rand() % 16;
	i = r / Length;
	j = r % Length;
	//�����λ��û��ֵ,�Ͳ���2��4
	if (arr[i][j] == 0) {
		//����Ƶ��
		if (r < 13) {
			arr[i][j] = 2;
			transfer(2, i, j);
		}
		else {
			arr[i][j] = 4;
			transfer(4, i, j);
		}
	}

	//��Ϣѭ��
	bool quit = false;

	while (!quit) {
		while (SDL_PollEvent(&gameevent) != 0) {
			if (gameevent.type == SDL_QUIT)
				quit = true;
			else if (gameevent.type == SDL_KEYDOWN) {
				//���������
				//�жϾ����λ
				if (gameevent.key.keysym.sym == SDLK_a || gameevent.key.keysym.sym == SDLK_LEFT)
					core(2);   //��
				if (gameevent.key.keysym.sym == SDLK_w || gameevent.key.keysym.sym == SDLK_UP)
					core(1);   //��
				if (gameevent.key.keysym.sym == SDLK_s || gameevent.key.keysym.sym == SDLK_DOWN)
					core(4);   //��
				if (gameevent.key.keysym.sym == SDLK_d || gameevent.key.keysym.sym == SDLK_RIGHT)
					core(3);  //��
			}
		}
	}
	return;
}

//2048������� 
void core(int n) {

	//��
	if (n == 1) {
		for (int i = 0; i < Length; i++) {  //���б�����������
			for (int j = 0; j < Length - 1; j++) {	//���б���
				if (arr[i][j] != 0) {  //�����λ����ֵ
					for (int k = j + 1; k < Length; k++) {  //�鿴��һ��
						if (arr[i][k] != 0) {  //�����λ����ֵ
							if (arr[i][j] == arr[i][k]) {  //����������,�ϲ�,�Ʒ�,Ȼ�����
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
			for (int j = 0; j < Length - 1; j++) {  //���б���
				if (arr[i][j] == 0) {  //�����λ����ֵ
					for (int k = j + 1; k < Length; k++) {  //�鿴��һ��
						if (arr[i][k] != 0) {  //�����λ����ֵ,�ƶ�����,����
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

	//��
	if (n == 2) {
		for (int j = 0; j < Length; j++) {  //���б�����������
			for (int i = 0; i < Length - 1; i++) {  //���б���
				if (arr[i][j] != 0) {  //�����λ����ֵ
					for (int k = i + 1; k < Length; k++) {	//�鿴��һ��
						if (arr[k][j] != 0) {	//�����λ����ֵ
							if (arr[i][j] == arr[k][j]) {	//����������,�ϲ�,�Ʒ�,Ȼ�����
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
			for (int i = 0; i < Length - 1; i++) {  //���б���
				if (arr[i][j] == 0) {	//�����λ����ֵ
					for (int k = i + 1; k < Length; k++) {	//�鿴��һ��
						if (arr[k][j] != 0) {	//�����λ����ֵ,�ƶ�����,����
							arr[i][j] = arr[k][j];
							arr[k][j] = 0;
							break;
						}
					}
				}
			}
		}
	}

	//��
	if (n == 3) {
		for (int j = 0; j < Length; j++) {	//���б�����������
			for (int i = Length - 1; i >= 0; i--) {	//���б���
				if (arr[i][j] != 0) {	//�����λ����ֵ
					for (int k = i - 1; k >= 0; k--) {	//�鿴��һ��
						if (arr[k][j] != 0) {	//�����λ����ֵ
							if (arr[i][j] == arr[k][j]) {	//����������,�ϲ�,�Ʒ�,Ȼ�����
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
			for (int i = Length - 1; i >= 0; i--) {	//���б���
				if (arr[i][j] == 0) {	//�����λ����ֵ
					for (int k = i - 1; k >= 0; k--) {	//�鿴��һ��
						if (arr[k][j] != 0) {	//�����λ����ֵ,�ƶ�����,����
							arr[i][j] = arr[k][j];
							arr[k][j] = 0;
							break;
						}
					}
				}
			}
		}
	}

	//��
	if (n == 4) {
		for (int i = 0; i < Length; i++) {	//���б�����������
			for (int j = Length - 1; j >= 0; j--) {	//���б���
				if (arr[i][j] != 0) {	//�����λ����ֵ
					for (int k = j - 1; k >= 0; k--) {	//�鿴��һ��
						if (arr[i][k] != 0) {	//�����λ����ֵ
							if (arr[i][j] == arr[i][k]) {	//����������,�ϲ�,�Ʒ�,Ȼ�����
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
			for (int j = Length - 1; j >= 0; j--) {	//���б���
				if (arr[i][j] == 0) {	//�����λ����ֵ
					for (int k = j - 1; k >= 0; k--) {	//�鿴��һ��
						if (arr[i][k] != 0) {	//�����λ����ֵ,�ƶ�����,����
							arr[i][j] = arr[i][k];
							arr[i][k] = 0;
							break;
						}
					}
				}
			}
		}
	}

	//���λ�����������ж��Ƿ����

	//��ȡλ�ÿ������
	int m = 0;
	/*for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			if (arr[i][j] != 0)
				m++;
		}
	}*/
	//���λ��ȫ��,�������Ϸ
	if (/*m == Length * Length*/counts == 0 && flag == 0) {
		transfer(0, 0, 0);
		return;
	}//game over
	if (flag == 1) {
		transfer(1, 0, 0);
		return;  //�˳���������
	}//win
	//����п���λ��,������һ��2��4
	if (/*m != Length * Length*/counts != 0) {
		int i = 0, j = 0, r = 0;
		while (arr[i][j] >= 0) {
			srand((int)time(0));
			r = rand() % 16;
			i = r / Length;
			j = r % Length;
			//�����λ��û��ֵ,�Ͳ���2��4
			if (arr[i][j] == 0) {
				counts--;
				//����Ƶ��
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
	SDL_SetRenderDrawColor(surfase_render, 250, 248, 238, 200);  //����ɫ
	SDL_RenderClear(surfase_render);   //���Render

	//��ʾ
	SDL_RenderPresent(surfase_render);

	SDL_RenderClear(surfase_render);   //���Render

		//���ƾ���
		//�ṩ��ʼ����
	SDL_Rect gamerect;
	gamerect.x = (win_width - Length * 100) / 2 - 20;  //����
	gamerect.y = (win_height - Length * 100) / 2 + 50 - 20;  //����
	gamerect.w = Length * 100 + 30;
	gamerect.h = Length * 100 + 30;
	//���Ʊ߽��� ,��15
	SDL_SetRenderDrawColor(surfase_render, 185, 171, 158, 255);  //������ɫ
	SDL_Rect interval;
	interval.x = gamerect.x - 15;
	interval.y = gamerect.y - 15;
	interval.h = gamerect.h + 15 * 2;
	interval.w = gamerect.w + 15 * 2;
	SDL_RenderDrawRect(surfase_render, &interval);  //���ƾ���
	SDL_RenderFillRect(surfase_render, &interval);  //������
	//����߿�10; ���������ʾ����,��С100*100
	SDL_Rect gamerect1;
	gamerect1.w = 100;
	gamerect1.h = 100;
	SDL_SetRenderDrawColor(surfase_render, 203, 190, 179, 200);  //������ɫ  ���ƻ�ɫ
	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			gamerect1.x = gamerect.x + i * 110;
			Coo_X[i][j] = gamerect1.x;
			gamerect1.y = gamerect.y + j * 110;
			Coo_Y[i][j] = gamerect1.y;
			SDL_RenderDrawRect(surfase_render, &gamerect1);  //���ƾ���
			SDL_RenderFillRect(surfase_render, &gamerect1);  //������
		}
	}
	SDL_RenderPresent(surfase_render);  //��ʾ


	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			if (arr[i][j] > 0) {
				transfer(arr[i][j], i, j);
			}
		}
	}
	return;
}

//ͼƬ����
void transfer(int n, int i, int j) {
	SDL_Rect fillrectt;
	fillrectt.x = Coo_X[i][j];
	fillrectt.y = Coo_Y[i][j];
	fillrectt.w = 100;
	fillrectt.h = 100;

	//Ϊ��߳��������ٶ�,��ǰ����ͼƬ
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
	//Ϊ�˱����ڴ�ռ�ù���,�ͷż��ص�ͼƬ��texture
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

//����ϵͳ
void score() {
	//font = TTF_OpenFont("��������.ttf", 100);

	//SDL_Color textcolor = { 120,173,20 };  //������ɫ

	//SDL_Surface* std = TTF_RenderText_Solid(font, "2048asdfggasdfggs...", textcolor);

	cout << "�����ֵĵ÷�Ϊ:" << scores << endl;

	return;
}

//�ͷ�ý�岢�ر�
void close() {
	//�ر�����
	//TTF_CloseFont(font);
	//����ͼƬ
	//SDL_FreeSurface(imagebackground);


	//SDL_DestroyTexture(imageb);
	//imageb = NULL;

	//���ٱ���
	//SDL_FreeSurface(screen_surface);

	SDL_DestroyRenderer(surfase_render);
	surfase_render = NULL;

	//���ٴ���
	SDL_DestroyWindow(win);
	win = NULL;

	//��ȫ�˳�
	SDL_Quit();
	return;
}



/*
���������ݴ洦
��һ����ɫ(0)�ĳ�����(ȫ��)
SDL_FillRect(surface, NULL, 0);
���ڵĳ���ʱ��
SDL_Delay(8000);
����һ������ı���
SDL_Surface* surface = SDL_GetWindowSurface(win);
��ͼƬ����ȥ   ��һ��NULL : �и�ͼƬ����㡡�����ڶ���NULL����ͼƬ���Ͻ�����ʲôλ��
SDL_BlitSurface(imagesurface, NULL, surface, NULL);
ȫ�����rend, ÿ����ͼ֮ǰ
SDL_RenderClear(rend);
����һ��png��ʽͼƬ
SDL_Surface* imagebackground = IMG_Load("back.png");
����һ��bmp��ʽ��ͼƬ
SDL_Surface* coin = SDL_LoadBMP("image,bmp");
����
SDL_RenderDrawPoint(rend, 10, 10);
const int s[20] = { 2,2,4,2,2,2,4,2,2,2,4,2,2,2,2,2,2,2,4,2 };
�������2��4
��ĳһ����ɫ����Ϊ͸��, ����RGBֵ, ���������
SDL_SetColorKey(imagebackground, SDL_TRUE, SDL_MapRGB(imagebackground->format, 255, 0, 255));
��ͼƬ���óɰ�͸��
SDL_SetTextureBlendMode(imageb, SDL_BLENDMODE_BLEND);
���԰�͸��  0 - 255  0Ϊȫ͸��   ����͸����
SDL_SetTextureAlphaMod(imageb, 100);
else if (event.type == SDL_MOUSEMOTION) {
����ƶ�
int x = event.motion.x;  //��ǰ����λ��
int y = event.motion.y;
else if (event.type == SDL_MOUSEBUTTONDOWN) {
������
if (event.button.button == SDL_BUTTON_LEFT) {
}
����Ҽ�
else if (event.button.button == SDL_BUTTON_RIGHT) {
}
			}
���������: rand����һ��α�����,
�����Ҫһ����ʼֵ, �� : ����;
������, randĬ������Ϊ1;
void srand(unsigned int seed)
Ϊ����������, seed��������,
�м�seed��Ҫ����


*/
