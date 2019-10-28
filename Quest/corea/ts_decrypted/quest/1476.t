CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1476;
	title = 147602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 147609;
				ctype = 1;
				idx = 1651102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 147608;
				gtype = 2;
				area = 147601;
				goal = 147604;
				grade = 132203;
				rwd = 100;
				sort = 147605;
				stype = 1;
				taid = 1;
				title = 147602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 147607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSCheckClrQst
			{
				and = "1452;";
			}
			CDboTSClickNPC
			{
				npcidx = 1651102;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 147608;
			gtype = 2;
			oklnk = 2;
			area = 147601;
			goal = 147604;
			sort = 147605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 147602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 147614;
			nextlnk = 254;
			rwdtbl = 147601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1352101;
			}
		}
	}
}

