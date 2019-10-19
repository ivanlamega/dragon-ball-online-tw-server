#include <Game\World\WorldSession.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>
#include <Packet\Community\PacketUT.h>
#include <Packet\Community\PacketTU.h>
#include <Game\Object\Player.h>
#include <Game\Object\Mob.h>
#include <Game\Object\Npc.h>
#include <Game\Maps\MapManager.h>
#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <World.h>
#include <XmlParser2/XmlParser2.h>


void Player::BossEventUpdate()
{

	sGU_DYNAMIC_FIELD_COUNT_NFY BossCount;
	BossCount.wOpCode = GU_DYNAMIC_FIELD_COUNT_NFY;
	BossCount.wPacketSize = sizeof(sGU_DYNAMIC_FIELD_COUNT_NFY) - 2;

	BossCount.ValueMax = sWorld.BossEventMajinMaxCount;
	BossCount.ValueMin = sWorld.BossEventMajinCurCount;
	BossCount.ValueMax1 = 0;
	BossCount.ValueMin1 = 0;
	BossCount.unk = 0;
	if (sWorld.BossEventMajinCurCount >= sWorld.BossEventMajinMaxCount)
	{
		BossCount.ValueMax1 = sWorld.BossEventMajinMaxCount;
		BossCount.ValueMin1 = 0;
		BossCount.unk = 1;
	}
	if (GetWorldID() == 1)
	{
		if (sWorld.BossEventMajinCurCount >= sWorld.BossEventMajinMaxCount)
		{
			sWorld.ActiveEventBoss = true;
			sWorld.BossEventTimeRestart = 3600000;

			sGU_DYNAMIC_FIELD_SYSTEM_BOSS_POSITION_RES BossSpawn;
			memset(&BossSpawn, 0, sizeof(sGU_DYNAMIC_FIELD_SYSTEM_BOSS_POSITION_RES));
			BossSpawn.wOpCode = GU_DYNAMIC_FIELD_SYSTEM_BOSS_POSITION_RES;
			BossSpawn.wPacketSize = sizeof(sGU_DYNAMIC_FIELD_SYSTEM_BOSS_POSITION_RES) - 2;

			sVECTOR3 YellowMapLoc[6];

			YellowMapLoc[0].x = -1350.050049;
			YellowMapLoc[0].y = -81.809998;
			YellowMapLoc[0].z = 1319.489990;

			YellowMapLoc[1].x = -1342.969971;
			YellowMapLoc[1].y = -52.139999;
			YellowMapLoc[1].z = 2064.449951;

			YellowMapLoc[2].x = -2817.300049;
			YellowMapLoc[2].y = -39.240002;
			YellowMapLoc[2].z = 1311.979980;

			YellowMapLoc[3].x = -2708.360107;
			YellowMapLoc[3].y = -117.449997;
			YellowMapLoc[3].z = -534.340027;

			YellowMapLoc[4].x = -1493.170044;
			YellowMapLoc[4].y = -80.370003;
			YellowMapLoc[4].z = -132.089996;

			YellowMapLoc[5].x = -698.609985;
			YellowMapLoc[5].y = -86.099998;
			YellowMapLoc[5].z = -1345.390015;

			sVECTOR3 RedMapLoc[6];

			RedMapLoc[0].x = -1077.489990;
			RedMapLoc[0].y = -76.820000;
			RedMapLoc[0].z = -1652.319946;

			RedMapLoc[1].x = 1165.910034;
			RedMapLoc[1].y = -107.279999;
			RedMapLoc[1].z = -2593.280029;

			RedMapLoc[2].x = 1066.380005;
			RedMapLoc[2].y = -104.349998;
			RedMapLoc[2].z = -4459.009766;

			RedMapLoc[3].x = -923.179993;
			RedMapLoc[3].y = -118.110001;
			RedMapLoc[3].z = -3590.979980;

			RedMapLoc[4].x = -3780.239990;
			RedMapLoc[4].y = -136.080002;
			RedMapLoc[4].z = -3845.010010;

			RedMapLoc[5].x = -2933.899902;
			RedMapLoc[5].y = -88.720001;
			RedMapLoc[5].z = -1947.050049;
			BossSpawn.BossCount = sWorld.BossSpawnCount;
			int SpawnCount = 0;
			for (int i = 0; i <= 6; i++)
			{
				if (sWorld.BossIsSpawed == false)
				{
					MobTable * MobTable = sTBM.GetMobTable();
					sMOB_TBLDAT * pMOBTblData = reinterpret_cast<sMOB_TBLDAT*>(MobTable->FindData(14351201));
					if (pMOBTblData != NULL)
					{
						SpawnMOB spawnData;
						memset(&spawnData, 0, sizeof(SpawnMOB));

						spawnData.wOpCode = GU_OBJECT_CREATE;
						spawnData.wPacketSize = sizeof(SpawnMOB) - 2;

						spawnData.curEP = pMOBTblData->wBasic_EP;
						spawnData.curLP = pMOBTblData->wBasic_LP;
						spawnData.Handle = sWorld.AcquireSerialId();
						spawnData.Level = pMOBTblData->byLevel;
						spawnData.maxEP = pMOBTblData->wBasic_EP;
						spawnData.maxLP = pMOBTblData->wBasic_LP;
						spawnData.Size = 10;
						spawnData.Type = OBJTYPE_MOB;
						spawnData.Tblidx = pMOBTblData->tblidx;

						spawnData.fLastWalkingSpeed = 2;
						spawnData.fLastRunningSpeed = 2;
						spawnData.fLastAirgSpeed = 2;
						spawnData.fLastAirgDashSpeed = 2;
						spawnData.fLastAirgDashAccelSpeed = 2;

						spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
						spawnData.State.sCharStateBase.vCurLoc = YellowMapLoc[i];

						spawnData.State.sCharStateBase.vCurDir.x = 1;
						spawnData.State.sCharStateBase.vCurDir.y = 0;
						spawnData.State.sCharStateBase.vCurDir.z = 1;
						spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

						Mob* created_mob = new Mob;
						if (pMOBTblData)
						{
							if (created_mob->Create(pMOBTblData, spawnData) == true)
							{
								created_mob->GetMapRef().link(this->GetMap(), created_mob);
								//	printf("Mob ID %d inserted into map", 15712101);
							}
							else
								delete created_mob;
						}
						sWorld.Boss_Info[SpawnCount].Handle = created_mob->GetHandle();
						sWorld.Boss_Info[SpawnCount].vBossPos.x = YellowMapLoc[i].x;
						sWorld.Boss_Info[SpawnCount].vBossPos.z = YellowMapLoc[i].z;
						sWorld.BossTime = GetTickCount();
						SpawnCount += 1;
					}
				}
			}
			for (int i = 0; i <= 6; i++)
			{
				if (sWorld.BossIsSpawed == false)
				{
					MobTable * MobTable = sTBM.GetMobTable();
					sMOB_TBLDAT * pMOBTblData = reinterpret_cast<sMOB_TBLDAT*>(MobTable->FindData(11151101));
					if (pMOBTblData != NULL)
					{
						SpawnMOB spawnData;
						memset(&spawnData, 0, sizeof(SpawnMOB));

						spawnData.wOpCode = GU_OBJECT_CREATE;
						spawnData.wPacketSize = sizeof(SpawnMOB) - 2;

						spawnData.curEP = pMOBTblData->wBasic_EP;
						spawnData.curLP = pMOBTblData->wBasic_LP;
						spawnData.Handle = sWorld.AcquireSerialId();
						spawnData.Level = pMOBTblData->byLevel;
						spawnData.maxEP = pMOBTblData->wBasic_EP;
						spawnData.maxLP = pMOBTblData->wBasic_LP;
						spawnData.Size = 10;
						spawnData.Type = OBJTYPE_MOB;
						spawnData.Tblidx = pMOBTblData->tblidx;

						spawnData.fLastWalkingSpeed = 2;
						spawnData.fLastRunningSpeed = 2;
						spawnData.fLastAirgSpeed = 2;
						spawnData.fLastAirgDashSpeed = 2;
						spawnData.fLastAirgDashAccelSpeed = 2;

						spawnData.State.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = 255;
						spawnData.State.sCharStateBase.vCurLoc = RedMapLoc[i];

						spawnData.State.sCharStateBase.vCurDir.x = 1;
						spawnData.State.sCharStateBase.vCurDir.y = 0;
						spawnData.State.sCharStateBase.vCurDir.z = 1;
						spawnData.State.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_SPAWNING;

						Mob* created_mob = new Mob;
						if (pMOBTblData)
						{
							if (created_mob->Create(pMOBTblData, spawnData) == true)
							{
								created_mob->GetMapRef().link(this->GetMap(), created_mob);
								//	printf("Mob ID %d inserted into map", 15712101);
							}
							else
								delete created_mob;
						}
						sWorld.Boss_Info[SpawnCount].Handle = created_mob->GetHandle();
						sWorld.Boss_Info[SpawnCount].vBossPos.x = RedMapLoc[i].x;
						sWorld.Boss_Info[SpawnCount].vBossPos.z = RedMapLoc[i].z;
						sWorld.BossTime = GetTickCount();
						SpawnCount += 1;
						if (SpawnCount == 12)
							sWorld.SendAnnounce("Boss Event Have Start Look In Map For Location´s");
					}
				}
			}
			int SinalCount = 0;
			for (int i = 0; i <= 12; i++)
			{
				if (sWorld.Boss_Info[i].Handle != 0 || sWorld.Boss_Info[i].Handle != INVALID_TBLIDX)
				{
					//printf("show Boss Data List %d \n", sWorld.Boss_Info[i].Handle);
					BossSpawn.Boss_Info[SinalCount].Handle = sWorld.Boss_Info[i].Handle;
					BossSpawn.Boss_Info[SinalCount].vBossPos = sWorld.Boss_Info[i].vBossPos;
					BossSpawn.BossCount = SinalCount;
					SinalCount += 1;
					sWorld.BossIsSpawed = true;
				}
			}


			if (sWorld.ActiveEventBoss == true)
			{
				DWORD BossTime = GetTickCount() - sWorld.BossTime;
				if (BossTime >= sWorld.BossEventTimeRestart)
				{
					for (int i = 0; i <= 12; i++)
					{
						Mob* MobInfo = static_cast<Mob*>(GetFromList(sWorld.Boss_Info[i].Handle));
						if (MobInfo != NULL)
						{
							sWorld.SendAnnounce("Boss Event Have Restart EvilMajin Are Avalible Again");
							sGU_UPDATE_CHAR_STATE state;
							state.handle = MobInfo->GetHandle();
							state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_FAINTING;
							state.sCharState.sCharStateDetail.sCharStateFainting.byReason = eFAINT_REASON::FAINT_REASON_HIT;
							state.wOpCode = GU_UPDATE_CHAR_STATE;

							state.sCharState.sCharStateBase.dwConditionFlag = 0;
							//	res.sCharState.sCharStateBase.bFightMode = false;
							state.sCharState.sCharStateBase.dwStateTime = 2;
							state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;

							SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));

							sGU_OBJECT_DESTROY sPacket;

							sPacket.wOpCode = GU_OBJECT_DESTROY;
							sPacket.handle = MobInfo->GetHandle();
							sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

							SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));

							MobInfo->SetIsDead(true);
							MobInfo->RemoveFromWorld();
						}
						if (i == 12)
						{
							sWorld.BossEventMajinCurCount = 0;
							sWorld.ActiveEventBoss = false;
							sWorld.BossIsSpawed = false;
						}
					}
				}
			}

			sWorld.SendToAll((char*)&BossSpawn, sizeof(sGU_DYNAMIC_FIELD_SYSTEM_BOSS_POSITION_RES));
		}
	}
	if (sWorld.NpcIsSpawed == true)
	{
		DWORD NpcTime = GetTickCount() - sWorld.BossNpcTimeDespawns;
		if (NpcTime >= sWorld.BossNpcTimeDespawn)
		{
			for (int i = 0; i <= 12; i++)
			{
				Npc* NpcInfo = static_cast<Npc*>(GetFromList(sWorld.NPCHandle[i]));
				if (NpcInfo != NULL)
				{
					sWorld.SendAnnounce("NPC From Boss Event Have Despawn Kill Another Boss To Get Reward´s");
					sGU_UPDATE_CHAR_STATE state;
					state.handle = NpcInfo->GetHandle();
					state.sCharState.sCharStateBase.byStateID = eCHARSTATE::CHARSTATE_FAINTING;
					state.sCharState.sCharStateDetail.sCharStateFainting.byReason = eFAINT_REASON::FAINT_REASON_HIT;
					state.wOpCode = GU_UPDATE_CHAR_STATE;

					state.sCharState.sCharStateBase.dwConditionFlag = 0;
					//	res.sCharState.sCharStateBase.bFightMode = false;
					state.sCharState.sCharStateBase.dwStateTime = 2;
					state.wPacketSize = sizeof(sGU_UPDATE_CHAR_STATE) - 2;

					SendPacket((char*)&state, sizeof(sGU_UPDATE_CHAR_STATE));

					sGU_OBJECT_DESTROY sPacket;

					sPacket.wOpCode = GU_OBJECT_DESTROY;
					sPacket.handle = NpcInfo->GetHandle();
					sPacket.wPacketSize = sizeof(sGU_OBJECT_DESTROY) - 2;

					SendPacket((char*)&sPacket, sizeof(sGU_OBJECT_DESTROY));
					NpcInfo->SetIsDead(true);
					NpcInfo->RemoveFromWorld();
					sWorld.NPCHandle[i] = INVALID_TBLIDX;
					if (i == 12)
						sWorld.NpcIsSpawed = false;
				}
			}
		}
	}

	SendPacket((char*)&BossCount, sizeof(sGU_DYNAMIC_FIELD_COUNT_NFY));
}