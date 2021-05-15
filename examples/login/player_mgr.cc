#include "player_mgr.h"
#include "player.h"

PlayerMgr::~PlayerMgr()
{
    auto it = players_.begin();
    while (it != players_.end())
    {
        delete it->second;
        it++;
    }

    players_.clear();
    accounts_.clear();
}

void PlayerMgr::AddPlayer(int socket, const std::string &account, const std::string &password)
{
    auto it = players_.find(socket);
    if (it != players_.end())
    {
        return;
    }

    players_[socket] = new Player(socket, account, password);
    accounts_[account] = socket;
}

void PlayerMgr::RemovePlayer(int socket)
{
    auto it = players_.find(socket);
    if (it != players_.end())
        return;

    Player *player = it->second;

    accounts_.erase(player->GetAccount());
    players_.erase(socket);
}

Player *PlayerMgr::GetPlayer(int socket)
{
    auto it = players_.find(socket);
    if (it == players_.end())
        return nullptr;

    return it->second;
}

Player *PlayerMgr::GetPlayer(const std::string &account)
{
    auto it = accounts_.find(account);
    if (it == accounts_.end())
        return nullptr;

    return players_[it->second];
}