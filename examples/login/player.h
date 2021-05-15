#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
public:
    Player(int socket, const std::string &account, const std::string &password);

    const std::string &GetAccount() const { return account_; }
    void SetAccount(const std::string &account) { account_ = account; }

    const std::string &GetPassword() const { return password_; }
    void SetPassword(const std::string &password) { password_ = password; }

    int GetSocket() const { return socket_; }

private:
    int socket_;
    std::string account_;
    std::string password_;
};

#endif