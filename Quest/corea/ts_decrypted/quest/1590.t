CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1590;
	title = 159002;

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
				conv = 159009;
				ctype = 1;
				idx = 5063106;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 159008;
				gtype = 1;
				area = 159001;
				goal = 159004;
				grade = 132203;
				rwd = 100;
				sort = 159005;
				stype = 2;
				taid = 1;
				title = 159002;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 159014;
			nextlnk = 254;
			rwdtbl = 159001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3242102;
			}
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
			cont = 159008;
			gtype = 1;
			oklnk = 2;
			area = 159001;
			goal = 159004;
			sort = 159005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 159002;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 159007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5063106;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
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

