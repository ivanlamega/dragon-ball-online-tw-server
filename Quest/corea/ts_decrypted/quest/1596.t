CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1596;
	title = 159602;

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
				conv = 159609;
				ctype = 1;
				idx = 3143116;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 159608;
				gtype = 0;
				area = 159601;
				goal = 159604;
				grade = 132203;
				rwd = 100;
				sort = 159605;
				stype = 1;
				taid = 1;
				title = 159602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 159607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3143116;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1588;";
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
			cont = 159608;
			gtype = 0;
			oklnk = 2;
			area = 159601;
			goal = 159604;
			sort = 159605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 159602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 159614;
			nextlnk = 254;
			rwdtbl = 159601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3172401;
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

