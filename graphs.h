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
    int verteces, edges;
    int** _graph;
public:
    gen_graph(int m, double saturation) {
        verteces = m;
        edges = round(saturation * verteces * (verteces - 1) / 2);
        _graph = new int * [verteces];
        for (int i = 0; i < verteces; i++) {
            _graph[i] = new int [verteces];
            for (int j = 0; j < verteces; j++) {
                _graph[i][j] = 0;
            }
        }
    }

    gen_graph(int m, int n) {
        verteces = m;
        if (m * (m-1)/2 < n)
            edges = (m * (m - 1)) / 2; // max
        else
            edges = n;

        _graph = new int * [verteces];
        for (int i = 0; i < verteces; i++) {
            _graph[i] = new int [verteces];
            for (int j = 0; j < verteces; j++) {
                _graph[i][j] = 0;
            }
        }
    }

    ~gen_graph() {
        if (_graph != nullptr) {
            for (int i = 0; i < verteces; i++) {
                delete[] _graph[i];
            }
            delete[] _graph;
        }
    }

    [[nodiscard]] int get_e_nr() const { return edges; }

    bool del(int a, int b) {
        if (a < 0 || b < 0 || a >= verteces || b >= verteces) {
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
        for (int i = 0; i < verteces; i++) {
            for (int j = 0; j < verteces; j++) {
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
        for (int i = 0; i < verteces; i++) {
            for (int j = 0; j < verteces; j++) {
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
        for (int i = 0; i < verteces; i++) {
            for (int j = 0; j < verteces; j++) {
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
        for (int i = 0; i < verteces; i++) {
            for (int j = 0; j < verteces; j++) {
                if (i == j) {
                    continue;
                }
                _graph[i][j] = 1;
            }
        }

        int edge_count = verteces * (verteces - 1) / 2;
        if (verteces % 2 == 0) {
            for (int i = verteces - 1; i >= 0; i--) {
                del(i, verteces - 1 - i);
            }
            edge_count = verteces * (verteces - 2) / 2;
        }

        int triangle[3];
        int odd_counter = 0;
        while (edge_count - edges >= 2) {
            triangle[0] = rand() % verteces;
            triangle[1] = rand() % verteces;
            triangle[2] = rand() % verteces;
            while (!is_edge(triangle[0], triangle[1])
                   || !is_edge(triangle[1], triangle[2])
                   || !is_edge(triangle[2], triangle[0])
                   || triangle[0] == triangle[1]
                   || triangle[1] == triangle[2]
                   || triangle[2] == triangle[0]) {
                triangle[odd_counter % 3] = rand() % verteces;
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
    int verteces, edges{};
    double sat{};
    std::vector<int> seq;

public:
    Eulerian_cycle(int m, double saturation) {
        verteces = m;

        if (sat < 0.48)
            sat = 0.48;
        else
            sat = saturation;

        _graph = new int * [verteces];
        for (int i = 0; i < verteces; i++) {
            _graph[i] = new int [verteces];
            for (int j = 0; j < verteces; j++) {
                _graph[i][j] = 0;
            }
        }
    }

    Eulerian_cycle(int m, int n) {
        verteces = m;
        if (m * (m-1)/2 < n)
            edges = (m * (m - 1)) / 2; // max
        else if (n < (int)((m * (m-1))/2) * 0.48)
            edges = static_cast<int>(((m * (m - 1)) / 2) * 0.48);
        else
            edges = n;

        _graph = new int * [verteces];
        for (int i = 0; i < verteces; i++) {
            _graph[i] = new int [verteces];
            for (int j = 0; j < verteces; j++) {
                _graph[i][j] = 0;
            }
        }
    }


    ~Eulerian_cycle() {
        if (_graph != nullptr) {
            for (int i = 0; i < verteces; i++) {
                delete[] _graph[i];
            }
            delete[] _graph;
        }
    }

    std::vector<std::pair<int, int>> get_eulerian() {
        int odd_counter = 0;
        std::vector<std::pair<int, int>> e;
        for (int i = 0; i < verteces; i++) {
            for (int j = 0; j < verteces; j++) {
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
        if (a < 0 || b < 0 || a >= verteces || b >= verteces) {
            return false;
        } else {
            _graph[a][b] = 1;
            _graph[b][a] = 1;
            return true;
        }
    }

    void display() {
        for (int i = 0; i < verteces; i++) {
            for (int j = 0; j < verteces; j++) {
                std::cout << _graph[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void load() {
        auto* gen = (sat==0) ? new gen_graph(verteces, edges) : new gen_graph(verteces, sat);
        bool tmp_bool;
        tmp_bool = gen->euler_generate();

        while (!tmp_bool) {
            delete gen;
            gen = (sat==0) ? new gen_graph(verteces, edges) : new gen_graph(verteces, sat);
            tmp_bool = gen->euler_generate();
        }

        for (int i = 0; i < verteces; i++) {
            for (int j = 0; j < verteces; j++) {
                if (gen->is_edge(i, j)) {
                    add(i, j);
                }
            }
        }

        edges = gen->get_e_nr();
        delete gen;
    }

    bool del_edge(int a, int b) {
        if (a < 0 || b < 0 || a >= verteces || b >= verteces) {
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
