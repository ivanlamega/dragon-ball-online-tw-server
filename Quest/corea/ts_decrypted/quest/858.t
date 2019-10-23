CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 858;
	title = 85802;

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
				conv = 85809;
				ctype = 1;
				idx = 6312109;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 85808;
				gtype = 1;
				area = 85801;
				goal = 85804;
				grade = 132203;
				rwd = 100;
				sort = 85805;
				stype = 1;
				taid = 1;
				title = 85802;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 85807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6312109;
			}
			CDboTSCheckLvl
			{
				maxlvl = 38;
				minlvl = 30;
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
			cont = 85808;
			gtype = 1;
			oklnk = 2;
			area = 85801;
			goal = 85804;
			sort = 85805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 85802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 85814;
			nextlnk = 254;
			rwdtbl = 85801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031208;
			}
		}
	}
}

