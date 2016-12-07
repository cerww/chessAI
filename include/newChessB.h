#ifndef NEWCHESSB_H
#define NEWCHESSB_H

#include "../vectors.h"
#include <array>
#include "../chessAI.h"
class newChessB{
    public:
        newChessB(){};
        ~newChessB(){};
        void setPiece(const vector2<char>& spot,const Cpiece& stuff);
        std::array<unsigned char,32> getBoard(){return m_board;};
    private:
        std::array<unsigned char,32> m_board;//each piece is 1/2 bytes,4 bits,64*1/2 bytes = 32

};

#endif // NEWCHESSB_H
