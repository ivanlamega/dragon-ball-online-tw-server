CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1551;
	title = 155102;

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
				conv = 155109;
				ctype = 1;
				idx = 3331205;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 155108;
				gtype = 0;
				area = 155101;
				goal = 155104;
				grade = 132203;
				rwd = 100;
				sort = 155105;
				stype = 1;
				taid = 1;
				title = 155102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 155107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3331205;
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
			cont = 155108;
			gtype = 0;
			oklnk = 2;
			area = 155101;
			goal = 155104;
			sort = 155105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 155102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 155114;
			nextlnk = 254;
			rwdtbl = 155101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5312103;
			}
		}
	}
}

