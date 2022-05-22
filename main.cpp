#include<iostream>
#include<vector>
#include<unistd.h>
#include<string>
#include<map>
#include<limits>
#include<set>
#include<queue>
#include<string.h>
#include<algorithm>
#include<future>
#include<mutex>
#include<ctime>
#include<chrono>
#include<thread>
#include<atomic>

using namespace std;
#define AIRCRAFTS 10
#define GATES 3
#define RUNWAYS 1

static int id = 0;
int dijk[11][11];
bool visited[11];
int con[11][11];
set <pair<int, int>> s;
int parent[11][11];
static int book = 0;
map <int , string> guiz;
map <int , string> :: iterator mapit;
mutex output;
struct inform
{
    string name;
    int age;
    int seat;
};

class airport
{
    int capacity;
    int current = 0;
    int index;

    public:
    vector <pair<int ,int>> v[11];
    airport()
    {
        cout << "\n\n";
    }
    airport(int );
    void plane(int);
    void depart();
    void arrive();
    void show(airport);
    void distance(airport ,airport , int);
    int MST();
    void init(mutex mtx_g[], mutex mtx_r[], int plane);
};

class planes : public airport
{
    private:
    int seats;
    int reserved;
    queue <string> waiting;
    vector <inform> info;
    public:
    planes(int);
    void waiting_list();
};
void home();
planes :: planes(int x)
{
    seats = x;
    reserved = 0;
}
void display()
{
    cout << "\n\t\033[0;31msource id" << " " << "source_name\033[0m" << endl;
    cout << "\n\t 0" << " " << "\t Jakarta" ;
    cout << "\n\t 1" << " " << "\t Delhi" ;
    cout << "\n\t 2" << " " << "\t Singapore" ;
    cout << "\n\t 3" << " " << "\t Kuala lumpur" ;
    cout << "\n\t 4" << " " << "\t Mumbai" ;
    cout << "\n\t 5" << " " << "\t Tokyo" ;
    cout << "\n\t 6" << " " << "\t Hyderabad" ;
    cout << "\n\t 7" << " " << "\t Seoul" ;
    cout << "\n\t 8" << " " << "\t Chennai" ;
    cout << "\n\t 9" << " " << "\t Shanghai" ;
    cout << "\n\t 10" << " " <<"\t New York" ;
}
airport :: airport(int n)
{
    capacity = n;
    index = id;
    id++;
}
void airport :: distance(airport a1 ,airport a2 ,int dis)
{
    int ind1 = a1.index;
    int ind2 = a2.index;
    v[ind1].push_back(make_pair(ind2 ,dis));
    v[ind2].push_back(make_pair(ind1 ,dis));
    dijk[ind1][ind2]=dis;
    dijk[ind2][ind1]=dis;
    con[ind1][ind2] = 1;
    con[ind2][ind1] = 1;
}
void airport :: show(airport a)
{
    vector <pair<int,int>> :: iterator it;
    int ind = a.index;
    for(it=v[ind].begin(); it!=v[ind].end(); it++)
    {
        cout << "\t\t" << it->second << " --------------- " << it->first << endl;
    }
    cout << endl;
}
void airport :: arrive()
{
    if(capacity == current)
    {
        cout << "No more space available" << endl;
        return;
    }
    current++;
}
void airport :: depart()
{
    if(current == 0)
    {
        cout << "No plane available" << endl;
        return;
    }
    current--;
}
void airport :: plane(int n)
{
    if(current == capacity || current + n > capacity)
    {
        cout << "Overflow" << endl;
        return;
    }
    current = current +n;
}
void set_infi()
{
    for(int i=0; i<11; i++)
    {
        visited[i] = false;
        for(int j=0; j<11; j++)
        {
            if(i==j)
            {
                dijk[i][j]=0;
                con[i][j]=0;
            }
            else
            {
                dijk[i][j]=99999;
            }
        }
    }
}
void mini()
{
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            cout << dijk[i][j] << " ";
        }
        cout << endl;
    }
}
void flyod(int x,int y)
{
    int min[11][11];
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            min[i][j]=dijk[i][j];
        }
    }
    for (int k=0; k<11; k++)
    {
        for(int i=0; i<11; i++)
        {
            for(int j=0; j<11; j++)
            {
                if(min[i][k] + min[k][j] < min[i][j])
                {
                    min[i][j] = min[i][k] + min[k][j];
                    parent[i][j] = k;
                }
            }
        }
    }
    cout << "\n\tMinimum distance between your specified source and destination is -> " << min[x][y];
}
void flyod()
{
    int min[11][11];
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            min[i][j]=dijk[i][j];
        }
    }
    for (int k=0; k<11; k++)
    {
        for(int i=0; i<11; i++)
        {
            for(int j=0; j<11; j++)
            {
                if(min[i][k] + min[k][j] < min[i][j])
                {
                    min[i][j] = min[i][k] + min[k][j];
                    parent[i][j] = k;
                }
            }
        }
    }
}
void cost(int x,int y)
{
    double price[11][11];
    double price1[11][11];
    double price2[11][11];
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            price[i][j]=dijk[i][j]*2.7;
            price1[i][j]=dijk[i][j]*3.0;
            price2[i][j]=dijk[i][j]*2.9;
        }
    }
    for (int k=0; k<11; k++)
    {
        for(int i=0; i<11; i++)
        {
            for(int j=0; j<11; j++)
            {
                if(price[i][k] + price[k][j] < price[i][j])
                {
                    price[i][j] = price[i][k] + price[k][j];
                }
                if(price1[i][k] + price1[k][j] < price1[i][j])
                {
                    price1[i][j] = price1[i][k] + price1[k][j];
                }
                if(price2[i][k] + price2[k][j] > price2[i][j])
                {
                    price2[i][j] = price2[i][k] + price2[k][j];
                }
            }
        }
    }
    cout << "\n\t\033[0;31mMinimum cost between your specified source and destination is ->\033[0m " << price[x][y] <<" \033[0;31mRupees\033[0m " << endl;
    cout << "\n\t\033[0;31mMedian cost between your specified source and destination is ->\033[0m " << price1[x][y] << " \033[0;31mRupees\033[0m " << endl;
    cout << "\n\t\033[0;31mMaximum cost between your specified source and destination is ->\033[0m " << price2[x][y] << " \033[0;31mRupees\033[0m " << endl;
}
void path(int a,int b)
{
    int min[11][11];
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            min[i][j]=dijk[i][j];
        }
    }
    for (int k=0; k<11; k++)
    {
        for(int i=0; i<11; i++)
        {
            for(int j=0; j<11; j++)
            {
                if(min[i][k] + min[k][j] < min[i][j])
                {
                    min[i][j] = min[i][k] + min[k][j];
                    parent[i][j] = k;
                }
            }
        }
    }  
    mapit = guiz.find(a);
    cout << "\n\t" << mapit->second << " -> ";
    while(parent[a][b]!=0)
    {
        cout << parent[a][b] << " -> ";
        int temp = parent[a][b];
        parent[a][b] = parent[temp][b];
    }
    mapit = guiz.find(b);
    cout << mapit->second << endl;
}
void soja3()
{
//sleep(3);
system("clear");
}
void intro()
{
    cout << "\n\t\tAir traffic controller " ;
    cout << "\n\n\n\n" ;
    soja3();
}
int countwalks( int u, int v, int k)
{
    int count[11][11][k+1];
    for (int e = 0; e <= k; e++)
    {
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                count[i][j][e] = 0;
                if (e == 0 && i == j)
                count[i][j][e] = 1;
                if (e == 1 && con[i][j])
                count[i][j][e] = 1;
                if (e > 1)
                {
                    for (int a = 0; a < 11; a++)
                    if (con[i][a])
                    count[i][j][e] += count[a][j][e-1];
                }
            }
        }
    }
    return count[u][v][k];
}
void init(mutex mtx_g[], mutex mtx_r[], int plane)
{
 //this_thread::sleep_for(chrono::milliseconds(100));
 /* PRINT MESSAGES */
 output.lock();
 cout << "[AC] Flight " << plane << " requesting landing" << endl;
 output.unlock();
 //land
 srand(time(NULL));
 bool landed = false;
 bool gate = false;

 int runawayTime = rand()%(5000-2000 + 1) + 5000;
 try 
 {
     while (landed == false)
     {
         for (int i = 0; i < RUNWAYS; i++)
         {
             if (mtx_r[i].try_lock())
             {
                 
                 /* PRINT MESSAGES */
                 output.lock();
                 cout << "[AC] Airplane " << plane << " assigned to runway " << i + 1 << endl;
                 cout << "[AC] Airplane " << plane << " has landed" << endl;
                 output.unlock();
                 this_thread::sleep_for(chrono::milliseconds(2000));
                 landed = true;
                 mtx_r[i].unlock();
                 break;
                 
             }
 }
 if (landed) {break;}
         
     }
 }
 catch (exception e)
 {
     output.lock();
     cout << "Hi. " << e.what() << " Plane: " << plane << endl;
     output.unlock();
 }


 /* PRINT MESSAGES */
 output.lock();
 cout << "[AC] Airplane " << plane << " requesting gate" << endl;
 output.unlock();
 
 //dock to gate
 while (gate == false)
 {
     for (int j = 0; j < GATES; ++j)
     {
         if (mtx_g[j].try_lock())
         {
             /* PRINT MESSAGES */
             output.lock();
             cout << "[AC] Airplane " << plane << " assigned gate " << j + 1 << endl;
             output.unlock();
             this_thread::sleep_for(chrono::milliseconds(runawayTime));
             gate = true;
             mtx_g[j].unlock();
             break;
         }
     }
     if (gate) {break;}
 }
 output.lock();
 cout << "[AC] Airplane " << plane << "has departed" << endl;
 output.unlock();
}

int main()
{
    planes p(2);
    airport a(50);
    a.plane(25);
    airport b(50);
    b.plane(18);
    airport c(50);
    c.plane(29);
    airport d(50);
    d.plane(25);
    airport e(50);
    e.plane(10);
    airport f(50);
    f.plane(31);
    airport g(50);
    g.plane(30);
    airport h(50);
    h.plane(20);
    airport i(50);
    i.plane(15);
    airport j(50);
    j.plane(26);
    airport k(25);
    k.plane(15);
    set_infi();
    guiz.insert(pair<int , string> (0 , "Jakarta"));
    guiz.insert(pair<int , string> (1 , "Delhi"));
    guiz.insert(pair<int , string> (2 , "Singapore"));
    guiz.insert(pair<int , string> (3 , "Kuala lumpur "));
    guiz.insert(pair<int , string> (4 , "Mumbai"));
    guiz.insert(pair<int , string> (5 , "Tokyo"));
    guiz.insert(pair<int , string> (6 , "Hyderabad"));
    guiz.insert(pair<int , string> (7 , "Seoul"));
    guiz.insert(pair<int , string> (8 , "Chennai"));
    guiz.insert(pair<int , string> (9 , "Shanghai"));
    guiz.insert(pair<int , string> (10 , "New York"));
    a.distance(a, b, 1654);
    a.distance(a, c, 850);
    a.distance(a, d, 900);
    a.distance(a, e, 2296);
    a.distance(a, f, 2227);
    b.distance(b, a, 2987);
    b.distance(b, c, 879);
    b.distance(b, d, 797);
    b.distance(b, e, 1504);
    b.distance(b, i, 2221);
    c.distance(c, a, 1626);
    c.distance(c, b, 1896);
    c.distance(c, f, 523);
    c.distance(c, g, 1359);
    d.distance(d, a, 1589);
    d.distance(d, b, 887);
    d.distance(d, f, 876);
    d.distance(d, g, 850);
    d.distance(d, h, 1212);
    d.distance(d, j, 2124);
    e.distance(e, a, 2296);
    e.distance(e, b, 1504);
    e.distance(e, f, 1950);
    e.distance(e, i, 1670);
    e.distance(e, k, 1302);
    f.distance(f, a, 2227);
    f.distance(f, c, 523);
    f.distance(f, d, 776);
    f.distance(f, e, 1950);
    f.distance(f, h, 981);
    f.distance(f, i, 1337);
    f.distance(f, j, 1676);
    g.distance(g, d, 780);
    g.distance(g, c, 1219);
    g.distance(g, i, 629);
    h.distance(h, d, 1212);
    h.distance(h, f, 591);
    h.distance(h, i, 920);
    h.distance(h, j, 1349);
    i.distance(i, b, 2211);
    i.distance(i, e, 1670);
    i.distance(i, f, 1337);
    i.distance(i, g, 629);
    i.distance(i, h, 920);
    i.distance(i, j, 727);
    i.distance(i, k, 1362);
    j.distance(j, d, 2124);
    j.distance(j, f, 1676);
    j.distance(j, h, 1349);
    j.distance(j, i, 805);
    k.distance(k, e, 1402);
    k.distance(k, i, 1362);
intro();
 char ch;
 a: int choice;
 cout << "\n\n\t\t\033[0;31mAIR TRAFFIC CONTROLLER\033[0m\n\n";
 cout << "\n\n\033[0;31m\tEnter your choice\033[0m\n";
 cout << "\n\t\033[0;31m1.\033[0m Shortest path between source and destination.\n";
 cout << "\n\t\033[0;31m2.\033[0m Minimum Price of ticket .\n";
 cout << "\n\t\033[0;31m3.\033[0m Display path.\n";
 cout << "\n\t\033[0;31m4.\033[0m No of paths between two airport with transit.\n";
 cout << "\n\t\033[0;31m5.\033[0m Landing and Takeoff \t";
 cout << "\n\n\t\033[0;31mEnter your choice \033[0m\t";
 cin >> choice;
//choose(choice);
int source ,destination;
switch(choice)
{
    case 1:
    {
        display();
        char choice;
        do
        {
            cout << "\n\n\tEnter your source id ->\t";
            cin >> source;
            cout << "\n\tEnter your destination id ->\t";
            cin >> destination;
            flyod(source , destination);
            cout << "\n\tWant To enter other input ?\n\t\033[0;31mPress Y for yes or N to exit\t\033[0m";
            cin >> choice;
        }
        while(choice=='y');
        break;
    }
    
    case 2:
    {
        display();
        char choice;
        do
        {
            cout << "\n\n\tEnter your source id ->\t";
            cin >> source;
            cout << "\n\tEnter your destination id ->\t";
            cin >> destination;
            cost(source , destination);
            cout << "\n\tWant To enter other input ?\n\t\033[0;31mPress Y for yes or N to exit \t\033[0m";
            cin >> choice;
        }
        while(choice=='y');
        break;
    }
    
    case 3:
    {
        display();
        char choice;
        do
        {
            cout << "\n\n\tEnter your source id ->\t";
            cin >> source;
            cout << "\n\tEnter your destination id ->\t";
            cin >> destination;
            path(source ,destination);
            cout << "\n\tWant To enter other input ?\n\t\033[0;31mPress Y for yes or N to exit \t\033[0m";
            cin >> choice;
        }
        while(choice=='y');
        break;
    }
    
    case 4:
    {
        display();
        char choice;
        do
        {
            int k, no_paths;
            cout << "\n\n\tEnter your source id ->\t";
            cin >> source;
            cout << "\n\tEnter your destination id ->\t";
            cin >> destination;
            cout << "\n\tEnter no of airport ->\t";
            cin >> k;
            no_paths = countwalks(source ,destination, k+1);
            cout << "\n\tno_paths -> " << no_paths << endl;
            cout << "\n\tWant To enter other input ?\n\t\033[0;31mPress Y for yes or N to exit\t\033[0m";
            cin >> choice;
        }
        while(choice=='y');
        break;
    }
    
    case 5:
    {
        do
        {
            // Airport Setup
            vector <future<void>> airplanes;
            // Mutex
            mutex mtx_g[GATES];
            mutex mtx_r[RUNWAYS];
            for (int i = 0; i < AIRCRAFTS; i++)
            {
                airplanes.push_back(async(launch::async, &init, mtx_g, mtx_r, i + 1));
            }
            for (auto i = 0; i < AIRCRAFTS; ++i)
            {
                airplanes[i].get();
            }
            cout << "\n\tWant to exit ? Press Y else any other key.\t" ;
            cin >> choice;
        }
        while(choice!='y');
        break;
    }
    
    default:
    {
        system("clear");
        cout << "\n\t\033[0;31mInvalid! Enter again :\033[0m" << endl;
        goto a;
        break;
    }
}
cout << "\n\n\t\033[0;31mEnter N to end the program or Y to continue :\033[0m \t";
cin >> ch;
if(ch == 'n' || ch == 'Y')
{
    exit(1);
}
if(ch == 'y' || ch == 'N')
{
    goto a;
}
return 0;
}






