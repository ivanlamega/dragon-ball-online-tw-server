CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1461;
	title = 146102;

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
				conv = 146109;
				ctype = 1;
				idx = 3143113;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 146108;
				gtype = 1;
				area = 146101;
				goal = 146104;
				grade = 132203;
				rwd = 100;
				sort = 146105;
				stype = 2;
				taid = 1;
				title = 146102;
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
			cont = 146108;
			gtype = 1;
			oklnk = 2;
			area = 146101;
			goal = 146104;
			sort = 146105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 146102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 146114;
			nextlnk = 254;
			rwdtbl = 146101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4111101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 146107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3143113;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSCheckClrQst
			{
				and = "1444;";
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

