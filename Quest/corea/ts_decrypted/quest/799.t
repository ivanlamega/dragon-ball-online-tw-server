CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 799;
	title = 79902;

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
				conv = 79909;
				ctype = 1;
				idx = 5061202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 79908;
				gtype = 1;
				area = 79901;
				goal = 79904;
				grade = 132203;
				rwd = 100;
				sort = 79905;
				stype = 1;
				taid = 1;
				title = 79902;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 79908;
			gtype = 1;
			oklnk = 2;
			area = 79901;
			goal = 79904;
			sort = 79905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 79902;
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
			desc = 79914;
			nextlnk = 254;
			rwdtbl = 79901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1311204;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 79907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5061202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 35;
				minlvl = 27;
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

