CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1914;
	title = 191402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 191407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 5591202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 5;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 191409;
				ctype = 1;
				idx = 5591202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 191408;
				gtype = 2;
				area = 191401;
				goal = 191404;
				grade = 132203;
				rwd = 100;
				sort = 191405;
				stype = 1;
				taid = 1;
				title = 191402;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSUseMail
			{
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 191414;
			nextlnk = 254;
			rwdtbl = 191401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5591202;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 191408;
			gtype = 2;
			oklnk = 2;
			area = 191401;
			goal = 191404;
			sort = 191405;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 191402;
		}
	}
}

