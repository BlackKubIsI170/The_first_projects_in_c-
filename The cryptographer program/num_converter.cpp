#include <iostream>
#include <cstring>


void to_s(int n, int s2);
int to_d(char *a, int s1);

int main(){
    int s1, s2;
    std::cout << "В какой систтеме счисления число? - ";
    std::cin >> s1;
    std::cout << "Введите чило: ";
    char n[30] = "";
    std::cin >> n;
    std::cout << "В какую систему счисления перевести число? - ";
    std::cin >> s2;

    to_s(to_d(n, s1), s2);
    return 0;
}

void to_s(int n, int s2){
    char arr[100] = "";
    int i = 0;
    while (n != 0){
        if (n % s2 >= 0 && n % s2 < 10){
            arr[i] = n % s2 + 48;
        }
        else arr[i] = char(n % s2 + 55);
        n /= s2;
        i++;
    }
    for (int g = 0;g < strlen(arr) / 2;g++){
        char c = arr[g];
        arr[g] = arr[strlen(arr) - g - 1];
        arr[strlen(arr) - g - 1] = c;
    }
    std::cout << "Ответ: " << arr << std::endl;
}

int to_d(char *a, int s1){
    int arr[strlen(a)], k = 0, p = 1;
    for (int i = 0;a[i] != '\0';i++){
        if (isdigit(a[i])) arr[i] = int(a[i]) - 48;
        else arr[i] = int(a[i]) - 55;
    }
    for (int i = 0;i < strlen(a);i++){
        k += arr[strlen(a) - i - 1] * p;
        p *= s1;
    }
    return k;
}
