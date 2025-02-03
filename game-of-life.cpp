#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

class GameOfLife {
public:
    GameOfLife(int rows, int cols) : rows(rows), cols(cols) {
        grid.resize(rows, vector<bool>(cols, false));
    }

    void initialize() {
        grid[1][2] = true;
        grid[2][3] = true;
        grid[3][1] = true;
        grid[3][2] = true;
        grid[3][3] = true;
    }

    void display() {
        system("clear");
        for (const auto& row : grid) {
            for (bool cell : row) {
                cout << (cell ? "O" : ".") << " ";
            }
            cout << endl;
        }
    }

    void update() {
        vector<vector<bool>> newGrid = grid;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int liveNeighbors = countLiveNeighbors(i, j);
                if (grid[i][j]) {
                    newGrid[i][j] = (liveNeighbors == 2 || liveNeighbors == 3);
                } else {
                    newGrid[i][j] = (liveNeighbors == 3);
                }
            }
        }
        grid = newGrid;
    }

private:
    int rows, cols;
    vector<vector<bool>> grid;

    int countLiveNeighbors(int x, int y) {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int newX = x + i;
                int newY = y + j;
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY]) {
                    count++;
                }
            }
        }
        return count;
    }
};

int main() {
    int rows = 10;
    int cols = 10;
    GameOfLife game(rows, cols);
    game.initialize();
    while (true) {
        game.display();
        game.update();
        usleep(500000);
    }
    return 0;
}
