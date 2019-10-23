CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1624;
	title = 162402;

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
				conv = 162409;
				ctype = 1;
				idx = 6204201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 162408;
				gtype = 0;
				area = 162401;
				goal = 162404;
				grade = 132203;
				rwd = 100;
				sort = 162405;
				stype = 1;
				taid = 1;
				title = 162402;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 162407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6204201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1623;";
			}
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
			cont = 162408;
			gtype = 0;
			oklnk = 2;
			area = 162401;
			goal = 162404;
			sort = 162405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 162402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 162414;
			nextlnk = 254;
			rwdtbl = 162401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6412107;
			}
		}
	}
}

