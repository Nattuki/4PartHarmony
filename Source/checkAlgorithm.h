#pragma once

#include<stdio.h>
#include<set>
#include<vector>
using namespace std;


//四部同向
bool isParallel(int tone_now[2][4],set<pair<int,int>> &marked_note)
{
    int counter = 0;
    for(int j=0;j<4;j++)
    {
        if(tone_now[0][j]<tone_now[1][j])counter++;
        else if(tone_now[0][j]>tone_now[1][j])counter--;
    }
    
    if(abs(counter)==4)
    {
        for(int i=0;i<2;i++)for(int j=0;j<4;j++)marked_note.insert({i,j});
        return true;
    }
    else return false;
}

//声部交叉
bool isOverlap(int tone_now[2][4],set<pair<int,int>> &marked_note)
{
    bool flag = false;
    for(int j=0;j<4;j++)for(int k=0;k<j;k++)if(tone_now[1][j]>tone_now[0][k])
    {
        flag = true;
        marked_note.insert({1,j});
        marked_note.insert({0,k});
    }
    for(int j=3;j>=0;j--)for(int k=3;k>j;k--)if(tone_now[1][j]<tone_now[0][k])
    {
        flag = true;
        marked_note.insert({1,j});
        marked_note.insert({0,k});
    }
    return flag;
}

//隐伏五八
bool isHiddenConsec(int tone_now[2][4],set<pair<int,int>> &marked_note)
{
    bool flag1 = false, flag2 = false, flag3 = false;
    int d = tone_now[1][0]-tone_now[1][3];
    
    if((d-7)%12==0 || d%12==0)flag1 = true;
    if((tone_now[1][0]-tone_now[0][0])*(tone_now[1][3]-tone_now[0][3])>0)flag2 = true;
    if(abs(tone_now[1][0]-tone_now[0][0])>=5)flag3=true;

    if(flag1&&flag2&&flag3)
    {
        marked_note.insert({0,0});marked_note.insert({1,0});
        marked_note.insert({0,3});marked_note.insert({1,3});
        return true;
    }
    else return false;
}

//平行五度
bool isConsecutive5ths(int tone_now[2][4],set<pair<int,int>> &marked_note)
{
    bool flag = false;
    for(int j=0;j<4;j++)for(int k=j+1;k<4;k++)
    {
        if(tone_now[0][j]==tone_now[1][j]&&tone_now[0][k]==tone_now[1][k])continue;
        int d0 = tone_now[0][j]-tone_now[0][k], d1 = tone_now[1][j]-tone_now[1][k];
        if(((d0-7)%12==0) && ((d1-7)%12==0))
        {
            flag = true;
            marked_note.insert({0,j});marked_note.insert({0,k});
            marked_note.insert({1,j});marked_note.insert({1,k});
        }
    }
    return flag;
}

//平行八度
bool isConsecutiveOct(int tone_now[2][4],set<pair<int,int>> &marked_note)
{
    bool flag = false;
    for(int j=0;j<4;j++)for(int k=j+1;k<4;k++)
    {
        if(tone_now[0][j]==tone_now[1][j]&&tone_now[0][k]==tone_now[1][k])continue;
        int d0 = tone_now[0][j]-tone_now[0][k], d1 = tone_now[1][j]-tone_now[1][k];
        if((d0%12==0) && (d1%12==0))
        {
            flag = true;
            marked_note.insert({0,j});marked_note.insert({0,k});
            marked_note.insert({1,j});marked_note.insert({1,k});
        }
    }
    return flag;
}


