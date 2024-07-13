#include <iostream>
#include "kt-bestfirst.hpp"

int main(int argc, char* argv[]) {
    ChessBoard cb(8);
    Knight knight;
    knight.tour(cb);
}