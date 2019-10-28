CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1567;
	title = 156702;

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
				conv = 156709;
				ctype = 1;
				idx = 3142117;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 156708;
				gtype = 0;
				area = 156701;
				goal = 156704;
				grade = 132203;
				rwd = 100;
				sort = 156705;
				stype = 1;
				taid = 1;
				title = 156702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 156707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3142117;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 156708;
			gtype = 0;
			oklnk = 2;
			area = 156701;
			goal = 156704;
			sort = 156705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 156702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 156714;
			nextlnk = 254;
			rwdtbl = 156701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1651108;
			}
		}
	}
}

