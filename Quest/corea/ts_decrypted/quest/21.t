CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 21;
	title = 2102;

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
				conv = 2109;
				ctype = 1;
				idx = 4181101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 2108;
				gtype = 0;
				area = 2101;
				goal = 2104;
				grade = 132203;
				rwd = 100;
				sort = 2105;
				stype = 1;
				taid = 1;
				title = 2102;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
			cont = 2108;
			gtype = 0;
			oklnk = 2;
			area = 2101;
			goal = 2104;
			sort = 2105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 2102;
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
			desc = 2114;
			nextlnk = 254;
			rwdtbl = 2101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3331101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 2107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4181101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 12;
				minlvl = 4;
			}
			CDboTSCheckClrQst
			{
				and = "19;";
			}
		}
	}
}

