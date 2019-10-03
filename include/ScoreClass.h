#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>


const constexpr std::size_t TABLE_SIZE=8;
class ScoreClass
{
private:
    std::string path;
    std::string Name;
    int Score=-1;
    std::ifstream from_file;
    std::ofstream in_file;
    std::array<std::pair<std::string, int>,TABLE_SIZE> score_table;
    size_t cur=0;
    
public:
    ScoreClass(std::string path) :path(path)
    {
        from_file.open(path, std::ios::in);
        if(!from_file.is_open()) std::cerr << "Couldn't open file" << std::endl;
        for(cur=0; !from_file.eof() && cur<TABLE_SIZE; cur++)
        {
            std::string aName;
            int aScore=-1;
            from_file >> aName;
            from_file >> aScore;
            if(aName.size()!=0 && aScore!=-1)
                score_table[cur]=std::make_pair(aName,aScore);
            else
            {
                cur--;
            }
        }
        for(size_t i=cur;i<TABLE_SIZE;i++)
        {
            score_table[i]=std::make_pair(" ", -1);
        }
        for(auto &p:score_table)
        {
            std::cout << p.first << std::endl;
            std::cout << p.second << std::endl;
        }
    }
    ~ScoreClass()
    {
        from_file.close();       
    }
    void distruct()
    {
        std::ofstream in_file(path, std::ios::out|std::ios::trunc);
        if(!in_file.is_open()) std::cerr << "Couldn't open file" << std::endl;
        std::cout << cur << std::endl;
        for(size_t i=0; i < cur; i++)
        {
            in_file << score_table[i].first;
            in_file.put('\n');
            in_file << score_table[i].second;
            in_file.put('\n');
            std::cout << score_table[i].first << std::endl;
        }
        in_file.close();
    }
    void PushName(std::string n)
    {
        Name=n;
    }
    void PushScore(int s)
    {
        if(s>0)
            Score=s;
    }
    void UpdateFile()
    {
        if(Name.size()!=0 && Score!=-1)
        {
            auto it = std::find_if(score_table.begin(), score_table.begin()+cur, 
            [this](auto a)
            {
                return this->Name == a.first;
            });
            if(it!=score_table.begin()+cur) {
                if(Score > it->second)
                    it->second = Score;
            }
            else if(cur<TABLE_SIZE)
            {
                score_table[cur]=std::make_pair(Name,Score);
                cur++;
            }
            else if(score_table[TABLE_SIZE-1].second < Score)
            {
                score_table[TABLE_SIZE-1]=std::make_pair(Name,Score);
            }
            std::sort(score_table.begin(),score_table.begin()+cur,
            [](auto a,auto b)
            {
                return a.second>b.second;
            }
            );
        } 
        Name.clear();
        Score = -1;
    }
    std::array<std::pair<std::string,int>,TABLE_SIZE> GetScoreTable() const
    {
        return score_table;
    }
    std::string getName() const
    {
        return Name;
    }
    int getScore() const
    {
        return Score;
    }
    
    
};