#ifndef _GRAPHS_H
#define _GRAPHS_H

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <list>
#include <algorithm>
#include <cstring>
#include <stack>

class gen_graph {
    int v_nr, e_nr;
    int** _graph;
public:
    gen_graph(int m, float saturation) {
        this->v_nr = m;
        this->e_nr = round(saturation * this->v_nr * (this->v_nr - 1) / 2);
        this->_graph = new int * [this->v_nr];
        for (int i = 0; i < this->v_nr; i++) {
            this->_graph[i] = new int [this->v_nr];
            for (int j = 0; j < this->v_nr; j++) {
                this->_graph[i][j] = 0;
            }
        }
    }

    ~gen_graph() {
        if (this->_graph != NULL) {
            for (int i = 0; i < this->v_nr; i++) {
                delete [] this->_graph[i];
                this->_graph[i] = NULL;
            }
            delete [] this->_graph;
            this->_graph = NULL;
        }
    }

    int get_e_nr() { return e_nr; }

    bool del(int a, int b) {
        if (a < 0 || b < 0 || a >= this->v_nr || b >= this->v_nr) {
            return false;
        }
        else {
            this->_graph[a][b] = 0;
            this->_graph[b][a] = 0;
            return true;
        }
    }

    bool is_edge(int a, int b) {
        if (this->_graph[a][b] == 1) {
            return true;
        }
        else {
            return false;
        }
    }

    bool is_eulerian() {
        int odd_counter = 0;
        for (int i = 0; i < this->v_nr; i++) {
            for (int j = 0; j < this->v_nr; j++) {
                if (this->_graph[i][j] == 1) {
                    odd_counter++;
                }
            }
            if (odd_counter % 2 != 0 || odd_counter == 0) {
                return false;
            }
            odd_counter = 0;
        }
        return true;
    }


    bool euler_generate() {
        for (int i = 0; i < this->v_nr; i++) {
            for (int j = 0; j < this->v_nr; j++) {
                if (i == j) {
                    continue;
                }
                this->_graph[i][j] = 1;
            }
        }
        int edge_count = this->v_nr * (this->v_nr - 1) / 2;
        if (this->v_nr % 2 == 0) {
            for (int i = this->v_nr - 1; i >= 0; i--) {
                this->del(i, this->v_nr - 1 - i);
            }
            edge_count = this->v_nr * (this->v_nr - 2) / 2;
        }
        int triangle[3];
        int odd_counter = 0;
        while (edge_count - this->e_nr >= 2) {
            triangle[0] = rand() % this->v_nr;
            triangle[1] = rand() % this->v_nr;
            triangle[2] = rand() % this->v_nr;
            while (!this->is_edge(triangle[0], triangle[1]) || !this->is_edge(triangle[1], triangle[2]) || !this->is_edge(triangle[2], triangle[0]) || triangle[0] == triangle[1] || triangle[1] == triangle[2] || triangle[2] == triangle[0]) {
                triangle[odd_counter % 3] = rand() % this->v_nr;
                odd_counter++;
            }
            this->del(triangle[0], triangle[1]);
            this->del(triangle[1], triangle[2]);
            this->del(triangle[2], triangle[0]);
            edge_count -= 3;
        }
        return this->is_eulerian();
    }

};

class Eulerian_cycle {
    int** _graph;
    int v_nr, e_nr;
    float sat;
    std::vector<int> seq;

public:
    Eulerian_cycle(int m, float saturation) {
        this->v_nr = m;
        this->sat = saturation;
        this->_graph = new int * [this->v_nr];
        for (int i = 0; i < this->v_nr; i++) {
            this->_graph[i] = new int [this->v_nr];
            for (int j = 0; j < this->v_nr; j++) {
                this->_graph[i][j] = 0;
            }
        }
    }


    ~Eulerian_cycle() {
        if (this->_graph != NULL) {
            for (int i = 0; i < this->v_nr; i++) {
                delete [] this->_graph[i];
                this->_graph[i] = NULL;
            }
            delete [] this->_graph;
            this->_graph = NULL;
        }
    }

    bool is_edge(int a, int b) {
        if (this->_graph[a][b] == 1) {
            return true;
        }
        else {
            return false;
        }
    }

    bool add(int a, int b) {
        if (a < 0 || b < 0 || a >= this->v_nr || b >= this->v_nr) {
            return false;
        }
        else {
            this->_graph[a][b] = 1;
            this->_graph[b][a] = 1;
            return true;
        }
    }

    void display() {
        for (int i = 0; i < this->v_nr; i++) {
            for (int j = 0; j < this->v_nr; j++) {
                std::cout << this->_graph[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void load() {
        gen_graph* gen = new gen_graph(this->v_nr, this->sat);
        bool tmp_bool;
        tmp_bool = gen->euler_generate();
        while (!tmp_bool) {
            delete gen;
            gen = NULL;
            gen = new gen_graph(this->v_nr, this->sat);
            tmp_bool = gen->euler_generate();
        }
        for (int i = 0; i < this->v_nr; i++) {
            for (int j = 0; j < this->v_nr; j++) {
                if (gen->is_edge(i, j)) {
                    this->add(i, j);
                }
            }
        }
        this->e_nr = gen->get_e_nr();
        delete gen;
        gen = NULL;
    }


    bool are_adjecent(int a) {
        for (int i = 0; i < this->v_nr; i++) {
            if (this->is_edge(a, i)) {
                return true;
            }
        }
        return false;
    }

    int first_adjecent(int a) {
        for (int i = 0; i < this->v_nr; i++) {
            if (this->_graph[a][i] == 1) {
                return i;
            }
        }
        return -1;
    }

    bool del_edge(int a, int b) {
        if (a < 0 || b < 0 || a >= this->v_nr || b >= this->v_nr) {
            return false;
        }

        if (!this->is_edge(a, b)) {
            return false;
        }

        this->_graph[a][b] = 0;
        this->_graph[b][a] = 0;
        return true;
    }

    double perform() {
        clock_t begin, end;
        begin = clock();
        std::stack<int> util_stack;
        int v = 0;
        int u;
        util_stack.push(v);
        while (!util_stack.empty()) {
            v = util_stack.top();
            if (this->are_adjecent(v)) {
                u = this->first_adjecent(v);
                util_stack.push(u);
                this->del_edge(u, v);
                v = u;
            }
            else {
                util_stack.pop();
                this->seq.push_back(v);
            }
        }
        end = clock();
        return double (end - begin) / CLOCKS_PER_SEC;
    }
};

#endif //_GRAPHS_H
