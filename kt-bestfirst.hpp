#ifndef kt_bestfirst_hpp
#define kt_bestfirst_hpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include "chessboard.hpp"
using namespace std;

typedef pair<int,int> ScoredMove; 
typedef priority_queue<ScoredMove, vector<ScoredMove>, greater<ScoredMove>> _priorityQueue;

class PriorityQueue {
    private:
        _priorityQueue _pq;
    public:
        PriorityQueue() { }
        bool empty() { 
            return _pq.empty(); 
        }
        void push(int score, int move) {
            _pq.push(make_pair(score, move));
        }
        int pop() {
            int move = _pq.top().second;
            _pq.pop();
            return move;
        }
};


class Knight {
    private:
        int coloffset[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
        int rowoffset[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
        bool promising(ChessBoard& cb, int col, int row) {
            return cb.inBounds(col, row) && (cb.getPosition(row,col) == -1);
        }
        int countMovesFrom(ChessBoard& cb, int c, int r) {
            int valid_moves = 0;
            for (int i = 0; i < 8; i++) {
                int nc = c + coloffset[i];
                int nr = r + rowoffset[i];
                if (promising(cb, nc, nr))
                    valid_moves++;
            }
            return valid_moves;
        }
        void scoreNextMoves(ChessBoard& cb, int c, int r, int placed, PriorityQueue& pq) {
            for (int i = 0; i < 8; i++) {
                int nc = c + coloffset[i];
                int nr = r + rowoffset[i];
                if (promising(cb, nc, nr)) {
                    int cm = countMovesFrom(cb, nc, nr);
                    cout<<nc<<"/"<<nr<<": "<<cm<<endl;
                    if (cm > 0 || placed == 63)
                        pq.push(cm, i);
                }
            }
        }
        bool tryMove(ChessBoard& cb, int c, int r, int move, int placed) {
            int nc = c + coloffset[move];
            int nr = r + rowoffset[move];
            cb.setPosition(nr, nc, placed);
            cout<<"Trying: "<<nc<<"/"<<nr<<endl;
            if (findTour(cb, nc, nr, placed+1))
                return true;
            cout<<"Backtracking..."<<endl;
            cb.setPosition(nr, nc, -1);
            return false; 
        }
        bool findTour(ChessBoard cb, int c, int r, int placed) {
            if (placed == cb.size() * cb.size()) {
                cb.printBoard();
                return true;
            } else {
                PriorityQueue pq;
                scoreNextMoves(cb, c, r, placed, pq);
                while (!pq.empty()) {
                    int next = pq.pop();
                    if (tryMove(cb, c, r, next, placed))    
                        return true;
                }
            }
            return false;
        }
    public:
        Knight() { }
        bool tour(ChessBoard& cb) {
            cb.setPosition(0, 0, 0);
            return findTour(cb, 0, 0, 1);
        }
};
#endif