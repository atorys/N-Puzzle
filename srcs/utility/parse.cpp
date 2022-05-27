//
// Created by Achiote Tory on 5/27/22.
//
#include "utility.hpp"

std::vector<std::string>    split(std::string &str){
    std::vector<std::string>    result;
    std::string                 slice;
    unsigned long               index;

    if (str.find('#') != std::string::npos) {
        str = str.substr(str.find('#'));
    }
    while ((index = str.find(' ')) != std::string::npos) {
        slice = str.substr(0, index + 1);
        if (slice.find(' ') == std::string::npos && !slice.empty()) {
            result.push_back(slice);
        }
        slice.clear();
        str.erase(0, index + 1);
    }
    if ((str.find(' ') == std::string::npos)){
        result.push_back(str);
    }
    return result;
}

std::pair<int, std::vector<int>>    getBoard(char *filename) {
    std::string                 line;
    std::vector<std::string>    args;
    std::vector<int>            board;
    std::ifstream               infile;
    int                         n = 0;

    infile.open(filename);
    if (infile.is_open()) {
        while (!n && getline(infile, line)) {
            args = split(line);
            if (args.size() == 1)
                n = atoi(args[0].c_str());
        }
        int i = 0;
        while (n && getline(infile, line)) {
            args = split(line);
            while (line != "" && !args.empty() && i != n * n) {
                board.push_back(atoi(args[0].c_str()));
                args.erase(args.begin());
            }
        }
        infile.close();
        return std::make_pair(n, board);
    }
    return std::make_pair(0, board);
}