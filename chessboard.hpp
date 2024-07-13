#ifndef chessboard_hpp
#define chessboard_hpp
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class ChessBoard {
    private:
        using Board = vector<vector<int>>; 
        Board board;
        int N;
        void init(int n) {
            N = n;
            board = vector<vector<int>>(n, vector<int>(n, -1));
        }
    public:
        ChessBoard(int n) {
            init(n);
        }
        int size() {
            return N;
        }
        bool inBounds(int col, int row) {
            return (row >= 0 && row < N && col >= 0 && col < N);
        }
        void setPosition(int row, int col, int value) {
            board[row][col] = value;
        }
        int getPosition(int row, int col) {
            return board[row][col];
        }
        void printBoard() {
            for (int k = 0; k < board.size()*6; k++)
                cout<<"-";
                cout<<endl;
            for (int i = 0; i < board.size(); i++) {
                cout<<"|";
                for (int j = 0; j < board[i].size(); j++) {
                    cout<<setw(4)<<board[i][j]<<"| ";
                }
                cout<<endl;
                for (int k = 0; k < board.size()*6; k++)
                    cout<<"-";
                cout<<endl;
            }
        }
};
#endif