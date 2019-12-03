#include <iostream>
#include <time.h>
#include <string>

using namespace std;

struct edge
{
    string vertex[2];
    int weight;
    bool added;
    bool unaddable;
};

bool linked(edge* Edge, edge Current, int num, string x, int count)
{
    if(Current.vertex[num] == x)
    {
        return true;
    }
    for(int i=0; i<count; i++)
    {
        if(Edge[i].added == true && !(Edge[i].vertex[0] == Current.vertex[0] && Edge[i].vertex[1] == Current.vertex[1] && Edge[i].weight == Current.weight))
        {
            if(Edge[i].vertex[0] == Current.vertex[num])
            {
                if(linked(Edge, Edge[i], 1, x, count))
                    return true;
            }
            if(Edge[i].vertex[1] == Current.vertex[num])
            {
                if(linked(Edge, Edge[i], 0, x, count))
                    return true;
            }
        }
    }
    return false;
}

int main()
{
    typedef struct edge edge;
    edge Edge[50];
    char current;
    int i;
    for(i=0; i<50; i++)
    {
        current = getchar();
        if(current == '\n')
            break;
        Edge[i].vertex[0].push_back(current);
        current = getchar();
        while(current != ' ')
        {
            Edge[i].vertex[0].push_back(current);
            current = getchar();
        };
        do
        {
            current = getchar();
            if(current != ' ')
                Edge[i].vertex[1].push_back(current);
        }while(current != ' ');
        cin >> Edge[i].weight;
        while(getchar() != '\n');
        Edge[i].added = false;
        Edge[i].unaddable = false;
    }
    int count = i;
    edge temp;
    for(int i=1;i<count;i++)
        for(int j=i; j>0; j--)
        {
            if(Edge[j-1].weight<=Edge[j].weight)
                break;
            temp = Edge[j-1];
            Edge[j-1] = Edge[j];
            Edge[j] = temp;
        }
    edge* MST = new edge[50];
    int MSTcount = 0;
    for(i=0; i<count; i++)
    {
        if(Edge[i].added == false && Edge[i].unaddable == false)
        {
            if(linked(Edge, Edge[i], 0, Edge[i].vertex[1], count))
                Edge[i].unaddable = true;
            else
            {
                Edge[i].added = true;
                MST[MSTcount] = Edge[i];
                MSTcount++;
            }
        }
    }
    for(int i=1;i<MSTcount;i++)
        for(int j=i; j>0; j--)
        {
            if((MST[j-1].vertex[0][0]*100+MST[j-1].vertex[1][0])<=(MST[j].vertex[0][0]*100+MST[j].vertex[1][0]))
                break;
            temp = MST[j-1];
            MST[j-1] = MST[j];
            MST[j] = temp;
        }
    int weight = 0;
    for(i=0; i<MSTcount; i++)
    {
        cout << MST[i].vertex[0] << ' ' << MST[i].vertex[1] << ' ' << MST[i].weight << endl;
        weight += MST[i].weight;
    }
    cout << "Summary weight = " << weight << endl;
    return 0;
}
