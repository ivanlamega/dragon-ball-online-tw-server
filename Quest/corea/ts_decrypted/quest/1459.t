CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1459;
	title = 145902;

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
				conv = 145909;
				ctype = 1;
				idx = 3143113;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 145908;
				gtype = 0;
				area = 145901;
				goal = 145904;
				grade = 132203;
				rwd = 100;
				sort = 145905;
				stype = 2;
				taid = 1;
				title = 145902;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 145914;
			nextlnk = 254;
			rwdtbl = 145901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5531101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 145908;
			gtype = 0;
			oklnk = 2;
			area = 145901;
			goal = 145904;
			sort = 145905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 145902;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 145907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3143113;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSCheckClrQst
			{
				and = "1458;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
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
	}
}

