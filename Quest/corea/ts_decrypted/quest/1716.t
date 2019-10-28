CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1716;
	title = 171602;

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
				conv = 171609;
				ctype = 1;
				idx = 5313202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 171608;
				gtype = 0;
				area = 171601;
				goal = 171604;
				grade = 132203;
				rwd = 100;
				sort = 171605;
				stype = 2;
				taid = 1;
				title = 171602;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 171608;
			gtype = 0;
			oklnk = 2;
			area = 171601;
			goal = 171604;
			sort = 171605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 171602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 171614;
			nextlnk = 254;
			rwdtbl = 171601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5041115;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 171607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5313202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1715;";
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

