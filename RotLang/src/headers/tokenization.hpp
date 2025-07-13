#ifndef HYDROGEN_TOKENIZATION_HPP
#define HYDROGEN_TOKENIZATION_HPP

#include <string>
#include <vector>
#include <optional>
#include <iostream>


enum class TokenType{
    _exit,
    int_litearl,
    semicol,
};

struct Token{
    TokenType type;
    std::optional<std::string> value {};
};
 
class Tokenizer{
public:
    inline Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }

    inline std::vector <Token> tokenize(){
    
        std::vector<Token> tokens;

        std::string buf;

        while(check().has_value())
        {
            if(std::isalpha(check().value()))
            {
                buf.push_back(consume());
                while(check().has_value() && std::isalnum(check().value()))
                {
                    buf.push_back(consume());
                }
            }
        }

        // for(int i = 0; i < str.length(); i++)
        // {
        //     char c = str.at(i);
        //     if(std::isalpha(c))
        //     {
        //         buf.push_back(c);
        //         i++;
        //         while(std::isalnum(str.at(i)))
        //         {
        //             buf.push_back(str.at(i));
        //             i++;
        //         }
        //         i--;

        //         if(buf == "exit"){
        //             tokens.push_back({.type = TokenType::_exit});
        //             buf.clear();
        //             continue;
        //         }
        //         else{
        //             std::cerr << "No valid synatax loser" << std::endl;
        //             exit(EXIT_FAILURE);
        //         }
        //     }
        //     else if(std::isdigit(c))
        //     {
        //         buf.push_back(c);
        //         i++;
        //         while(std::isdigit(str.at(i))){
        //             buf.push_back(str.at(i));
        //             i++;
        //         }
        //         i--;
        //         tokens.push_back({.type = TokenType::int_litearl, .value = buf});
        //         buf.clear();
        //     }
        //     else if(c == ';'){
        //         tokens.push_back({.type = TokenType::semicol});
        //     }
        //     else if(std::isspace(c))
        //     {
        //         continue;
        //     }
        //     else{
        //         std::cerr << "Everything went wrong" << std::endl;
        //         exit(EXIT_FAILURE);
        //     }
        // }

        // return tokens;

    }

private:

    std::optional <char> check(int ahead = 1) const
    {
        if((m_index + ahead) >= m_src.length())
        {
            return {};
        }
        else
        {
            return m_src.at(m_index);
        };
    };

    char consume()
    {
        return m_src.at(m_index++); 
    }

    const std::string m_src;
    int m_index;
};

#endif