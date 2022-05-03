#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>


std::string rot1(std::string a){
    for (int i = 0; i < (int) a.size(); i++) a[i] = (char) (((int) a[i]) + 1);
    return a;
}


std::string transpositions(std::string a){
    for (int i = 0; i < (int) a.size() - (int) a.size() % 2; i += 2){
        char c = a[i];
        a[i] = a[i + 1];
        a[i + 1] = c;
    }
    return a;
}


std::string morse_code(std::string a){
    std::string d[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
          "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
          "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
          "--.."};
    std::string new_a;
    for (int i = 0; i < (int) a.size(); i++){
        if (isalnum(a[i])){
            new_a += d[(int) tolower(a[i]) - 97];
        }
    }
    return new_a;
}


std::string caesars_cipher(std::string a, int n){
    for (int i = 0; i < (int) a.size(); i++){
        if (isalnum(a[i])){
            a[i] = (char) (97 + (((int) tolower(a[i]) - 97) + n) % 26);
        }
    }
    return a;
}


std::string vigener_cipher(std::string a){
    std::string control_s = caesars_cipher(a, std::rand() % 26 + 1);
    for (int i = 0; i < (int) a.size(); i++){
        if (isalnum(a[i])){
            a[i] = (char) (97 + (((int) tolower(a[i]) - 97) + (
                ((int) tolower(control_s[i])) - 97)) % 26);
        }
    }
    return a;
}


std::string binary(std::string a){
    std::string d[26] = {"00000001", "00000010", "00000011", "00000100",
                         "00000101", "00000110", "00000111", "00001000",
                         "00001001", "00001010", "00001011", "00001100",
                         "00001101", "00001110", "00001111", "00010000",
                         "00010001", "00010010", "00010011", "00010100",
                         "00010101", "00010110", "00010111", "00011000",
                         "00011001", "00011010"};
    std::string new_a = "";
    for (int i = 0; i < (int) a.size(); i++){
        if (isalnum(a[i])){
            new_a += d[(int) tolower(a[i]) - 97];
        }
        else new_a += a[i];
    }
    return new_a;
}


std::string a1z26(std::string a){
    std::string new_a = "";
    for (int i = 0; i < (int) a.size(); i++) new_a += std::to_string((int) a[i]);
    return new_a;
}


std::string encrypt(std::string cipher, std::string message){
    if (cipher == "rot1")
        return rot1(message);
    else if (cipher == "transpositions")
        return transpositions(message);
    else if (cipher == "morse_code")
        return morse_code(message);
    else if (cipher == "caesars_cipher")
        return caesars_cipher(message, 3);
    else if (cipher == "vigener_cipher")
        return vigener_cipher(message);
    else if (cipher == "binary")
        return binary(message);
    else if (cipher == "a1z26")
        return a1z26(message);
    else
        return "The cipher is not defined";
}


int main() {
    std::string a = "", cipher = "rot1", message = "";
    std::cout << "Hi! This is a cryptographer program. To select a cipher, enter the command [select {cipher}]. To encrypt a message, enter the command [encrypt] and enter the message on the next line. For other information: [help]." << std::endl;

    do {
        std::cin >> a;
        if (a == "select"){
            std::cin >> cipher;
        }
        else if (a == "encrypt"){
            std::cin.ignore();
            getline(std::cin, message);
            std::cout << encrypt(cipher, message) << std::endl;
        }
        else if (a == "help"){
            std::cout << "Valid ciphers: rot1, transpositions, morse_code, caesars_cipher, vigener_cipher, binary, a1z26." << std::endl;
        }
    } while(a != "exit");
    return 0;
}
