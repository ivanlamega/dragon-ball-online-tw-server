CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1655;
	title = 165502;

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
				conv = 165509;
				ctype = 1;
				idx = 5041126;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 165508;
				gtype = 0;
				area = 165501;
				goal = 165504;
				grade = 132203;
				rwd = 100;
				sort = 165505;
				stype = 2;
				taid = 1;
				title = 165502;
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
			desc = 165514;
			nextlnk = 254;
			rwdtbl = 165501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5041114;
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
			cont = 165508;
			gtype = 0;
			oklnk = 2;
			area = 165501;
			goal = 165504;
			sort = 165505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 165502;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 165507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5041126;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1654;";
			}
		}
	}
}

