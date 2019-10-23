CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 657;
	title = 65702;

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
				conv = 65709;
				ctype = 1;
				idx = 1654107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 65708;
				gtype = 1;
				area = 65701;
				goal = 65704;
				grade = 132203;
				rwd = 100;
				sort = 65705;
				stype = 2;
				taid = 1;
				title = 65702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 65707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1654107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
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
			cont = 65708;
			gtype = 1;
			oklnk = 2;
			area = 65701;
			goal = 65704;
			sort = 65705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 65702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 65714;
			nextlnk = 254;
			rwdtbl = 65701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3032105;
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

