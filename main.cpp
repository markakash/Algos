#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

bool dfs(std::string word, std::vector<std::vector<char>> grid, int r, int c, int index, std::set<std::tuple<int, int>> path) {
    // BASE CASE: If index == length of the word, then return True
    if (index == word.size()) {
        return true;
    }

    int ROW = grid.size(), COL = grid[0].size();

    // BASE CASE 2: Cases when u return false:
    // 1. When r < 0 or c < 0 or r >= ROW of grid, c >= COL of grid or word[i] != grid[r][c] or path contains r or c
    // Then we return false
    if (
        r < 0 || c < 0 || r >= ROW || c >= COL || word[index] != grid[r][c]
        || path.find(std::make_tuple(r, c)) != path.end()) {
        return false;
        }

    // If the above cases aren't the case then we need to check in 4 position.
    // Top of i, left or i, right of i and below i;
    // So if the above conditions aren't met then we found a match/path
    // Add its index to the path
    path.insert(std::make_tuple(r, c));
    auto res = (dfs(word, grid, r + 1, c, index + 1, path) ||
                   dfs(word, grid, r - 1, c, index + 1, path) ||
                   dfs(word, grid, r, c + 1, index + 1, path) ||
                   dfs(word, grid, r, c - 1, index + 1, path));
    // Remove the path we visited cause we visited it already
    path.erase(std::make_tuple(r, c));
    return res;
}

bool exists(std::string word, std::vector<std::vector<char>> grid) {
    // The idea of backtracking is that we visit every possible solution and if we get stuck then undo the previous solution
    // Create a vector to store the visited path. This way we don't visit the same row or col again
    std::set<std::tuple<int, int>> path;

    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (dfs(word, grid, row, col, 0, path)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::vector<std::vector<char>> grid = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    std::cout << exists("ASAA", grid) << std::endl;
    return 0;
}
