CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1356;
	title = 135602;

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
				conv = 135609;
				ctype = 1;
				idx = 4111101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 135608;
				gtype = 1;
				area = 135601;
				goal = 135604;
				grade = 132203;
				rwd = 100;
				sort = 135605;
				stype = 2;
				taid = 1;
				title = 135602;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 135614;
			nextlnk = 254;
			rwdtbl = 135601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7131122;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 135607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4111101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1351;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 135608;
			gtype = 1;
			oklnk = 2;
			area = 135601;
			goal = 135604;
			sort = 135605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 135602;
		}
	}
}

