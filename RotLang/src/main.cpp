#include <iostream>
#include <fstream>
#include <sstream>

#include "headers/tokenization.hpp"



std::vector<Token> tokenize(const std::string& str){

    
}

std::string tokens_to_asm(const std::vector<Token>& tokens)
{
    std::stringstream output;
    output << "global _start\n_start:\n"; 
    for(int i = 0; i < tokens.size(); i++)
    { 
        const Token& token = tokens.at(i);

        if(token.type == TokenType::_exit)
        {
            if(i+1 < tokens.size() && tokens.at(i + 1).type == TokenType::int_litearl)
            {
                if(i + 2 < tokens.size() && tokens.at(i + 2).type == TokenType::semicol)
                {
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << tokens.at(i+1).value.value() << "\n";
                    output << "    syscall";
                }
            }
        }
    }
    return output.str();
}

int main(int argc, char* argv[]) {

    if(argc != 2)
    {
        std::cerr << "Invalid usage" << std::endl;
        std::cerr << "Use rotl <example.rot>" << std::endl;
        return 1;
    }

    std::fstream file(argv[1], std::ios::in);
    std::stringstream contents_stream;

    if(!file.is_open())
    {
        std::cerr << "Error:" << argv[1] << std::endl;
        return 1;
    }

    contents_stream << file.rdbuf();
    std::string contents = contents_stream.str();

    file.close();

    std::vector<Token> thing = tokenize(contents);

    {
    std::fstream filed("out.asm", std::ios::out);
    filed << tokens_to_asm(thing);
    filed.close();
    
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");
    // system("./out");
    // system("echo $?");

    //std::cout << argv[1] << std::endl;
    return 0;
}