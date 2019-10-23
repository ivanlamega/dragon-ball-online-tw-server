CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1599;
	title = 159902;

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
				conv = 159909;
				ctype = 1;
				idx = 3142216;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 159908;
				gtype = 0;
				area = 159901;
				goal = 159904;
				grade = 132203;
				rwd = 100;
				sort = 159905;
				stype = 2;
				taid = 1;
				title = 159902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 159907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3142216;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1541;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 159908;
			gtype = 0;
			oklnk = 2;
			area = 159901;
			goal = 159904;
			sort = 159905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 159902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 159914;
			nextlnk = 254;
			rwdtbl = 159901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061111;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

