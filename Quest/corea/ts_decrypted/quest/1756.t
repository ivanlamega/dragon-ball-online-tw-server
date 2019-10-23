CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1756;
	title = 175602;

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
				conv = 175609;
				ctype = 1;
				idx = 6311201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 175608;
				gtype = 1;
				area = 175601;
				goal = 175604;
				grade = 132203;
				rwd = 100;
				sort = 175605;
				stype = 2;
				taid = 1;
				title = 175602;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 175614;
			nextlnk = 254;
			rwdtbl = 175601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2611102;
			}
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
			cont = 175608;
			gtype = 1;
			oklnk = 2;
			area = 175601;
			goal = 175604;
			sort = 175605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 175602;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 175607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6311201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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

