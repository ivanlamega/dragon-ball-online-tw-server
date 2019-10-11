#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser.h>


//----------------------------------------
//	Start the mail session
//----------------------------------------

void Player::StartMail(Packet pPacket)
{
	sUG_MAIL_START_REQ* req = (sUG_MAIL_START_REQ*)pPacket.GetPacketBuffer();
	sGU_MAIL_START_RES sMail;

	sMail.wOpCode = GU_MAIL_START_RES;
	sMail.wPacketSize = sizeof(sGU_MAIL_START_RES) - 2;
	sMail.hObject = req->hObject; // If Wearing a scouter this will return INVALID_TBLIDX
	sMail.bIsAway = this->CheckMailAwayStatus(); // Make sure that the character isn't away
	
	if (sMail.bIsAway == true)
	{
		sMail.wResultCode = GAME_MAIL_TARGET_AWAY_STATE;
	}
	else
	{
		sMail.wResultCode = GAME_SUCCESS;
	}
	SendPacket((char*)&sMail, sizeof(sGU_MAIL_START_RES));
}

//----------------------------------------
//	Load All the mail
//----------------------------------------
void Player::LoadMail(Packet pPacket)
{
	sUG_MAIL_LOAD_REQ* req = (sUG_MAIL_LOAD_REQ*)pPacket.GetPacketBuffer();
	//Get the mail	

	sql::ResultSet* result = sDB.executes("SELECT * FROM mail WHERE CharacterID = %d", this->GetCharacterID());
	if (result == NULL)
		return;
	if (result && result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
	if (result && result->rowsCount() >= 0)
	{
		//For all mail in the result set, send MailLoadData
		while (true)
		{
			sGU_MAIL_LOAD_INFO sMailData;
			sMailData.wOpCode = GU_MAIL_LOAD_INFO;
			sMailData.wPacketSize = sizeof(sGU_MAIL_LOAD_INFO) - 2;
			sMailData.sData.bIsAccept = result->getBoolean("bIsAccept");
			sMailData.sData.bIsLock = result->getBoolean("bIsLock");
			sMailData.sData.bIsRead = result->getBoolean("bIsRead");
			sMailData.sData.bySenderType = result->getInt("SenderType"); //eMAIL_SENDER_TYPE::eMAIL_SENDER_TYPE_GM;
			sMailData.sData.byMailType = result->getInt("byMailType");eMAIL_TYPE::eMAIL_TYPE_ITEM;
			wcscpy_s(sMailData.wszText, 128, s2ws(result->getString("wszText")).c_str());
			wcscpy_s(sMailData.sData.wszFromName, 16, s2ws(result->getString("wszFromName")).c_str());
			sMailData.byTextSize = result->getInt("byTextSize");
			sMailData.sData.dwZenny = result->getInt("dwZenny");
			sMailData.byTextSize = result->getInt("byTextSize");
			sMailData.sData.endTime = result->getInt("byDay");
			sMailData.sData.mailID = result->getInt("id");
			sMailData.sData.sItemProfile.handle = sWorld.AcquireItemSerialId();
			sMailData.sData.sItemProfile.tblidx = result->getInt("item_id");
			sMailData.sData.sItemProfile.byPlace = result->getInt("item_place");
			sMailData.sData.sItemProfile.byPos = result->getInt("item_pos");
			sMailData.sData.sItemProfile.byStackcount = 1;//result->getInt("StackCount");
			sMailData.sData.sItemProfile.byRank = 1;
			sMailData.sData.sItemProfile.byCurDur = 100;
			sMailData.sData.sItemProfile.bNeedToIdentify = false;
			sMailData.sData.sItemProfile.byGrade = 0;
			sMailData.sData.sItemProfile.byBattleAttribute = eBATTLE_ATTRIBUTE::BATTLE_ATTRIBUTE_NONE;
			sMailData.sData.sItemProfile.byRestrictType = eITEM_RESTRICT_TYPE::ITEM_RESTRICT_TYPE_NONE;
			sMailData.sData.sItemProfile.aOptionTblidx = result->getInt("item_id");
			sMailData.sData.sItemProfile.aOptionTblidx1 = INVALID_TBLIDX;
			for (int i = 0; i <= 6; i++)
			{
				sMailData.sData.sItemProfile.aitemEffect[i].wType = INVALID_TBLIDX;
				sMailData.sData.sItemProfile.aitemEffect[i].dwValue = INVALID_TBLIDX;
			}
			for (int i = 0; i <= 2; i++)
			{
				sMailData.sData.sItemProfile.aitemExtraEffect[i].wType = INVALID_TBLIDX;
				sMailData.sData.sItemProfile.aitemExtraEffect[i].dwValue = INVALID_TBLIDX;
			}
			sMailData.sData.sItemProfile.byDurationType = eDURATIONTYPE::eDURATIONTYPE_NORMAL;

			SendPacket((char*)&sMailData, sizeof(sGU_MAIL_LOAD_INFO));
			if (result->next())
				continue;
			else
				break;
		}
		
		delete result;
		return;
	}

	sGU_MAIL_LOAD_RES res;
	res.hObject = req->hObject;
	res.wOpCode = GU_MAIL_LOAD_RES;
	res.wPacketSize = sizeof(sGU_MAIL_LOAD_RES) - 2;
	res.wResultCode = GAME_SUCCESS;
	SendPacket((char*)&res, sizeof(sGU_MAIL_START_RES));
	
}

//----------------------------------------
//	Check if mail is Away
//----------------------------------------
bool Player::CheckMailAwayStatus()
{
	if (sDB.CheckIfMailAway(this->GetCharacterID()))
		return true;
	else 
		return false;
		
}

//----------------------------------------
//	Send mail
//----------------------------------------
void Player::SendMail(Packet pPacket)
{
	sUG_MAIL_SEND_REQ * req = (sUG_MAIL_SEND_REQ*)pPacket.GetPacketBuffer();

	sGU_MAIL_SEND_RES sMailData;
	sMailData.wOpCode = GU_MAIL_LOAD_DATA;
	sMailData.wPacketSize = sizeof(sGU_MAIL_SEND_RES) - 2;
	
	char targetname[16];
	wcstombs(targetname, req->wszTargetName, 16);
	char PlayerName[16];
	wcstombs(PlayerName, GetPcProfile()->awchName, 16);
	char *text = new char[req->byTextSize];
	wcstombs(text, req->wszText, req->byTextSize);
	text[req->byTextSize] = '\0';
	
	sql::ResultSet* result = sDB.executes("SELECT * FROM characters WHERE Name = '%s';", targetname);
	if (result == NULL)
		return;
	if (result && result->rowsCount() <= 0)
	{				
		//printf(" Char Name not Valid \n");
		sMailData.wOpCode = GU_MAIL_SEND_RES;
		sMailData.hObject = req->hObject;
		sMailData.wResultCode = GAME_MAIL_NOT_EXISTING_PLAYER;
		SendPacket((char*)&sMailData, sizeof(sGU_MAIL_SEND_RES));
		delete result;
		return;
	}
	if (targetname == this->GetName())
	{
		//printf(" cant send mail to Yourself \n");
		sMailData.wOpCode = GU_MAIL_SEND_RES;
		sMailData.hObject = req->hObject;
		sMailData.wResultCode = GAME_MAIL_CANT_SEND_MAIL_TO_YOURSELF;
		SendPacket((char*)&sMailData, sizeof(sGU_MAIL_SEND_RES));
		delete result;
		return;

	}
		int id = result->getInt("CharacterID");		
		//printf("%d \n", id);
		wcscpy_s(sMailData.wszTargetName, 16, req->wszTargetName);
		sMailData.wOpCode = GU_MAIL_SEND_RES;
		sMailData.hObject = req->hObject;
		bool isAway = result->getBoolean("MailIsAway");
		if (isAway == 1)
		{
			//printf(" GAME_MAIL_TARGET_AWAY_STATE");
			sMailData.wResultCode = GAME_MAIL_TARGET_AWAY_STATE;
		}
		else
		{
			if (req->byMailType == eMAIL_TYPE::eMAIL_TYPE_BASIC)
			{
				//printf(" GAME_SUCCESS \n");
				sMailData.wResultCode = GAME_SUCCESS;			
				sDB.AddMail(id, req->byDay, req->byMailType, req->byTextSize, text,targetname, PlayerName, 0, 0, 0);
			}	
			if (req->byMailType == eMAIL_TYPE::eMAIL_TYPE_ITEM)
			{
				//printf(" GAME_SUCCESS \n");
				sMailData.wResultCode = GAME_COMMON_CANT_DO_THAT_FOR_SOME_REASON;
				//sDB.AddMail(id, req->byDay, req->byMailType, req->byTextSize, text, targetname, PlayerName, 0, 0, 0);
			}
			if (req->byMailType == eMAIL_TYPE::eMAIL_TYPE_ZENNY)
			{
				//printf(" GAME_SUCCESS \n");
				sMailData.wResultCode = GAME_COMMON_CANT_DO_THAT_FOR_SOME_REASON;
				//sDB.AddMail(id, req->byDay, req->byMailType, req->byTextSize, text, targetname, PlayerName, 0, 0, 0);
			}
			if (req->byMailType == eMAIL_TYPE::eMAIL_TYPE_ITEM_ZENNY)
			{
				//printf(" GAME_SUCCESS \n");
				sMailData.wResultCode = GAME_COMMON_CANT_DO_THAT_FOR_SOME_REASON;
				//sDB.AddMail(id, req->byDay, req->byMailType, req->byTextSize, text, targetname, PlayerName, 0, 0, 0);
			}
			if (req->byMailType == eMAIL_TYPE::eMAIL_TYPE_ITEM_ZENNY_REQ)
			{
				//printf(" GAME_SUCCESS \n");
				sMailData.wResultCode = GAME_COMMON_CANT_DO_THAT_FOR_SOME_REASON;
				//sDB.AddMail(id, req->byDay, req->byMailType, req->byTextSize, text, targetname, PlayerName, 0, 0, 0);
			}
			if (req->byMailType == eMAIL_TYPE::eMAIL_TYPE_ZENNY_REQ)
			{
				//printf(" GAME_SUCCESS \n");
				sMailData.wResultCode = GAME_COMMON_CANT_DO_THAT_FOR_SOME_REASON;
				//sDB.AddMail(id, req->byDay, req->byMailType, req->byTextSize, text, targetname, PlayerName, 0, 0, 0);
			}
		}		
		//printf(" Packet enviado \n");
		SendPacket((char*)&sMailData, sizeof(sGU_MAIL_SEND_RES));
		delete result;
		return;

}
//----------------------------------------
//	Read mail
//----------------------------------------
void Player::ReadMail(Packet pPacket)
{
	sUG_MAIL_READ_REQ * req = (sUG_MAIL_READ_REQ*)pPacket.GetPacketBuffer();


	sGU_MAIL_READ_RES  res;
	res.wOpCode = GU_MAIL_READ_RES;
	res.wPacketSize = sizeof(sGU_MAIL_READ_RES) - 2;
	res.wResultCode = GAME_SUCCESS;
	res.hObject = req->hObject;
	res.mailID = req->mailID;
	res.byRemainDay = 0;
	res.endTime = 0;

	SendPacket((char*)&res, sizeof(sGU_MAIL_READ_RES));
	
	
}
//----------------------------------------
//	Delet mail
//----------------------------------------
void Player::DeletMail(Packet pPacket)
{
	sUG_MAIL_DEL_REQ * req = (sUG_MAIL_DEL_REQ*)pPacket.GetPacketBuffer();


	sGU_MAIL_DEL_RES  res;
	res.wOpCode = GU_MAIL_DEL_RES;
	res.wPacketSize = sizeof(sGU_MAIL_DEL_RES) - 2;
	res.wResultCode = GAME_SUCCESS;
	res.mailID = req->mailID;
	res.hObject = req->hObject;

	// Remove in Data Base
	sDB.DelMail(res.mailID);
	SendPacket((char*)&res, sizeof(sGU_MAIL_DEL_RES));
}
//----------------------------------------
//	Reload mail
//----------------------------------------
void Player::ReloadMail(Packet pPacket)
{
	sUG_MAIL_RELOAD_REQ * req = (sUG_MAIL_RELOAD_REQ*)pPacket.GetPacketBuffer();
	sGU_MAIL_RELOAD_NFY  res;
	res.wOpCode = GU_MAIL_RELOAD_NFY;
	res.wPacketSize = sizeof(sGU_MAIL_RELOAD_NFY) - 2;
	//res.hObject = req->hObject;	
	//res.wResultCode = GAME_SUCCESS;
	sql::ResultSet* result = sDB.executes("SELECT * FROM mail WHERE CharacterID = %d", this->GetCharacterID());
	if (result == NULL)
		return;
	if (result && result->rowsCount() <= 0)
	{
		delete result;
		return;
	}
		res.byMailCount = result->rowsCount();
		res.byManagerCount = result->rowsCount();
		res.byNormalCount = result->rowsCount();
		int i = 0;
		while (true)
		{
			res.aMailID[i] = result->getInt("id");
			i++;
			if (result->next())
				continue;
			else
				break;
		}
		SendPacket((char*)&res, sizeof(sGU_MAIL_RELOAD_NFY));
		delete result;
		return;
		
}
//----------------------------------------
//	return mail
//----------------------------------------
void Player::ReturnMail(Packet pPacket)
{
}

//----------------------------------------
//	Send Bank Start
//----------------------------------------
void Player::SendBankStart(Packet pPacket)
{
	printf("START BANK \n");
	sUG_BANK_START_REQ * req = (sUG_BANK_START_REQ*)pPacket.GetPacketBuffer();

	
	sGU_BANK_START_RES  res;
	res.wOpCode = GU_BANK_START_RES;
	res.wPacketSize = sizeof(sGU_BANK_START_RES) - 2;	
	res.wResultCode = GAME_SUCCESS;
	res.handle = req->handle;
	
	SendPacket((char*)&res, sizeof(sGU_BANK_START_RES));

}
void Player::SendBankLoad(Packet pPacket)
{
	printf("Confirm Load BANK \n");
	sUG_BANK_LOAD_REQ * req = (sUG_BANK_LOAD_REQ*)pPacket.GetPacketBuffer();

	sGU_BANK_LOAD_RES  res;
	res.wOpCode = GU_BANK_LOAD_RES;
	res.wPacketSize = sizeof(sGU_BANK_LOAD_RES) - 2;
	res.wResultCode = GAME_SUCCESS;
	res.handle = req->handle;

	SendPacket((char*)&res, sizeof(sGU_BANK_LOAD_RES));

}
//----------------------------------------
//	Send bank load
//----------------------------------------
void Player::SendBankInfo(Packet pPacket)
{	
	sGU_BANK_ITEM_INFO	res;
	memset(&res, 0, sizeof(sGU_BANK_ITEM_INFO));

	res.wOpCode = GU_BANK_ITEM_INFO;

	int totalItem = inventoryManager.GetTotalItemsCount();
	int divide = 1;
	int sendCount = 0;

	res.byBeginCount = 0;
	res.byItemCount = 0;

	if (totalItem >= 31)
	{
		divide = 6;
	}
	else
		divide = 1;
	for (int totalLoop = 0; totalLoop < divide; totalLoop++)
	{
		for (int i = 0; i <= std::round(totalItem / divide); i++, sendCount++)
		{
			
				printf("Place %d \n", inventoryManager.GetInventory()[sendCount].byPlace);
				res.aBankProfile[i].handle = inventoryManager.GetInventory()[sendCount].handle;
				res.aBankProfile[i].tblidx = inventoryManager.GetInventory()[sendCount].tblidx;
				res.aBankProfile[i].byPlace = inventoryManager.GetInventory()[sendCount].byPlace;
				res.aBankProfile[i].byPos = inventoryManager.GetInventory()[sendCount].byPos;
				res.aBankProfile[i].byStackcount = inventoryManager.GetInventory()[sendCount].byStackcount;
				res.aBankProfile[i].byRank = inventoryManager.GetInventory()[sendCount].byRank;
				res.aBankProfile[i].byGrade = inventoryManager.GetInventory()[sendCount].byGrade;
				res.aBankProfile[i].byCurDur = inventoryManager.GetInventory()[sendCount].byCurDur;
				res.aBankProfile[i].byBattleAttribute = 0;
				res.aBankProfile[i].byRestrictType = inventoryManager.GetInventory()[sendCount].byRestrictType;
				res.aBankProfile[i].aOptionTblidx = inventoryManager.GetInventory()[sendCount].aOptionTblidx;
				for (int k = 0; k < 2; k++)
				{
					res.aBankProfile[i].aitemExtraEffect[k] = inventoryManager.GetInventory()[sendCount].aitemExtraEffect[k];
				}
				for (int k = 0; k < 6; k++)
				{
					res.aBankProfile[i].aitemEffect[k] = inventoryManager.GetInventory()[sendCount].aitemEffect[k];
				}
				for (int k = 0; k <= 16; k++)
					res.aBankProfile[i].awchMaker[k] = inventoryManager.GetInventory()[sendCount].awchMaker[k];
				res.byItemCount = i + 1;
						
		}
		res.byBeginCount = (sendCount - res.byItemCount);
		res.wPacketSize = (6 + (res.byItemCount * sizeof(sITEM_PROFILE)));
		SendPacket((char*)&res, sizeof(sGU_BANK_ITEM_INFO));
		if (inventoryManager.GetInventory()[sendCount].tblidx == INVALID_TBLIDX)
			break;
		cout << "Tamanho Packet" << endl;
		std::cout << sizeof(sGU_BANK_ITEM_INFO) << std::endl;
	}
}
//----------------------------------------
//	Send Bank End
//----------------------------------------
void Player::SendBankEnd(Packet pPacket)
{
	
	sGU_BANK_END_RES res;

	res.wOpCode = GU_BANK_END_RES;
	res.wPacketSize = sizeof(sGU_BANK_END_RES) - 2;
	res.wResultCode = GAME_SUCCESS;

	SendPacket((char*)&res, sizeof(sGU_BANK_END_RES));
}
