CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 394;
	title = 39402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 39414;
			nextlnk = 254;
			rwdtbl = 39401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7071102;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 39408;
			gtype = 2;
			oklnk = 2;
			area = 39401;
			goal = 39404;
			sort = 39405;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 39402;
		}
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
			stdiag = 39407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7071102;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 10;
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
				conv = 39409;
				ctype = 1;
				idx = 7071102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 39408;
				gtype = 2;
				area = 39401;
				goal = 39404;
				grade = 132203;
				rwd = 100;
				sort = 39405;
				stype = 1;
				taid = 1;
				title = 39402;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSRB
			{
				cond = 1;
				idx = -1;
			}
		}
	}
}

