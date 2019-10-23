CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1078;
	title = 107802;

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
				conv = 107809;
				ctype = 1;
				idx = 4071116;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 107808;
				gtype = 1;
				area = 107801;
				goal = 107804;
				grade = 132203;
				rwd = 100;
				sort = 107805;
				stype = 2;
				taid = 1;
				title = 107802;
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
			desc = 107814;
			nextlnk = 254;
			rwdtbl = 107801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1655101;
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
			cont = 107808;
			gtype = 1;
			oklnk = 2;
			area = 107801;
			goal = 107804;
			sort = 107805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 107802;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 107807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4071116;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
		}
	}
}

