#ifndef PLAYERMGR_H
#define PLAYERMGR_H

#include <map>

class Player;
class PlayerMgr
{
public:
    ~PlayerMgr();

	void AddPlayer(int socket, const std::string& account, const std::string& password);
	void RemovePlayer(int socket);

	Player* GetPlayer(int socket);
	Player* GetPlayer(const std::string& account);

private:
	std::map<int, Player*> players_;
	std::map <std::string, int> accounts_;
};

#endif