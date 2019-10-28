CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1309;
	title = 130902;

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
				conv = 130909;
				ctype = 1;
				idx = 5533402;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 130908;
				gtype = 1;
				area = 130901;
				goal = 130904;
				grade = 132203;
				rwd = 100;
				sort = 130905;
				stype = 1;
				taid = 1;
				title = 130902;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 130908;
			gtype = 1;
			oklnk = 2;
			area = 130901;
			goal = 130904;
			sort = 130905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 130902;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 130914;
			nextlnk = 254;
			rwdtbl = 130901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1752103;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 130907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5533402;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
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

