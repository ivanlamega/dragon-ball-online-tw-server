CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 358;
	title = 35802;

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
				conv = 35809;
				ctype = 1;
				idx = 4511405;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 35808;
				gtype = 0;
				area = 35801;
				goal = 35804;
				grade = 132203;
				rwd = 100;
				sort = 35805;
				stype = 1;
				taid = 1;
				title = 35802;
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
			cont = 35808;
			gtype = 0;
			oklnk = 2;
			area = 35801;
			goal = 35804;
			sort = 35805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 35802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 35814;
			nextlnk = 254;
			rwdtbl = 35801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751204;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 35807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511405;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 27;
				minlvl = 19;
			}
		}
	}
}

