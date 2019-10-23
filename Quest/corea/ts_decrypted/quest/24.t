CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 24;
	title = 2402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 2408;
				gtype = 1;
				area = 2401;
				goal = 2404;
				grade = 132203;
				rwd = 100;
				sort = 2405;
				stype = 2;
				taid = 1;
				title = 2402;
			}
			CDboTSActNPCConv
			{
				conv = 2409;
				ctype = 1;
				idx = 8032101;
				taid = 2;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 2407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8032101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 13;
				minlvl = 5;
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
			cont = 2408;
			gtype = 1;
			oklnk = 2;
			area = 2401;
			goal = 2404;
			sort = 2405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 2402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 2414;
			nextlnk = 254;
			rwdtbl = 2401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8031501;
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

