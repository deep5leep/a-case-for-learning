///gggggggggggggggggggggggggg
#include<graphics.h>
#include<cstdio>
#define WIDTH 460
#define HEIGHT 530
#define SIZE 30
#define POOLW 300
#define POOLH 510
#define TIPSIZE 120
const int poolx=149;
const int pooly=10;
const int tipx=11;
const int tipy=10;
const int w=POOLW/SIZE;
const int h=POOLH/SIZE;
int style[7][4][4][4]={//纪录七种形状[种类][形状方向][x][y] 
	{
	 {{0,0,0,0},{0,1,0,0},{1,1,0,0},{0,1,0,0}},//0010
	 {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},//0111
	 {{1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},//0000
	 {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}} //0000
	},
	{
	 {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},//0100
	 {{0,0,0,0},{0,1,0,0},{1,1,0,0},{1,0,0,0}},//0110
	 {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},//0010
	 {{0,0,0,0},{0,1,0,0},{1,1,0,0},{1,0,0,0}} //0000
	},
	{
	 {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},//0010
	 {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},//0110
	 {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},//0100
	 {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}} //0000
	},
	{
	 {{0,0,0,0},{1,1,0,0},{1,1,0,0},{0,0,0,0}},//0110
	 {{0,0,0,0},{1,1,0,0},{1,1,0,0},{0,0,0,0}},//0110
	 {{0,0,0,0},{1,1,0,0},{1,1,0,0},{0,0,0,0}},//0000
	 {{0,0,0,0},{1,1,0,0},{1,1,0,0},{0,0,0,0}} //0000
	},
	{
	 {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},//1111
	 {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},//0000
	 {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},//0000
	 {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}} //0000
	}, 
	{
	 {{0,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,0,0}},//0100
	 {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},//0111
	 {{1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}},//0000
	 {{0,0,0,0},{0,0,1,0},{1,1,1,0},{0,0,0,0}} //0000
	},
	{
	 {{0,0,0,0},{0,1,0,0},{0,1,0,0},{1,1,0,0}},//0001
	 {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},//0111
	 {{1,1,0,0},{1,0,0,0},{1,0,0,0},{0,0,0,0}},//0000
	 {{0,0,0,0},{1,0,0,0},{1,1,1,0},{0,0,0,0}} //0000
	},
}; 
class Game{
	public:
		Game()
		{
			score=0;
			nextColor=int2rgb(random(5));
			transform=random(7);
			direction=random(4);
			for(int x=0;x<4;x++)
			for(int y=0;y<4;y++)
			{
				square[x][y]=tip[x][y]=false;
				squareX[x][y]=0;
				squareY[x][y]=0;
			}
			for(int x=0;x<w;x++)
			for(int y=0;y<h;y++)
			{
				pool[x][y]=false;
				squareColor[x][y]=0;
			}
			drawPool();//画游戏主池
			newSquare();
			drawSquares();
			gameScene();
			//游戏结束
			char c;
			setcolor(WHITE);
			setfont(14,0,"黑体");
			outtextxy(poolx+POOLW/5,pooly+2,"请按Enter键重新开始,Esc结束");
			while(is_run())
			{
				c=getch();
				if(c=='\r')
				{
					cleardevice();
					break;
				}
				if(c==27) exit(0);
			}
			
		}
		void gameScene()
		{
			char c;
			bool isredown=false;
			for(int n;is_run();delay_fps(60),n++)
			{
				while(kbhit())
				{
					c=getch();
					if(c==40)
					{
						n=0;
						if(isredown)
						{
							do
							{
								;
							}while(!falling()&&is_run());
							for(int x=0;x<w;x++)
							if(pool[x][0])//游戏结束 
							{
								gameOver();
								return;
							} 
							cleardevice();
							eliminate();
						    if(newSquare())
							{
								gameOver();
								return;
							}
							drawPool();
							drawSquares();
							isredown=false;
							break;
						}
						else
						{
						cleardevice();
						if(falling())
						{
						for(int x=0;x<w;x++)
						if(pool[x][0])//游戏结束 
						{
							gameOver();
							return;
						}  
						eliminate();
						if(newSquare())
							{
								gameOver();
								return;
							}
						}
						drawPool();
						drawSquares();
						}
						isredown=true;
					}
					if(c==37||c==39)
					{
						cleardevice();
						lrMove(c);
						drawPool();
						drawSquares();
					}
					if(c==38)
					{
						if(changeDirection())
						{
							cleardevice();
							drawPool();
							drawSquares();
						}
					}
					if(c=='P'||c=='p')//暂停功能 
					{
						while(is_run())
						{
							if(kbhit())
							{
								c=getch();
								if(c=='P'||c=='p')
								break;
							}
						}
					}	
				}
				if(n>=30)
				{
					n=0;
					isredown=false;
					cleardevice();
					if(falling())
					{
						for(int x=0;x<w;x++)
						if(pool[x][0])//游戏结束 
						{
							gameOver();
							return;
						} 
						eliminate();
						if(newSquare())
							{
								gameOver();
								return;
							}
					}
					drawPool();
					drawSquares();
				}	
			}
		}
		~Game()
		{
		}	
	private:
		bool pool[w][h];
		bool tip[4][4];
		bool square[4][4];
		int squareX[4][4];
		int squareY[4][4];
		color_t squareColor[w][h];
		unsigned int realTransform;
		unsigned int realDirection;
		unsigned int transform;
		unsigned int direction;
		unsigned int score;
		color_t realColor;
		color_t nextColor;
		void drawPool()//游戏边框主池
		{
			float h,s,v;
			h=0.0f;
			s=0.0f; 
			v=1.0f;
			for(int i=-1;i<2;i=i+2)//主池边框
			for(int j=0;j<4;j++)
			{
				setcolor(hsv2rgb(h,s,v-0.25f*(float)j));
				line(poolx-4+i*j,pooly-4+i*j,poolx+3-i*j+POOLW,pooly-4+i*j);
				line(poolx+3-i*j+POOLW,pooly-4+i*j,poolx+3+POOLW-i*j,pooly+3+POOLH-i*j);
				line(poolx+3+POOLW-i*j,pooly+3+POOLH-i*j,poolx-4+i*j,pooly+3+POOLH-i*j);
				line(poolx-4+i*j,pooly+3-i*j+POOLH,poolx-4+i*j,pooly-4+i*j);
			}
			for(int i=-1;i<2;i=i+2)//提示边框
			for(int j=0;j<4;j++)
			{
				setcolor(hsv2rgb(h,s,v-0.25f*(float)j));
				line(tipx-4+i*j,tipy-4+i*j,tipx+3-i*j+TIPSIZE,tipy-4+i*j);
				line(tipx+3-i*j+TIPSIZE,tipy-4+i*j,tipx+3+TIPSIZE-i*j,tipy+3+TIPSIZE-i*j);
				line(tipx+3+TIPSIZE-i*j,tipy+3+TIPSIZE-i*j,tipx-4+i*j,tipy+3+TIPSIZE-i*j);
				line(tipx-4+i*j,tipy+3-i*j+TIPSIZE,tipx-4+i*j,tipy-4+i*j);
			}
			//显示分数
			char str[16];
			setfont(24,0,"黑体");
			setcolor(WHITE);
			sprintf(str,"%8d",score);
			outtextxy(50,200,"分数");
			outtextxy(20,250,str);
		}
		bool falling()
		{
			bool istouch=false;
			for(int y=3;y>=0;y--)
			for(int x=0;x<4;x++)
			{
				int px=squareX[x][y];
				int py=squareY[x][y];
				if(square[x][y])//有方块
				{
					if(py>=h-1)//接触地面
					{
						istouch=true;
						return istouch;
					}
					else
					{
						if(pool[px][py+1]&&!square[x][y+1])//接触其他方块 
						{
							istouch=true;
							return istouch;
						}
					} 
				}
			}
			if(!istouch)
			{
				moveSquare(40);
				return istouch;
			}
		}
		bool changeDirection()
		{
			int defaultNumber=0;
			int realNumber=0; 
			unsigned int number=realDirection;
			if(number>=3)
			number=0;
			else
			number++;
			for(int x=0;x<4;x++)//判断是否可以变换 
			for(int y=0;y<4;y++) 
			{
				if(style[realTransform][number][x][y]&&!square[x][y])
				{
					if(squareX[x][y]>w-1||squareX[x][y]<0) return false;
					if(squareY[x][y]>h-1) return false;
					defaultNumber++;
					if(!pool[squareX[x][y]][squareY[x][y]])
					realNumber++;
				}
			}
			if(defaultNumber==realNumber)//满足则变换 
			{
				realDirection=number;
				for(int x=0;x<4;x++)
				for(int y=0;y<4;y++)
				{
					if(square[x][y]&&pool[squareX[x][y]][squareY[x][y]])
					{
						pool[squareX[x][y]][squareY[x][y]]=false;
						squareColor[squareX[x][y]][squareY[x][y]]=BLACK;
					}
					if(style[realTransform][number][x][y])
					{
						pool[squareX[x][y]][squareY[x][y]]=true;
						squareColor[squareX[x][y]][squareY[x][y]]=realColor;
					}
					square[x][y]=style[realTransform][number][x][y];
						
				} 
			}
			else return false;	
		}
		int lrMove(int direction)
		{
			bool istouch=false;
			if(direction==37)
			for(int x=0;x<4;x++)
			for(int y=3;y>=0;y--)
			{
				int px=squareX[x][y];
				int py=squareY[x][y];
				if(square[x][y])//有方块
				{
					if(px<=0)//接触边界 
					{
						istouch=true;
						return istouch;
					}
					else
					{
						if(realTransform==4&&(realDirection==0||
						   realDirection==2)&&pool[px-1][py]&&x==0)
						{
							istouch=true;
							return istouch;
						}
						if(pool[px-1][py]&&!square[x-1][y])//接触其他方块 
						{
							istouch=true;
							return istouch;
						}
					} 
				}
			}
			if(direction==39)
			for(int x=3;x>=0;x--)
			for(int y=3;y>=0;y--)
			{
				int px=squareX[x][y];
				int py=squareY[x][y];
				if(square[x][y])//有方块
				{
					if(px>=w-1)//接触边界 
					{
						istouch=true;
						return istouch;
					}
					else
					{
						if(realTransform==4&&(realDirection==0||
						   realDirection==2)&&pool[px+1][py]&&x==3)
						{
							istouch=true;
							return istouch;
						}
						if(pool[px+1][py]&&!square[x+1][y])//接触其他方块 
						{
							istouch=true;
							return istouch;
						}
					} 
				}
			}
			if(!istouch)
			{
				moveSquare(direction);
				return istouch;
			}
		}
		void moveSquare(int direction)
		{
			if(direction==40)//下 
			for(int y=3;y>=0;y--)
				for(int x=0;x<4;x++)
				{
					int px=squareX[x][y];
					int py=squareY[x][y];
					if(square[x][y])
					{
						pool[px][py]=false;
						pool[px][py+1]=true;
						squareColor[px][py+1]=squareColor[px][py];
						squareColor[px][py]=BLACK;
					}
					squareY[x][y]++;
				}
			if(direction==37)//左 
			for(int x=0;x<4;x++)
				for(int y=3;y>=0;y--)
				{
					int px=squareX[x][y];
					int py=squareY[x][y];
					if(square[x][y])
					{
						pool[px][py]=false;
						pool[px-1][py]=true;
						squareColor[px-1][py]=squareColor[px][py];
						squareColor[px][py]=BLACK;
					}
					squareX[x][y]--;
				}
			if(direction==39)//右
			for(int x=3;x>=0;x--)
				for(int y=3;y>=0;y--)
				{
					int px=squareX[x][y];
					int py=squareY[x][y];
					if(square[x][y])
					{
						pool[px][py]=false;
						pool[px+1][py]=true;
						squareColor[px+1][py]=squareColor[px][py];
						squareColor[px][py]=BLACK;
					}
					squareX[x][y]++;
				}	
		} 
		void drawBar(int x,int y,color_t color)
		{
			/*float h,s,v;
			int dx,dy;
			dx=poolx+x*SIZE;
			dy=pooly+y*SIZE;
			rgb2hsv(color,&h,&s,&v);
			for(int x=0;x<30;x++)
			for(int y=0;y<30;y++)
			putpixel(dx+x,dy+y,hsv2rgb(h,s,v-0.015f*x-0.015f*y));*/
			float h,s,v;//旧风格 
			int dx,dy,size;
			dx=poolx+x*SIZE;
			dy=pooly+y*SIZE;
			size=SIZE-10;
			rgb2hsv(color,&h,&s,&v);
			setfillcolor(hsv2rgb(h,s,v));
			bar(dx+5,dy+5,dx+5+size,dy+5+size);
	   		for(int i=0;i<5;i++)
	   		{
	   			setcolor(hsv2rgb(h,s,0.1f*i+0.5f));
				line(dx+i,dy+i,dx+SIZE-1-i,dy+i);
	   	  		line(dx+i,dy+SIZE-1-i,dx+i,dy+i);
	   		}
	   		for(int i=0;i<5;i++)
	   		{
	   			setcolor(hsv2rgb(h,s,0.12f*i+0.4f));
				line(dx+SIZE-1-i,dy+i,dx+SIZE-1-i,dy+SIZE-1-i);
	   	  		line(dx+SIZE-1-i,dy+SIZE-1-i,dx+i,dy+SIZE-1-i);
	   		}
		}
		void drawTipbar(int x,int y,color_t color)
		{
			float h,s,v;
			int dx,dy,size;
			dx=tipx+x*SIZE;
			dy=tipy+y*SIZE;
			size=SIZE-10;
			rgb2hsv(color,&h,&s,&v);
			setfillcolor(hsv2rgb(h,s,v));
			bar(dx+5,dy+5,dx+5+size,dy+5+size);
	   		//setcolor(hsv2rgb(h,s,v));
	   		for(int i=0;i<5;i++)
	   		{
	   			setcolor(hsv2rgb(h,s,0.1f*i+0.5f));
				line(dx+i,dy+i,dx+SIZE-1-i,dy+i);
	   	  		line(dx+i,dy+SIZE-1-i,dx+i,dy+i);
	   		}
	   		//setcolor(hsv2rgb(h,s,0.4f*v));
	   		for(int i=0;i<5;i++)
	   		{
	   			setcolor(hsv2rgb(h,s,0.12f*i+0.4f));
				line(dx+SIZE-1-i,dy+i,dx+SIZE-1-i,dy+SIZE-1-i);
	   	  		line(dx+SIZE-1-i,dy+SIZE-1-i,dx+i,dy+SIZE-1-i);
	   		}
		}
		bool newSquare()
		{
			int repeatRank=0;
			for(int y=3;y>=0;y--)
			for(int x=0;x<4;x++)
			{
				squareX[x][y]=x+3;
				squareY[x][y]=y;
				square[x][y]=style[transform][direction][x][y];//记录目前方块样式 
			}		
			for(int y=3;y>=0;y--)//检测是否能够创建新方块 
			for(int x=0;x<4;x++)
			if(square[x][y]&&pool[x+3][y])
			{
				repeatRank++;
				for(int i=0;i<4;i++)
				for(int j=0;j<4;j++)
				{
					if(j==3)
					square[i][j]=false;
					else
					square[i][j]=square[i][j+1];
				    squareY[x][y]--;
				}
				break;
			}
			for(int y=3-repeatRank;y>=0;y--)
			for(int x=0;x<4;x++)
			{
				if(square[x][y])
				{
				pool[x+3][y]=square[x][y];
				squareColor[x+3][y]=nextColor;
				}
			}
			if(repeatRank!=0)
			{
				drawPool();
				drawSquares();
				gameOver();
				return true;
			} 
			realColor=nextColor;
			realTransform=transform;
			realDirection=direction;
			nextColor=int2rgb(random(5));
			transform=random(7);
			direction=random(4);
			for(int x=0;x<4;x++)
			for(int y=0;y<4;y++)
			tip[x][y]=style[transform][direction][x][y];
			return false;
		}
		void drawSquares()
		{
			for(int x=0;x<w;x++)
			for(int y=0;y<h;y++)
			if(pool[x][y])
			{
				drawBar(x,y,squareColor[x][y]);
			}
			for(int x=0;x<4;x++)
			for(int y=0;y<4;y++)
			if(tip[x][y])
			{
				drawTipbar(x,y,nextColor);
			}
		}
		color_t int2rgb(int number)
		{
			color_t color; 
			if(number==0) return(color=hsv2rgb(0.0f,1.0f,1.0f));//红色 
			if(number==1) return(color=hsv2rgb(120.0f,1.0f,1.0f));//绿色 
			if(number==2) return(color=hsv2rgb(25.0f,1.0f,1.0f));//橙色 
			if(number==3) return(color=hsv2rgb(210.0f,1.0f,1.0f));//蓝色 
			if(number==4) return(color=hsv2rgb(60.0f,1.0f,1.0f));//黄色 
		}
		unsigned int rgb2int(color_t color)
		{
			if(color==hsv2rgb(0.0f,1.0f,1.0f)) return 0;
			if(color==hsv2rgb(120.0f,1.0f,1.0f)) return 1;
			if(color==hsv2rgb(25.0f,1.0f,1.0f)) return 2;
			if(color==hsv2rgb(210.0f,1.0f,1.0f)) return 3;
			if(color==hsv2rgb(60.0f,1.0f,1.0f)) return 4;		
		}
		void eliminate()
		{
			char str[32];
			int rank[5]={0};int n=0; 
			for(int y=h-1;y>=0;y--)
			{	
				int number=0;
				for(int x=0;x<w;x++)
				if(pool[x][y])
				number++;
				if(number==0)
				{
					rank[n]=y;
					break;	
				}
				if(number==10)
				{
					rank[n++]=y;
				}	
			}
			if(n!=0)
			{ 
				int scoreTemp=0;
				for(int i=0;i<n;i++)//加分 
				{
				int colorNumber[5]={0};
				for(int j=0;j<10;j++)
				{
					colorNumber[rgb2int(squareColor[j][rank[i]])]++;
				}
				for(int j=0;j<4;j++)
				{
					if(colorNumber[j]>colorNumber[j+1])
					colorNumber[j+1]=colorNumber[j];	
				}
				if(colorNumber[4]==10)
				scoreTemp+=1000;
				else
				scoreTemp+=100+10*colorNumber[4];
				}
				score+=scoreTemp*n;
				for(int i=0;i<n;i++)
				{
					for(int y=rank[i];y>rank[i+1];y--)
					for(int x=0;x<w;x++)
					{
						if(y==rank[i])
						{
							pool[x][y]=false;
							squareColor[x][y]=BLACK;
						}
						else
						{
							pool[x][y+i+1]=pool[x][y];
							squareColor[x][y+i+1]=squareColor[x][y];
							pool[x][y]=false;
							squareColor[x][y]=BLACK;
						}
					}
				}
			}
		}
		void gameOver()
		{
			for(int y=h-1;y>3;y--)
			{
				for(int x=0;x<w;x++)
				{
					if(pool[x][y])
					{
						squareColor[x][y]=hsv2rgb(0.0f,0.1f,0.9f);
					}
				}
				drawPool();
				drawSquares();
				Sleep(50);
			}
			for(int y=3;y>=0;y--)
			{
				for(int x=0;x<w;x++)
				{
					if(pool[x][y])
					{
						bool isfind=false;
						for(int i=0;i<4;i++)
						for(int j=0;j<4;j++)
						if(x==squareX[i][j]&&y==squareY[i][j]&&square[i][j])
						isfind=true;
						if(!isfind)
						squareColor[x][y]=hsv2rgb(0.0f,0.1f,0.9f);
					}
				}
				drawPool();
				drawSquares();
				Sleep(50);
			}
			
		}
};

int main()
{
	randomize();
	setinitmode(INIT_NOFORCEEXIT);
	initgraph(WIDTH,HEIGHT);
	setcaption("俄罗斯方块-Powered by LR");
	setbkmode(TRANSPARENT);
	while(is_run())
	Game newgame;
	//newgame.gameScene();
	closegraph();
	return 0;
}
