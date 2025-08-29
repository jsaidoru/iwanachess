#include "movegen/generate_all_moves.hpp"
#include "Board.hpp"
#include "types.hpp"
#include "MoveList.hpp"

long long perft(Board& board, int depth) { 
    if (depth == 0)
        return 1;

    MoveList moves = generate_all_pseudo_moves(board);

    long long nodes = 0; 
    for (int i = 0; i < moves.size; i++) {
        Move move = moves.moves[i];

        if (!board.push(move)) 
            continue;

        nodes += perft(board, depth - 1);

        board.pop(); 
    }
    return nodes;
}

int main(){
    std::string startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Board b(startpos);
    std::cout << "depth 1 perft:"<<perft(b, 1);
    std::cout << "depth 2 perft:"<<perft(b, 1);
    std::cout << "depth 3 perft:"<<perft(b, 1);
    std::cout << "depth 4 perft:"<<perft(b, 1);
}