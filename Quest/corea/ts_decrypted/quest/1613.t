CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1613;
	title = 161302;

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
				conv = 161309;
				ctype = 1;
				idx = 1651101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 161308;
				gtype = 1;
				area = 161301;
				goal = 161304;
				grade = 132203;
				rwd = 100;
				sort = 161305;
				stype = 2;
				taid = 1;
				title = 161302;
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
			cont = 161308;
			gtype = 1;
			oklnk = 2;
			area = 161301;
			goal = 161304;
			sort = 161305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 161302;
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
			desc = 161314;
			nextlnk = 254;
			rwdtbl = 161301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6412106;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 161307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1651101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
		}
	}
}

