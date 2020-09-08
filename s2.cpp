// Matthew Roh's Game of COVID19.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 라이프 게임 변종 프로젝트: Matthew Roh's Game of COVID19
// 
// 격자의 각 상태: 0, 1, 2, 3
// 0: 사람이 없음.
// 1: 비확진자
// 2: 무증상 확진자. 가로/세로/대각선 1칸 거리 안의 '1' 상태의 칸이 다음 세대에서 '2'로 바뀜. 자기 자신은 다음 세대에서 '3'으로 바뀜. (증상 발현)
// 3: 유증상 확진자. 가로/세로/대각선 2칸 거리 안의 '1' 상태의 칸이 다음 세대에서 '2'로 바뀜. 자기 자신은 다음 세대에서 '0'으로 바뀜. (사망)

int grid[20][20];

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <thread>

void applyrule()
{
    int newgrid[20][20];
    /*for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            newgrid[i][j] = grid[i][j];*/
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            int a = 0;
            if (i != 0)
            {
                if(j!=0)if (grid[i - 1][j - 1] >= 1)a++;
                if (grid[i - 1][j] >= 1)a++;
                if(j!=19)if (grid[i - 1][j + 1] >= 1)a++;
            }
            if(j!=0)if (grid[i][j - 1] >= 1)a++;
            if(j!=19)if (grid[i][j + 1] >= 1)a++;
            if (i != 19)
            {
                if(j!=0)if (grid[i + 1][j - 1] >= 1)a++;
                if (grid[i + 1][j] >= 1)a++;
                if(j!=19)if (grid[i + 1][j + 1] >= 1)a++;
            }
            if (grid[i][j] == 0)
            {
                if (a == 3)newgrid[i][j] = 1;
                else newgrid[i][j] = 0;
            }
            else
            {
                if (a == 2 or a == 3)newgrid[i][j] = grid[i][j];
                else newgrid[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (grid[i][j] == 2)
            {
                for (int i1 = std::max(i - 1, 0); i1 <= std::min(i + 1, 19); i1++)
                {
                    for (int j1 = std::max(j - 1, 0); j1 <= std::min(j + 1, 19); j1++)
                    {
                        if (newgrid[i1][j1] == 1)newgrid[i1][j1] = 2;
                    }
                }
                newgrid[i][j] = 3;
            }
            else if (grid[i][j] == 3)
            {
                for (int i1 = std::max(i - 2, 0); i1 <= std::min(i + 2, 19); i1++)
                {
                    for (int j1 = std::max(j - 2, 0); j1 <= std::min(j + 2, 19); j1++)
                    {
                        if (newgrid[i1][j1] == 1)newgrid[i1][j1] = 2;
                    }
                }
                newgrid[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            grid[i][j] = newgrid[i][j];
}

int main()
{
    using namespace std::chrono_literals;
    srand(time(0));
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)grid[j][i] = 0; // 기본적으로 빈칸으로 초기화
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            if (rand() % 100 >= 100-50)grid[i][j] = 1; // 격자의 약 50%를 비확진자로 채움
    grid[rand() % 20][rand() % 20] = 2; //확진자 1명 임의의 위치에 배치.
    int gen = 0;
    while (1)
    {
        int safe=0, slcont=0, sacont=0;
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (grid[i][j] == 1)safe++;
                else if (grid[i][j] == 2)slcont++;
                else if (grid[i][j] == 3)sacont++;
            }
        }
        std::cout << "-----Statistics-----" << std::endl;
        std::cout << "Generation : " << gen << std::endl;
        std::cout << "Safe People : " << safe << std::endl;
        std::cout << "Symptomless Infections : " << slcont << std::endl;
        std::cout << "Symptomatic Infections : " << sacont << std::endl;
        gen++;
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)std::cout << grid[i][j] << ""; //Grid 출력.
            std::cout << std::endl;
        }
        std::cout << std::endl;
        applyrule();
        std::this_thread::sleep_for(3s);
    }
    return 0;
}
