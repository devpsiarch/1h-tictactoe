#include <iostream>
#include <cassert>
using namespace std;
void init_ttt(int *arr){
    for(int i = 0; i < 3 ; i++){
        for (int j = 0; j < 3; j++) {
            assert(i*3+j < 9);
            arr[i*3+j] = 0;
        }
    }
}
// i will consider 1 as a X and -1 as an O
void print_board(int *arr){
    for(int i = 0; i < 3 ; i++){
        for (int j = 0; j < 3; j++) {
            assert(i*3+j < 9);
            switch (arr[i*3+j]) {
                case 1:
                    cout << "X ";
                    continue;
                case -1:
                    cout << "O ";
                    continue;
                default:
                   cout << "0 ";
                    continue;
            }
        }
        cout << endl;
    }
}
bool set_loc(int *arr,int loc,char val){
    assert(loc < 9);
    assert(val == 'X' || val == 'O');
    if(arr[loc] != 0) return false;
    arr[loc] = (val == 'X') ? 1 : -1;
    return true;
}
bool check_dig(int* arr,int n,int val){
    assert(n < 3);
    for(int i = n ; i < 9 ; i+= 3){
        if(arr[i] != val) return false;
    }
    return true;
}
bool check_hor(int *arr,int n,int val){
    assert(n % 3 == 0);
    for(int i = 0 ; i < 3 ; i++){
        if(arr[n+i] != val) return false;
    }
    return true;
}
bool check_til(int *arr,int val){
    // 0 , 4 , 8 || 2,4,6 
    // in this case idk if there is a better solution for this
    int checker[2][3] = {
        {0,4,8},
        {2,4,6},
    };
    bool res1 = true;
    bool res2 = true;
    for (int i = 0; i < 3; i++) {
        if(arr[checker[0][i]] != val) res1 &= false;
    }
    for (int i = 0; i < 3; i++) {
        if(arr[checker[1][i]] != val) res2 &= false;
    }
    return res1 | res2;
}
bool check_win(int *arr,int val){
    bool res = false;
    for (int i = 0; i < 3; i++) {
        res |= check_dig(arr,i,val);
        res |= check_hor(arr,i*3,val);
    }
    res |= check_til(arr,val);
    return res;
}

bool check_draw(bool win,int *arr){
    if(win) return false;
    //check for the ocupency of the board
    int res = 0;
    for(int i = 0 ; i < 9 ; i++){
        if(arr[i] == 0) res ++;
    }
    return (res > 0) ? false : true; 
}
int main(void){
    //init the board
    int ttt[9];
    init_ttt(ttt);
    bool turn = true;
    //hold location for setting the board
    int x ,y;
    bool game_state = check_win(ttt,1) || check_win(ttt,-1) ;
    bool draw = check_draw(game_state,ttt);
    //while no one wins and no draws
    while(!game_state && !draw){
        print_board(ttt);
        //takes turns in the setting the plays
        if(turn){
            cout << "X turn : ";
            cin >> x >> y;
            if(!set_loc(ttt,x*3+y,'X')) continue;
            turn = !turn ;
        }else{
            cout << "O turn : ";
            cin >> x >> y;
            if(!set_loc(ttt,x*3+y,'O')) continue;
            turn = !turn ;
        }
        //updating the game state 
        game_state = check_win(ttt,1) || check_win(ttt,-1) ;
        draw = check_draw(game_state,ttt);
    }
    print_board(ttt);
    //showing the results
    if(draw){
        cout << "DRAW!!!\n";
        return 0;
    }
    if(check_win(ttt,1)){
        cout << "X won!!!\n";
        return 0;
    }
    if(check_win(ttt,-1)){
        cout << "O won!!!\n";
        return 0;
    }   
    return 0;
}
