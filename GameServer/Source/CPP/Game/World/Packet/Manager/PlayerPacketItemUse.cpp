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
#include <XmlParser2/XmlParser2.h>
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
			for (int Effect = 0; Effect < 2; Effect++)
			{
				sSYSTEM_EFFECT_TBLDAT * SystemEffectData = NULL;
				SystemEffectData = (sSYSTEM_EFFECT_TBLDAT*)sTBM.GetSystemEffectTable()->FindData(UseItemData->adwSystemEffect[Effect]);
				if (SystemEffectData != NULL)
				{	
					UseItem.tblidxItem = UseItemData->tblidx;
					UseItem.byPlace = Item->byPlace;
					UseItem.byPos = Item->byPos;
					UseItem.wResultCode = GAME_ITEM_CANT_USE_FOR_SOME_REASON;
				//	printf("effectCode %d \n ", SystemEffectData->effectCode);
					switch (SystemEffectData->effectCode)
					{
						//eSYSTEM_EFFECT_CODE
						case eSYSTEM_EFFECT_CODE::ACTIVE_HEAL_OVER_TIME://Food LP
						{	
							if (GetAttributesManager()->LpFoodIsActive == false)
							{
								UseItem.wResultCode = GAME_SUCCESS;

								Acionitem.handle = GetHandle();
								Acionitem.wResultCode = GAME_SUCCESS;
								Acionitem.dwLpEpEventId = INVALID_TBLIDX;
								Acionitem.itemTblidx = UseItemData->tblidx;
								Acionitem.bySkillResultCount = 1;
								Acionitem.aSkillResult->hTarget = GetHandle();
								SendPacket((char*)&Acionitem, sizeof(sGU_CHAR_ACTION_ITEM));//Error not fount come from it because is not handle

								sGU_BUFF_REGISTERED pBuffData;
								memset(&pBuffData, 0, sizeof(sGU_BUFF_REGISTERED));
								//memset(&pBuffData, INVALID_TBLIDX, sizeof(sGU_BUFF_REGISTERED));
								pBuffData.wOpCode = GU_BUFF_REGISTERED;
								pBuffData.wPacketSize = sizeof(sGU_BUFF_REGISTERED) - 2;
								pBuffData.tblidx = UseItemData->tblidx;
								pBuffData.hHandle = GetHandle();
								pBuffData.bySourceType = 1;
								pBuffData.dwInitialDuration = UseItemData->dwCooldownMs;
								pBuffData.dwTimeRemaining = UseItemData->dwKeepTimeMs;//Time
								pBuffData.isactive = true;
								pBuffData.BuffType.BuffEffectType = 5;
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.TbxCommonConfig = UseItemData->adwSystemEffect[Effect];
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainValue = UseItemData->adSystemEffectValue[Effect];
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
								GetAttributesManager()->sFoodInfo[FreePlace].FoodItemID = UseItemData->tblidx;
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
							if (GetAttributesManager()->EpFoodIsActive == false)
							{								

								UseItem.wResultCode = GAME_SUCCESS;

								Acionitem.handle = GetHandle();
								Acionitem.wResultCode = GAME_SUCCESS;
								Acionitem.dwLpEpEventId = INVALID_TBLIDX;
								Acionitem.itemTblidx = UseItemData->tblidx;
								Acionitem.bySkillResultCount = 1;
								Acionitem.aSkillResult->hTarget = GetHandle();
								SendPacket((char*)&Acionitem, sizeof(sGU_CHAR_ACTION_ITEM));

								sGU_BUFF_REGISTERED pBuffData;
								memset(&pBuffData, 0, sizeof(sGU_BUFF_REGISTERED));
								//memset(&pBuffData, INVALID_TBLIDX, sizeof(sGU_BUFF_REGISTERED));
								pBuffData.wOpCode = GU_BUFF_REGISTERED;
								pBuffData.wPacketSize = sizeof(sGU_BUFF_REGISTERED) - 2;
								pBuffData.tblidx = UseItemData->tblidx;
								pBuffData.hHandle = GetHandle();
								pBuffData.bySourceType = 1;
								pBuffData.dwInitialDuration = UseItemData->dwCooldownMs;
								pBuffData.dwTimeRemaining = UseItemData->dwKeepTimeMs;//Time
								pBuffData.isactive = true;
								pBuffData.BuffType.BuffEffectType = 5;
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.TbxCommonConfig = UseItemData->adwSystemEffect[Effect];
								pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainValue = UseItemData->adSystemEffectValue[Effect];
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
																
								GetAttributesManager()->sFoodInfo[FreePlace].FoodItemID = UseItemData->tblidx;
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
						case eSYSTEM_EFFECT_CODE::ACTIVE_SCRIPT_EXECUTE_WPS_LOC:
						{
							
							if (static_cast<NTL_TS_T_ID>(UseItemData->adSystemEffectValue[0]) == 6003)
							{
								std::vector<TBLIDX> spawns = sTBM.GetMobSpawnTable(800000)->FindSpawnByObjectTblidx(5011201);
								for (std::vector<TBLIDX>::size_type i = 0; i != spawns.size(); i++)
								{
									sSPAWN_TBLDAT* spawn = (sSPAWN_TBLDAT*)sTBM.GetMobSpawnTable(800000)->FindData(spawns[i]);
									if (spawn)
									{
										GetAttributesManager()->growUpInfo.mobTblidx = 5011201;
										GetAttributesManager()->growUpInfo.maxKill = 4;
										GetAttributesManager()->growUpInfo.countKill = 0;
										m_session->SpawnMobForQuest(5011201, INVALID_TBLIDX, 0);
									}
								}
							}
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_QUEST_TRIGGER:
						{
							sGU_TS_EXCUTE_TRIGGER trigger;
							trigger.wOpCode = GU_TS_EXCUTE_TRIGGER;
							trigger.wPacketSize = sizeof(sGU_TS_EXCUTE_TRIGGER) - 2;
							trigger.tId = static_cast<NTL_TS_T_ID>(UseItemData->adSystemEffectValue[0]);
							trigger.byTsType = TS_TYPE_QUEST_CS;
							trigger.hHandle = Item->handle;
							SendPacket((char*)&trigger, sizeof(sGU_TS_EXCUTE_TRIGGER));
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_OBJECT_TRIGGER:
						{
							TBLIDX objTblidx = INVALID_TBLIDX;
							Map* map = GetMap();
							//sLog.outDebug("Request handle interaction == %d", req->hTarget);
							if (map)
							{
								WorldObjectRefManager ref = map->GetWorldObject();
								for (auto reference = ref.begin(); reference != ref.end(); ++reference)
								{
									if (reference->getSource()->GetHandle() == req->hTarget)
									{
										objTblidx = ((WorldObject*)reference->getSource())->GetTblidx();
										sLog.outString("FOUNDED object tblidx %d hTarget %d", objTblidx, req->hTarget);

										// SUB CLASS
										
										if (GetAttributesManager()->questSubCls.curQuestId != 0 && GetAttributesManager()->questSubCls.curQuestId != INVALID_TBLIDX)
										{
											sLog.outError("QUEST ID: %d", GetAttributesManager()->questSubCls.curQuestId);
											sLog.outDebug("Item Tblidx %d %d", GetAttributesManager()->questSubCls.useItemTblidx == Item->tblidx,
												((WorldObject*)reference->getSource())->GetTblidx());

											QuestData questDat;
											questDat.QuestID = GetAttributesManager()->questSubCls.curQuestId;
											if (m_session->FindObjectTriggerInformation(&questDat, req->hTarget, objTblidx) == RESULT_SUCCESS)
											{
												sGU_ITEM_USE_RES res;
												res.wOpCode = GU_ITEM_USE_RES;
												res.wPacketSize = sizeof(sGU_ITEM_USE_RES) - 2;
												res.wResultCode = RESULT_SUCCESS;
												res.tblidxItem = Item->tblidx;
												res.byPlace = req->byPlace;
												res.byPos = req->byPos;
												SendPacket((char*)&res, sizeof(sGU_ITEM_USE_RES));
												sLog.outDebug("Item trigger: %d %d %d", res.tblidxItem, req->hTarget, objTblidx);

												GetInventoryManager()->DeleteItem(Item->byPlace, Item->byPos, Item->handle);
												break;
											}
										}
										// SUB CLASS

										for (int i = 0; i <= 30; i++)
										{
											//--------------------------------
											if (GetAttributesManager()->QuestDat[i].QuestID == 0)
											{
												continue;
											}
											sLog.outDebug("EVT TYPE %d", GetAttributesManager()->QuestDat[i].evtDataType);
											switch (GetAttributesManager()->QuestDat[i].evtDataType)
											{
												case eSTOC_EVT_DATA_TYPE_CUSTOM_EVT_CNT:
												{
													for (int slot = 0; slot < GetAttributesManager()->QuestDat[i].uEvtData.MAX_CUSTOM_EVT_CNT; slot++)
													{
														sLog.outDebug("EVT COUNT %d", GetAttributesManager()->QuestDat[i].uEvtData.sCustomEvtCnt[slot].nCurCnt);

														sLog.outError("QUEST ID: %d", GetAttributesManager()->QuestDat[i].QuestID);
														if (GetAttributesManager()->QuestDat[i].uEvtData.sCustomEvtCnt[slot].nCurCnt <
															GetAttributesManager()->QuestDat[i].uEvtData.sCustomEvtCnt[slot].nMaxCnt)
														{
															sLog.outDebug("Item Tblidx %d %d", GetAttributesManager()->QuestDat[i].uEvtData.sCustomEvtCnt[slot].uiCustomEvtID,
																((WorldObject*)reference->getSource())->GetTblidx());

															if (m_session->FindObjectTriggerInformation(&GetAttributesManager()->QuestDat[i], req->hTarget, objTblidx) == RESULT_SUCCESS)
															{
																sGU_ITEM_USE_RES res;
																res.wOpCode = GU_ITEM_USE_RES;
																res.wPacketSize = sizeof(sGU_ITEM_USE_RES) - 2;
																res.wResultCode = RESULT_SUCCESS;
																res.tblidxItem = Item->tblidx;
																res.byPlace = req->byPlace;
																res.byPos = req->byPos;
																SendPacket((char*)&res, sizeof(sGU_ITEM_USE_RES));
																sLog.outDebug("Item trigger: %d %d %d", res.tblidxItem, req->hTarget, objTblidx);
															}

														}
													}
												}
											}
										}
									}
								}
							}
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
					/*	case eSYSTEM_EFFECT_CODE::ACTIVE_VEHICLE: // Gives a gameserver crash.
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
							SetState(eCHARSTATE::CHARSTATE_STANDING);
							UpdateAspectState(eASPECTSTATE::ASPECTSTATE_VEHICLE);
							break;
						}*/
						case eSYSTEM_EFFECT_CODE::ACTIVE_RECIPE_UPDATE://Regista a Receita de Craft
						{
							UseItem.wResultCode = GAME_SUCCESS;
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
							sGU_HOIPOIMIX_RECIPE_REG_NFY HoiPoiReg;
							HoiPoiReg.wOpCode = GU_HOIPOIMIX_RECIPE_REG_NFY;
							HoiPoiReg.wPacketSize = sizeof(sGU_HOIPOIMIX_RECIPE_REG_NFY) - 2;

							HoiPoiReg.recipeTblidx = UseItemData->tblidx;
							sDB.LearnRecipe(charid, HoiPoiReg.recipeTblidx);
							SendPacket((char*)&HoiPoiReg, sizeof(sGU_HOIPOIMIX_RECIPE_REG_NFY));
							break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_AIR_MOVE_DASH_ACCEL://Fly scroll
						{						
						break;
						}
						case eSYSTEM_EFFECT_CODE::ACTIVE_EXP_BOOSTER://ExP Booster
						{	
							/*UseItem.wResultCode = GAME_SUCCESS;

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
							pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.TbxCommonConfig = UseItemData->adwSystemEffect[i]; // [i] error
							pBuffData.BuffType.sBuffTypeLP_EP_AutoRecover.dwRemainValue = UseItemData->adSystemEffectValue[i]; // [i] error
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
							}	*/					
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
								if (GetPcProfile()->byLevel >= UseItemData->adSystemEffectValue[Effect])
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
									LevelUpByComand(UseItemData->adSystemEffectValue[Effect]);
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
								SendAddTitle(UseItemData->adSystemEffectValue[Effect]);
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
								sql::ResultSet* result = sDB.executes("UPDATE characters SET IsAdult = 1 WHERE CharacterID = '%d';", GetCharacterID()); // Saving Adult to database
							}
							else
							{
								ConvertAdult(false);
								sql::ResultSet* result = sDB.executes("UPDATE characters SET IsAdult = 0 WHERE CharacterID = '%d';", GetCharacterID()); // Saving the reverse to database
							}
							UseItem.wResultCode = GAME_SUCCESS;
							break;
						}
						/*case eSYSTEM_EFFECT_CODE::ACTIVE_MALE_FEMALE_TRANSFORM:// Gender Changer
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
							if (GetPcProfile()->bGenderID == false)
							{
								ConvertFemale(true);
								sql::ResultSet* result = sDB.executes("UPDATE characters SET GenderID = 1 WHERE CharacterID = '%d';", GetCharacterID()); // Saving Female to database
							}
							else
							{
								ConvertFemale(false);
								sql::ResultSet* result = sDB.executes("UPDATE characters SET GenderID = 0 WHERE CharacterID = '%d';", GetCharacterID()); // Saving the reverse to database
							}
							UseItem.wResultCode = GAME_SUCCESS;
							break;
						}*/

					}
				}
			}
			
			SendPacket((char*)&UseItem, sizeof(sGU_ITEM_USE_RES));
			
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
	sFORMULA_TBLDAT *EnchantTable = NULL;
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
			SetStatsByEquip(ItemTbl->eItemType);
			sGU_ITEM_SOCKET_INSERT_BEAD_RES DoggiBallEffect;
			memset(&DoggiBallEffect, INVALID_TBLIDX, sizeof(sGU_ITEM_SOCKET_INSERT_BEAD_RES));
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
			
			int StatsCounts = 1 + rand() % 5;
			
			for (int i = 0; i <= StatsCounts; i++)
			{
				int randommstats = rand() % GetAttributesManager()->countstats;
				if (GetAttributesManager()->Stats[randommstats] != 0 && GetAttributesManager()->Stats[randommstats] != INVALID_TBLIDX)
				{
					EnchantTable = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(GetAttributesManager()->Stats[randommstats]);
					if (EnchantTable != NULL)
					{
						float randStats = 1 + rand() % static_cast<int>(Dbo_GetItemsStatsPoints(ItemTbl->eRank, ItemTbl->byNeedLevel) / EnchantTable->wEnchantValue) + 1;
						DoggiBallEffect.DoggiEffectType = GetAttributesManager()->Stats[randommstats];
						DoggiBallEffect.DoggiEffectValue = randStats;//
						GetAttributesManager()->Stats[randommstats] = INVALID_TBLIDX;
						
					}
				}
			}
			
			for (int i = 0; i <= 2; i++)
			
			DoggiBallEffect.DoggiEffectValue1 = INVALID_TBLIDX;
			DoggiBallEffect.DoggiEffectType1 = INVALID_TBLIDX;			
			DoggiBallEffect.DoggiEffectType = DoggiBallEffect.DoggiEffectType;
			DoggiBallEffect.DoggiEffectValue = DoggiBallEffect.DoggiEffectValue;
			

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
void Player::SetStatsByEquip(BYTE ItemType)
{	
	if (ItemType == eITEM_TYPE::ITEM_TYPE_GLOVE)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::STR_Incress;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Focus_Incress;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Soul_Incress;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[8] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[9] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[10] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;		
		GetAttributesManager()->countstats = 11;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_STAFF)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::STR_Incress;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Focus_Incress;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Soul_Incress;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[8] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[9] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[10] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 11;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_CLAW)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_AXE)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_SCROLL)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}	
	if (ItemType == eITEM_TYPE::ITEM_TYPE_GEM)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_STICK)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_SWORD)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_FAN)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_WAND)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_INSTRUMENT)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_CLUB)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_DRUM)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_MASK)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_NECKLACE)//not complete
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::STR_Incress;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Dex_Incress;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Eng_Incress;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Focus_Incress;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::S_Defense_Prop;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::W_Defense_Prop;
		GetAttributesManager()->Stats[8] = eSTATSATRIBUTES::E_Defense_Prop;
		GetAttributesManager()->Stats[9] = eSTATSATRIBUTES::F_Defense_Prop;
		GetAttributesManager()->Stats[10] = eSTATSATRIBUTES::LP_Absorption_Increase;
		GetAttributesManager()->Stats[11] = eSTATSATRIBUTES::EP_Absorption_Increase;
		GetAttributesManager()->Stats[12] = eSTATSATRIBUTES::Skill_Cooldown_Time_Decrease;
		GetAttributesManager()->Stats[13] = eSTATSATRIBUTES::Prop_attack_Defense;
		GetAttributesManager()->Stats[14] = eSTATSATRIBUTES::H_attack_prop;
		GetAttributesManager()->Stats[15] = eSTATSATRIBUTES::S_attack_prop;
		GetAttributesManager()->Stats[16] = eSTATSATRIBUTES::W_attack_prop;
		GetAttributesManager()->Stats[17] = eSTATSATRIBUTES::E_attack_prop;
		GetAttributesManager()->Stats[18] = eSTATSATRIBUTES::F_attack_prop;
		GetAttributesManager()->countstats = 19;		
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_EARRING)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::STR_Incress;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Dex_Incress;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Eng_Incress;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Focus_Incress;//H prop
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::S_Defense_Prop;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::W_Defense_Prop;
		GetAttributesManager()->Stats[8] = eSTATSATRIBUTES::E_Defense_Prop;
		GetAttributesManager()->Stats[9] = eSTATSATRIBUTES::F_Defense_Prop;
		GetAttributesManager()->Stats[10] = eSTATSATRIBUTES::LP_Absorption_Increase;
		GetAttributesManager()->Stats[11] = eSTATSATRIBUTES::EP_Absorption_Increase;
		GetAttributesManager()->Stats[12] = eSTATSATRIBUTES::Skill_Cooldown_Time_Decrease;
		GetAttributesManager()->Stats[13] = eSTATSATRIBUTES::Prop_attack_Defense;
		GetAttributesManager()->Stats[14] = eSTATSATRIBUTES::H_attack_prop;
		GetAttributesManager()->Stats[15] = eSTATSATRIBUTES::S_attack_prop;
		GetAttributesManager()->Stats[16] = eSTATSATRIBUTES::W_attack_prop;
		GetAttributesManager()->Stats[17] = eSTATSATRIBUTES::E_attack_prop;
		GetAttributesManager()->Stats[18] = eSTATSATRIBUTES::F_attack_prop;	
		GetAttributesManager()->countstats = 19;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_JACKET)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Maximum_LP_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Maximum_EP_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::CON_Incress;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Focus_Incress;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Dex_Incress;		
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Eng_Incress;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Recover_LP_From_dmg_taken;
		GetAttributesManager()->Stats[8] = eSTATSATRIBUTES::Recover_EP_From_dmg_taken;
		GetAttributesManager()->Stats[9] = eSTATSATRIBUTES::Recover_LP_percent_when_receiving_damage;
		GetAttributesManager()->Stats[10] = eSTATSATRIBUTES::Recover_EP_percent_when_receiving_damage;
		GetAttributesManager()->Stats[11] = eSTATSATRIBUTES::Anti_Critic;
		GetAttributesManager()->countstats = 12;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_PANTS)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Maximum_LP_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Maximum_EP_Increase;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::CON_Incress;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Focus_Incress;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::STR_Incress;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Recover_LP_From_dmg_taken;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Recover_EP_From_dmg_taken;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Recover_LP_percent_when_receiving_damage;
		GetAttributesManager()->Stats[8] = eSTATSATRIBUTES::Recover_EP_percent_when_receiving_damage;
		GetAttributesManager()->countstats = 9;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_BOOTS)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::CON_Incress;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Focus_Incress;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Dex_Incress;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Soul_Incress;
		GetAttributesManager()->Stats[4] = eSTATSATRIBUTES::Bleed_def_rate;
		GetAttributesManager()->Stats[5] = eSTATSATRIBUTES::Poison_def_rate;
		GetAttributesManager()->Stats[6] = eSTATSATRIBUTES::Burn_Def_Rate;
		GetAttributesManager()->Stats[7] = eSTATSATRIBUTES::Movement_Speed_Increase;
		GetAttributesManager()->countstats = 8;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_COSTUME)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::CON_Incress;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Recover_LP_percent_when_receiving_damage;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Movement_Speed_Increase;
		GetAttributesManager()->countstats = 3;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_HAIR)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Phy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Soul_Incress;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->countstats = 3;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_ACCESSORY1)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Focus_Incress;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Skill_Cooldown_Time_Decrease;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Attack_Speed_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->countstats = 4;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_ACCESSORY2)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Physical_Crit_Rate_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Dex_Incress;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Hit_Rate_Increase;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::Energy_Crit_Rate_Increase;
		GetAttributesManager()->countstats = 4;
	}
	if (ItemType == eITEM_TYPE::ITEM_TYPE_ACCESSORY3)
	{
		GetAttributesManager()->Stats[0] = eSTATSATRIBUTES::Energy_Attack_Increase;
		GetAttributesManager()->Stats[1] = eSTATSATRIBUTES::Energy_Critical_Damage_Percent;
		GetAttributesManager()->Stats[2] = eSTATSATRIBUTES::Recover_EP_percent_when_receiving_damage;
		GetAttributesManager()->Stats[3] = eSTATSATRIBUTES::STR_Incress;
		GetAttributesManager()->countstats = 4;
	}
}
void Player::ItemOptionsChange(Packet pPacket)
{
	sUG_ITEM_CHANGE_OPTION_REQ *req = (sUG_ITEM_CHANGE_OPTION_REQ*)pPacket.GetPacketBuffer();

	sITEM_PROFILE *Item = NULL;
	sITEM_PROFILE *Box = NULL;
	sITEM_TBLDAT *ItemTbl = NULL;
	sITEM_TBLDAT *BoxTbl = NULL;
	sFORMULA_TBLDAT *EnchantTable = NULL;
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
			SetStatsByEquip(ItemTbl->eItemType);
			sGU_ITEM_CHANGE_OPTION_RES ItemEffect;
			memset(&ItemEffect, INVALID_TBLIDX, sizeof(sGU_ITEM_CHANGE_OPTION_RES));
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
			//printf("Item Option %d \n", ItemTbl->tbxItemOption);
			int StatsCounts = 1 + rand() % 5;
			int count = 0;
			for (int i = 0; i <= StatsCounts; i++)
			{
				int randommstats = rand()% GetAttributesManager()->countstats;
				if (GetAttributesManager()->Stats[randommstats] != 0 && GetAttributesManager()->Stats[randommstats] != INVALID_TBLIDX)
				{	
					EnchantTable = (sFORMULA_TBLDAT*)sTBM.GetFormulaTable()->FindData(GetAttributesManager()->Stats[randommstats]);
					if(EnchantTable != NULL)
					{
						float randStats = 1 + rand() % static_cast<int>(Dbo_GetItemsStatsPoints(ItemTbl->eRank, ItemTbl->byNeedLevel) / EnchantTable->wEnchantValue) + 1;
						ItemEffect.aitemEffect[count].wType = GetAttributesManager()->Stats[randommstats];
						ItemEffect.aitemEffect[count].dwValue = randStats;//
						GetAttributesManager()->Stats[randommstats] = INVALID_TBLIDX;
						//printf("Item Effect %d number %d \n", ItemEffect.aitemEffect[count].wType, count);
						count += 1;
					}
				}				
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
			if (Box->byStackcount <= 1)
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
				Box->byStackcount = 0;
				ItemEffect.ByCount = 0;
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
//	printf(" White Place %d \n White pos %d \n", req->WhiteStonePlace, req->WhiteStonePos);
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
					if (Rate >= 0 && Rate <= 50)
					{
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
					if (Rate >= 0 && Rate <= 60)
					{
						Upgrade.Grade = Item->byGrade + 1;
						Upgrade.UpgradeResult = GAME_SUCCESS;//Success Card
					}
					if (Rate >= 61 && Rate <= 90)
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
						Upgrade.Grade = Item->byGrade + 1;
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
	sGU_SKILL_LEARN_BY_ITEM_RES res;
	res.wOpCode = GU_SKILL_LEARN_BY_ITEM_RES;
	res.wPacketSize = sizeof(sGU_SKILL_LEARN_BY_ITEM_RES) - 2;
	res.wResultCode = GAME_FAIL;
	sGU_ITEM_STACK_UPDATE ItmStackUpdate;
	ItmStackUpdate.wOpCode = GU_ITEM_STACK_UPDATE;
	ItmStackUpdate.wPacketSize = sizeof(sGU_ITEM_STACK_UPDATE) - 2;
	sGU_ITEM_DELETE itmDelete;
	itmDelete.wOpCode = GU_ITEM_DELETE;
	itmDelete.wPacketSize = sizeof(sGU_ITEM_DELETE) - 2;
	//printf("pos %d \n place %d \n", req->itemPos, req->itemPlace);
	sITEM_PROFILE *Item = NULL;
	sITEM_TBLDAT *ItemData = NULL;
	sUSE_ITEM_TBLDAT * UseItemData = NULL;
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
			if ((UseItemData = (sUSE_ITEM_TBLDAT*)sTBM.GetUseItemTable()->FindData(ItemData->tbxUseItem)) == NULL)
			{
				UseItemData = (sUSE_ITEM_TBLDAT2*)sTBM.GetUseItemTable2()->FindData(ItemData->tbxUseItem);
			}			
			if (UseItemData != NULL)
			{								
				SkillTable * skillTable = sTBM.GetSkillTable();
				sSKILL_TBLDAT * skillDataOriginal = reinterpret_cast<sSKILL_TBLDAT*>(skillTable->FindData(UseItemData->adSystemEffectValue[0]));
				if (skillDataOriginal != NULL)
				{
					if (GetClassFlag(GetAttributesManager()->PlayerClassID, ITEM_TYPE_UNKNOWN) == skillDataOriginal->dwPC_Class_Bit_Flag)
					{						
						//	printf("adSystemEffectValue %f \n ", UseItemData->adSystemEffectValue[0]);
						if (GetPcProfile()->byLevel >= ItemData->byNeedLevel)
						{
							if (skillDataOriginal->bySkill_Grade == 1 && skillDataOriginal->bySkill_Class != eSKILL_CLASS::SKILL_CLASS_HTB && skillManager.isSkillLearned(skillDataOriginal->tblidx) == false)
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
								res.wResultCode = GAME_SUCCESS;
								skillManager.LoadSkill(charid);
								int Slotid = NULL;
								sGU_SKILL_LEARNED_NFY nfy;
								nfy.bySlot = skillManager.getSkillsCount() + 1;//Need set frist skill to 0 when Reset skills;
								nfy.skillId = skillDataOriginal->tblidx;
								nfy.wOpCode = GU_SKILL_LEARNED_NFY;
								nfy.wPacketSize = sizeof(sGU_SKILL_LEARNED_NFY) - 2;
								nfy.wResultCode = GAME_SUCCESS;
								SendPacket((char*)&nfy, sizeof(sGU_SKILL_LEARNED_NFY));
								sDB.LearnSkill(nfy.skillId, GetCharacterID(), nfy.bySlot);
								//Load skill for can use after that
								skillManager.LoadSkill(charid);
								m_session->SendAvatarSkillInfo();
								m_session->SendUpdateSkillPassiveAtributeByID(nfy.skillId, false);
							}
							else
							{
								//Alardy got Skill
								res.wResultCode = GAME_SKILL_ALREADY_MASTERED_SKILL;
							}
						}
						else
						{							
							//Need More Level 
							res.wResultCode = GAME_ITEM_NEED_MORE_LEVEL;
						}
					}
					else
					{
						//Class Worong
						res.wResultCode = GAME_ITEM_CLASS_FAIL;
					}
					
				}
					//Skill Table mull		
			}
			//UseItem Table mull	
		}
		//ItemData Table mull	
	}
	//ItemBag mull	
	SendPacket((char*)&res, sizeof(sGU_SKILL_LEARN_BY_ITEM_RES));
}
