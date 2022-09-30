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
    gen_graph(int m, double saturation) {
        v_nr = m;
        e_nr = round(saturation * v_nr * (v_nr - 1) / 2);
        _graph = new int * [v_nr];
        for (int i = 0; i < v_nr; i++) {
            _graph[i] = new int [v_nr];
            for (int j = 0; j < v_nr; j++) {
                _graph[i][j] = 0;
            }
        }
    }

    gen_graph(int m, int n) {
        v_nr = m;
        if (m * (m-1)/2 < n)
            e_nr = (m * (m-1))/2; // max
        else
            e_nr = n;

        _graph = new int * [v_nr];
        for (int i = 0; i < v_nr; i++) {
            _graph[i] = new int [v_nr];
            for (int j = 0; j < v_nr; j++) {
                _graph[i][j] = 0;
            }
        }
    }

    ~gen_graph() {
        if (_graph != nullptr) {
            for (int i = 0; i < v_nr; i++) {
                delete[] _graph[i];
            }
            delete[] _graph;
        }
    }

    [[nodiscard]] int get_e_nr() const { return e_nr; }

    bool del(int a, int b) {
        if (a < 0 || b < 0 || a >= v_nr || b >= v_nr) {
            return false;
        } else {
            _graph[a][b] = 0;
            _graph[b][a] = 0;
            return true;
        }
    }

    bool is_edge(int a, int b) {
        if (_graph[a][b] == 1) {
            return true;
        } else {
            return false;
        }
    }

    bool is_eulerian() {
        int odd_counter = 0;
        for (int i = 0; i < v_nr; i++) {
            for (int j = 0; j < v_nr; j++) {
                if (_graph[i][j] == 1) {
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

    std::vector<std::pair<int, int>> get_eulerian() {
        int odd_counter = 0;
        std::vector<std::pair<int, int>> e;
        for (int i = 0; i < v_nr; i++) {
            for (int j = 0; j < v_nr; j++) {
                if (_graph[i][j] == 1) {
                    odd_counter++;
                    e.emplace_back(i, j);
                }
            }
            if (odd_counter % 2 != 0 || odd_counter == 0) {
                e.clear();
                return e;
            }
            odd_counter = 0;
        }
        return e;
    }

    void display() {
        for (int i = 0; i < v_nr; i++) {
            for (int j = 0; j < v_nr; j++) {
                std::cout << _graph[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void display_eulerian() {
        std::vector<std::pair<int, int>> v;
        v = get_eulerian();

        for (std::pair<int, int> i : v) {
            std::cout << '[' << i.first << ',' << i.second << "] ";
        }
    }

    bool euler_generate() {
        for (int i = 0; i < v_nr; i++) {
            for (int j = 0; j < v_nr; j++) {
                if (i == j) {
                    continue;
                }
                _graph[i][j] = 1;
            }
        }
        int edge_count = v_nr * (v_nr - 1) / 2;
        if (v_nr % 2 == 0) {
            for (int i = v_nr - 1; i >= 0; i--) {
                del(i, v_nr - 1 - i);
            }
            edge_count = v_nr * (v_nr - 2) / 2;
        }
        int triangle[3];
        int odd_counter = 0;
        while (edge_count - e_nr >= 2) {
            triangle[0] = rand() % v_nr;
            triangle[1] = rand() % v_nr;
            triangle[2] = rand() % v_nr;
            while (!is_edge(triangle[0], triangle[1])
                   || !is_edge(triangle[1], triangle[2])
                   || !is_edge(triangle[2], triangle[0])
                   || triangle[0] == triangle[1]
                   || triangle[1] == triangle[2]
                   || triangle[2] == triangle[0]) {
                triangle[odd_counter % 3] = rand() % v_nr;
                odd_counter++;
            }
            del(triangle[0], triangle[1]);
            del(triangle[1], triangle[2]);
            del(triangle[2], triangle[0]);
            edge_count -= 3;
        }
        return is_eulerian();
    }

};

class Eulerian_cycle {
    int** _graph;
    int v_nr, e_nr{};
    double sat{};
    std::vector<int> seq;

public:
    Eulerian_cycle(int m, double saturation) {
        v_nr = m;

        if (sat < 0.48)
            sat = 0.48;
        else
            sat = saturation;

        _graph = new int * [v_nr];
        for (int i = 0; i < v_nr; i++) {
            _graph[i] = new int [v_nr];
            for (int j = 0; j < v_nr; j++) {
                _graph[i][j] = 0;
            }
        }
    }

    Eulerian_cycle(int m, int n) {
        v_nr = m;
        if (m * (m-1)/2 < n)
            e_nr = (m * (m-1))/2; // max
        else if (n < (int)((m * (m-1))/2) * 0.48)
            e_nr = static_cast<int>(((m * (m-1))/2) * 0.48);
        else
            e_nr = n;

        _graph = new int * [v_nr];
        for (int i = 0; i < v_nr; i++) {
            _graph[i] = new int [v_nr];
            for (int j = 0; j < v_nr; j++) {
                _graph[i][j] = 0;
            }
        }
    }


    ~Eulerian_cycle() {
        if (_graph != nullptr) {
            for (int i = 0; i < v_nr; i++) {
                delete[] _graph[i];
            }
            delete[] _graph;
        }
    }

    std::vector<std::pair<int, int>> get_eulerian() {
        int odd_counter = 0;
        std::vector<std::pair<int, int>> e;
        for (int i = 0; i < v_nr; i++) {
            for (int j = 0; j < v_nr; j++) {
                if (_graph[i][j] == 1) {
                    odd_counter++;
                    e.emplace_back(i, j);
                }
            }
            if (odd_counter % 2 != 0 || odd_counter == 0) {
                e.clear();
                return e;
            }
            odd_counter = 0;
        }
        return e;
    }

    void display_eulerian() {
        std::vector<std::pair<int, int>> v;
        v = get_eulerian();

        for (std::pair<int, int> i : v) {
            std::cout << '[' << i.first << ',' << i.second << "] ";
        }
    }

    bool is_edge(int a, int b) {
        if (_graph[a][b] == 1) {
            return true;
        } else {
            return false;
        }
    }

    bool add(int a, int b) {
        if (a < 0 || b < 0 || a >= v_nr || b >= v_nr) {
            return false;
        } else {
            _graph[a][b] = 1;
            _graph[b][a] = 1;
            return true;
        }
    }

    void display() {
        for (int i = 0; i < v_nr; i++) {
            for (int j = 0; j < v_nr; j++) {
                std::cout << _graph[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void load() {
        auto* gen = (sat==0) ? new gen_graph(v_nr, e_nr) : new gen_graph(v_nr, sat);
        bool tmp_bool;
        tmp_bool = gen->euler_generate();

        while (!tmp_bool) {
            delete gen;
            gen = (sat==0) ? new gen_graph(v_nr, e_nr) : new gen_graph(v_nr, sat);
            tmp_bool = gen->euler_generate();
        }

        for (int i = 0; i < v_nr; i++) {
            for (int j = 0; j < v_nr; j++) {
                if (gen->is_edge(i, j)) {
                    add(i, j);
                }
            }
        }

        e_nr = gen->get_e_nr();
        delete gen;
    }

    bool del_edge(int a, int b) {
        if (a < 0 || b < 0 || a >= v_nr || b >= v_nr) {
            return false;
        }

        if (!is_edge(a, b)) {
            return false;
        }

        _graph[a][b] = 0;
        _graph[b][a] = 0;
        return true;
    }
};

#endif //_GRAPHS_H
