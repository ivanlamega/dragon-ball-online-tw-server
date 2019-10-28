CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 124;
	title = 12402;

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
				conv = 12409;
				ctype = 1;
				idx = 3143104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 12408;
				gtype = 1;
				area = 12401;
				goal = 12404;
				grade = 132203;
				rwd = 100;
				sort = 12405;
				stype = 2;
				taid = 1;
				title = 12402;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 12414;
			nextlnk = 254;
			rwdtbl = 12401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142102;
			}
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
			cont = 12408;
			gtype = 1;
			oklnk = 2;
			area = 12401;
			goal = 12404;
			sort = 12405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 12402;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 12407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3143104;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 35;
				minlvl = 17;
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
	}
}

