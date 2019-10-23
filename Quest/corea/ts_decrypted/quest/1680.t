CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1680;
	title = 168002;

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
				conv = 168009;
				ctype = 1;
				idx = 7135201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 168008;
				gtype = 1;
				area = 168001;
				goal = 168004;
				grade = 132203;
				rwd = 100;
				sort = 168005;
				stype = 1;
				taid = 1;
				title = 168002;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 168007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7135201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 168008;
			gtype = 1;
			oklnk = 2;
			area = 168001;
			goal = 168004;
			sort = 168005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 168002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 168014;
			nextlnk = 254;
			rwdtbl = 168001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3143107;
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
	}
}

