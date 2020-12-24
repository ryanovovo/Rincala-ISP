#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<set>
using namespace std;
class log{
public:
	int player;
	int init_stack;
	int direction;
	int player_obtain_points;
	int final_stack;
	int init_stack_size;
	log(){
		player = 0;
		init_stack = 0;
		direction = 0;
		player_obtain_points = 0;
		final_stack = 0;
		init_stack_size = 0;
	}
};
class game_status{
public:
	deque<log> game_log;
	int stack_nums; //總共有幾堆
	int color_nums; //有幾種顏色
	int chess_nums; //一堆有幾個
	int player_nums; //遊戲人數
	deque<deque<int>> game_board;
	vector<int> player_point;
};
class rincala{
public:
	game_status game;
	rincala(){
		clear();
	}
	~rincala(){
		clear();
	}
	void clear(){
		game.game_log.clear();
		game.stack_nums = 0;
		game.color_nums = 0;
		game.chess_nums = 0;
		game.player_nums = 0;
		game.player_point.clear();
		game.game_board.clear();
	}
	bool game_over(){
		set<int> check;
		for(int current_stack = 0; current_stack < game.stack_nums; current_stack++){
			for(int element : game.game_board[current_stack]){
				if(check.find(element) != check.end()){
					return false;
				}
				else{
					check.insert(element);
				}
			}
		}
		return true;
	}
	void init_game_status(int _stack_nums, int _color_nums, int _chess_nums, int _player_nums){
		game.stack_nums = _stack_nums;
		game.color_nums = _color_nums;
		game.chess_nums = _chess_nums;
		game.player_nums = _player_nums;
		game.player_point.clear();
		for(int i = 0; i < game.player_nums; i++){
			game.player_point.push_back(0);
		}
	}
	void init_game_status(){
		cout << "Number of stacks" << endl;
		cin >> game.stack_nums;
		cout << "Number of colors" << endl;
		cin >> game.color_nums;
		cout << "Number of chess per stack" << endl;
		cin >> game.chess_nums;
		cout << "Number of players" << endl;
		cin >> game.player_nums;
		game.player_point.clear();
		for(int i = 0; i < game.player_nums; i++){
			game.player_point.push_back(0);
		}
	}
	void manual_setup(){
		for(int current_stack = 0; current_stack < game.stack_nums; current_stack++){
			int current_stack_color;
			cin >> current_stack_color;
			deque<int> tmp(game.chess_nums, current_stack_color);
			game.game_board.push_back(tmp);
		}// setup every game board with specified color
	}
	void auto_setup(){
		srand(time(NULL));
		for(int current_stack = 0; current_stack < game.stack_nums; current_stack++){
			deque<int> tmp;
			for(int current_idx = 0; current_idx < game.chess_nums; current_idx++){
				tmp.push_back((rand()%game.color_nums) + 1);
			}
			game.game_board.push_back(tmp);
		}
	}//random setup game board
	void move(int init_stack, bool direction, int player){// 1 = clockwise 0 = counter clockwise
		log movement;
		movement.init_stack = init_stack;
		movement.direction = direction;
		movement.player = player;
		movement.init_stack_size = game.game_board[init_stack].size();
		deque<int> init_stack_cpy = game.game_board[init_stack];
		game.game_board[init_stack].clear();
		if(direction == 1){
			int final_stack = (init_stack + init_stack_cpy.size())%game.stack_nums;
			int init_stack_size = init_stack_cpy.size();
			movement.final_stack = final_stack;
			for(int current_stack = init_stack+1; current_stack <= init_stack_size+init_stack; current_stack++){
				game.game_board[current_stack%game.stack_nums].push_back(init_stack_cpy.front());
				init_stack_cpy.pop_front();
			}
			if(game.game_board[final_stack].size() > 1){
				int final_stack_idx_last = *(game.game_board[final_stack].end()-1);
				int final_stack_idx_second_last = *(game.game_board[final_stack].end()-2);
				if(final_stack_idx_last == final_stack_idx_second_last){
					game.player_point[player] += final_stack_idx_last;
					movement.player_obtain_points = final_stack_idx_last;
					game.game_board[final_stack].pop_back();
					game.game_board[final_stack].pop_back();
				}
				else{
					movement.player_obtain_points = 0;
				}
			}
		}
		else if(direction == 0){
			int final_stack;
			int init_stack_size = init_stack_cpy.size();
			if((init_stack - init_stack_size)%game.stack_nums < 0){
				final_stack = (init_stack - init_stack_size)%game.stack_nums + game.stack_nums;
			}
			else{
				final_stack = (init_stack - init_stack_size)%game.stack_nums;
			}
			movement.final_stack = final_stack;
			cout << final_stack << endl;
			for(int current_stack = init_stack-1; current_stack >= init_stack-init_stack_size; current_stack--){
				if(current_stack%game.stack_nums < 0){
					game.game_board[current_stack%game.stack_nums+game.stack_nums].push_back(init_stack_cpy.front());
				}
				else{
					game.game_board[current_stack%game.stack_nums].push_back(init_stack_cpy.front());
				}
				init_stack_cpy.pop_front();
			}
			if(game.game_board[final_stack].size() > 1){
				int final_stack_idx_last = *(game.game_board[final_stack].end()-1);
				int final_stack_idx_second_last = *(game.game_board[final_stack].end()-2);
				if(final_stack_idx_last == final_stack_idx_second_last){
					game.player_point[player] += final_stack_idx_last;
					movement.player_obtain_points = final_stack_idx_last;
					game.game_board[final_stack].pop_back();
					game.game_board[final_stack].pop_back();
				}
				else{
					movement.player_obtain_points = 0;
				}
			}
		}
		game.game_log.push_back(movement);
	}// move a specified stack
	int calculate_points(int init_stack, int direction){
		int before = game.player_point[0];
		move(init_stack, direction, 0);
		int after = game.player_point[0];
		undo();
		return after - before;
	}
	pair<int, int> max_point(){
		pair <int, int> rt; // max stack it, direction
		int current_max_val = 0;
		rt.first  = 0;
		rt.second = 0;
		for(int current_stack = 0; current_stack < game.stack_nums; current_stack++){
			if(current_max_val.first < calculate_points(current_stack, 0)){
				current_max_val.fisrt  = calculate_points(current_stack, 0);
				current_max_val.second = current_stack;
			}
		}
		for(int current_stack = 0; current_stack < game.stack_nums; current_stack++){
			if(current_max_val.first < calculate_points(current_stack, 1)){
				current_max_val.fisrt  = calculate_points(current_stack, 1);
				current_max_val.second = current_stack;
			}
		}
		return current_max_val;
	}
	void show_game_status(){
		cout << "===================================================" << endl;
		for(int current_stack = 0; current_stack < game.stack_nums; current_stack++) {
			cout << current_stack << " ";
			for(int current_idx = 0; current_idx < game.game_board[current_stack].size(); current_idx++) {
				cout << game.game_board[current_stack][current_idx] << ",";
			}
			cout << endl;
		}
		cout << "===================================================" << endl;
		for(int current_player_idx = 0; current_player_idx < game.player_nums; current_player_idx++) {
			cout << " player" << current_player_idx << ": " << game.player_point[current_player_idx];
		}
		cout << endl;
	}//show what is going on 
	void undo(){
		if(game.game_log.empty()){
			cout << "already the last one" << endl;
			return;
		}
		else{
			log latest_log = game.game_log.back();
			int init_stack = latest_log.init_stack; //prev move stack
			int init_stack_size = latest_log.init_stack_size; // prev move stack size
			int stack_nums = game.stack_nums; // total number of stacks
			int player = latest_log.player; // player movement
			int player_obtain_points = latest_log.player_obtain_points; // player obtain points
			int final_stack = latest_log.final_stack; // which stack is the final one
			if(player_obtain_points > 0){
				game.game_board[final_stack].push_back(player_obtain_points); 
				game.game_board[final_stack].push_back(player_obtain_points);
			}// if the player gets any points, must reset
			if(latest_log.direction == 1){
				deque<int> tmp;
				for(int current_stack = final_stack; current_stack > final_stack-init_stack_size; current_stack--) {
					if(current_stack%stack_nums < 0){
						tmp.push_back(game.game_board[(current_stack%stack_nums)+stack_nums].back());
						game.game_board[(current_stack%stack_nums)+stack_nums].pop_back();
					}
					else{
						tmp.push_back(game.game_board[current_stack%stack_nums].back());
						game.game_board[current_stack%stack_nums].pop_back();
					}
				}
				reverse(tmp.begin(), tmp.end());
				game.game_board[init_stack] = tmp;
			}
			else{
				deque<int> tmp;
				for(int current_stack = final_stack; current_stack < final_stack+init_stack_size; current_stack++) {
					tmp.push_back(game.game_board[current_stack%stack_nums].back());
					game.game_board[current_stack%stack_nums].pop_back();
				}
				reverse(tmp.begin(), tmp.end());
				game.game_board[init_stack] = tmp;
			}
			game.game_log.pop_back();
			game.player_point[player] -= player_obtain_points;
		}
	}
};
int main(){
	rincala game;
	game.init_game_status(10, 5, 7, 2);
	game.auto_setup();
	while(!game.game_over()){
		pair<int, int> mx = game.max_point;
	}
}
