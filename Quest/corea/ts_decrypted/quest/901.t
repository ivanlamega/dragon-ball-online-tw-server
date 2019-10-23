CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 901;
	title = 90102;

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
				conv = 90109;
				ctype = 1;
				idx = 5061101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 90108;
				gtype = 0;
				area = 90101;
				goal = 90104;
				grade = 132203;
				rwd = 100;
				sort = 90105;
				stype = 2;
				taid = 1;
				title = 90102;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 90114;
			nextlnk = 254;
			rwdtbl = 90101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2951102;
			}
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
			cont = 90108;
			gtype = 0;
			oklnk = 2;
			area = 90101;
			goal = 90104;
			sort = 90105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 90102;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 90107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5061101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 39;
				minlvl = 31;
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
	}
}

