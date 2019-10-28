CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1686;
	title = 168602;

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
				conv = 168609;
				ctype = 1;
				idx = 7135201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 168608;
				gtype = 1;
				area = 168601;
				goal = 168604;
				grade = 132203;
				rwd = 100;
				sort = 168605;
				stype = 2;
				taid = 1;
				title = 168602;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 168614;
			nextlnk = 254;
			rwdtbl = 168601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5313202;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 168607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7135201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1684;";
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
			cont = 168608;
			gtype = 1;
			oklnk = 2;
			area = 168601;
			goal = 168604;
			sort = 168605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 168602;
		}
	}
}

