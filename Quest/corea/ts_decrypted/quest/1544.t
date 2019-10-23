CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1544;
	title = 154402;

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
				conv = 154409;
				ctype = 1;
				idx = 4372201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 154408;
				gtype = 1;
				area = 154401;
				goal = 154404;
				grade = 132203;
				rwd = 100;
				sort = 154405;
				stype = 2;
				taid = 1;
				title = 154402;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 154408;
			gtype = 1;
			oklnk = 2;
			area = 154401;
			goal = 154404;
			sort = 154405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 154402;
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
			desc = 154414;
			nextlnk = 254;
			rwdtbl = 154401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4371203;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 154407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4372201;
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
	}
}

