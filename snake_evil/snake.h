#ifndef SNAKE_H
#define SNAKE_H

#include<iostream>
#include <utility>
#include<deque>
using namespace std;

bool gameover = 0;

 class point
 {

 private:

	 pair<int,int> pos;

 public:
	 point()
	 {
		 pos.first = 0;
		 pos.second = 0;
	 }

	 point( const int &x, const int &y) //°´XY×ø±ê¸³Öµ
	 {
		 pos.first = x;
		 pos.second = y;
	 }

	 void change(const int &x, const int &y)
	 {
		 pos.first = x;
		 pos.second = y;
	 }
	 void equalup()
	 { 
		 if ((--pos.second) <0)
		 {
			 gameover = 1;
		 }
	 }
	 void equaldown()
	 {

		 if ((++pos.second)==64)
		 {
			 gameover=1;
		 }
	 }
	 void equalleft()
	 {
		 if ((--pos.first)<0)
		 {
			 gameover=1;
		 }
	 }
	 void equalright()
	 {
		 if ((++pos.first) == 64)
		 {
			 gameover=1;
		 }
	 }
	 friend ostream& operator<<(ostream &out, point po)
	 {
		 out << "(" << po.pos.first << "," << po.pos.second << ")" << "  ";
		 return out;
	 }

	 bool operator==(point p)
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

	 deque<point> body{ {32,32},{ 32,32 }, { 32,32 },{ 32,32 } };
	 deque<point>::const_iterator bo=body.begin();
	 point new_head=*bo;
	 char state = 'a'£»
	 bool ate = 0;
	 point apple;
	
 public:
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
			 return 1;
		 else
			 return 0;
	 }

	 void  newApple()
	 {
		 char equ = 1;
		 while (equ)
		 {
			 apple.change(rand() % 64, rand() % 64);
			 deque<point>::const_iterator sa = body.begin();
			 for (unsigned int i = 0; i < body.size(); i++)
			 {
				 if (apple==*(sa++))
				 {
					 equ = 1;
				 }
			 }
			 equ = 0;
		 }
	 }
	 //void set() //just for test
	 //{
		// ate = 1;
	 //}
	 //void reSet() //just for test
	 //{
		// ate = 0;
	 //}
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
		 else
		 {
			 left();
		 }
		 bo = body.begin();
		 sa= *bo;
		 for (unsigned int i = 0; i < (body.size())-1; i++)
		 {
			 if (sa == *(++bo))
			 {
				 gameover=1;
			 }
		 }
	 }
	 void printsnake()
	 {
		 deque<point>::const_iterator sa=body.begin();
		 for (unsigned int i = 0; i < body.size();i++)
		 {
			 cout << *(sa++);
		 }
		 cout <<"apple located at : "<<apple<<"  gameover"<<gameover<<endl;
	 }

 };
#endif
