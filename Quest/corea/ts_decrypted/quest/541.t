CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 541;
	title = 54102;

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
				conv = 54109;
				ctype = 1;
				idx = 3273101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 54108;
				gtype = 0;
				area = 54101;
				goal = 54104;
				grade = 132203;
				rwd = 100;
				sort = 54105;
				stype = 2;
				taid = 1;
				title = 54102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 54107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 3273101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 26;
				minlvl = 18;
			}
			CDboTSCheckClrQst
			{
				and = "540;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 54108;
			gtype = 0;
			oklnk = 2;
			area = 54101;
			goal = 54104;
			sort = 54105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 54102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 54114;
			nextlnk = 254;
			rwdtbl = 54101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4371201;
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

