CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 728;
	title = 72802;

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
				conv = 72809;
				ctype = 1;
				idx = 4511605;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 72808;
				gtype = 1;
				area = 72801;
				goal = 72804;
				grade = 132203;
				rwd = 100;
				sort = 72805;
				stype = 1;
				taid = 1;
				title = 72802;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 72807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511605;
			}
			CDboTSCheckLvl
			{
				maxlvl = 32;
				minlvl = 24;
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
			cont = 72808;
			gtype = 1;
			oklnk = 2;
			area = 72801;
			goal = 72804;
			sort = 72805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 72802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 72814;
			nextlnk = 254;
			rwdtbl = 72801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061106;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

