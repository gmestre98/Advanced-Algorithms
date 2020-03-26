// https://github.com/simongog/sdsl-lite
#include <iostream>
#include <vector>

class AdjMatrix {
    bool matrix[5][5];
public:
    AdjMatrix() {}
    void addLink(int v1, int v2) {
        matrix[v1][v2] = true;
        matrix[v2][v1] = true;
    }

    void removeLink(int v1, int v2) {
        matrix[v1][v2] = false;
        matrix[v2][v1] = false;
    }

    void getNeighbours(int v, bool* result) {

        for (int i=0; i < 5; ++i) {
            if(matrix[v][i] == true)
                result[i] = true;
        }

    }   
};

int main(int argc, char** argv) {
    AdjMatrix* matrix = new AdjMatrix();
    bool result[5] = {false};

    matrix->addLink(0,1);
    matrix->addLink(0,2);
    matrix->addLink(0,3);

    matrix->getNeighbours(0, result);
    for(int i=0; i < 5; ++i){
        std::cout << result[i] << "\n";
    }

    return 0;
}