#include <iostream>
#include <vector>

#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

using namespace std;
SDL_Window *win = SDL_CreateWindow("Seven Segment Display | Abthahi Ahmed Rifat", 100, 100, 500, 200, 0);
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
SDL_Event event;



class SegmentDisplay{
	
private:
	int x, y;
	int digit = 0;
	
	int a, b, c, d, e, f, g;
	
	vector<vector<int>> sdigit = {
			{0, 	  this->a, this->a, this->a, 0      },
			{this->b, 0,       0,       0,       this->c},
			{this->b, 0,       0,       0,       this->c},
			{this->b, 0,       0,       0,       this->c},
			{this->b, 0,       0,       0,       this->c},
			{0,       this->d, this->d, this->d, 0      },
			{this->e, 0,       0,       0,       this->f},
			{this->e, 0,       0,       0,       this->f},
			{this->e, 0,       0,       0,       this->f},
			{this->e, 0,       0,       0,       this->f},
			{0,       this->g, this->g, this->g, 0      },
		};
	void reset(){
		this->a = -1;
		this->b = -1;
		this->c = -1;
		this->d = -1;
		this->e = -1;
		this->f = -1;
		this->g = -1;		
	}
	
public:

	SegmentDisplay(int x, int y){
		this->x = x;
		this->y = y;
		
		this->a = -1;
		this->b = -1;
		this->c = -1;
		this->d = -1;
		this->e = -1;
		this->f = -1;
		this->g = -1;
	}
	
	void setNumber(int digit){
		this->digit = digit;
	}
	
	void update(){
	
		if (this->digit == 0){
			reset();
			this->a = this->b = this->c = this->e = this->f = this->g = 1;
		}
		else if (this->digit == 1){
			reset();
			this->c = this->f = 1;
		}
		else if(this->digit == 2){
			reset();
			this->a = this->c = this->d = this->e = this->g = 1;
		}
		else if(this->digit == 3){
			reset();
			this->a = this->c = this->d = this->f = this->g = 1;
		}	
		else if(this->digit == 4){
			reset();
			this->b = this->c = this->d = this->f = 1;
		}
		else if(this->digit == 5){
			reset();
			this->a = this->b = this->d = this->f = this->g = 1;
		}
		else if(this->digit == 6){
			reset();
			this->a = this->b = this->d = this->e = this->f = this->g = 1;
		}
		else if(this->digit == 7){
			reset();
			this->a = this->c = this->f = 1;
		}		
		else if(this->digit == 8){
			reset();
			this->a = this->b = this->c = this->d = this->e = this->f = this->g = 1;
		}
		else if(this->digit == 9){
			reset();
			this->a = this->b = this->c = this->d = this->f = this->g = 1;
		}
		else {
			reset();
		}
		
		
		
		this->sdigit = {
			{0, 	  this->a, this->a, this->a, 0      },
			{this->b, 0,       0,       0,       this->c},
			{this->b, 0,       0,       0,       this->c},
			{this->b, 0,       0,       0,       this->c},
			{this->b, 0,       0,       0,       this->c},
			{0,       this->d, this->d, this->d, 0      },
			{this->e, 0,       0,       0,       this->f},
			{this->e, 0,       0,       0,       this->f},
			{this->e, 0,       0,       0,       this->f},
			{this->e, 0,       0,       0,       this->f},
			{0,       this->g, this->g, this->g, 0      },
		};
	}
	
	void draw(){
		
		for (int i = 0; i < 11; i++){
			for (int j = 0; j < 5; j++){
				
				if (this->sdigit[i][j] == 1){
					SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
					SDL_Rect rect = {x + j * 10, y + i * 10, 10, 10};
					SDL_RenderFillRect(ren, &rect);	
				}
				else if (this->sdigit[i][j] == -1){
					SDL_SetRenderDrawColor(ren, 40, 0, 0, 255);
					SDL_Rect rect = {x + j * 10, y + i * 10, 10, 10};
					SDL_RenderFillRect(ren, &rect);	
				}				
			}
		}
		
		
		
	}
	
	
	
};




int main(int argc, char **argv)
{

	vector<SegmentDisplay> clock;
	
	for (int i = 0; i < 6; i++){
		int a = 0;
		int x = i * 70;
		
		if (i != 0 && i % 2 == 0) a += 10;
		x += a;
		
		clock.push_back(SegmentDisplay(40 + x, 50));
	}
	
	int h, m, s;

	
	
	while (true){
		
		time_t t = time(0);
		struct tm* time = localtime(&t);
		
		h = (time->tm_hour > 12) ? time->tm_hour - 12 : time->tm_hour;
		m = time->tm_min;
		s = time->tm_sec;
		
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		
		
		
		// Hours
		clock[0].setNumber(h / 10);
		clock[1].setNumber(h % 10);
		// Minutes
		clock[2].setNumber(m / 10);
		clock[3].setNumber(m % 10);	
		// Seconds
		clock[4].setNumber(s / 10);
		clock[5].setNumber(s % 10);		
		
		for (auto s : clock){
			s.update();
			s.draw();
		}		
		
		
		
		
		
		SDL_RenderPresent(ren);
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT){
			break;
		}
		
	}
	
	

	
	return 0;
}
