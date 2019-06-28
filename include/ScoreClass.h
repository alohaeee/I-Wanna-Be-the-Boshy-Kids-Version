#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class ScoreClass
{
private:
    std::string path;
    std::string Name;
    int Score=-1;
    std::ifstream from_file;
    std::ofstream in_file;
public:
    ScoreClass(std::string path) :path(path)
    {
        from_file.open(path, std::ios::in);
        in_file.open(path, std::ios::out|std::ios::app);
        if(!from_file.is_open()) std::cerr << "Couldn't open file" << std::endl;
        if(!in_file.is_open()) std::cerr << "Couldn't open file" << std::endl;
    }
    ~ScoreClass()
    {
        from_file.close();
        in_file.close();
    }
    void PushName(std::string n)
    {
        Name=n;
    }
    void PushScore(int s)
    {
        Score=s;
    }
    void UpdateFile()
    {
        if(Name.size()!=0 && Score>0)
        {
            in_file << Name;
            in_file.put('\n');
            in_file << std::to_string(Score);
            in_file.put('\n');
            in_file.close();
            in_file.open(path,std::ios::out|std::ios::app);
        }
        Name.clear();
        Score = -1;
    }
    std::vector<std::pair<std::string,int>> GetScoreTable() 
    {
        from_file.seekg(std::ios::beg);
        std::vector<std::pair<std::string,int>> vec;
        while(!from_file.eof())
        {   

            std::string aName;
            std::string aScore;
            //std::getline(from_file,aName);
            //std::getline(from_file,aScore);
            from_file >> aName;
            from_file >> aScore;
            vec.push_back(std::make_pair(aName,std::atoi(aScore.c_str())));
            //from_file >> aName;
        }
        std::sort(vec.begin(),vec.end(),[](auto a, auto b)
        {
            return a.second < b.second;
        });
        return vec;
    }
    std::string getName() const
    {
        return Name;
    }
    
    
};