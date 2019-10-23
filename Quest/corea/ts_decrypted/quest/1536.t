CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1536;
	title = 153602;

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
				conv = 153609;
				ctype = 1;
				idx = 3142116;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 153608;
				gtype = 1;
				area = 153601;
				goal = 153604;
				grade = 132203;
				rwd = 100;
				sort = 153605;
				stype = 2;
				taid = 1;
				title = 153602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 153607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3142116;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1534;";
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
			cont = 153608;
			gtype = 1;
			oklnk = 2;
			area = 153601;
			goal = 153604;
			sort = 153605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 153602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 153614;
			nextlnk = 254;
			rwdtbl = 153601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3241102;
			}
		}
	}
}

