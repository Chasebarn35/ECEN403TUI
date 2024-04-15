#include <ncurses.h>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

bool is_number(const string& s) {     return !s.empty() && find_if(s.begin(),          s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end(); }

int main(int argc, char** argv){
	// initialize the screen
	// sets up memory and clears the screen
	initscr();
	cbreak(); //
	noecho(); //Dont print text arbitarily to screen
	curs_set(0);
	int height, width, start_y, start_x;
	height = 5;
	width = 70;
	start_x = 5;
	start_y = 2;
	WINDOW * win =  newwin(height,width,start_y, start_x);
	WINDOW * win2 = newwin(1,2,start_y+1, start_x+width / 2);
	WINDOW * win3 = newwin(1,2,start_y+3, start_x+width / 2);

	int fd = open("/dev/ttyACM0", O_RDWR);
	ssize_t written, red;

	box(win,0,0);
	mvwprintw(win,2,4,"[------------------------------------------------------------]");
	intptr_t bar = 0;
	intptr_t rcv = 0;
	intptr_t tmp = 0;
	mvwprintw(win2,0,0,"%d",bar);
	mvwprintw(win3,0,0,"%d",rcv);
	refresh();
	wrefresh(win);
	wrefresh(win2);
	wrefresh(win3);
	char str[4];
	while(true){
		char c = getch();
		switch(c){
			case 'q':
				endwin();
				return 0;
				break;
			case 'l':
				if(bar < 60){
					mvwaddch(win,2,bar+5,'|');
					bar++;
				}
				break;
			case 'h':
				if(bar > 0){
					bar--;
					mvwaddch(win,2,bar+5,'-');
				}
				break;
			case 'i':
				getnstr(str,2);//Between 0 and 99 input
				if(is_number(string(str))){
					tmp = atoi(str);
					if(tmp <=60 && tmp >=0)	
						bar = tmp;
				}
				break;
			case 'e':
				//TODO WRITE BAR TO TTYACM0
				written = write(fd, (void*)bar, 1);
				if(written >=0){
					//TODO READ
					red = read(fd,(void*)&rcv,1);
				}
				break;


				/*default:
				  mvwprintw(win, 1, 1, "%d",c);
				  wrefresh(win);
				  break;*/
		}
		werase(win2);
		mvwprintw(win2,0,0,"%d",bar);
		mvwprintw(win3,0,0,"%d",rcv);
		wrefresh(win);
		wrefresh(win2);
	}	
	//[------------------------------]
	//[███|--------------------------]
	//endwin();
	//deallocates memory and ends ncurses
	//return 0;
}
