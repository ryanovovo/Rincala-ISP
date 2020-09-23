#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;

class rincala{
public:
	int stack_nums; //總共有幾堆
	int color_nums; //有幾種顏色
	int chess_nums; //一堆有幾個
	int player_nums; //遊戲人數
	deque<deque<int>> game_board;
	vector<int> player_point;
	rincala(){
		stack_nums = 0;
		color_nums = 0;
		chess_nums = 0;
		player_nums = 0;
		for(int i = 0; i < game_board.size(); i++) {
			game_board[i].clear(); // init
		}
		player_point.clear();
	}
	void clear(){
		stack_nums = 0;
		color_nums = 0;
		chess_nums = 0;
		player_nums = 0;
		for(int i = 0; i < game_board.size(); i++){
			game_board[i].clear(); // init game board
		}
		player_point.clear();
	}
	~rincala(){
		clear();
	}
	void init_game_status(int _stack_nums, int _color_nums, int _chess_nums, int _player_nums){
		stack_nums = _stack_nums;
		color_nums = _color_nums;
		chess_nums = _chess_nums;
		player_nums = _player_nums;
		player_point.clear();
		for(int i = 0; i < player_nums; i++){
			player_point.push_back(0);
		}
	}
	void init_game_status(){
		cout << "Number of stacks" << endl;
		cin >> stack_nums;
		cout << "Number of colors" << endl;
		cin >> color_nums;
		cout << "Number of chess per stack" << endl;
		cin >> chess_nums;
		cout << "Number of players" << endl;
		cin >> player_nums;
		player_point.clear();
		for(int i = 0; i < player_nums; i++){
			player_point.push_back(0);
		}
	}
	void manual_setup(){
		for(int current_stack = 0; current_stack < stack_nums; current_stack++){
			int current_stack_color;
			cin >> current_stack_color;
			deque<int> tmp(chess_nums, current_stack_color);
			game_board.push_back(tmp);
		}// setup every game board with specified color
	}
	void auto_setup(){
		srand(time(NULL));
		for(int current_stack = 0; current_stack < stack_nums; current_stack++){
			deque<int> tmp;
			for(int current_idx = 0; current_idx < chess_nums; current_idx++){
				tmp.push_back((rand()%color_nums) + 1);
			}
			game_board.push_back(tmp);
		}
	}//random setup game board
	void move(int init_stack, bool direction, int player){// 1 = clockwise 0 = counter clockwise
		if(direction == 1){
			int final_stack = (init_stack + game_board[init_stack].size())%stack_nums;
			int init_stack_size = game_board[init_stack].size();
			for(int current_stack = init_stack+1; current_stack <= init_stack_size+init_stack; current_stack++){
				game_board[current_stack%stack_nums].push_back(game_board[init_stack].front());
				game_board[init_stack].pop_front();
			}
			if(game_board[final_stack].size() > 1){
				int final_stack_idx_last = *(game_board[final_stack].end()-1);
				int final_stack_idx_second_last = *(game_board[final_stack].end()-2);
				if(final_stack_idx_last == final_stack_idx_second_last){
					player_point[player] += final_stack_idx_last;
					game_board[final_stack].pop_back();
					game_board[final_stack].pop_back();
				}
			}
		}
		else if(direction == 0){
			int final_stack = (init_stack - game_board[init_stack].size())%stack_nums;
			int final_stack_size = game_board[final_stack].size()+1;
			int init_stack_size = game_board[init_stack].size();
			for(int current_stack = init_stack-1; current_stack >= init_stack-init_stack_size; current_stack--){
				game_board[current_stack%stack_nums].push_back(game_board[init_stack].front());
				game_board[init_stack].pop_front();	
			}
			if(game_board[final_stack].size() > 1){
				int final_stack_idx_last = *(game_board[final_stack].end()-1);
				int final_stack_idx_second_last = *(game_board[final_stack].end()-2);
				if(final_stack_idx_last == final_stack_idx_second_last){
					player_point[player] += final_stack_idx_last;
					game_board[final_stack].pop_back();
					game_board[final_stack].pop_back();
				}
			}
		}
	}
	/*int calculate_points (int init_stack, bool direction){
		int final_stack = 0;
		if(direction == 1){
			final_stack = (init_stack + game_board[init_stack].size())%stack_nums;
		}
		else if(direction == 0){
			final_stack = (init_stack - game_board[init_stack].size())%stack_nums;
		}
		deque<int> tmp = game_board[init_stack];
		game_board[init_stack].clear();
		int final_stack_size = game_board[final_stack].size();
		if(final_stack_size > 1){
			int final_stack_idx_last = *(game_board[final_stack].end()-1);
			int final_stack_idx_second_last = *(game_board[final_stack].end()-2);
			if( final_stack_idx_last == final_stack_idx_second_last){
				game_board[init_stack] = tmp;
				return final_stack_idx_last;
			}
		}
		else{
			game_board[init_stack] = tmp;
			return 0;
		}
	}*/
	void show_game_status(){
		cout << "===================================================" << endl;
		for(int current_stack = 0; current_stack < stack_nums; current_stack++) {
			cout << current_stack << " ";
			for(int current_idx = 0; current_idx < game_board[current_stack].size(); current_idx++) {
				cout << game_board[current_stack][current_idx];
			}
			cout << endl;
		}
		cout << "===================================================" << endl;
		for(int current_player_idx = 0; current_player_idx < player_nums; current_player_idx++) {
			cout << " player" << current_player_idx << ": " << player_point[current_player_idx];
		}
		cout << endl;
	}
};
int main(){
	rincala game;
	game.init_game_status();
	game.auto_setup();
	game.show_game_status();
	cout << game.calculate_points(1, 1) << endl;
	game.move(1, 1, 1);

	game.show_game_status();
}
