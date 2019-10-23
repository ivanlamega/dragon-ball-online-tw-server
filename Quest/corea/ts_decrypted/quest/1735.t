CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1735;
	title = 173502;

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
				conv = 173509;
				ctype = 1;
				idx = 6313104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 173508;
				gtype = 0;
				area = 173501;
				goal = 173504;
				grade = 132203;
				rwd = 100;
				sort = 173505;
				stype = 1;
				taid = 1;
				title = 173502;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 173514;
			nextlnk = 254;
			rwdtbl = 173501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5063105;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 173507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6313104;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 173508;
			gtype = 0;
			oklnk = 2;
			area = 173501;
			goal = 173504;
			sort = 173505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 173502;
		}
	}
}

