#include "newChessB.h"


void newChessB::setPiece(const vector2<char>& spot,const Cpiece& piece){
    //
    //spot.x*8+spot.y
    //
    m_board[(spot.x*8+spot.y)/2] = (m_board[(spot.x*8+spot.y)/2]&((spot.x*8+spot.y)%2==0?0b00001111:0b11110000))|(((char)piece.c()%2)<<((spot.x*8+spot.y)%2==0?4:0));
    m_board[(spot.x*8+spot.y)/2] = m_board[(spot.x*8+spot.y)/2]|(((char)piece.n()<<3)<<((spot.x*8+spot.y)%2==0?4:0));

}
