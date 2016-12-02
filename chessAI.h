#ifndef CHESSAI_H
#define CHESSAI_H
#include <thread>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
//#include "chessPiece.h"
//#include <SFML/Graphics.hpp>
#include "vectors.h"
#include <memory>
#include <algorithm>
#include "vecFuncs.h"
enum class pieceColor:char{WHITE,BLACK,NONE};
enum class pieceName:char{PAWN,ROOK,BISHOP,QUEEN,KING,HORSE,NONE};
struct Cpiece{
	Cpiece():n((pieceName)0),c((pieceColor)0){};
	Cpiece(pieceName k,pieceColor l):n(k),c(l){};
	pieceName n;
	pieceColor c;
	//vector2<int> spot;
};
inline bool operator==(const Cpiece& a,const Cpiece& other){
	return 1;
	//return (int)a.n+(int)a.c*10+a.spot.x*40+a.spot.y*400==(int)other.n+(int)other.c*10+other.spot.x*40+other.spot.y*400;
}
template<class T,int L>
inline bool operator==(const std::array<T,L>& one,const std::array<T,L>& two){
	for(int x = 0;x<L;++x)
		if(one[x]!=two[x])
			return 0;
	return 1;
}
struct chessB{
	//chessB(){b.resize(8);		for(int x = 0;x<8;++x){			b[x].resize(8);		}};
	chessB(){};
	std::array<std::array<Cpiece,8>,8 > b;
	//std::vector<std::vector<Cpiece> > b;
	//std::arr<std::vector<Cpiece> > b;
	bool operator<(const chessB& other){
		//return (int)n+(int)c*10+spot.x*100+spot.y*1000>(int)other.n+(int)other.c*10+spot.x*100+spot.y*1000;
		//return b<other.b;
		return 1;
	}

};
inline bool operator ==(const chessB& one,const chessB& other){
	return one.b==other.b;
}
namespace std{
	template <>
        class hash<chessB>{
        public :
            size_t operator()(const chessB &a ) const{
				string k;
				//vector<unsigned int> k(128);
				k.resize(128);
                for(int x = 0;x<8;++x)
					for(int y = 0;y<8;++y){
						k.at((x*8)+y)=((int)a.b[x][y].n)+65;
						k.at((x*8)+y+64)=((int)a.b[x][y].c)+65;
					}
				//return hash<vector<unsigned int> >()(k);
				return hash<string>()(k);
            }
    };
};
struct Bpoints{
	int white = 0;
	int black = 0;
	int operator[](int o);
};
inline int Bpoints::operator[](int o){
	if(o==0)return white;
	return black;
}
struct boardNode{
	boardNode(){};
	chessB board;//128 bytes
	std::array<std::vector<std::pair<vector2<char>,vector2<char>> >,2 >  moveSpots;
	std::array<std::vector<int>,2> edges;
};
inline bool operator==(const boardNode& one,const boardNode& two){
	return one.board==two.board;
}
namespace std{
	template<>
	class hash<boardNode>{
		public:
		size_t operator()(const boardNode& a)const {
			return hash<chessB>()(a.board);
		}
	};
};
class chessAI{
	public:
		static void run(const chessB b,std::pair<vector2<char>,vector2<char>>* toDoMove);
		static std::unordered_map<boardNode,int> dp;//half nodes, i should fix this
		static std::unordered_map<boardNode,int> dp3;
		static std::unordered_map<int,boardNode> dp2;//half nodes, i should fix this
		static std::unordered_map<int,boardNode> dp4;
		static std::unordered_map<chessB,boardNode> thingy1;
		static std::unordered_map<boardNode,int> thingy2;
		static int done;
		//static std::map<std::vector<std::vector<Cpiece> >,boardNode> thingy1;
		//static std::map<chessB,std::map<Cpiece,std::vector<vector2<int>> > > thingy1;
};
#endif

