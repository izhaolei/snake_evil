#ifndef SNAKE_H
#define SNAKE_H

#include<iostream>
#include <utility>
#include "time.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include<deque>
#include<string>
using namespace std;
using namespace cv;

bool gameover = 0;

 class point
 {

 private:

	 pair<char,char> pos;

 public:
	 point()
	 {
		 pos.first = 0;
		 pos.second = 0;
	 }

	 point( const char &x, const char &y) //°´XY×ø±ê¸³Öµ
	 {
		 pos.first = x;
		 pos.second = y;
	 }

	 void change(const char &x, const char &y)
	 {
		 pos.first = x;
		 pos.second = y;
	 }
	 void equalup()
	 { 
		 if ((--pos.second) <0)
		 {
			 gameover = 1;
			 pos.second = 63;
		 }
	 }
	 void equaldown()
	 {

		 if ((++pos.second)==64)
		 {
			 gameover=1;
			 pos.second = 0;
		 }
	 }
	 void equalleft()
	 {
		 if ((--pos.first)<0)
		 {
			 gameover=1;
			 pos.first = 63;
		 }
	 }
	 void equalright()
	 {
		 if ((++pos.first) == 64)
		 {
			 gameover=1;
			 pos.first = 0;
		 }
	 }
	 char first_data()
	 {
		 return pos.first;
	 }
	 char second_data()
	 {
		 return pos.second;
	 }
	 friend ostream& operator<<(ostream &out, point po)
	 {
		 out << "(" << po.pos.first << "," << po.pos.second << ")" << "  ";
		 return out;
	 }

	 bool operator==(const point p)
	 {
		 if (pos == p.pos)
			 return 1;
		 else
			 return 0;
	 }

	 };

 class snake
 {
	
 private:

	 deque<point> body{ {32,32},{ 32,33 }, { 32,34 },{ 32,35 } };
	 deque<point>::const_iterator bo = body.begin();
	 Mat data = Mat::ones(640, 640, CV_8UC1);
	 Mat game = imread("E:/snake/snake_evil/game.jpg");
	 Mat RIO = data(Rect(0, 0, 10, 10));
	 point new_head = *bo;
	 string code[10] = {"E:/snake/snake_evil/0.jpg",
		 "E:/snake/snake_evil/1.jpg", 
		 "E:/snake/snake_evil/2.jpg", 
		 "E:/snake/snake_evil/3.jpg", 
		 "E:/snake/snake_evil/4.jpg", 
		 "E:/snake/snake_evil/5.jpg", 
		 "E:/snake/snake_evil/6.jpg", 
		 "E:/snake/snake_evil/7.jpg", 
		 "E:/snake/snake_evil/8.jpg", 
		 "E:/snake/snake_evil/9.jpg" };
	 char s;
	 char num=0, speed=100;
	 char state = 'a';
	 bool ate = 0;
	 point apple;
	
 public:
	 void  init()
	 {

		 namedWindow("snake", WINDOW_AUTOSIZE);
		 newApple();
		 while (1)
		 {
			 
			 s = waitKey(speed);
			 if (s != -1)
				 changeState(s);
			 move();
			 printsnake();
		 }
	 }
	 void up()
	 {
		 if (ate)
		 {
			 new_head.equalup();
			 body.push_front(new_head);
			 bo = body.begin();
			 new_head = *bo;
		 }
		 new_head.equalup();
		 body.push_front(new_head);
		 body.pop_back();
		 state = 'w';
	 }
	 void down()
	 {
		 if (ate)
		 {
			 new_head.equaldown();
			 body.push_front(new_head);
			 bo = body.begin();
			 new_head = *bo;
		 }
		 new_head.equaldown();
		 body.push_front(new_head);
		 body.pop_back();
		 state = 's';
	 }
	 void left()
	 {
		 if (ate)
		 {
			 new_head.equalleft();
			 body.push_front(new_head);
			 bo = body.begin();
			 new_head = *bo;
		 }
		 new_head.equalleft();
		 body.push_front(new_head);
		 body.pop_back();
		 state = 'a';
	 }
	 void right()
	 {
		 if (ate)
		 {
			 new_head.equalright();
			 body.push_front(new_head);
			 bo = body.begin();
			 new_head = *bo;
		 }
		 new_head.equalright();
		 body.push_front(new_head);
		 body.pop_back();
		 state = 'd';
	 }

	 void changeState(const char sta)
	 {
		 state = sta;
	 }

	 bool eatApple()
	 {
		 if (new_head == apple)
		 {
			 num++;
			 if (num<15)
			 {
				 speed -= 5;
			 }
			 return 1;
		 }
			 
		 else
			 return 0;
	 }

	 void  newApple()
	 {
		 //apple.change(rand() % 64, rand() % 64);
		 char equ = 1;
		 while (equ)
		 {
			 srand(time(0));
			 apple.change(rand() % 60, rand() % 60);
			 deque<point>::const_iterator sa = body.begin();
			 for (unsigned int i = 0; i < body.size(); i++)
			 {
				 if (apple == *(sa++))
				 {
					 equ = 1;
				 }
			 }
			 equ = 0;
		 }
	 }

	 void move()
	 {
		 point sa;
		 bo = body.begin();
		 new_head = *bo;
		 if (eatApple())  //test
		 {
			 ate = 1;
			 newApple();
		 }
		 else
			 ate = 0;
		 if (state == 'w')
			 up();
		 else if (state=='s')
		 {
			 down();
		 }
		 else if (state=='d')
		 {
			 right();
		 }
		 else if(state=='a')
		 {
			 left();
		 }
		 bo = body.begin();
		 sa= *bo;
		 for (unsigned char i = 0; i < (body.size())-1; i++)
		 {
			 if (sa == *(++bo))
			 {
				 gameover=1;
			 }
		 }
	 }
	 void printsnake()
	 {
		 	 if (gameover)
			  {
				  RIO= RIO = game(Rect(310, 430, 20, 25));
				  Mat score = imread(code[num/10]);
				  Mat mask = imread(code[num / 10], 0);
				  score.copyTo(RIO, mask);
				  RIO = RIO = game(Rect(330, 430, 20, 25));
				  score = imread(code[num % 10]);
				  mask = imread(code[num % 10], 0);
				  score.copyTo(RIO, mask);
				  while (1)
				  {
					  imshow("snake", game);
					  if (waitKey(100) != -1)
						  exit(0);
				  }
			  }
		 
		 

			 data = Mat::ones(640, 640, CV_8UC1);
			 for (unsigned char i = 0; i < body.size(); i++)
			 {

				 RIO = data(Rect((body.at(i)).first_data() * 10, (body.at(i)).second_data() * 10, 9, 9));
				 RIO = RIO * 255;
			 }
			 RIO = data(Rect(apple.first_data() * 10, apple.second_data() * 10, 9, 9));
			 RIO = RIO * 255;
			 imshow("snake", data);
		 

	 }

 };
#endif
