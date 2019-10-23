CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1053;
	title = 105302;

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
				conv = 105309;
				ctype = 1;
				idx = 8031201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 105308;
				gtype = 1;
				area = 105301;
				goal = 105304;
				grade = 132203;
				rwd = 100;
				sort = 105305;
				stype = 2;
				taid = 1;
				title = 105302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 105307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8031201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
			CDboTSCheckClrQst
			{
				and = "1052;";
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
			cont = 105308;
			gtype = 1;
			oklnk = 2;
			area = 105301;
			goal = 105304;
			sort = 105305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 105302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 105314;
			nextlnk = 254;
			rwdtbl = 105301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4071114;
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
	}
}

