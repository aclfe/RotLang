#include <iostream>
#include <fstream>
#include <sstream>


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
    std::cout << contents << std::endl;
    file.close();

    // std::cout << argv[1] << std::endl;
    return 0;
}