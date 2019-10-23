CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1134;
	title = 113402;

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
				conv = 113409;
				ctype = 1;
				idx = 3147103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 113408;
				gtype = 0;
				area = 113401;
				goal = 113404;
				grade = 132203;
				rwd = 100;
				sort = 113405;
				stype = 1;
				taid = 1;
				title = 113402;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 113414;
			nextlnk = 254;
			rwdtbl = 113401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061302;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
			cont = 113408;
			gtype = 0;
			oklnk = 2;
			area = 113401;
			goal = 113404;
			sort = 113405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 113402;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 113407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3147103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
		}
	}
}

