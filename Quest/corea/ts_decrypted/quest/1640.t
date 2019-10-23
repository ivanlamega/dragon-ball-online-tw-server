CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1640;
	title = 164002;

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
				conv = 164009;
				ctype = 1;
				idx = 3242104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 164008;
				gtype = 0;
				area = 164001;
				goal = 164004;
				grade = 132203;
				rwd = 100;
				sort = 164005;
				stype = 2;
				taid = 1;
				title = 164002;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 164014;
			nextlnk = 254;
			rwdtbl = 164001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142214;
			}
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
			cont = 164008;
			gtype = 0;
			oklnk = 2;
			area = 164001;
			goal = 164004;
			sort = 164005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 164002;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 164007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3242104;
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
	}
}

