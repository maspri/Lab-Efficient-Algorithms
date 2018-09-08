#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

enum TAG {
    ROW_NEGATED,
    ROW,
    COLUMN_NEGATED,
    COLUMN

};

class Literal {
public:
    TAG tag;
    int id;

    Literal(){};

    void setValues(int id, char type, int direction){
        this->id = id;
        if(type == 'z'){
            if(direction ==1){
                this->tag = ROW;
            } else{
                this->tag = ROW_NEGATED;
            }
        } else{
            if(direction ==1){
                this->tag = COLUMN;
            } else{
                this->tag = COLUMN_NEGATED;
            }
        }
    }
};

class DnfClause {
public:
    Literal one;
    Literal two;

};

struct point {
    int x;
    int y;
};
struct query {
    point p1;
    point p2;
};

/*
 * the first n nodes are the positve literals of the variables for the orientation of edges at x postion
 * the second n nodes are the negativ literals of the variables for the orientation of edges at x postion
 * the next m nodes are the positve literals of the variables for the orientation of edges at y postion
 * the last m nodes are the negative literals of the varaibles for the orientation of edges at y postion
 */
class TwoSATGraph {
public:
    vector<vector<int>> nodes;
    int n; //number of x variables
    int m; //number of y variables

    TwoSATGraph(int n, int m):nodes((n+m)*2,vector<int>()),n(n),m(m){
    }

    /**
     * For the degenerated clauses
     * @param clause
     */
    void addEdge(DnfClause clause){
        addEdge(getNode(clause.one.id,invertTag(clause.one.tag)),
                getNode(clause.one.id, clause.one.tag));
    }

    /**
     *
     * @param clause1
     * @param clause2
     * */
    void addEdges(DnfClause clause1, DnfClause clause2){
        //not( clause1.one) ->  clause2.one
        addEdge(getNode(clause1.one.id,invertTag(clause1.one.tag)),
                getNode(clause2.one.id, clause2.one.tag));
        //not( clause1.two) ->  clause2.one
        addEdge(getNode(clause1.two.id,invertTag(clause1.two.tag)),
                getNode(clause2.one.id, clause2.one.tag));
        //not( clause1.one) ->  clause2.two
        addEdge(getNode(clause1.one.id,invertTag(clause1.one.tag)),
                getNode(clause2.two.id, clause2.two.tag));
        //not( clause1.two) ->  clause2.two
        addEdge(getNode(clause1.two.id,invertTag(clause1.two.tag)),
                getNode(clause2.two.id, clause2.two.tag));
    }

private:

    void addEdge(int v, int w){
        nodes[v].push_back(w);
    }

    int getNode(int id, TAG tag){
        switch (tag){
            case ROW:
                return id;
            case ROW_NEGATED:
                return id+n;
            case COLUMN:
                return id+(2*n);
            case COLUMN_NEGATED:
                return id+(2*n)+m;
            default:
                throw new exception();
        }

    }

    TAG invertTag(TAG tag) {
        switch (tag) {
            case ROW:
                return ROW_NEGATED;
            case ROW_NEGATED:
                return ROW;
            case COLUMN:
                return COLUMN_NEGATED;
            case COLUMN_NEGATED:
                return COLUMN;
            default:
                throw new exception();
        }
    }

};

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

/**
 *
 * @param N
 * @param start
 * @param goal
 * @param nodes
 * @param prev
 * @return
 */
bool dfs(int N,int start, int goal, const vector<vector<int>> &nodes){

    vector<int > open;
    open.push_back(start);
    vector<bool> visited(N,false);
    visited[start] = true;
    bool found = false;

    while (open.size() > 0){
        int v = open.back();
        open.pop_back();

        if(v == goal){
            found = true;
            break;
        }

        for (int e: nodes[v]) {
            if(!visited[e]){
                open.push_back(e);
                visited[e] = true;
            }
        }
    }
    if(!found){
        return -1;
    } else {
        return 0;
    }
}

TwoSATGraph& constructGraph(vector<query>& queries, int n, int m) {
    TwoSATGraph *graph = new TwoSATGraph(n, m);

    for (auto &query: queries) {
        point direction;
        direction.x = sgn(query.p2.x - query.p1.x);
        direction.y = sgn(query.p2.y - query.p1.y);

        DnfClause c1, c2;

        Literal lit11, lit12;
        c1.one.setValues(query.p1.y, 'z', direction.x);
        c1.two.setValues(query.p2.x, 's', direction.y);
        c2.one.setValues(query.p2.y, 'z', direction.x);
        c2.two.setValues(query.p1.x, 's', direction.y);

        if (direction.x == 0) {
            //degenerated case
            c1.one = c1.two;
            graph->addEdge(c1);
        } else if (direction.y == 0) {
            //degenerated case
            c1.two = c1.one;
            graph->addEdge(c1);
        } else {
            graph->addEdges(c1, c2);

        }
    }

    return *graph;
}

bool graphContainsConflict(TwoSATGraph &g){
    //check the row literals
    for (int i = 0; i < g.n; ++i) {
        if(dfs((g.n+g.m)*2,i,i+g.n,g.nodes) && dfs((g.n+g.m)*2,i+g.n,i,g.nodes) ){
            return true;
        }
    }
    //check the column literals
    for (int i = 2*g.n; i < (2*g.n)+g.m; ++i) {
        if(dfs((g.n+g.m)*2,i,i+g.m,g.nodes) && dfs((g.n+g.m)*2,i+g.m,i,g.nodes) ){
            return true;
        }
    }

    return false;
}


int main() {
    int n,m,s;

    cin >> n >> m >> s;
    vector<query> queries(s,query());
    for (int i = 0; i < s; ++i) {
        cin >> queries[i].p1.x >> queries[i].p2.y >> queries[i].p2.x >> queries[i].p2.y;
    }

    TwoSATGraph & g = constructGraph(queries,n,m);
    if(graphContainsConflict(g)){
        cout<<"impossible";
    } else{
        cout<<"possible";
    }


    return 0;
}