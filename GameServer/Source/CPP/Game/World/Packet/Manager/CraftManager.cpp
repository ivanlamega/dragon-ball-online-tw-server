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


void WorldSession::SendHoiPoiMixCreate(Packet & packet)
{
	sUG_HOIPOIMIX_ITEM_CREATE_EX_REQ *req = (sUG_HOIPOIMIX_ITEM_CREATE_EX_REQ*)packet.GetPacketBuffer();

	printf("Recipe ID %d \n", req->RecipeID);
	sITEM_RECIPE_TBLDAT* tbldat = (sITEM_RECIPE_TBLDAT*)sTBM.GetItemRecipeTable()->FindData(req->RecipeID);
	if (tbldat == NULL)
	{
		tbldat = (sITEM_RECIPE_TBLDAT2*)sTBM.GetItemRecipeTable2()->FindData(req->RecipeID);
	}
	if (tbldat != NULL)
	{
		//printf("IS NoT NuLL %d ");
		sITEM_PROFILE createdItem;
		WORD result = _player->GetInventoryManager()->PerformShopBuy(tbldat->asCreateItemTblidx[0].itemTblidx, tbldat->asCreateItemTblidx[0].itemRate, createdItem);
		if (result == GAME_SUCCESS && createdItem.tblidx != INVALID_TBLIDX)
		{
			SendItemCreate(&createdItem);
		}

		sGU_HOIPOIMIX_ITEM_MAKE_RES CreateItemCraft;

		CreateItemCraft.wOpCode = GU_HOIPOIMIX_ITEM_MAKE_RES;
		CreateItemCraft.wPacketSize = sizeof(sGU_HOIPOIMIX_ITEM_MAKE_RES) - 2;
		CreateItemCraft.wResultCode = GAME_SUCCESS;
		CreateItemCraft.bySuccessResult = eITEM_MIX_RESULT_TYPE::ITEM_MIX_RESULT_TYPE_SUCCESS;
		CreateItemCraft.objHandle = req->Handle;
		CreateItemCraft.recipeTblidx = req->RecipeID;
		CreateItemCraft.itemHandle = createdItem.handle;
		SendPacket((char*)&CreateItemCraft, sizeof(sGU_HOIPOIMIX_ITEM_MAKE_RES));
	}
}