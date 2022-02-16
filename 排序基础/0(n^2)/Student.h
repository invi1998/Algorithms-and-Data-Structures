#ifndef SELECTIONSORT_STUDENT_H
#define SELECTIONSORT_STUDENT_H

#include <iostream>
#include <string>

using namespace std;

struct Student
{
    string name;
    int score;
    
    bool operator<(const Student& temps)
    {
        // return score < temps.score;
        
        // 按成绩从大到小排序，如果成绩相同，按名字的字典序进行排序
        return score != temps.score ? score > temps.score : name < temps.name;
    }
    
    friend ostream& operator<<(ostream &os, const Student &temps)
    {
        os<<"Student: "<<temps.name<<"  "<<temps.score<<endl;
        return os;
    }
};

#endif