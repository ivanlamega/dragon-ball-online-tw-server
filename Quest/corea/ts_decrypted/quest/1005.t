CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1005;
	title = 100502;

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
				conv = 100509;
				ctype = 1;
				idx = 8031201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 100508;
				gtype = 1;
				area = 100501;
				goal = 100504;
				grade = 132203;
				rwd = 100;
				sort = 100505;
				stype = 2;
				taid = 1;
				title = 100502;
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
			desc = 100514;
			nextlnk = 254;
			rwdtbl = 100501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3612102;
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
			cont = 100508;
			gtype = 1;
			oklnk = 2;
			area = 100501;
			goal = 100504;
			sort = 100505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 100502;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 100507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8031201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 45;
				minlvl = 37;
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

