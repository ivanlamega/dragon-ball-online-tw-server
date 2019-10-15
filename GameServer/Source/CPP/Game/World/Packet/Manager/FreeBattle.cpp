#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Object\Player.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser.h>

void Player::CheckPVPArea()
{
	//printf("Plat Check \n");	
	if (GetVectorPosition().x <= 5792.100 && GetVectorPosition().x >= 5752.100
		&& GetVectorPosition().z >= 748.037 && GetVectorPosition().z <= 787.037 && GetAttributesManager()->IsinPVP == false)
	{
		//	printf("Plat in \n");
		sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY PVPZone;
		PVPZone.wOpCode = GU_WORLD_FREE_PVP_ZONE_ENTERED_NFY;
		PVPZone.wPacketSize = sizeof(sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY) - 2;
		PVPZone.Handle = GetHandle();
		SendPacket((char*)&PVPZone, sizeof(sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY));
		SendToPlayerList((char*)&PVPZone, sizeof(sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY));
		GetAttributesManager()->IsinPVP = true;
		mutexPlayer.lock();
		for (auto it = objList.begin(); it != objList.end();)
		{
			if (it->second != NULL)
			{
				if (it->second->GetTypeId() == OBJTYPE_PC)
				{
					Player* plr = static_cast<Player*>(it->second);
					if (plr->IsInWorld() == true && plr->GetSession() != NULL)
					{
						if (plr->GetAttributesManager()->IsinPVP == true)
						{
							sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY PVPZone;
							PVPZone.wOpCode = GU_WORLD_FREE_PVP_ZONE_ENTERED_NFY;
							PVPZone.wPacketSize = sizeof(sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY) - 2;
							PVPZone.Handle = plr->GetHandle();
							SendPacket((char*)&PVPZone, sizeof(sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY));
						}
						else
						{
							sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY PVPZone;
							PVPZone.wOpCode = GU_WORLD_FREE_PVP_ZONE_LEFT_NFY;
							PVPZone.wPacketSize = sizeof(sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY) - 2;
							PVPZone.Handle = plr->GetHandle();
							SendPacket((char*)&PVPZone, sizeof(sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY));
						}
					}
				}
			}
			it++;
		}
		mutexPlayer.unlock();
	}
	if (GetVectorPosition().x >= 5793.100 && GetAttributesManager()->IsinPVP == true
		|| GetVectorPosition().x <= 5751.100 && GetAttributesManager()->IsinPVP == true
		|| GetVectorPosition().z <= 746.037 && GetAttributesManager()->IsinPVP == true
		|| GetVectorPosition().z >= 788.037 && GetAttributesManager()->IsinPVP == true)
	{
		//	printf("Plat out \n");
		sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY PVPZone;
		PVPZone.wOpCode = GU_WORLD_FREE_PVP_ZONE_LEFT_NFY;
		PVPZone.wPacketSize = sizeof(sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY) - 2;
		PVPZone.Handle = GetHandle();
		SendPacket((char*)&PVPZone, sizeof(sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY));
		SendToPlayerList((char*)&PVPZone, sizeof(sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY));
		GetAttributesManager()->IsinPVP = false;
		mutexPlayer.lock();
		for (auto it = objList.begin(); it != objList.end();)
		{
			if (it->second != NULL)
			{
				if (it->second->GetTypeId() == OBJTYPE_PC)
				{
					Player* plr = static_cast<Player*>(it->second);
					if (plr->IsInWorld() == true && plr->GetSession() != NULL)
					{
						if (plr->GetAttributesManager()->IsinPVP == true)
						{
							sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY PVPZone;
							PVPZone.wOpCode = GU_WORLD_FREE_PVP_ZONE_ENTERED_NFY;
							PVPZone.wPacketSize = sizeof(sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY) - 2;
							PVPZone.Handle = plr->GetHandle();
							SendPacket((char*)&PVPZone, sizeof(sGU_WORLD_FREE_PVP_ZONE_ENTERED_NFY));
						}
						else
						{
							sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY PVPZone;
							PVPZone.wOpCode = GU_WORLD_FREE_PVP_ZONE_LEFT_NFY;
							PVPZone.wPacketSize = sizeof(sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY) - 2;
							PVPZone.Handle = plr->GetHandle();
							SendPacket((char*)&PVPZone, sizeof(sGU_WORLD_FREE_PVP_ZONE_LEFT_NFY));
						}
					}
				}
			}
			it++;
		}
		mutexPlayer.unlock();
	}
}