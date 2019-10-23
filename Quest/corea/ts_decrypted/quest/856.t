CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 856;
	title = 85602;

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
				conv = 85609;
				ctype = 1;
				idx = 3032103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 85608;
				gtype = 1;
				area = 85601;
				goal = 85604;
				grade = 132203;
				rwd = 100;
				sort = 85605;
				stype = 2;
				taid = 1;
				title = 85602;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 85614;
			nextlnk = 254;
			rwdtbl = 85601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1311201;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
			cont = 85608;
			gtype = 1;
			oklnk = 2;
			area = 85601;
			goal = 85604;
			sort = 85605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 85602;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 85607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3032103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 38;
				minlvl = 30;
			}
		}
	}
}

