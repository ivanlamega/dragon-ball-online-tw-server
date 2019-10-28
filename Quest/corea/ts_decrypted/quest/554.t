CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 554;
	title = 55402;

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
				conv = 55409;
				ctype = 1;
				idx = 2611101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 55408;
				gtype = 0;
				area = 55401;
				goal = 55404;
				grade = 132203;
				rwd = 100;
				sort = 55405;
				stype = 2;
				taid = 1;
				title = 55402;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 55407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 2611101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 28;
				minlvl = 20;
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
			cont = 55408;
			gtype = 0;
			oklnk = 2;
			area = 55401;
			goal = 55404;
			sort = 55405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 55402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 55414;
			nextlnk = 254;
			rwdtbl = 55401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4152101;
			}
		}
	}
}

