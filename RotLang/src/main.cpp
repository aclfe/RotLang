#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <string>


enum class TokenType{
    _return,
    int_litearl,
    semicol,
};

struct Token{
    TokenType type;
    std::optional<std::string> value {};
};

std::vector<Token> tokenize(const std::string& str){

    std::vector<Token> tokens;

    std::string buf;

    for(int i = 0; i < str.length(); i++)
    {
        char c = str.at(i);
        if(std::isalpha(c))
        {
            buf.push_back(c);
            i++;
            while(std::isalnum(str.at(i)))
            {
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            if(buf == "return"){
                tokens.push_back({.type = TokenType::_return});
                buf.clear();
                continue;
            }
            else{
                std::cerr << "No valid synatax loser" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if(std::isdigit(c))
        {
            buf.push_back(c);
            i++;
            while(std::isdigit(str.at(i))){
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::int_litearl, .value = buf});
            buf.clear();
        }
        else if(c == ';'){
            tokens.push_back({.type = TokenType::semicol});
        }
        else if(std::isspace(c))
        {
            continue;
        }
        else{
            std::cerr << "Everything went wrong" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return tokens;
}

std::string tokens_to_asm(const std::vector<Token>& tokens)
{
    std::stringstream output;
    output << "global _start\n_start:\n"; 
    for(int i = 0; i < tokens.size(); i++)
    { 
        const Token& token = tokens.at(i);

        if(token.type == TokenType::_return)
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
    std::cout << tokens_to_asm(thing) << std::endl;

    //std::cout << argv[1] << std::endl;
    return 0;
}