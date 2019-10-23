CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1144;
	title = 114402;

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
				conv = 114409;
				ctype = 1;
				idx = 5061302;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 114408;
				gtype = 0;
				area = 114401;
				goal = 114404;
				grade = 132203;
				rwd = 100;
				sort = 114405;
				stype = 1;
				taid = 1;
				title = 114402;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 114407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5061302;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
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
			cont = 114408;
			gtype = 0;
			oklnk = 2;
			area = 114401;
			goal = 114404;
			sort = 114405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 114402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 114414;
			nextlnk = 254;
			rwdtbl = 114401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1551101;
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
	}
}

