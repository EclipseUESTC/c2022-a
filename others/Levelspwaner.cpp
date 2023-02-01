#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<windows.h>
using namespace std;
typedef struct {
    string name;
    int levels;
}World;
vector<World> worldList;
void addWorld(string name,int levels);
void init();
void check();
bool levelRepeated(World A,World B);
void randomSpawn(int num);
int main()
{
    init();
//  check();
    randomSpawn(100);
    system("pause");
    return 0;
}
void addWorld(string name,int levels)
{
    World world;
    world.name = name;
    world.levels = levels;
    worldList.push_back(world);
}
void init()
{
    addWorld("Ancient_Egypt",25);
    addWorld("Pirate_Seas",25);
    addWorld("Wild_West",25);
    addWorld("Far_Future",25);
    addWorld("Dark_Ages",20);
    addWorld("Big_Wave_Beach",32);
    addWorld("Frostbite_Caves",32);
    addWorld("Lost_City",32);
    addWorld("Neon_Mixtape_Tour",32);
    addWorld("Jurassic_Marsh",32);
    addWorld("Modern_Day",32);
}
void check()
{
    for (unsigned int i=0;i<worldList.size();i++)
    {
        cout<<worldList[i].name<<" "<<worldList[i].levels<<endl;
    }
}
bool levelRepeated(World A,World B)
{
    return A.name == B.name && A.levels == B.levels;
}
void randomSpawn(int num)
{
    vector<World> levelList;
    srand(time(nullptr));
    int i = 0;
    while (i < num)
    {
        bool repeated = false;
        int world = rand() % worldList.size();
        int No = rand() % worldList[world].levels + 1;
        World level;
        level.name = worldList[world].name;
        level.levels = No;
        for (unsigned int j=0;j<levelList.size();j++)
        {
            if (levelRepeated(level,levelList[j]))
            {
                repeated = true;
                break;
            }
        }
        if (!repeated){
            levelList.push_back(level);
            i++;
            cout<<i<<" "<<level.name<<" "<<level.levels<<endl;
        }
    }
}