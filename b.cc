#include "chessAI.h"
#include <iostream>
#include <deque>
//std::unique_ptr<std::unordered_map<chessB,std::unordered_map<Cpiece,std::vector<vector2<char>> > > > chessAI::thingy1 = std::unique_ptr<std::unordered_map<chessB,std::unordered_map<Cpiece,std::vector<vector2<char>> > > >(new std::unordered_map<chessB,std::unordered_map<Cpiece,std::vector<vector2<char>> > >);
//std::unordered_map<boardNode,int>* chessAI::dp;
//std::map<chessB,std::map<Cpiece,std::vector<vector2<char>> > > chessAI::thingy1;
//std::map<chessB,std::map<int,int> > chessAI::abc;
#define TURNSY 4
#define TEST_START std::cout<<"b"<<std::endl;
#define TEST_END std::cout<<"a"<<std::endl;
int chessAI::done = 0;
std::unordered_map<chessB,boardNode> chessAI::thingy1;
//std::unordered_map<boardNode,int> chessAI::thingy2;
std::unordered_map<boardNode,int> chessAI::dp;
std::unordered_map<int,boardNode> chessAI::dp2;
//std::unordered_map<boardNode,int> chessAI::dp3;
//std::unordered_map<int,boardNode> chessAI::dp4;
int chessAI::numNodes = 0;
//static std::unordered_map<chessB,boardNode> thingy1;
std::vector<vector2<char>> getMoveSpots(const chessB& b,const Cpiece& p,vector2<char> spot){
	std::vector<vector2<char> > moveSpots;
	if(p.n == pieceName::NONE){return moveSpots;}
	else if(p.n==pieceName::PAWN){
		if(p.c==pieceColor::BLACK){
			for(int x = 1;x<(spot.y==1?3:2);++x){
				if(b.b[spot.x][spot.y+x].c==pieceColor::NONE)
					moveSpots.emplace_back(spot.x,spot.y+x);
				else break;
			}
			if(spot.x!=7)
				if(b.b[spot.x+1].at(spot.y+1).c==pieceColor::WHITE){
					moveSpots.emplace_back(spot.x+1,(spot.y+1));
					//board.board[spot.x+1].at(spot.y+1).k[this] = something();
				}
			if(spot.x!=0)
				if(b.b[spot.x-1].at(spot.y+1).c==pieceColor::WHITE){
					moveSpots.emplace_back(spot.x-1,spot.y+1);
					//board.board[spot.x-1].at(spot.y+1).k[this] = something();
				}
		}
		else {
			for(int x = 1;x<(spot.y==6?3:2);++x){
				if(b.b[spot.x][spot.y-x].c==pieceColor::NONE)
					moveSpots.emplace_back(spot.x,spot.y-x);
				else break;
			}
			if(spot.x!=7)
				if(b.b[spot.x+1][spot.y-1].c==pieceColor::BLACK){
					moveSpots.emplace_back(spot.x+1,spot.y-1);
					//board.board[spot.x+1].at(spot.y-1).k[this] = something();
				}
			if(spot.x!=0)
				if(b.b[spot.x-1][spot.y-1].c==pieceColor::BLACK){
					moveSpots.emplace_back(spot.x-1,spot.y-1);
					//board.board[spot.x-1].at(spot.y-1).k[this] = something();
				}
		}
	}//else if(p.n==pieceName::BISHOP){}
	else if(p.n==pieceName::ROOK){
		for(int x = spot.x+1;x<8;++x){
			if(b.b[x][spot.y].c==pieceColor::NONE)
				//moveableSpots[x][spot.y]=1;
				moveSpots.emplace_back(x,spot.y);
			else if(b.b[x][spot.y].c==p.c){
				break;
			}else{
				moveSpots.emplace_back(x,spot.y);
				break;
			}
		}
		for(int x = spot.x-1;x>=0;--x){
			if(b.b[x][spot.y].c==pieceColor::NONE)
				moveSpots.emplace_back(x,spot.y);
			else if(b.b[x][spot.y].c==p.c){
				break;
			}else{
				moveSpots.emplace_back(x,spot.y);
				break;
			}
		}
		for(int y = spot.y+1;y<8;++y){
			if(b.b[spot.x][y].c==pieceColor::NONE)
				moveSpots.emplace_back(spot.x,y);
			else if(b.b[spot.x][y].c==p.c){
				break;
			}else{
				moveSpots.emplace_back(spot.x,y);
				break;
			}
		}
		for(int y = spot.y-1;y>=0;--y){
			if(b.b[spot.x][y].c==pieceColor::NONE)
				moveSpots.emplace_back(spot.x,y);
			else if(b.b[spot.x][y].c==p.c){
				break;
			}else{
				moveSpots.emplace_back(spot.x,y);
				break;
			}
		}
	}
	else if(p.n==pieceName::HORSE){
		if(spot.x<7&&spot.y>1&&b.b[spot.x+1][spot.y-2].c!=p.c)moveSpots.emplace_back(spot.x+1,spot.y-2);
		if(spot.x<7&&spot.y<6&&b.b[spot.x+1][spot.y+2].c!=p.c)moveSpots.emplace_back(spot.x+1,spot.y+2);

		if(spot.x>0&&spot.y>1&&b.b[spot.x-1][spot.y-2].c!=p.c)moveSpots.emplace_back(spot.x-1,spot.y-2);
		if(spot.x>0&&spot.y<6&&b.b[spot.x-1][spot.y+2].c!=p.c)moveSpots.emplace_back(spot.x-1,spot.y+2);

		if(spot.x<6&&spot.y>0&&b.b[spot.x+2][spot.y-1].c!=p.c)moveSpots.emplace_back(spot.x+2,spot.y-1);
		if(spot.x<6&&spot.y<7&&b.b[spot.x+2][spot.y+1].c!=p.c)moveSpots.emplace_back(spot.x+2,spot.y+1);

		if(spot.x>1&&spot.y>0&&b.b[spot.x-2][spot.y-1].c!=p.c)moveSpots.emplace_back(spot.x-2,spot.y-1);
		if(spot.x>1&&spot.y<7&&b.b[spot.x-2][spot.y+1].c!=p.c)moveSpots.emplace_back(spot.x-2,spot.y+1);
	}
	else if(p.n==pieceName::BISHOP){
		//+x +y
		for(int c = 1;c+spot.x<8&&c+spot.y<8;++c){
			if(b.b[c+spot.x][c+spot.y].c==pieceColor::NONE){
				moveSpots.emplace_back(c+spot.x,c+spot.y);
				continue;
			}
			if(b.b[c+spot.x][c+spot.y].c==p.c)
				break;
			if(b.b[c+spot.x][c+spot.y].c!=p.c){
				moveSpots.emplace_back(c+spot.x,c+spot.y);
				break;
			}
		}
		//-x -y
		for(int c = 1;spot.x-c>=0&&spot.y-c>=0;++c){
			if(b.b[spot.x-c][spot.y-c].c==pieceColor::NONE){
				moveSpots.emplace_back(spot.x-c,spot.y-c);
				continue;
			}
			if(b.b[spot.x-c][spot.y-c].c==p.c)
				break;
			if(b.b[spot.x-c][spot.y-c].c!=p.c){
				moveSpots.emplace_back(spot.x-c,spot.y-c);
				break;
			}
		}
		//+x -y
		for(int c = 1;spot.x+c<8&&spot.y-c>=0;++c){
			if(b.b[spot.x+c][spot.y-c].c==pieceColor::NONE){
				moveSpots.emplace_back(spot.x+c,spot.y-c);
				continue;
			}
			if(b.b[spot.x+c][spot.y-c].c==p.c)
				break;
			if(b.b[spot.x+c][spot.y-c].c!=p.c){
				moveSpots.emplace_back(spot.x+c,spot.y-c);
				break;
			}
		}
		//-x +y
		for(int c = 1;spot.x-c>=0&&spot.y+c<8;++c){
			if(b.b[spot.x-c][spot.y+c].c==pieceColor::NONE){
				moveSpots.emplace_back(spot.x-c,spot.y+c);
				continue;
			}
			if(b.b[spot.x-c][spot.y+c].c==p.c)
				break;
			if(b.b[spot.x-c][spot.y+c].c!=p.c){
				moveSpots.emplace_back(spot.x-c,spot.y+c);
				break;
			}
		}
	}//4,0
	else if(p.n==pieceName::QUEEN){
		for(int c = 1;c+spot.x<8&&c+spot.y<8;++c){
			if(b.b[c+spot.x][c+spot.y].c==pieceColor::NONE){
				moveSpots.emplace_back(c+spot.x,c+spot.y);
				continue;
			}
			if(b.b[c+spot.x][c+spot.y].c==p.c)
				break;
			if(b.b[c+spot.x][c+spot.y].c!=p.c){
				moveSpots.emplace_back(c+spot.x,c+spot.y);
				break;
			}
		}
		//-x -y
		for(int c = 1;spot.x-c>=0&&spot.y-c>=0;++c){
			if(b.b[spot.x-c][spot.y-c].c==pieceColor::NONE){
				moveSpots.emplace_back(spot.x-c,spot.y-c);
				continue;
			}
			if(b.b[spot.x-c][spot.y-c].c==p.c)
				break;
			if(b.b[spot.x-c][spot.y-c].c!=p.c){
				moveSpots.emplace_back(spot.x-c,spot.y-c);
				break;
			}
		}
		//+x -y
		for(int c = 1;spot.x+c<8&&spot.y-c>=0;++c){
			if(b.b[spot.x+c][spot.y-c].c==pieceColor::NONE){
				moveSpots.emplace_back(spot.x+c,spot.y-c);
				continue;
			}
			if(b.b[spot.x+c][spot.y-c].c==p.c)
				break;
			if(b.b[spot.x+c][spot.y-c].c!=p.c){
				moveSpots.emplace_back(spot.x+c,spot.y-c);
				break;
			}
		}
		//-x +y
		for(int c = 1;spot.x-c>=0&&spot.y+c<8;++c){
			if(b.b[spot.x-c][spot.y+c].c==pieceColor::NONE){
				moveSpots.emplace_back(spot.x-c,spot.y+c);
				continue;
			}
			if(b.b[spot.x-c][spot.y+c].c==p.c)
				break;
			if(b.b[spot.x-c][spot.y+c].c!=p.c){
				moveSpots.emplace_back(spot.x-c,spot.y+c);
				break;
			}
		}
		//rook part
		for(int x = spot.x+1;x<8;++x){
			if(b.b[x][spot.y].c==pieceColor::NONE)
				//moveableSpots[x][spot.y]=1;
				moveSpots.emplace_back(x,spot.y);
			else if(b.b[x][spot.y].c==p.c){
				break;
			}else{
				moveSpots.emplace_back(x,spot.y);
				break;
			}
		}
		for(int x = spot.x-1;x>=0;--x){
			if(b.b[x][spot.y].c==pieceColor::NONE)
				moveSpots.emplace_back(x,spot.y);
			else if(b.b[x][spot.y].c==p.c){
				break;
			}else{
				moveSpots.emplace_back(x,spot.y);
				break;
			}
		}
		for(int y = spot.y+1;y<8;++y){
			if(b.b[spot.x][y].c==pieceColor::NONE)
				moveSpots.emplace_back(spot.x,y);
			else if(b.b[spot.x][y].c==p.c){
				break;
			}else{
				moveSpots.emplace_back(spot.x,y);
				break;
			}
		}
		for(int y = spot.y-1;y>=0;--y){
			if(b.b[spot.x][y].c==pieceColor::NONE)
				moveSpots.emplace_back(spot.x,y);
			else if(b.b[spot.x][y].c==p.c){
				break;
			}else{
				moveSpots.emplace_back(spot.x,y);
				break;
			}
		}
	}
	else if(p.n==pieceName::KING){
		if(spot.x!=7){
			if(spot.y!=7)
				moveSpots.emplace_back(spot.x+1,spot.y+1);
			moveSpots.emplace_back(spot.x+1,spot.y  );
			if(spot.y!=0)
				moveSpots.emplace_back(spot.x+1,spot.y-1);
		}
		if(spot.x!=0){
			if(spot.y!=7)
				moveSpots.emplace_back(spot.x-1,spot.y+1);
			moveSpots.emplace_back(spot.x-1,spot.y+0);
			if(spot.y!=0)
				moveSpots.emplace_back(spot.x-1,spot.y-1);
		}if(spot.y!=7)
			moveSpots.emplace_back(spot.x  ,spot.y+1);
		if(spot.y!=0)
			moveSpots.emplace_back(spot.x  ,spot.y-1);
	}
	//chessAI::thingy1[b][p] = moveSpots;
	return moveSpots;
}

boardNode makeNode(const chessB& b){
	if(chessAI::thingy1.find(b)!=chessAI::thingy1.end())
		return chessAI::thingy1[b];
	boardNode re;
	//std::pair<std::vector<std::pair<vector2<char>,vector2<char>> >,std::vector<std::pair<vector2<char>,vector2<char>> > >n;
	std::array<std::vector<std::pair<vector2<char>,vector2<char>> >,2> n;
	for(int x = 0;x<8;++x){
		for(int y = 0;y<8;++y){
			if(b.b[x][y].n == pieceName::NONE) continue;
			std::vector<vector2<char>> o = getMoveSpots(b,b.b[x][y],vector2<char>(x,y));
			if(b.b[x][y].c==pieceColor::BLACK){
				n[0].resize(n[0].size()+o.size());
				for(unsigned m = n[0].size()-o.size();m<n[0].size();++m){
					n[0][m]=(std::pair<vector2<char>,vector2<char>>(vector2<char>(x,y),o[m-n[0].size()+o.size()]));
				}
			}else if(b.b[x][y].c==pieceColor::WHITE){
				n[1].resize(n[1].size()+o.size());
				for(unsigned m = n[1].size()-o.size();m<n[1].size();++m)
					n[1][m]=(std::pair<vector2<char>,vector2<char>>(vector2<char>(x,y),o[m-n[1].size()+o.size()]));

			}
		}
	}
	re.moveSpots=n;
	re.board = b;
	chessAI::thingy1[b]=re;
    chessAI::dp[re]=chessAI::numNodes;
	chessAI::dp2[chessAI::numNodes]=re;
	++chessAI::numNodes;
	return re;
}
void spotMove(const std::pair<vector2<char>,vector2<char>>& move,chessB& board){
	//std::cout<<move.second.x<<" "<<move.second.y<<std::endl<<move.first.x<<" "<<move.first.y<<std::endl;
	board.b[(int)move.second.x][(int)move.second.y] = std::move(board.b[(int)move.first.x][(int)move.first.y]);
	board.b[(int)move.first.x][(int)move.first.y] = Cpiece(pieceName::NONE,pieceColor::NONE);
	if(board.b[move.second.x][move.second.y].n==pieceName::PAWN&& move.second.y == (board.b[move.second.x][move.second.y].c==pieceColor::BLACK?7:0))
        board.b[move.second.x][move.second.y].n = pieceName::QUEEN;


}
int getPdiff(const vector2<int>& i){
	return i.x-i.y;
}
int getPieceValue(pieceName p){
	if(p==pieceName::PAWN) return 2;
	if(p==pieceName::BISHOP) return 10;
	if(p==pieceName::HORSE) return 11;
	if(p==pieceName::ROOK) return 20;
	if(p==pieceName::QUEEN) return 50;
	if(p==pieceName::KING) return 1000000;
	return 0;
}
vector2<int> getP(const chessB& board){//can be made better
	static std::unordered_map<chessB,vector2<int>> cache;
	if(cache.find(board)!=cache.end()) return cache[board];
	vector2<int> p(0,0);
	for(int x = 0;x<8;++x){
		for(int y = 0;y<8;++y){
			if(board.b[x][y].n==pieceName::NONE) continue;
			else if(board.b[x][y].c==pieceColor::BLACK){
				p.x+= getPieceValue(board.b[x][y].n);//((std::map<pieceName,int>){{pieceName::KING,1000000},{pieceName::QUEEN,50},{pieceName::ROOK,20},{pieceName::BISHOP,10},{pieceName::HORSE,11},{pieceName::PAWN,2}})[board.b[x][y].n];
			}else p.y+=	getPieceValue(board.b[x][y].n);//((std::map<pieceName,int>){{pieceName::KING,1000000},{pieceName::QUEEN,50},{pieceName::ROOK,20},{pieceName::BISHOP,10},{pieceName::HORSE,11},{pieceName::PAWN,2}})[board.b[x][y].n];
		}
	}cache[board]=p;
	return p;
}
int traverseTree(int node,int turns,std::map<int,std::vector<std::vector<int> > >* visited){//inefficient
	/*
	if(visited->find(node)!=visited->end()){
		const std::vector<int> vals = (*visited)[node][turns];
		if(vals[0]!=100000000){
			if(turns%2==1) return vecMin(vals);
			return vecMax(vals);
		}
	}//more effieient now*/
	auto nodey = &chessAI::dp2[node];
	std::vector<int> vals(nodey->edges[turns%2].size());
	//std::cout<<vals.size()<<std::endl;
	if(!vals.size()|| turns==TURNSY){
		return getPdiff(getP(nodey->board));
	}
	for(unsigned x= 0;x<vals.size();++x){
		//std::cout<<"before"<<std::endl;
		vals[x] = traverseTree(nodey->edges[turns%2][x],turns+1,visited);//getPdiff(getP(chessAI::dp[nodey->edges[x]]));
		//std::cout<<"after"<<std::endl;
	}
	/*
	if(!((*visited)[node].size()))
		(*visited)[node].resize(TURNSY+1,{100000000});
	for(int i = turns;i<TURNSY+1;++i)(*visited)[node][turns]= vals;*/
	//return 2;board.b[move.second.x][move.second.y].n
	if(turns%2==1) return vecMin(vals);
	return vecMax(vals);
}
void abc(const std::vector<int>* o,std::vector<int>* k,int start,int end,std::map<int,std::vector<std::vector<int> > >* visited){
	for(int x = start;x<end;++x){
		(*k)[x]=traverseTree((*o)[x],1,visited);
	}
}
std::pair<vector2<char>,vector2<char> > getThingy(const boardNode& c){
	int root = chessAI::dp[c];
	std::vector<int> q(1,root);
	const auto lol = chessAI::dp2[root];

	int a = lol.edges[0].size();
	int threads = 0;
	std::vector<int> vecs(a);
	std::vector<std::thread> workk;
	int t = 0;
	std::map<int,std::vector<std::vector<int> > > visited;
	for(int x = 0;x<threads;++x){
		workk.emplace_back(abc,&lol.edges[0],&vecs,t,t+(a/(threads+1)),&visited);
		t+=(a/(threads+1));
	}
	for(unsigned x = t;x<lol.edges[0].size();++x){
		vecs[x]=traverseTree(lol.edges[0][x],1,&visited);
	}
	for(int i = 0;i<threads;++i){
		workk[i].join();
	}
	if(!a) return std::pair<vector2<char>,vector2<char>>(vector2<char>(0,0),vector2<char>(0,0));
	int highestIndex = 1;

	for(int x = 1;x<a;++x){
		if(vecs[x]>=vecs[highestIndex])
			highestIndex=x;
	}return lol.moveSpots[0][highestIndex];
}

void getFullTree(const boardNode& c){
	std::array<std::unordered_map<int,char>,2> levels;
	char level = 0;
	std::vector<int> que(1,chessAI::dp[c]);
	levels[0][chessAI::dp[c]]=0;
	while(que.size()&& level<(TURNSY)){
		std::vector<int> next;
		for(auto& currenta:que){
            //std::cout<<"abc"<<std::endl;
            auto current = &chessAI::dp2[currenta];
			auto qwe = getP(current->board);
			if(qwe.x+qwe.y<1200000){
				current->moveSpots[0].clear();
				current->moveSpots[1].clear();
			}//for(int i = 0;i<2;++i){
			char i = level%2;
				for(auto& x:current->moveSpots[i]){
					chessB k = current->board;
					spotMove(x,k);
					//auto newNode = makeNode(k);
					int newNodeSpot = chessAI::dp[makeNode(k)];
					if(levels[i].find(newNodeSpot)==levels[i].end()){
						levels[i][newNodeSpot] = level;
						next.push_back(newNodeSpot);
					}
				}
			//}//fix #1,generate only nessaccary boards,should not be 60 moves
		}++level;
		que = std::move(next);
		std::cout<<que.size()<<std::endl;
		std::cout<<"next level"<<std::endl;
	}
}
void treeThingy(int root){
	int level =0;
	std::array<std::map<int,int>,2> levels;
	std::vector<int> que(1,root);
	while(que.size()&&level <(TURNSY)){
		std::vector<int> next;
		for(auto& m:que){
			auto current = &chessAI::dp2[m];
			//for(int c = 0;c<2;++c){
			int c = level%2;
				if(current->edges[c].size()==current->moveSpots[c].size()) continue;
				current->edges[c].resize(current->moveSpots[c].size());
				for(unsigned i = 0;i<current->moveSpots[c].size();++i){
					chessB k = current->board;
					spotMove(current->moveSpots[c][i],k);
					auto newNode = makeNode(k);
					current->edges[c][i] = chessAI::dp[newNode];
					int l = chessAI::dp[newNode];
					if(levels[c].find(l)==levels[c].end()){
						levels[c][l] = level;
						next.push_back(l);
					}
				}
			//}
			//chessAI::dp3[*current] = chessAI::dp[*current];
		}++level;
		que = next;
		std::cout<<que.size()<<std::endl;
	}
}
void chessAI::run(const chessB b,std::pair<vector2<char>,vector2<char>>* toDoMove){
    //std::cout<<chessAI::dp2.size()<<std::endl;
	boardNode c = makeNode(b);
	//std::cout<<chessAI::dp2.size()<<std::endl;
	//do bfs
	//redo with dfs instead
	//nvm dont redo with dfs
	//i'll just do bfs twice
	//:(
	getFullTree(c);
	treeThingy(chessAI::dp[c]);
	//now have bottom of tree
	*toDoMove = getThingy(c);

	chessAI::done = 1;

	std::cout<<"abc"<<std::endl;
}



