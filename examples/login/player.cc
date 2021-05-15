#include "player.h"

Player::Player(int socket, const std::string& account, const std::string& password)
    : socket_(socket),
    account_(account),
    password_(password)
{

}