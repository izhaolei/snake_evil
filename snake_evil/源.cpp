#include "snake.h"
#include "conio.h"
#include<windows.h>
#include"opencv2/opencv.hpp"
using namespace cv;
int main()
{
	char s;
	snake a;
	a.newApple();
	while (1)
	{
		while (!_kbhit())
		{
			a.move();
			a.printsnake();
			Sleep(1000);
		}
		s = _getch();
		a.changeState(s);
	}
	
}

