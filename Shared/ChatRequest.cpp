#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <Packet/Char/PacketCU.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <list>

unsigned int MySQLConnWrapper::GetFriendIdByName(std::string charName)
{
	sql::ResultSet* result = sDB.executes("SELECT CharacterID FROM characters WHERE Name = '%s'", charName.c_str());
	if (result == NULL)
		return -1;
	if (result->rowsCount() == 0)
	{
		delete result;
		return -1;
	}

	return result->getInt("CharacterID");
}

void MySQLConnWrapper::AddFriendToList(CHARACTERID ownerId, CHARACTERID friendId)
{
	sql::ResultSet* result = sDB.executes("insert into friendlist (ownerid, charid) select %d, %d from dual where not exists (select * from friendlist where OwnerID = %d and charid = %d) limit 1",
		ownerId, friendId, ownerId, friendId);
	if (result != NULL)
		delete result;
}