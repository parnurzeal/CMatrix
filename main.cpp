#include<iostream>
#include<vector>
#include<stdio.h>
#include<ctime>
#include<sys/ioctl.h>
#include<map>
#include<deque>
using namespace std;

int msleep(unsigned long milisec)
{
    struct timespec req={0};
    time_t sec=(int)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    while(nanosleep(&req,NULL)==-1)
        continue;
    return 1;
}

typedef struct{
  char c;
  int live;
}Code;

int main(void){
  static const char alpha[] =
    "0123456789"
    "!@#$%^&*"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int alphaSize = sizeof(alpha)/sizeof(char);
  cout<<alphaSize;
  // get terminal size
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  int col_size = w.ws_col;
  int row_size = w.ws_row;
  cout<< col_size<< " "<<row_size<<endl;
  deque<map<int, Code> > matrix;
  for(int i=0;i<10;i++){
    map<int,Code> new_map;
    for(int i = 0;i<10;i++){
      int new_col = rand()%col_size+1;
      int new_live = rand()%row_size+1;
      char new_c = alpha[rand()%alphaSize];
      //cout<<new_c<<endl;
      //cout<<new_col<<" "<<new_live<<" "<<new_c<<endl;
      Code new_code = { new_c, new_live};
      new_map[new_col] = new_code;
    }
    matrix.push_front(new_map);
  }
  // clear screen
  printf("\033[2J\033[1;1H");
  // render
  for(int i = 0;i<matrix.size();i++){
    for(map<int,Code>::iterator it = matrix[i].begin();it!=matrix[i].end();it++){
      int print_col = it->first;
      Code print_code = it->second;
      printf("\033[%d;%dH",i,print_col);//, 0, print_col);
      printf("%c",print_code.c);
      //printf("hello");
      //printf("%c",print_code.c);
      fflush(stdout);
    }
  }
  msleep(1000L);
  return 0;
}
