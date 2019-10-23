CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 660;
	title = 66002;

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
				conv = 66009;
				ctype = 1;
				idx = 4371402;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 66008;
				gtype = 1;
				area = 66001;
				goal = 66004;
				grade = 132203;
				rwd = 100;
				sort = 66005;
				stype = 1;
				taid = 1;
				title = 66002;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 66007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4371402;
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
			cont = 66008;
			gtype = 1;
			oklnk = 2;
			area = 66001;
			goal = 66004;
			sort = 66005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 66002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 66014;
			nextlnk = 254;
			rwdtbl = 66001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3032102;
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

