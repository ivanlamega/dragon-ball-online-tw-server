CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 953;
	title = 95302;

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
				conv = 95309;
				ctype = 1;
				idx = 3172301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 95308;
				gtype = 1;
				area = 95301;
				goal = 95304;
				grade = 132203;
				rwd = 100;
				sort = 95305;
				stype = 2;
				taid = 1;
				title = 95302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 95307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3172301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 42;
				minlvl = 34;
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
			cont = 95308;
			gtype = 1;
			oklnk = 2;
			area = 95301;
			goal = 95304;
			sort = 95305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 95302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 95314;
			nextlnk = 254;
			rwdtbl = 95301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1571101;
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

