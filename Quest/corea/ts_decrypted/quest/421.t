CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 421;
	title = 42102;

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
				cont = 42108;
				gtype = 0;
				area = 42101;
				goal = 42104;
				grade = 132203;
				rwd = 100;
				sort = 42105;
				stype = 1;
				taid = 1;
				title = 42102;
			}
			CDboTSActNPCConv
			{
				conv = 42109;
				ctype = 1;
				idx = 7711101;
				taid = 2;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 42107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7711101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 12;
				minlvl = 4;
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
			cont = 42108;
			gtype = 0;
			oklnk = 2;
			area = 42101;
			goal = 42104;
			sort = 42105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 42102;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 42114;
			nextlnk = 254;
			rwdtbl = 42101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2413108;
			}
		}
	}
}

