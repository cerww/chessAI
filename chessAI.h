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
enum class pieceName:char{PAWN,ROOK,BISHOP,QUEEN,KING,HORSE,NONE};/**/
//000 000 00
struct Cpiece{
	Cpiece(){};//:n((pieceName)0),c((pieceColor)0){};
	Cpiece(pieceName k,pieceColor l):all((unsigned char)l|((unsigned char)k<<2)){}//:n(k),c(l){};
	//pieceName n;
	unsigned char all;
    pieceName n()const {return (pieceName)(all>>2);};
    pieceColor c()const {return (pieceColor)(all%4);};
	//pieceColor c;
	//char pieceAndName;
	//vector2<int> spot;
};
inline bool operator==(const Cpiece& a,const Cpiece& other){
	//return 1;
	//return a.n==other.n&&a.c==other.c;
	return a.all == other.all;
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
	bool operator<(const chessB& other) const {
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
						k[(x*8)+y]=((char)(a.b[x][y].n()))+65;
						k[(x*8)+y+64]=((char)a.b[x][y].c())+65;
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
	chessB board;//64 bytes now
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
		 void run(const chessB b,std::pair<vector2<char>,vector2<char>>* toDoMove);
		 std::unordered_map<boardNode,int> dp;
		 std::unordered_map<int,boardNode> dp2;//half nodes, i should fix this
		//static std::unordered_map<int,boardNode> dp4;
		 std::unordered_map<chessB,int> thingy1;
		//static std::unordered_map<boardNode,int> thingy2;
		 int numNodes;
		 int done;
		 std::vector<vector2<char>> getMoveSpots(const chessB& b,const Cpiece& p,vector2<char> spot);
		 int makeNode(const chessB& b);
		 boardNode makeNode2(const chessB& b);
		 void spotMove(const std::pair<vector2<char>,vector2<char>>& move,chessB& board);
		 vector2<short> getP(const boardNode& board);
		 short traverseTree(int node,int turns,std::map<int,std::vector<std::vector<short> > >* visited);
		 short traverseTree2(const chessB& b,int turns,std::unordered_map<chessB,std::vector<std::vector<short> > >* visited);
		 std::pair<vector2<char>,vector2<char> > getThingy(const int& root);
		 std::pair<vector2<char>,vector2<char> > getThingy2(const chessB& c);
		 void getFullTree(const int& c);
		 vector2<short> getP2(const boardNode& board);
		 void treeThingy(int root);
		//static std::map<std::vector<std::vector<Cpiece> >,boardNode> thingy1;
		//static std::map<chessB,std::map<Cpiece,std::vector<vector2<int>> > > thingy1;
};
#endif

