CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1684;
	title = 168402;

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
				conv = 168409;
				ctype = 1;
				idx = 6312110;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 168408;
				gtype = 0;
				area = 168401;
				goal = 168404;
				grade = 132203;
				rwd = 100;
				sort = 168405;
				stype = 2;
				taid = 1;
				title = 168402;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 168408;
			gtype = 0;
			oklnk = 2;
			area = 168401;
			goal = 168404;
			sort = 168405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 168402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 168414;
			nextlnk = 254;
			rwdtbl = 168401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7135201;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 168407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6312110;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1683;";
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
	}
}

