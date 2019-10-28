CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 438;
	title = 43802;

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
				conv = 43809;
				ctype = 1;
				idx = 4261101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 43808;
				gtype = 0;
				area = 43801;
				goal = 43804;
				grade = 132203;
				rwd = 100;
				sort = 43805;
				stype = 2;
				taid = 1;
				title = 43802;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 43807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4261101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 16;
				minlvl = 8;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 43808;
			gtype = 0;
			oklnk = 2;
			area = 43801;
			goal = 43804;
			sort = 43805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 43802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 43814;
			nextlnk = 254;
			rwdtbl = 43801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4151201;
			}
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

