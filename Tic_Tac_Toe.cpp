#include <iostream>
#include <cmath>

// funkS

int result(int* empty_box, char* box);
int next(int* empty_box, char* box, char move);
int sum(int* arr);
int n_of_wins(int* empty_box, char* box, int n, char move);
int div_two(int i, int n);
void prinT(char *box);

//

int main(){
    char player = 'O';
    char ai = 'X';

    int empty_box[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    char box[9] = {'*', '*', '*', '*', '*', '*', '*', '*', '*'};

    while (result(empty_box, box) != 0 && result(empty_box, box) != 10 && result(empty_box, box) != -10){
        prinT(box);
        int x, y;
        std::cout << "Введите y: ";
        std::cin >> x;
        std::cout << "Введите x: ";
        std::cin >> y;
        box[(x - 1)* 3 + y - 1] = 'O';
        empty_box[(x - 1)* 3 + y - 1] = 1;
        int n = next(empty_box, box, 'X');
        box[n] = 'X';
        empty_box[n] = 1;
    }
    prinT(box);
    if (result(empty_box, box) == 0) std::cout << "Ничья" << std::endl;
    else if (result(empty_box, box) == 10) std::cout << "Победил компьютер" << std::endl;
    else if (result(empty_box, box) == -10) std::cout << "Победил игрок" << std::endl;
    return 0;
}

// funkS

int result(int* empty_box, char* box){

    if (
        (box[0] == 'O' && box[1] == 'O' && box[2] == 'O') ||
        (box[3] == 'O' && box[4] == 'O' && box[5] == 'O') ||
        (box[6] == 'O' && box[7] == 'O' && box[8] == 'O') ||
        (box[0] == 'O' && box[3] == 'O' && box[6] == 'O') ||
        (box[1] == 'O' && box[4] == 'O' && box[7] == 'O') ||
        (box[2] == 'O' && box[5] == 'O' && box[8] == 'O') ||
        (box[0] == 'O' && box[4] == 'O' && box[8] == 'O') ||
        (box[2] == 'O' && box[4] == 'O' && box[6] == 'O')
    ) return -10;
    else if(
        (box[0] == 'X' && box[1] == 'X' && box[2] == 'X') ||
        (box[3] == 'X' && box[4] == 'X' && box[5] == 'X') ||
        (box[6] == 'X' && box[7] == 'X' && box[8] == 'X') ||
        (box[0] == 'X' && box[3] == 'X' && box[6] == 'X') ||
        (box[1] == 'X' && box[4] == 'X' && box[7] == 'X') ||
        (box[2] == 'X' && box[5] == 'X' && box[8] == 'X') ||
        (box[0] == 'X' && box[4] == 'X' && box[8] == 'X') ||
        (box[2] == 'X' && box[4] == 'X' && box[6] == 'X')
    ) return 10;
    else if (sum(empty_box) == 9) return 0;
    else return -1;
}

int next(int* empty_box_, char* arr, char move){
    if (sum(empty_box_) == 9){
        return -1;
    }
    char box[9];
    int empty_box[9];
    for (int i = 0;i < 9;i++) box[i] = arr[i];
    for (int i = 0;i < 9;i++) empty_box[i] = empty_box_[i];


    for (int i = 0;i < 9;i++){
        if (empty_box[i] == 0){
            box[i] = 'X';
            empty_box[i] = 1;
            if (result(empty_box, box) == 10) return i;
            for (int i = 0;i < 9;i++) box[i] = arr[i];
            for (int i = 0;i < 9;i++) empty_box[i] = empty_box_[i];
            box[i] = 'O';
            empty_box[i] = 1;
            if (result(empty_box, box) == -10) return i;
            for (int i = 0;i < 9;i++) box[i] = arr[i];
            for (int i = 0;i < 9;i++) empty_box[i] = empty_box_[i];
        }
    }

    for (int i = 0;i < 9;i++) box[i] = arr[i];
    for (int i = 0;i < 9;i++) empty_box[i] = empty_box_[i];
    int next_boxes[9 - sum(empty_box)][2];
    for (int i = 0, k = 0;i < 9;i++){
        if (empty_box[i] == 0){
            next_boxes[k][0] = n_of_wins(empty_box, box, i, move);
            next_boxes[k][1] = i;
            k++;
        }
    }
    int max_n = next_boxes[0][0], n = next_boxes[0][1];
    for (int i = 0;i < 9 - sum(empty_box);i++){
        if (max_n <= next_boxes[i][0]){
            max_n = next_boxes[i][0];
            n = next_boxes[i][1];
        }
    }
    return n;
}

int sum(int * arr){
    int k = 0;
    for (int i = 0;i < 9;i++){
        k += arr[i];
    }
    return k;
}

int n_of_wins(int* empty_box, char* box, int n, char move){
    int wins = 0;
    box[n] = move;
    empty_box[n] = 1;

    //prinT(box);

    for (int i = 0;i < pow(2, 9 - sum(empty_box));i++){
        char arr[9];
        for (int m = 0;m < 9;m++) arr[m] = box[m];
        for (int g = 0, k = 0;g < 9;g++){
            if (empty_box[g] == 0){
                if (k == 0){
                    if (div_two(i, k) % 2 == 1) arr[g] = 'X';
                    else arr[g] = 'O';
                }
                else{
                    if (div_two(i, k) % 2 == 1) arr[g] = 'X';
                    else arr[g] = 'O';
                }
                k++;
            }
        }
        int empty_box_[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        if (result(empty_box_, arr) == 10) wins++;
        //std::cout << result(empty_box_, arr) << std::endl;
        //prinT(arr);
    }
    return wins;
}

int div_two(int i, int n){
    if (n == 0) return i;
    else return div_two(i / 2, n - 1);
}

void prinT(char *box){
    std::cout << "    1   2   3   " << std::endl;
    std::cout << "---------------" << std::endl << 1 << " | ";
    for (int i = 0;i < 9;i++){
        if (i != 0 && i % 3 == 0) std::cout << std::endl << "---------------" << std::endl << i / 3 + 1 << " | ";
        std::cout << box[i] << " | ";
    }
    std::cout << std::endl << "---------------" << std::endl;
}

//
