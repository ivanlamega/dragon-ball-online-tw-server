CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 71;
	title = 7102;

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
				conv = 7109;
				ctype = 1;
				idx = 1351101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 7108;
				gtype = 0;
				area = 7101;
				goal = 7104;
				grade = 132203;
				rwd = 100;
				sort = 7105;
				stype = 2;
				taid = 1;
				title = 7102;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 7108;
			gtype = 0;
			oklnk = 2;
			area = 7101;
			goal = 7104;
			sort = 7105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 7102;
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
			desc = 7114;
			nextlnk = 254;
			rwdtbl = 7101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5041101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 7107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 1351101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 19;
				minlvl = 11;
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
	}
}

