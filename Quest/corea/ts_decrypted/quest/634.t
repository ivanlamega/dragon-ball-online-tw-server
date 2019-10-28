CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 634;
	title = 63402;

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
				cont = 63408;
				gtype = 1;
				area = 63401;
				goal = 63404;
				grade = 132203;
				rwd = 100;
				sort = 63405;
				stype = 2;
				taid = 1;
				title = 63402;
			}
			CDboTSActNPCConv
			{
				conv = 63409;
				ctype = 1;
				idx = 3183101;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 63414;
			nextlnk = 254;
			rwdtbl = 63401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4261102;
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
			cont = 63408;
			gtype = 1;
			oklnk = 2;
			area = 63401;
			goal = 63404;
			sort = 63405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 63402;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 63407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 3183101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
			CDboTSCheckClrQst
			{
				and = "633;";
			}
		}
	}
}

