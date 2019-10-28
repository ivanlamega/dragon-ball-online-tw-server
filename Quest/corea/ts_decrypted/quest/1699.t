CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1699;
	title = 169902;

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
				conv = 169909;
				ctype = 1;
				idx = 5311101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 169908;
				gtype = 1;
				area = 169901;
				goal = 169904;
				grade = 132203;
				rwd = 100;
				sort = 169905;
				stype = 2;
				taid = 1;
				title = 169902;
			}
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 169914;
			nextlnk = 254;
			rwdtbl = 169901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7135201;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 169907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5311101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1697;1698;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 169908;
			gtype = 1;
			oklnk = 2;
			area = 169901;
			goal = 169904;
			sort = 169905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 169902;
		}
	}
}

