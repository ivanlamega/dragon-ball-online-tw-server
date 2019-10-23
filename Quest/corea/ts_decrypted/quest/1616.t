CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1616;
	title = 161602;

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
				conv = 161609;
				ctype = 1;
				idx = 6412106;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 161608;
				gtype = 1;
				area = 161601;
				goal = 161604;
				grade = 132203;
				rwd = 100;
				sort = 161605;
				stype = 2;
				taid = 1;
				title = 161602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 161607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6412106;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1613;";
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
			cont = 161608;
			gtype = 1;
			oklnk = 2;
			area = 161601;
			goal = 161604;
			sort = 161605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 161602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 161614;
			nextlnk = 254;
			rwdtbl = 161601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4952101;
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

