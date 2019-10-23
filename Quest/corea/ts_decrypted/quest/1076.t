CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1076;
	title = 107602;

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
				conv = 107609;
				ctype = 1;
				idx = 4071114;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 107608;
				gtype = 1;
				area = 107601;
				goal = 107604;
				grade = 132203;
				rwd = 100;
				sort = 107605;
				stype = 2;
				taid = 1;
				title = 107602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 107607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4071114;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
			CDboTSCheckClrQst
			{
				and = "1053;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 107614;
			nextlnk = 254;
			rwdtbl = 107601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4071113;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 107608;
			gtype = 1;
			oklnk = 2;
			area = 107601;
			goal = 107604;
			sort = 107605;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 107602;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
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

