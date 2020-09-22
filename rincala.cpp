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
		for(int current_stack = 0; current_stack < stack_nums; current_stack++){
			for(int current_idx = 0; current_idx < chess_nums; current_idx++){
				srand(time(NULL));
				game_board[current_stack][current_idx] = rand()%color_nums + 1;
			}
		}
	}
	void move(int init_stack, bool direction, int player){
		if(direction == 1){
			int final_stack = (init_stack + game_board[init_stack].size())%stack_nums;
			int final_stack_size = game_board[final_stack].size()+1;
			int init_stack_size = game_board[init_stack].size();
			for(int current_stack = init_stack+1; current_stack <= init_stack_size+init_stack; current_stack++){
				game_board[current_stack].push_back(game_board[init_stack].front());
				game_board[init_stack].pop_front();
			}
			if(game_board[final_stack][final_stack_size-1] == game_board[final_stack][final_stack_size-2]){
				player_point[player] += game_board[final_stack][final_stack_size-1];
				game_board[final_stack].pop_back();
				game_board[final_stack].pop_back();
			}
		}
		else if(direction == 0){
			int final_stack = (init_stack - game_board[init_stack].size())%stack_nums;
			int final_stack_size = game_board[final_stack].size()+1;
			int init_stack_size = game_board[init_stack].size();
			for(int current_stack = init_stack-1; current_stack >= init_stack-init_stack_size; current_stack--){
				game_board[current_stack].push_back(game_board[init_stack].front());
				game_board[init_stack].pop_front();	
			}
			if(game_board[final_stack][final_stack_size-1] == game_board[final_stack][final_stack_size-2]){
				player_point[player] += game_board[final_stack][final_stack_size-1];
				game_board[final_stack].pop_back();
				game_board[final_stack].pop_back();
			}
		}
	}
	int calculate_points (int init_stack, bool direction){
		int final_stack = 0;
		int final_stack_size = 0;
		int init_stack_size = game_board[init_stack].size();
		if(direction == 1){
			final_stack = (init_stack + game_board[init_stack].size())%stack_nums;
			final_stack_size = game_board[final_stack].size()+1;

		}
		else if(direction == 0){
			final_stack = (init_stack - game_board[init_stack].size())%stack_nums;
			final_stack_size = game_board[final_stack].size()+1;
		}
		if(game_board[init_stack][init_stack_size-1] == game_board[final_stack][final_stack_size-1]){
			return game_board[init_stack][init_stack_size-1];
		}
		return 0;
	}
	void show_game(){
		
	}
};
int main(){
}
