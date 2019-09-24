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
#include <World.h>


void Player::HandleItemUse(Packet pPacket)
{
	sUG_ITEM_USE_REQ *req = (sUG_ITEM_USE_REQ*)pPacket.GetPacketBuffer();
		
	sGU_ITEM_USE_RES UseItem;
	UseItem.wOpCode = GU_ITEM_USE_RES;
	UseItem.wPacketSize = sizeof(sGU_ITEM_USE_RES) - 2;	
	sGU_CHAR_ACTION_ITEM Acionitem;
	Acionitem.wOpCode = GU_CHAR_ACTION_ITEM;
	Acionitem.wPacketSize = sizeof(sGU_CHAR_ACTION_ITEM) - 2;
	sGU_ITEM_STACK_UPDATE ItmStackUpdate;
	ItmStackUpdate.wOpCode = GU_ITEM_STACK_UPDATE;
	ItmStackUpdate.wPacketSize = sizeof(sGU_ITEM_STACK_UPDATE) - 2;
	sGU_ITEM_DELETE itmDelete;
	itmDelete.wOpCode = GU_ITEM_DELETE;
	itmDelete.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;
	sITEM_PROFILE *Item = NULL;
	sITEM_PROFILE *Item2 = NULL;//some times used
	sITEM_TBLDAT *ItemData = NULL;
	sUSE_ITEM_TBLDAT * UseItemData = NULL;
	//sSYSTEM_EFFECT_TBLDAT * SystemEffectData = NULL;
	Item = this->inventoryManager.GetItemAtPlaceAndPost(req->byPlace, req->byPos);
	
	if (Item != NULL)
	{
		//Get Item Data
		if ((ItemData = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Item->tblidx)) == NULL)
		{
			ItemData = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Item->tblidx);
		}		
		if (ItemData != NULL)
		{
		if ((UseItemData = (sUSE_ITEM_TBLDAT*)sTBM.GetUseItemTable()->FindData(ItemData->tbxUseItem)) == NULL)
		{
			UseItemData = (sUSE_ITEM_TBLDAT2*)sTBM.GetUseItemTable2()->FindData(ItemData->tbxUseItem);
		}
		if (UseItemData != NULL)
		{
			for (int i = 0; i <= 2; i++)
			{
				sSYSTEM_EFFECT_TBLDAT * SystemEffectData = NULL;
				SystemEffectData = (sSYSTEM_EFFECT_TBLDAT*)sTBM.GetSystemEffectTable()->FindData(UseItemData->adwSystemEffect[i]);
				if (SystemEffectData != NULL)
				{	
					UseItem.tblidxItem = UseItemData->tblidx;
					UseItem.byPlace = Item->byPlace;
					UseItem.byPos = Item->byPos;
					UseItem.wResultCode = GAME_ITEM_CANT_USE_FOR_SOME_REASON;
					printf("effectCode %d \n ", SystemEffectData->effectCode);
					switch (SystemEffectData->effectCode)
					{
						//eSYSTEM_EFFECT_CODE
						case eSYSTEM_EFFECT_CODE::ACTIVE_HEAL_OVER_TIME://Food LP
						{	
							if (GetAttributesManager()->LpFoodIsActive == true)
							{
								UseItem.wResultCode = GAME_SUCCESS;

								Acionitem.handle = GetHandle();
								Acionitem.wResultCode = GAME_SUCCESS;
								Acionitem.dwLpEpEventId = INVALID_TBLIDX;
								Acionitem.itemTblidx = Item->tblidx;
								Acionitem.bySkillResultCount = 1;
								Acionitem.aSkillResult->hTarget = GetHandle();


								sGU_BUFF_REGISTERED pBuffData;
								memset(&pBuffData, 0, sizeof(sGU_BUFF_REGISTERED));
								//memset(&pBuffData, INVALID_TBLIDX, sizeof(sGU_BUFF_REGISTERED));
								pBuffData.wOpCode = GU_BUFF_REGISTERED;
								pBuffData.wPacketSize = sizeof(sGU_BUFF_REGISTERED) - 2;
								pBuffData.tblidx = Item->tblidx;
								pBuffData.hHandle = GetHandle();
								pBuffData.bySourceType = 1;
								pBuffData.dwInitialDuration = UseItemData->dwCooldownMs;
								pBuffData.dwTimeRemaining = UseItemData->dwKeepTimeMs;//Time
								pBuffData.isactive = true;
								pBuffData.BuffType.BuffEffectType = 5;
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.TbxCommonConfig = UseItemData->adwSystemEffect[i];
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainValue = UseItemData->adSystemEffectValue[i];
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainTime = UseItemData->dwKeepTimeMs;
								pBuffData.NeedDisplayMensage = false;
								SendPacket((char*)&pBuffData, sizeof(sGU_BUFF_REGISTERED));
								int FreePlace = 0;
								for (int i = 0; i <= 16; i++)
								{
									if (GetAttributesManager()->sFoodInfo[i].FoodItemID == 0 || GetAttributesManager()->sFoodInfo[i].FoodItemID == INVALID_TBLIDX)
									{
										FreePlace = i;
									}

								}																
								GetAttributesManager()->sFoodInfo[FreePlace].FoodItemID = Item->tblidx;
								GetAttributesManager()->sFoodInfo[FreePlace].TypeEffect = pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.TbxCommonConfig;
								GetAttributesManager()->sFoodInfo[FreePlace].FoodHealAumont[0] = pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainValue;
								GetAttributesManager()->sFoodInfo[FreePlace].BuffTime = GetTickCount();
								GetAttributesManager()->sFoodInfo[FreePlace].BuffKeepTime = pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainTime;
								GetAttributesManager()->LpFoodIsActive = true;

								if (Item->byStackcount <= 1)
								{
									itmDelete.bySrcPlace = Item->byPlace;
									itmDelete.bySrcPos = Item->byPos;
									itmDelete.hSrcItem = Item->handle;
									SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
									Item->byPlace = INVALID_TBLIDX;
									Item->byPos = INVALID_TBLIDX;
									Item->tblidx = INVALID_TBLIDX;
								}
								else
								{
									//UpdateStack item 2
									ItmStackUpdate.hItemHandle = Item->handle;
									ItmStackUpdate.byStack = Item->byStackcount - 1;
									ItmStackUpdate.bIsNew = false;
									Item->byStackcount = ItmStackUpdate.byStack;
									SendPacket((char*)&ItmStackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
								}
							}
							else
								UseItem.wResultCode = GAME_ITEM_ALREADY_EXIST;
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_EP_OVER_TIME://Drink EP
						{
							if (GetAttributesManager()->EpFoodIsActive == true)
							{								

								UseItem.wResultCode = GAME_SUCCESS;

								Acionitem.handle = GetHandle();
								Acionitem.wResultCode = GAME_SUCCESS;
								Acionitem.dwLpEpEventId = INVALID_TBLIDX;
								Acionitem.itemTblidx = Item->tblidx;
								Acionitem.bySkillResultCount = 1;
								Acionitem.aSkillResult->hTarget = GetHandle();
								

								sGU_BUFF_REGISTERED pBuffData;
								memset(&pBuffData, 0, sizeof(sGU_BUFF_REGISTERED));
								//memset(&pBuffData, INVALID_TBLIDX, sizeof(sGU_BUFF_REGISTERED));
								pBuffData.wOpCode = GU_BUFF_REGISTERED;
								pBuffData.wPacketSize = sizeof(sGU_BUFF_REGISTERED) - 2;
								pBuffData.tblidx = Item->tblidx;
								pBuffData.hHandle = GetHandle();
								pBuffData.bySourceType = 1;
								pBuffData.dwInitialDuration = UseItemData->dwCooldownMs;
								pBuffData.dwTimeRemaining = UseItemData->dwKeepTimeMs;//Time
								pBuffData.isactive = true;
								pBuffData.BuffType.BuffEffectType = 5;
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.TbxCommonConfig = UseItemData->adwSystemEffect[i];
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainValue = UseItemData->adSystemEffectValue[i];
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainTime = UseItemData->dwKeepTimeMs;
								pBuffData.NeedDisplayMensage = false;
								SendPacket((char*)&pBuffData, sizeof(sGU_BUFF_REGISTERED));
								int FreePlace = 0;
								for (int i = 0; i <= 16; i++)
								{
									if (GetAttributesManager()->sFoodInfo[i].FoodItemID == 0 || GetAttributesManager()->sFoodInfo[i].FoodItemID == INVALID_TBLIDX)
									{
										FreePlace = i;
									}

								}
																
								GetAttributesManager()->sFoodInfo[FreePlace].FoodItemID = Item->tblidx;
								GetAttributesManager()->sFoodInfo[FreePlace].TypeEffect = pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.TbxCommonConfig;
								GetAttributesManager()->sFoodInfo[FreePlace].FoodHealAumont[0] = pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainValue;
								GetAttributesManager()->sFoodInfo[FreePlace].BuffTime = GetTickCount();
								GetAttributesManager()->sFoodInfo[FreePlace].BuffKeepTime = pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainTime;
								GetAttributesManager()->EpFoodIsActive = true;

								if (Item->byStackcount <= 1)
								{
									itmDelete.bySrcPlace = Item->byPlace;
									itmDelete.bySrcPos = Item->byPos;
									itmDelete.hSrcItem = Item->handle;
									SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
									Item->byPlace = INVALID_TBLIDX;
									Item->byPos = INVALID_TBLIDX;
									Item->tblidx = INVALID_TBLIDX;
								}
								else
								{
									//UpdateStack item 2
									ItmStackUpdate.hItemHandle = Item->handle;
									ItmStackUpdate.byStack = Item->byStackcount - 1;
									ItmStackUpdate.bIsNew = false;
									Item->byStackcount = ItmStackUpdate.byStack;
									SendPacket((char*)&ItmStackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
								}
							}
							else
								UseItem.wResultCode = GAME_ITEM_ALREADY_EXIST;
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_RP_UP://RP Ball
						{
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_GAMBLE_ITEM:
						{
							sQUEST_PROBABILITY_TBLDAT * ProbabilityTableData = NULL;
							if ((ProbabilityTableData = (sQUEST_PROBABILITY_TBLDAT*)sTBM.GetQuestProbabilityTable()->FindData(Item->tblidx)) == NULL)
							{
								ProbabilityTableData = (sQUEST_PROBABILITY_TBLDAT2*)sTBM.GetQuestProbabilityTable2()->FindData(Item->tblidx);
							}
							if (ProbabilityTableData != NULL)
							{																	
							if(GetInventoryManager()->IsInventoryFull() == false && GetInventoryManager()->GetTotalFreeSpaceInBag() >= ProbabilityTableData->unknown2)
							{						
								if (GetPcProfile()->byLevel < ItemData->byNeedLevel)
								{
										UseItem.wResultCode = GAME_ITEM_NEED_MORE_LEVEL;
								}
								else
								{
									Item2 = this->inventoryManager.GetItemAtPlaceAndPost(req->byPlace2, req->byPos2);
									if (Item2 != NULL)
									{
										if (Item2->byStackcount <= 1)
										{
											itmDelete.bySrcPlace = Item2->byPlace;
											itmDelete.bySrcPos = Item2->byPos;
											itmDelete.hSrcItem = Item2->handle;
											SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
											Item2->byPlace = INVALID_TBLIDX;
											Item2->byPos = INVALID_TBLIDX;
											Item2->tblidx = INVALID_TBLIDX;
										}
										else
										{
											//UpdateStack item 2
											ItmStackUpdate.hItemHandle = Item2->handle;
											ItmStackUpdate.byStack = Item2->byStackcount - 1;
											ItmStackUpdate.bIsNew = false;
											Item2->byStackcount = ItmStackUpdate.byStack;
											SendPacket((char*)&ItmStackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
										}
									}
									if (Item->byStackcount <= 1)
									{
										itmDelete.bySrcPlace = Item->byPlace;
										itmDelete.bySrcPos = Item->byPos;
										itmDelete.hSrcItem = Item->handle;
										SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
										Item->byPlace = INVALID_TBLIDX;
										Item->byPos = INVALID_TBLIDX;
										Item->tblidx = INVALID_TBLIDX;
									}
									else
									{
										//UpdateStack
										ItmStackUpdate.hItemHandle = Item->handle;
										ItmStackUpdate.byStack = Item->byStackcount - 1;
										ItmStackUpdate.bIsNew = false;
										Item->byStackcount = ItmStackUpdate.byStack;
										SendPacket((char*)&ItmStackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
									}
									for (int i = 0; i <= ProbabilityTableData->unknown2; i++)
									{
										sITEM_PROFILE createdItem;
										WORD result = GetInventoryManager()->PerformShopBuy(ProbabilityTableData->asProbabilityData[i].tblidx, ProbabilityTableData->asProbabilityData[i].dwMaxValue, createdItem);
											if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
											{
												m_session->SendItemCreate(&createdItem);
												UseItem.wResultCode = GAME_SUCCESS;	
												SendPacket((char*)&UseItem, sizeof(sGU_ITEM_USE_RES));
												UseItem.wResultCode = GAME_ITEM_LOOTING;// because Chest + Key bug 
											}
										}											
									}									
								}
								else
									UseItem.wResultCode = GAME_ITEM_INVEN_FULL;
								}
								break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_VEHICLE:
						{
							UseItem.wResultCode = GAME_SUCCESS;
							Acionitem.handle = GetHandle();
							Acionitem.wResultCode = GAME_SUCCESS;
							Acionitem.dwLpEpEventId = INVALID_TBLIDX;
							Acionitem.itemTblidx = Item->tblidx;
							Acionitem.bySkillResultCount = 1;
							Acionitem.aSkillResult->hTarget = GetHandle();

							sGU_VEHICLE_START_NFY VEHICLE;
							VEHICLE.wOpCode = GU_VEHICLE_START_NFY;
							VEHICLE.wPacketSize = sizeof(sGU_VEHICLE_START_NFY) - 2;

							VEHICLE.hDriverHandle = GetHandle();
							VEHICLE.idFuelItemTblidx = INVALID_TBLIDX;
							VEHICLE.hVehicleItem = Item->handle;
							VEHICLE.idVehicleItemTblidx = Item->tblidx;

							SendPacket((char*)&VEHICLE, sizeof(sGU_VEHICLE_START_NFY));

							GetState()->sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = eASPECTSTATE::ASPECTSTATE_VEHICLE;
							GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.bIsEngineOn = false;
							GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.hVehicleItem = Item->handle;
							GetState()->sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = Item->tblidx;
							UpdateAspectState(eASPECTSTATE::ASPECTSTATE_VEHICLE);
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_AIR_MOVE_DASH_ACCEL://Fly scroll
						{						
						break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_EXP_BOOSTER://ExP Booster
						{	
							UseItem.wResultCode = GAME_SUCCESS;

							Acionitem.handle = GetHandle();
							Acionitem.wResultCode = GAME_SUCCESS;
							Acionitem.dwLpEpEventId = INVALID_TBLIDX;
							Acionitem.itemTblidx = Item->tblidx;
							Acionitem.bySkillResultCount = 1;
							Acionitem.aSkillResult->hTarget = GetHandle();


							sGU_BUFF_REGISTERED pBuffData;
							memset(&pBuffData, 0, sizeof(sGU_BUFF_REGISTERED));
							//memset(&pBuffData, INVALID_TBLIDX, sizeof(sGU_BUFF_REGISTERED));
							pBuffData.wOpCode = GU_BUFF_REGISTERED;
							pBuffData.wPacketSize = sizeof(sGU_BUFF_REGISTERED) - 2;
							pBuffData.tblidx = Item->tblidx;
							pBuffData.hHandle = GetHandle();
							pBuffData.bySourceType = 1;
							pBuffData.dwInitialDuration = UseItemData->dwCooldownMs;
							pBuffData.dwTimeRemaining = UseItemData->dwKeepTimeMs;//Time
							pBuffData.isactive = true;
							pBuffData.BuffType.BuffEffectType = 5;
							pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.TbxCommonConfig = UseItemData->adwSystemEffect[i];
							pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainValue = UseItemData->adSystemEffectValue[i];
							pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainTime = UseItemData->dwKeepTimeMs;
							pBuffData.NeedDisplayMensage = false;
							SendPacket((char*)&pBuffData, sizeof(sGU_BUFF_REGISTERED));
						

							if (Item->byStackcount <= 1)
							{
								itmDelete.bySrcPlace = Item->byPlace;
								itmDelete.bySrcPos = Item->byPos;
								itmDelete.hSrcItem = Item->handle;
								SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
								Item->byPlace = INVALID_TBLIDX;
								Item->byPos = INVALID_TBLIDX;
								Item->tblidx = INVALID_TBLIDX;
							}
							else
							{
								//UpdateStack item 2
								ItmStackUpdate.hItemHandle = Item->handle;
								ItmStackUpdate.byStack = Item->byStackcount - 1;
								ItmStackUpdate.bIsNew = false;
								Item->byStackcount = ItmStackUpdate.byStack;
								SendPacket((char*)&ItmStackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
							}						
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_MASCOT_REGIST://Mascot Register
						{
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_REVIVAL_AFTEREFFECT_CURE_MINOR://Resurreicion Buff Remove
						{
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_SET_LEVEL://Level Up Stone
						{	
							if (GetPcProfile()->byLevel < ItemData->byNeedLevel)
								UseItem.wResultCode = GAME_ITEM_NEED_MORE_LEVEL;
							else
							{
								if (GetPcProfile()->byLevel >= UseItemData->adSystemEffectValue[i])
									UseItem.wResultCode = GAME_ITEM_CANT_USE_NOW;
								else
								{									
									if (Item->byStackcount <= 1)
									{
										itmDelete.bySrcPlace = Item->byPlace;
										itmDelete.bySrcPos = Item->byPos;
										itmDelete.hSrcItem = Item->handle;
										SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
										Item->byPlace = INVALID_TBLIDX;
										Item->byPos = INVALID_TBLIDX;
										Item->tblidx = INVALID_TBLIDX;
									}
									else
									{
										//UpdateStack
										ItmStackUpdate.hItemHandle = Item->handle;
										ItmStackUpdate.byStack = Item->byStackcount - 1;
										ItmStackUpdate.bIsNew = false;
										Item->byStackcount = ItmStackUpdate.byStack;
										SendPacket((char*)&ItmStackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
									}
									LevelUpByComand(UseItemData->adSystemEffectValue[i]);
									UseItem.wResultCode = GAME_SUCCESS;
									
								}								
							}							
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_CHAR_TITLE:
						{
							// Need a verification to check if player alardy got that title
							if (Item->byStackcount <= 1)
							{
								itmDelete.bySrcPlace = Item->byPlace;
								itmDelete.bySrcPos = Item->byPos;
								itmDelete.hSrcItem = Item->handle;
								SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
								Item->byPlace = INVALID_TBLIDX;
								Item->byPos = INVALID_TBLIDX;
								Item->tblidx = INVALID_TBLIDX;
							}
							else
							{
								//UpdateStack
								ItmStackUpdate.hItemHandle = Item->handle;
								ItmStackUpdate.byStack = Item->byStackcount - 1;
								ItmStackUpdate.bIsNew = false;
								Item->byStackcount = ItmStackUpdate.byStack;
								SendPacket((char*)&ItmStackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
							}
							SendAddTitle(UseItemData->adSystemEffectValue[i]);
							UseItem.wResultCode = GAME_SUCCESS;
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_CHILD_ADULT_TRANSFORM://Kid Clock
						{	
							if (Item->byStackcount <= 1)
							{
								itmDelete.bySrcPlace = Item->byPlace;
								itmDelete.bySrcPos = Item->byPos;
								itmDelete.hSrcItem = Item->handle;
								SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
								Item->byPlace = INVALID_TBLIDX;
								Item->byPos = INVALID_TBLIDX;
								Item->tblidx = INVALID_TBLIDX;
							}
							else
							{
								//UpdateStack
								ItmStackUpdate.hItemHandle = Item->handle;
								ItmStackUpdate.byStack = Item->byStackcount - 1;
								ItmStackUpdate.bIsNew = false;
								Item->byStackcount = ItmStackUpdate.byStack;
								SendPacket((char*)&ItmStackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
							}
							if (GetPcProfile()->bIsAdult == false)
							{
								ConvertAdult(true);								
							}
							else
							{
								ConvertAdult(false);
							}
							UseItem.wResultCode = GAME_SUCCESS;
							break;
						}

					}
				}
			}
			
			SendPacket((char*)&UseItem, sizeof(sGU_ITEM_USE_RES));
			SendPacket((char*)&Acionitem, sizeof(sGU_CHAR_ACTION_ITEM));//Error not fount come from it because is not handle
		}	
	  }
	}
}

void Player::ItemSoketInsert(Packet pPacket)
{
	sUG_ITEM_SOCKET_INSERT_BEAD_REQ *req = (sUG_ITEM_SOCKET_INSERT_BEAD_REQ*)pPacket.GetPacketBuffer();
	sITEM_PROFILE *Item = NULL;
	sITEM_PROFILE *DoggiBall = NULL;
	sITEM_TBLDAT *ItemTbl = NULL;
	sITEM_TBLDAT *DoggiballTbl = NULL;
	Item = this->inventoryManager.GetItemAtPlaceAndPost(req->itemPlace, req->itemPos);
	DoggiBall = this->inventoryManager.GetItemAtPlaceAndPost(req->DogiBallplace, req->DogiBallPos);
	if (Item != NULL && DoggiBall != NULL)
	{
		//Get Item data
		if ((ItemTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Item->tblidx)) == NULL)
		{
			ItemTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Item->tblidx);
		}
		//Get DoggiBall data
		if ((DoggiballTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(DoggiBall->tblidx)) == NULL)
		{
			DoggiballTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(DoggiBall->tblidx);
		}
		if (ItemTbl != NULL && DoggiballTbl != NULL)
		{
			sGU_ITEM_SOCKET_INSERT_BEAD_RES DoggiBallEffect;
			memset(&DoggiBallEffect, 0, sizeof(sGU_ITEM_SOCKET_INSERT_BEAD_RES));

			DoggiBallEffect.wOpCode = GU_ITEM_SOCKET_INSERT_BEAD_RES;
			DoggiBallEffect.wPacketSize = sizeof(sGU_ITEM_SOCKET_INSERT_BEAD_RES) - 2;
			DoggiBallEffect.wResultCode = GAME_SUCCESS;
			DoggiBallEffect.ItemPlace = Item->byPlace;
			DoggiBallEffect.ItemPos = Item->byPos;
			DoggiBallEffect.BallID = 120;
			DoggiBallEffect.DogiballPlace = DoggiBall->byPlace;
			DoggiBallEffect.DoggiballPos = DoggiBall->byPos;
			DoggiBallEffect.DoggiballCount = DoggiBall->byStackcount - 1;
			DoggiBall->byStackcount = DoggiBallEffect.DoggiballCount;

			if (DoggiBall->byStackcount <= 0)
			{
				//Delet Item
				sGU_ITEM_DELETE itmDelete;
				itmDelete.wOpCode = GU_ITEM_DELETE;
				itmDelete.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;
				itmDelete.bySrcPlace = DoggiBall->byPlace;
				itmDelete.bySrcPos = DoggiBall->byPos;
				itmDelete.hSrcItem = DoggiBall->handle;
				DoggiBall->byPlace = INVALID_TBLIDX;
				DoggiBall->byPos = INVALID_TBLIDX;
				DoggiBall->tblidx = INVALID_TBLIDX;
				SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
			}
			else
			{
				//Update stack
				sGU_ITEM_STACK_UPDATE StackUpdate;
				StackUpdate.wOpCode = GU_ITEM_STACK_UPDATE;
				StackUpdate.wPacketSize = sizeof(sGU_ITEM_STACK_UPDATE) - 2;
				StackUpdate.hItemHandle = DoggiBall->handle;
				StackUpdate.byStack = DoggiBallEffect.DoggiballCount;
				StackUpdate.bIsNew = false;
				DoggiBall->byStackcount = StackUpdate.byStack;
				SendPacket((char*)&StackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
			}
			//not used
			for (int i = 0; i <= 16; i++)
			{
				DoggiBallEffect.unk[i] = 0;
			}
			//Define Effects 
			DoggiBallEffect.DoggiEffectType = 2001 + rand() % 50;
			DoggiBallEffect.DoggiEffectValue = 1 + rand() % 12;
			DoggiBallEffect.DoggiEffectType1 = 2001 + rand() % 50;
			DoggiBallEffect.DoggiEffectValue1 = 1 + rand() % 12;

			SendPacket((char*)&DoggiBallEffect, sizeof(sGU_ITEM_SOCKET_INSERT_BEAD_RES));
		}
	}
}

void Player::ItemSoketDestroy(Packet pPacket)
{
	sUG_ITEM_SOCKET_DESTROY_BEAD_REQ *req = (sUG_ITEM_SOCKET_DESTROY_BEAD_REQ*)pPacket.GetPacketBuffer();
	sITEM_PROFILE *Item = NULL;
	sITEM_TBLDAT *ItemTbl = NULL;
	Item = this->inventoryManager.GetItemAtPlaceAndPost(req->itemPlace, req->itemPos);
	if (Item != NULL)
	{
		//Get Item Data
		if ((ItemTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Item->tblidx)) == NULL)
		{
			ItemTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Item->tblidx);
		}
		if (ItemTbl != NULL)
		{
			sGU_ITEM_SOCKET_DESTROY_BEAD_RES RemoveDoggiEffect;

			memset(&RemoveDoggiEffect, 0, sizeof(sGU_ITEM_SOCKET_DESTROY_BEAD_RES));
			RemoveDoggiEffect.wOpCode = GU_ITEM_SOCKET_DESTROY_BEAD_RES;
			RemoveDoggiEffect.wPacketSize = sizeof(sGU_ITEM_SOCKET_DESTROY_BEAD_RES) - 2;
			RemoveDoggiEffect.wResultCode = GAME_SUCCESS;

			RemoveDoggiEffect.ItemPlace = req->itemPlace;
			RemoveDoggiEffect.ItemPos = req->itemPos;
			RemoveDoggiEffect.BallID = 0;

			SendPacket((char*)&RemoveDoggiEffect, sizeof(sGU_ITEM_SOCKET_DESTROY_BEAD_RES));
		}
	}
}

void Player::ItemOptionsChange(Packet pPacket)
{
	sUG_ITEM_CHANGE_OPTION_REQ *req = (sUG_ITEM_CHANGE_OPTION_REQ*)pPacket.GetPacketBuffer();

	sITEM_PROFILE *Item = NULL;
	sITEM_PROFILE *Box = NULL;
	sITEM_TBLDAT *ItemTbl = NULL;
	sITEM_TBLDAT *BoxTbl = NULL;

	Item = this->inventoryManager.GetItemAtPlaceAndPost(req->itemPlace, req->itemPos);
	Box = this->inventoryManager.GetItemAtPlaceAndPost(req->Boxplace, req->BoxPos);
	if (Item != NULL && Box != NULL)
	{
		//Get Item Data
		if ((ItemTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Item->tblidx)) == NULL)
		{
			ItemTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Item->tblidx);
		}
		//Get Equip Box Data
		if ((BoxTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Box->tblidx)) == NULL)
		{
			BoxTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Box->tblidx);
		}
		if (ItemTbl != NULL && BoxTbl != NULL)
		{
			sGU_ITEM_CHANGE_OPTION_RES ItemEffect;
			//memset(&ItemEffect, 0, sizeof(sGU_ITEM_CHANGE_OPTION_RES));
			ItemEffect.wOpCode = GU_ITEM_CHANGE_OPTION_RES;
			ItemEffect.wPacketSize = sizeof(sGU_ITEM_CHANGE_OPTION_RES) - 2;
			ItemEffect.wResultCode = GAME_SUCCESS;

			ItemEffect.ItemPlace = req->itemPlace;
			ItemEffect.ItemPos = req->itemPos;
			ItemEffect.unk = INVALID_TBLIDX;
			ItemEffect.unk1 = INVALID_TBLIDX;
			ItemEffect.BoxPlace = req->Boxplace;
			ItemEffect.BoxPos = req->BoxPos;			
			ItemEffect.ByCount = Box->byStackcount - 1;//Stack Count Box
			
			for (int i = 0; i <= 6; i++)
			{
				ItemEffect.aitemEffect[i].wType = 2001 + rand() % 50;
				ItemEffect.aitemEffect[i].dwValue = 1 + rand() % 34;
			}

			for (int i = 0; i <= 2; i++)
			{
				ItemEffect.aitemExtraEffect[i].wType = INVALID_TBLIDX;
				ItemEffect.aitemExtraEffect[i].dwValue = INVALID_TBLIDX;
			}

			Item->aitemEffect[0].wType = ItemEffect.aitemEffect[0].wType;
			Item->aitemEffect[0].dwValue = ItemEffect.aitemEffect[0].dwValue;
			Item->aitemEffect[1].wType = ItemEffect.aitemEffect[1].wType;
			Item->aitemEffect[1].dwValue = ItemEffect.aitemEffect[1].dwValue;
			Item->aitemEffect[2].wType = ItemEffect.aitemEffect[2].wType;
			Item->aitemEffect[2].dwValue = ItemEffect.aitemEffect[2].dwValue;
			Item->aitemEffect[3].wType = ItemEffect.aitemEffect[3].wType;
			Item->aitemEffect[3].dwValue = ItemEffect.aitemEffect[3].dwValue;
			Item->aitemEffect[4].wType = ItemEffect.aitemEffect[4].wType;
			Item->aitemEffect[4].dwValue = ItemEffect.aitemEffect[4].dwValue;
			Item->aitemEffect[5].wType = ItemEffect.aitemEffect[5].wType;
			Item->aitemEffect[5].dwValue = ItemEffect.aitemEffect[5].dwValue;

			
			//Need Update Item Equip Box Stackcount here
			if (Box->byStackcount <= 0)
			{
				sGU_ITEM_DELETE itmDelete;
				itmDelete.wOpCode = GU_ITEM_DELETE;
				itmDelete.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;
				itmDelete.bySrcPlace = Box->byPlace;
				itmDelete.bySrcPos = Box->byPos;
				itmDelete.hSrcItem = Box->handle;
				Box->byPlace = INVALID_TBLIDX;
				Box->byPos = INVALID_TBLIDX;
				Box->tblidx = INVALID_TBLIDX;
				SendPacket((char*)&itmDelete, sizeof(sGU_ITEM_DELETE));
			}
			else
			{
				sGU_ITEM_STACK_UPDATE StackUpdate;
				StackUpdate.wOpCode = GU_ITEM_STACK_UPDATE;
				StackUpdate.wPacketSize = sizeof(sGU_ITEM_STACK_UPDATE) - 2;
				StackUpdate.hItemHandle = Box->handle;
				StackUpdate.byStack = Box->byStackcount - 1;
				StackUpdate.bIsNew = false;
				Box->byStackcount = StackUpdate.byStack;
				ItemEffect.ByCount = StackUpdate.byStack;
				SendPacket((char*)&StackUpdate, sizeof(sGU_ITEM_STACK_UPDATE));
			}

			SendPacket((char*)&ItemEffect, sizeof(sGU_ITEM_CHANGE_OPTION_RES));
		}
	}
}
void Player::SendItemUpgrade(Packet & packet)
{
	sUG_ITEM_UPGRADE_WORK_REQ *req = (sUG_ITEM_UPGRADE_WORK_REQ*)packet.GetPacketBuffer();
	sITEM_PROFILE *Item = NULL;
	sITEM_PROFILE *Stone = NULL;
	sITEM_PROFILE *WhiteStone = NULL;
	sITEM_TBLDAT *ItemTbl = NULL;
	sITEM_TBLDAT *StoneTbl = NULL;
	sITEM_TBLDAT *WhiteStoneTbl = NULL;
	printf(" White Place %d \n White pos %d \n", req->WhiteStonePlace, req->WhiteStonePos);
	Item = this->inventoryManager.GetItemAtPlaceAndPost(req->byItemPlace, req->byItemPos);
	Stone = this->inventoryManager.GetItemAtPlaceAndPost(req->byStonPlace, req->byStonPos);
	WhiteStone = this->inventoryManager.GetItemAtPlaceAndPost(req->WhiteStonePlace, req->WhiteStonePos);
	if (Item != NULL && Stone != NULL || Item != NULL && Stone != NULL && WhiteStone != NULL)
	{
		//Get Item Data
		if ((ItemTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Item->tblidx)) == NULL)
		{
			ItemTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Item->tblidx);
		}
		//Get Equip Box Data
		if ((StoneTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Stone->tblidx)) == NULL)
		{
			StoneTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Stone->tblidx);
		}
		//Get Equip Box Data
		if ((WhiteStoneTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(WhiteStone->tblidx)) == NULL)
		{
			WhiteStoneTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(WhiteStone->tblidx);
		}
		if (ItemTbl != NULL && StoneTbl != NULL || ItemTbl != NULL && StoneTbl != NULL && WhiteStoneTbl != NULL)
		{
			sGU_ITEM_UPGRADE_WORK_RES Upgrade;			
			memset(&Upgrade, 0, sizeof(sGU_ITEM_UPGRADE_WORK_RES));
			Upgrade.wOpCode = GU_ITEM_UPGRADE_WORK_RES;
			Upgrade.wPacketSize = sizeof(sGU_ITEM_UPGRADE_WORK_RES) - 2;
			Upgrade.ResultCode = GAME_SUCCESS;
			Upgrade.ItemPlace = req->byItemPlace;
			Upgrade.ItemPos = req->byItemPos;
			Upgrade.StonePlace = req->byStonPlace;
			Upgrade.StonePos = req->byStonPos;			
			int Rate = rand() % 100 + 1;
			int GradeAdvacedStone = 1 + rand() % 3;
			//Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE; //Fail Card
			//Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL; Broken card
			//Upgrade.Grade = Item->byGrade;

			if (StoneTbl->eItemType == eITEM_TYPE::ITEM_TYPE_DOWGRADE_WEAPON || StoneTbl->eItemType == eITEM_TYPE::ITEM_TYPE_DOWGRADE_ARMOR)
			{
				//Update Grade of Item
				Upgrade.Grade = Item->byGrade - 1;
				Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card

			}
			//Red Stone Upgrade Weapon by +1
			else if (StoneTbl->eItemType == eITEM_TYPE::ITEM_TYPE_RED_STONE)
			{
				//Sucess 100%
				if (Item->byGrade >= 0 && Item->byGrade <= 5)
				{
					Upgrade.Grade = Item->byGrade + 1;
					Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
				}	
				//Rate +6
				if (Item->byGrade == 6)
				{
					if (Rate >= 0 && Rate <= 96)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 97 && Rate <= 98)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 99 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +7
				if (Item->byGrade == 7)
				{
					if (Rate >= 0 && Rate <= 90)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 91 && Rate <= 95)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 95 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +8
				if (Item->byGrade == 8)
				{
					if (Rate >= 0 && Rate <= 85)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 86 && Rate <= 90)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 91 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +9
				if (Item->byGrade == 9)
				{
					if (Rate >= 0 && Rate <= 70)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 71 && Rate <= 85)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 86 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +10
				if (Item->byGrade == 10)
				{
					if (Rate >= 0 && Rate <= 68)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 69 && Rate <= 80)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 81 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +11
				if (Item->byGrade == 11)
				{
					if (Rate >= 0 && Rate <= 60)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 61 && Rate <= 80)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 80 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +12
				if (Item->byGrade == 12)
				{
					if (Rate >= 0 && Rate <= 50)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 51 && Rate <= 70)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 71 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +13
				if (Item->byGrade == 13)
				{
					if (Rate >= 0 && Rate <= 40)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 41 && Rate <= 60)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 61 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +14
				if (Item->byGrade == 14)
				{
					if (Rate >= 0 && Rate <= 30)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 31 && Rate <= 50)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 51 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}			
			}
			////
			//Blue Stone Armor
			else if (StoneTbl->eItemType == eITEM_TYPE::ITEM_TYPE_BLUE_STONE)
			{
				//Sucess 100%
				if (Item->byGrade >= 0 && Item->byGrade <= 4)
				{
					Upgrade.Grade = Item->byGrade + 1;
					Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
				}
				//Rate +5
				if (Item->byGrade == 5)
				{
					if (Rate >= 0 && Rate <= 95)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 96 && Rate <= 98)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 99 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +6
				if (Item->byGrade == 6)
				{
					if (Rate >= 0 && Rate <= 96)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 97 && Rate <= 98)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 99 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +7
				if (Item->byGrade == 7)
				{
					if (Rate >= 0 && Rate <= 90)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 91 && Rate <= 95)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 95 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +8
				if (Item->byGrade == 8)
				{
					if (Rate >= 0 && Rate <= 85)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 86 && Rate <= 90)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 91 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +9
				if (Item->byGrade == 9)
				{
					if (Rate >= 0 && Rate <= 70)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 71 && Rate <= 85)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 86 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +10
				if (Item->byGrade == 10)
				{
					if (Rate >= 0 && Rate <= 68)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 69 && Rate <= 80)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 81 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +11
				if (Item->byGrade == 11)
				{
					if (Rate >= 0 && Rate <= 60)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 61 && Rate <= 80)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 80 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +12
				if (Item->byGrade == 12)
				{
					if (Rate >= 0 && Rate <= 50)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 51 && Rate <= 70)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 71 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +13
				if (Item->byGrade == 13)
				{
					if (Rate >= 0 && Rate <= 40)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 41 && Rate <= 60)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 61 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +14
				if (Item->byGrade == 14)
				{
					if (Rate >= 0 && Rate <= 30)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 31 && Rate <= 50)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 51 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}				
			}
			////
			else if (StoneTbl->eItemType == eITEM_TYPE::ITEM_TYPE_PURPLE_STONE)
			{
				//Sucess 100%
				if (Item->byGrade >= 0 && Item->byGrade <= 5)
				{
					Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
					Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
				}
				//Rate +6
				if (Item->byGrade == 6)
				{
					if (Rate >= 0 && Rate <= 50)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 51 && Rate <= 80)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 81 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +7
				if (Item->byGrade == 7)
				{
					if (Rate >= 0 && Rate <= 45)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 46 && Rate <= 75)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 76 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +8
				if (Item->byGrade == 8)
				{
					if (Rate >= 0 && Rate <= 40)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 41 && Rate <= 70)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 71 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +9
				if (Item->byGrade == 9)
				{
					if (Rate >= 0 && Rate <= 35)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 36 && Rate <= 65)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 66 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +10
				if (Item->byGrade == 10)
				{
					if (Rate >= 0 && Rate <= 30)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 31 && Rate <= 60)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 61 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +11
				if (Item->byGrade == 11)
				{
					if (Rate >= 0 && Rate <= 25)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 26 && Rate <= 55)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 56 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +12
				if (Item->byGrade == 12)
				{
					if (Rate >= 0 && Rate <= 20)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 21 && Rate <= 50)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 51 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +13
				if (Item->byGrade == 13)
				{
					if (Rate >= 0 && Rate <= 15)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 16 && Rate <= 45)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 46 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +14
				if (Item->byGrade == 14)
				{
					if (Rate >= 0 && Rate <= 10)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 11 && Rate <= 40)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 41 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}

			}	
			////
			else if (StoneTbl->eItemType == eITEM_TYPE::ITEM_TYPE_GREEN_STONE)
			{
				//Sucess 100%
				//Sucess 100%
				if (Item->byGrade >= 0 && Item->byGrade <= 4)
				{
					Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
					Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
				}
				//Rate +5
				if (Item->byGrade == 5)
				{
					if (Rate >= 0 && Rate <= 60)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 61 && Rate <= 91)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 91 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +6
				if (Item->byGrade == 6)
				{
					if (Rate >= 0 && Rate <= 50)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 51 && Rate <= 80)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 81 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +7
				if (Item->byGrade == 7)
				{
					if (Rate >= 0 && Rate <= 45)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 46 && Rate <= 75)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 76 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +8
				if (Item->byGrade == 8)
				{
					if (Rate >= 0 && Rate <= 40)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 41 && Rate <= 70)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 71 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +9
				if (Item->byGrade == 9)
				{
					if (Rate >= 0 && Rate <= 35)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 36 && Rate <= 65)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 66 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +10
				if (Item->byGrade == 10)
				{
					if (Rate >= 0 && Rate <= 30)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 31 && Rate <= 60)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 61 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +11
				if (Item->byGrade == 11)
				{
					if (Rate >= 0 && Rate <= 25)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 26 && Rate <= 55)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 56 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +12
				if (Item->byGrade == 12)
				{
					if (Rate >= 0 && Rate <= 20)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 21 && Rate <= 50)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 51 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +13
				if (Item->byGrade == 13)
				{
					if (Rate >= 0 && Rate <= 15)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 16 && Rate <= 45)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 46 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
				//Rate +14
				if (Item->byGrade == 14)
				{
					if (Rate >= 0 && Rate <= 10)
					{
						Upgrade.Grade = Item->byGrade + GradeAdvacedStone;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 11 && Rate <= 40)
					{
						Upgrade.Grade = Item->byGrade - 1;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail
					}
					if (Rate >= 41 && Rate <= 100)
					{
						Upgrade.Grade = 0;
						Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}
			}
			//if  have White Stone
			if (WhiteStone != NULL && WhiteStoneTbl != NULL)
			{
				 if (WhiteStoneTbl->eItemType == eITEM_TYPE::ITEM_TYPE_WHITE_STONE)
				{
					 if (Upgrade.UpgradeResult == GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE)
					{
						 Upgrade.Grade = Item->byGrade;
						 Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE;//Fail Card
					}
					if (Upgrade.UpgradeResult == GAME_ITEM_UPGRADE_FAIL)
					{
						 Upgrade.Grade = Item->byGrade - GradeAdvacedStone;
						 Upgrade.UpgradeResult = GAME_ITEM_UPGRADE_FAIL;//Broken Card
					}
				}

				Upgrade.WhiteStonePlace = req->WhiteStonePlace;
				Upgrade.WhiteStonePos = req->WhiteStonePos;
				Upgrade.WhiteStackCount = WhiteStone->byStackcount - 1;
			}
			//Update Stack Normal Stone
			Upgrade.StoneStackCount = Stone->byStackcount - 1;	
			//Grade Overflow
			if (Upgrade.Grade >= 15)
			{
				Upgrade.Grade = 15;
			}
			//if stack = 0 delet NormalStone on Db
			if (Upgrade.StoneStackCount <= 0 || Stone->byStackcount <= 0)
			{
				inventoryManager.DeleteItem(Stone->byPlace, Stone->byPos, Stone->handle);
			}
			//if stack = 0 delet  WhiteStone on db
			if (WhiteStone != NULL)
			{
				if (Upgrade.WhiteStackCount <= 0 || WhiteStone->byStackcount <= 0)
				{
					inventoryManager.DeleteItem(WhiteStone->byPlace, WhiteStone->byPos, WhiteStone->handle);
				}
			}	
			if (Upgrade.Grade >= 12 && Upgrade.Grade != Item->byGrade)
			{
				sTU_BROADCASTING_SYSTEM_NFY Notify;
				memset(&Notify, 0, sizeof(sTU_BROADCASTING_SYSTEM_NFY));
				std::wstring   _charName;
				Notify.wOpCode = TU_BROADCASTING_SYSTEM_NFY;
				Notify.wPacketSize = sizeof(sTU_BROADCASTING_SYSTEM_NFY) - 2;
				Notify.Count = 1;
				_charName = s2ws(GetName());
				wcscpy_s(Notify.awchSenderCharName, MAX_SIZE_CHAR_NAME_UNICODE + 1, (_charName).c_str());
				Notify.ItemID = Item->tblidx;
				Notify.Grade = Upgrade.Grade;
				//SendPacket((char*)&Notify, sizeof(sTU_BROADCASTING_SYSTEM_NFY));
				sWorld.SendToAll((char*)&Notify, sizeof(sTU_BROADCASTING_SYSTEM_NFY));
			}		
			//Update Value in Table
			Item->byGrade = Upgrade.Grade;
			Stone->byStackcount = Upgrade.StoneStackCount;
			Stone->byGrade = 0;
			if (WhiteStone != NULL)
			{
				WhiteStone->byStackcount = Upgrade.WhiteStackCount;
				WhiteStone->byGrade = 0;
			}
			SendPacket((char*)&Upgrade, sizeof(sGU_ITEM_UPGRADE_WORK_RES));
				
		}
	}
}

void Player::SendItemUpgradeByCoupon(Packet & packet)
{
	sUG_ITEM_UPGRADE_BY_COUPON_REQ *req = (sUG_ITEM_UPGRADE_BY_COUPON_REQ*)packet.GetPacketBuffer();
	sITEM_PROFILE *Item = NULL;
	sITEM_PROFILE *Ticket = NULL;
	sITEM_TBLDAT *ItemTbl = NULL;
	sITEM_TBLDAT *TicketTbl = NULL;
	Item = this->inventoryManager.GetItemAtPlaceAndPost(req->byItemPlace, req->byItemPos);
	Ticket = this->inventoryManager.GetItemAtPlaceAndPost(req->TicketPlace, req->TicketPos);
	if (Item != NULL && Ticket != NULL)
	{
		//Get Item Data
		if ((ItemTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Item->tblidx)) == NULL)
		{
			ItemTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Item->tblidx);
		}
		//Get Ticket Data
		if ((TicketTbl = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Ticket->tblidx)) == NULL)
		{
			TicketTbl = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Ticket->tblidx);
		}
		if (ItemTbl != NULL && TicketTbl != NULL)
		{			
			//Funcion
			sGU_ITEM_UPGRADE_BY_COUPON_RES TicketUpgrade;
			TicketUpgrade.wOpCode = GU_ITEM_UPGRADE_BY_COUPON_RES;
			TicketUpgrade.wPacketSize = sizeof(sGU_ITEM_UPGRADE_BY_COUPON_RES) - 2;
			TicketUpgrade.ResultCode = GAME_SUCCESS;
			TicketUpgrade.ItemPlace = req->byItemPlace;
			TicketUpgrade.ItemPos = req->byItemPos;
			TicketUpgrade.TicketPlace = req->TicketPlace;
			TicketUpgrade.TicketPos = req->TicketPos;
			TicketUpgrade.Grade = TicketTbl->tbxCharm;
			TicketUpgrade.TicketCount = 0;
			TicketUpgrade.TimeStart = 0;
			TicketUpgrade.TimeEnd = 0;
			TicketUpgrade.Unk = Ticket->byStackcount - 1;
			TicketUpgrade.Unk2 = 2;		
			

			//Update Values in sITEM_PROFILE
			Item->byGrade = TicketUpgrade.Grade;
			Ticket->byStackcount = TicketUpgrade.Unk;
			Ticket->byGrade = 0;

			if (TicketUpgrade.Unk <= 0 || Ticket->byStackcount <= 0)
			{
				inventoryManager.DeleteItem(Ticket->byPlace, Ticket->byPos, Ticket->handle);
			}

			SendPacket((char*)&TicketUpgrade, sizeof(sGU_ITEM_UPGRADE_BY_COUPON_RES));
		}
	}
}

void Player::SendLearnSkillByItem(Packet & packet)
{
	sUG_SKILL_LEARN_BY_ITEM_REQ *req = (sUG_SKILL_LEARN_BY_ITEM_REQ*)packet.GetPacketBuffer();
	printf("pos %d \n place %d \n", req->itemPos, req->itemPlace);
	sITEM_PROFILE *Item = NULL;
	sITEM_TBLDAT *ItemData = NULL;
	Item = this->inventoryManager.GetItemAtPlaceAndPost(req->itemPlace, req->itemPos);
	if (Item != NULL)
	{
		//Get Item Data
		if ((ItemData = (sITEM_TBLDAT*)sTBM.GetItemTable()->FindData(Item->tblidx)) == NULL)
		{
			ItemData = (sCASHITEM_TBLDAT*)sTBM.GetCashItemTable()->FindData(Item->tblidx);
		}
		if (ItemData != NULL)
		{				
			UseItemTable * UseItemTable = sTBM.GetUseItemTable();
			sUSE_ITEM_TBLDAT * UseItemTBLIDX = reinterpret_cast<sUSE_ITEM_TBLDAT*>(UseItemTable->FindData(ItemData->tbxUseItem));
			
			if (UseItemTBLIDX != NULL)
			{
				SkillTable * skillTable = sTBM.GetSkillTable();
				sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(UseItemTBLIDX->adSystemEffectValue[0]));
				if (skillDataOriginal != NULL)
				{
					if (GetClassFlag(GetAttributesManager()->PlayerClassID, ITEM_TYPE_UNKNOWN) == skillDataOriginal->dwPC_Class_Bit_Flag)
					{
						if (skillDataOriginal->bySkill_Grade == 1 && skillDataOriginal->bySkill_Class != eSKILL_CLASS::SKILL_CLASS_HTB && skillManager.isSkillLearned(skillDataOriginal->tblidx) == false)
						{
							printf("tbxUseItem %d \n ", UseItemTBLIDX->adSystemEffectValue[0]);
							m_session->LearnSkill(skillDataOriginal->tblidx);
						}
					}
				}
							
			}
		}
	}
}
