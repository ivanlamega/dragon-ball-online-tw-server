CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 591;
	title = 59102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSItemUpgrade
			{
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 59109;
				ctype = 1;
				idx = 4261101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 59108;
				gtype = 0;
				area = 59101;
				goal = 59104;
				grade = 132203;
				rwd = 100;
				sort = 59105;
				stype = 1;
				taid = 1;
				title = 59102;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 59108;
			gtype = 1;
			oklnk = 2;
			area = 59101;
			goal = 59104;
			sort = 59105;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 59102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 59114;
			nextlnk = 254;
			rwdtbl = 59101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4261101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 59107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4261101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 10;
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

