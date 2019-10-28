#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <queue>
#include "Graph.h"

using namespace std;


template<class Container>
void split1(const string &str, Container &cont) {
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int V = 0;                                                //number of towns
int E = 0;                                                //number of roads
int T = 0;                                                //number of thiefs
int J = 0;                                                //nummber of Jewelers
int thieves[2001][2001];
int dist[2001][1 << (14)];
# define INF 0x3f3f3f3f


struct Road {
    int source;
    int sink;
    int weight;

    Road(int so, int si, int w) {
        source = so;
        sink = si;
        weight = w;
    }
};


struct Vertice {
    vector<Road> neighbors;
    vector<int> coins;
};


struct element {
    int weight;
    int sink;
    set<int> coins;
    queue<int> parentPath;

    element(int w, int s, set<int> _coins, queue<int> _parentPath) {
        weight = w;
        sink = s;
        coins = _coins;
        parentPath = _parentPath;

    }


};

struct compare {
    bool operator()(const element &l, element &r) {
        return l.weight > r.weight;
    }
};


class myGraph {
public:
    Graph(int V) {
        this->V = V;
        vList = new Vertice[V + 1];
        for (int i = 0; i < 2001; i++) {
            for (int j = 0; j < 2001; j++)
                thieves[i][j] = 0;
            for (int k = 0; k < (1 << 14); k++)
                Coins[i][k] = 0;
        }

    }


    void addEdge(int source, int sink, int weight) {
        vList[source].neighbors.push_back(Road(source, sink, weight));
        vList[sink].neighbors.push_back(Road(sink, source, weight));
    }

    void addCoin(int town, int coin) {
        vList[town].coins.push_back(coin);
    }


    bool freeThief(set<int> s, vector<int> t) {
        int ind = 0;
        set<int>::iterator itr;
        for (itr = s.begin(); itr != s.end(); itr++) {
            for (int i = 0; i < t.size(); i++) {
                if (*itr == t[i])
                    ind++;
            }
        }

        if (ind == t.size())
            return false;
        else
            return true;


    }

    bool Graph::notExplored() {

    }


    void shortestPath() {
        int dist = 0;
        int start_node = 1;
        priority_queue<element, vector<element>, compare> pq;
        set<int> coinSet;
        for (int i = 0; i < vList[1].coins.size(); i++) {
            coinSet.insert(vList[1].coins[i]);
        }

        queue<int> parentQ;
        parentQ.push(1);
        element e(dist, start_node, coinSet, parentQ);
        pq.push(e);

        while (!pq.empty()) {
            element el = pq.top();
            pq.pop();

            if (el.sink == V) {
                cout << "WELCOME TO TEHRAN!!" << endl;
                path = el.parentPath;
                break;
            }

            for (int i = 0; i < vList[el.sink].neighbors.size(); i++) {
                if (!freeThief(el.coins, vList[el.sink].neighbors[i].thieves) &&
                    !notExplored(vList[el.sink].neighbors[i])) {
                    int sink = vList[el.sink].neighbors[i].sink;
                    int tweight = el.weight + vList[el.sink].neighbors[i].weight;

                    set<int> tempCoins = el.coins;
                    queue<int> tempPath = el.parentPath;
                    visitedEdge[el.sink][sink] = 1;

                    for (int i = 0; i < vList[sink].coins.size(); i++)
                        tempCoins.insert(vList[sink].coins[i]);

                    tempPath.push(vList[el.sink].neighbors[i].sink);
                    pq.push(element(tweight, sink, tempCoins, tempPath));

                }

            }

        }

        cout << "OPERATION FINISHED" << endl;

    }
};

int main(int argc, char *argv[]) {
    ifstream infile(argv[1]);
    string line;

    getline(infile, line);
    vector<string> words;
    split1(line, words);


    number_vertice = stoi(words[0]);
    number_roads = stoi(words[1]);
    number_thieves = stoi(words[2]);
    number_jewelers = stoi(words[3]);

    Graph m(number_vertice);

    //get info of jewellery
    for (int i = 0; i < number_jewelers; i++) {
        getline(infile, line);
        vector<string> words1;
        split1(line, words1);
        int town = stoi(words1[0]);
        int number = stoi(words1[1]);
        for (int j = 2; j <number+2; j++) {
            m.addCoin(town, stoi(words1[j]));
        }
    }

    //get info of edges
    for (int i = 0; i < number_roads; i++) {
        getline(infile, line);
        vector<string> words2;
        split1(line, words2);
        int source = stoi(words2[0]);
        int sink = stoi(words2[1]);
        int weight = stoi(words2[2]);
        int numberOfThiefs = stoi(words2[3]);
        for (int j = 4; j < numberOfThiefs+4; j++) {
            int temp=m.thieves[source][sink];
            temp=temp|stoi(words2[j]);
        }
        thieves[source][sink]=temp;
        m.addEdge(source, sink, weight);

    }

    cout<<"okuma islemi bitti" <<endl;

    m.shortestPath();

    if(m.path.size()==0)
        cout<<-1<<endl;
    else{
        while(!m.path.empty()){
            cout<<m.path.front()<<" ";
            m.path.pop();
        }
    }
    return 0;


}
