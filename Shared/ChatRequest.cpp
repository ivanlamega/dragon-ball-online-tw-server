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

BYTE MySQLConnWrapper::GetFriendList(CHARACTERID charID, sFRIEND_FULL_INFO * friends)
{
	sql::ResultSet* result = sDB.executes("SELECT friendlist.CharID, characters.Name, friendlist.IsBlack from friendlist JOIN characters on characters.CharacterID = friendlist.CharID WHERE friendlist.OwnerID = %d", charID);
	if (result == NULL)
		return 0;
	if (result->rowsCount() <= 0)
	{
		delete result;
		return 0;
	}

	BYTE byCount = result->rowsCount();

	for (int i = 0; i < byCount; i++)
	{

		wcscpy_s(friends[i].wchName, MAX_SIZE_CHAR_NAME_UNICODE + 1, charToWChar(result->getString("Name").c_str()));
		friends[i].charID = result->getInt("CharID");
		friends[i].bIsBlack = result->getBoolean("IsBlack");

		result->next();

		sLog.outDebug("Getting friends information for: %d", charID);
	}

	delete result;
	return byCount;
}