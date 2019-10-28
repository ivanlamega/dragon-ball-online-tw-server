CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 776;
	title = 77602;

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
				conv = 77609;
				ctype = 1;
				idx = 3173201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 77608;
				gtype = 1;
				area = 77601;
				goal = 77604;
				grade = 132203;
				rwd = 100;
				sort = 77605;
				stype = 2;
				taid = 1;
				title = 77602;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 77614;
			nextlnk = 254;
			rwdtbl = 77601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 77607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3173201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 34;
				minlvl = 26;
			}
			CDboTSCheckClrQst
			{
				and = "775;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 77608;
			gtype = 1;
			oklnk = 2;
			area = 77601;
			goal = 77604;
			sort = 77605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 77602;
		}
	}
}

