CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1004;
	title = 100402;

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
				conv = 100409;
				ctype = 1;
				idx = 3142105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 100408;
				gtype = 1;
				area = 100401;
				goal = 100404;
				grade = 132203;
				rwd = 100;
				sort = 100405;
				stype = 2;
				taid = 1;
				title = 100402;
			}
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
			desc = 100414;
			nextlnk = 254;
			rwdtbl = 100401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4072110;
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
			cont = 100408;
			gtype = 1;
			oklnk = 2;
			area = 100401;
			goal = 100404;
			sort = 100405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 100402;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 100407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3142105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 46;
				minlvl = 38;
			}
		}
	}
}

