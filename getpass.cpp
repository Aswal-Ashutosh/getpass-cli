#include<iostream>
#include<vector>
#include<algorithm>
#include<conio.h>
#include<fstream>

#define ADMIN_PASSWORD "Your Password" //Change before compiling
#define FILE_PATH "D:/path/to/secret/file.txt" //Change before compiling
#define QUIT "quit"
#define QUIT_C "quit -c"
#define CLEAR "clear"

#define RETURN 13
#define BACK_SPACE '\b'

#define RESET   "\033[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"

constexpr char endline = '\n';

bool handle_password(){
    std::cout << ">> Password: ";
    std::string password;
    for(char c; (c = getch()) != RETURN; ){
        if(c == BACK_SPACE && !password.empty()){
            password.pop_back();
        }else{
            password.push_back(c);
        }
    }
    return password == ADMIN_PASSWORD;
}

struct Data{
    std::string key;
    std::string value;
    Data(const std::string& key, const std::string& value) : key(key), value(value){

    }
};


Data parse_line(const std::string& line){
    const int n = line.size();
    int ptr = 0;
    std::string key, value;
    auto eat = [&ptr, &line, n](std::string& s, char delimeter){
        while(ptr < n && line[ptr] == ' '){
            ++ptr;
        }
        while(ptr < n && line[ptr] != delimeter){
            s.push_back(line[ptr++]);
        }
    };
    eat(key, ':');
    ++ptr;
    eat(value, '\0');
    return Data(key, value);
}

std::vector<Data> parse_file(){
    std::vector<Data> passwords;
    std::string line;
    std::fstream file(FILE_PATH, std::ios::in);
    while(!file.eof()){
        std::getline(file, line);
        passwords.emplace_back(parse_line(line));
    }
    file.close();
    auto to_lower = [](const std::string& in){
        std::string out;
        for(char c : in){
            out.push_back(std::tolower(c));
        }
        return out;
    };
    std::sort(std::begin(passwords), std::end(passwords), [to_lower](const Data& A, const Data& B)->bool{
        return to_lower(A.key) < to_lower(B.key);
    });
    return passwords;
}

int main(int argc, char** argv){
    system(""); //[System call is needed to enable ANSI escape code to work with terminal]
    if(argc != 1){
        std::cout << ">> " RED "Invalid Arguments!" RESET;
    }else{
        if(handle_password()){
            std::cout << "[" GREEN "Accepted" RESET "]\n\n";
            std::vector<Data> passwords = parse_file();
            auto show_options = [&passwords](){
                for(int i = 0; i < (int)passwords.size(); ++i){
                    std::cout << "[" GREEN << i + 1 << RESET "] " << passwords[i].key << endline;
                }
                std::cout << "\n-type `quit` to exit.";
                std::cout << "\n-type `quit -c` to exit and clear the prompt.";
                std::cout << "\n-type `clear` to clear the prompt.\n\n";
            };
            show_options();
            bool running = true, clear = false;
            do{
                if(clear){
                    clear = false;
                    system("cls");
                    show_options();
                }
                std::string input;
                std::cout << ">> ";
                std::getline(std::cin, input);
                if(input == QUIT){
                    running = false;
                }else if(input == QUIT_C){
                    running = false;
                    clear = true;
                }else if(input == CLEAR){
                    clear = true;
                }else{
                    try{
                        uint32_t index = std::stoi(input);
                        if(index < 1 || index > passwords.size()){
                            throw -1;
                        }
                        std::cout << ">> " << passwords[index - 1].key << ": " << GREEN << passwords[index - 1].value << RESET << endline;
                    }catch(...){
                        std::cout << ">> " RED "Invalid Input!" RESET << endline;
                    }
                }
            }while(running);
            if(clear){
                system("cls");
            }
        }else{
            std::cout << "[" RED "Invalid Password" RESET "]\n";
        }
    }
    return 0;
}