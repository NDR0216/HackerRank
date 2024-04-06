#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'knightlOnAChessboard' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts INTEGER n as parameter.
 */

struct Node {
    int row;
    int col;
    int moves;
};

bool visit(int row, int col, int moves, int n, bool** visited, queue<Node> *nodeQueue) {
    if (row == n-1 && col == n-1) {
        return true;    // found
    }

    if (row < 0 || row >= n || col < 0 || col >= n) {
        return false;   // not valid position
    }

    if (!visited[row][col]) {
        visited[row][col] = true;
        nodeQueue->push(Node{row, col, moves});
    }

    return false;   // not found
}

int KnightL(int a, int b, int n) {
    // BFS

    bool** visited = new bool*[n];
    for (int i = 0; i < n; i++) {
        visited[i] = new bool[n]{};
    }

    queue<Node> nodeQueue;

    // visit (0, 0)
    visited[0][0] = true;
    nodeQueue.push(Node{0, 0, 0});

    while (!nodeQueue.empty()) {
        Node p = nodeQueue.front();
        nodeQueue.pop();

        // return if found
        if (visit(p.col+a, p.row+b, p.moves+1, n, visited, &nodeQueue)) {
            return p.moves+1;
        }
        if (visit(p.col+a, p.row-b, p.moves+1, n, visited, &nodeQueue)) {
            return p.moves+1;
        }
        if (visit(p.col-a, p.row+b, p.moves+1, n, visited, &nodeQueue)) {
            return p.moves+1;
        }
        if (visit(p.col-a, p.row-b, p.moves+1, n, visited, &nodeQueue)) {
            return p.moves+1;
        }
        if (visit(p.col+b, p.row+a, p.moves+1, n, visited, &nodeQueue)) {
            return p.moves+1;
        }
        if (visit(p.col+b, p.row-a, p.moves+1, n, visited, &nodeQueue)) {
            return p.moves+1;
        }
        if (visit(p.col-b, p.row+a, p.moves+1, n, visited, &nodeQueue)) {
            return p.moves+1;
        }
        if (visit(p.col-b, p.row-a, p.moves+1, n, visited, &nodeQueue)) {
            return p.moves+1;
        }
    }

    return -1;  // impossible
}

vector<vector<int>> knightlOnAChessboard(int n) {
    vector<vector<int>> output(n-1, vector<int>(n-1));

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j <= i; j++) {  // symmetric
            int moves = KnightL(i+1, j+1, n);

            output[i][j] = moves;
            output[j][i] = moves;
        }
    }

    return output;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> result = knightlOnAChessboard(n);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            fout << result[i][j];

            if (j != result[i].size() - 1) {
                fout << " ";
            }
        }

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
