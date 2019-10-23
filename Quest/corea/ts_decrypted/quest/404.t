CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 404;
	title = 40402;

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
				conv = 40409;
				ctype = 1;
				idx = 7711101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 40408;
				gtype = 0;
				area = 40401;
				goal = 40404;
				grade = 132203;
				rwd = 100;
				sort = 40405;
				stype = 2;
				taid = 1;
				title = 40402;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 40407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 7711101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 10;
				minlvl = 2;
			}
			CDboTSCheckClrQst
			{
				and = "580;";
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
			cont = 40408;
			gtype = 0;
			oklnk = 2;
			area = 40401;
			goal = 40404;
			sort = 40405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 40402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 40414;
			nextlnk = 254;
			rwdtbl = 40401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8031301;
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

