CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6247;
	title = 624702;

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
				conv = 624709;
				ctype = 1;
				idx = 3148102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 624708;
				gtype = 1;
				area = 624701;
				goal = 624704;
				grade = 132203;
				rwd = 100;
				sort = 624705;
				stype = 2;
				taid = 1;
				title = 624702;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 624714;
			nextlnk = 254;
			rwdtbl = 624701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7092106;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 624708;
			gtype = 1;
			oklnk = 2;
			area = 624701;
			goal = 624704;
			sort = 624705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 624702;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 624707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3148102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "6243;";
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
	}
}

