#include <iostream>
#include "chessAI.h"
#include <string>
int main(){
    std::pair<vector2<char>,vector2<char>> a;
    chessB b;
    for(int i = 0;i<8;++i){
        b.b[i][1] = Cpiece(pieceName::PAWN,pieceColor::BLACK);
        b.b[i][6] = Cpiece(pieceName::PAWN,pieceColor::WHITE);
        for(int y = 2;y<6;++y){
            b.b[i][y] = Cpiece(pieceName::NONE,pieceColor::NONE);
        }
    }
    b.b[0][0] = Cpiece(pieceName::ROOK,pieceColor::BLACK);
	b.b[1][0] = Cpiece(pieceName::HORSE,pieceColor::BLACK);
	b.b[2][0] = Cpiece(pieceName::BISHOP,pieceColor::BLACK);
	b.b[3][0] = Cpiece(pieceName::QUEEN,pieceColor::BLACK);
	b.b[4][0] = Cpiece(pieceName::KING,pieceColor::BLACK);
	b.b[5][0] = Cpiece(pieceName::BISHOP,pieceColor::BLACK);
	b.b[6][0] = Cpiece(pieceName::HORSE,pieceColor::BLACK);
	b.b[7][0] = Cpiece(pieceName::ROOK,pieceColor::BLACK);

    b.b[0][7] = Cpiece(pieceName::ROOK,pieceColor::WHITE);
	b.b[1][7] = Cpiece(pieceName::HORSE,pieceColor::WHITE);
	b.b[2][7] = Cpiece(pieceName::BISHOP,pieceColor::WHITE);
	b.b[3][7] = Cpiece(pieceName::QUEEN,pieceColor::WHITE);
	b.b[4][7] = Cpiece(pieceName::KING,pieceColor::WHITE);
	b.b[5][7] = Cpiece(pieceName::BISHOP,pieceColor::WHITE);
	b.b[6][7] = Cpiece(pieceName::HORSE,pieceColor::WHITE);
	b.b[7][7] = Cpiece(pieceName::ROOK,pieceColor::WHITE);
	//b.b[5][6] = Cpiece(pieceName::NONE,pieceColor::NONE);
    //b.b[5][4] = Cpiece(pieceName::PAWN,pieceColor::WHITE);
	//std::cout<<sizeof (chessB)<<std::endl;
	chessAI::run(b,&a);
	std::cout<<(int)a.first.x<<" "<<(int)a.first.y<<"\n"<<(int)a.second.x<<" "<<(int)a.second.y<<std::endl;
    return 0;
}

