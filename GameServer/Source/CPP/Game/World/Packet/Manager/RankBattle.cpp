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

void Player::FindRankPlyer()
{
	for (int i = 0; i <= 100; i++)
	{
		if (sWorld.InfoRank[i].PlayerHandle != 0 || sWorld.InfoRank[i].PlayerHandle != INVALID_TBLIDX)
		{
			if (sWorld.InfoRank[i].isInvited == false && sWorld.PlayerRankcount >= 1)
			{
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
								if (sWorld.InfoRank[i].PlayerHandle == plr->GetHandle())
								{
									sLog.outDetail("Invited Now");
									sGU_TELEPORT_PROPOSAL_NFY TeleportProposal;
									TeleportProposal.wOpCode = GU_TELEPORT_PROPOSAL_NFY;
									TeleportProposal.wPacketSize = sizeof(sGU_TELEPORT_PROPOSAL_NFY) - 2;

									TeleportProposal.byTeleportType = eTELEPORT_TYPE::TELEPORT_TYPE_RANKBATTLE;
									TeleportProposal.byInfoIndex = 1;
									TeleportProposal.wWaitTime = 30;
									TeleportProposal.worldTblidx = sWorld.InfoRank[i].MapTblidx;

									TeleportProposal.dwReserve = INVALID_TBLIDX;
									TeleportProposal.byBudokaiMatchDepth = 0;

									TeleportProposal.bySummonerNameLength = 0;
									//ConfuseTarget.wszSummonnerName = 0;
									sWorld.InfoRank[i].isInvited = true;
									plr->SendPacket((char*)&TeleportProposal, sizeof(sGU_TELEPORT_PROPOSAL_NFY));

								}
							}
						}
					}
					it++;
				}
				mutexPlayer.unlock();
			}
		}
	}
}
void WorldSession::GetPlayerFromRankList()
{
	
}