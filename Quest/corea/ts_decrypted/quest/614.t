CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 614;
	title = 61402;

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
				conv = 61409;
				ctype = 1;
				idx = 3032103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 61408;
				gtype = 1;
				area = 61401;
				goal = 61404;
				grade = 132203;
				rwd = 100;
				sort = 61405;
				stype = 2;
				taid = 1;
				title = 61402;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 61407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3032103;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
			CDboTSCheckClrQst
			{
				and = "613;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 61408;
			gtype = 1;
			oklnk = 2;
			area = 61401;
			goal = 61404;
			sort = 61405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 61402;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 61414;
			nextlnk = 254;
			rwdtbl = 61401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
	}
}

