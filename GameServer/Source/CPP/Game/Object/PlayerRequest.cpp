#include <Game\Object\Player.h>
#include <WorldSession.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>

bool Player::LoadFromDB(CHARACTERID id)
{
	charid = id;

	// create and load guild
	//if (sDB.getInt("GuildID") != 0)
		//GuildName = "";
	return true;
}
