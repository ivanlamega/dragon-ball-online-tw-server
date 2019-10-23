CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 505;
	title = 50502;

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
				conv = 50509;
				ctype = 1;
				idx = 1351118;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 50508;
				gtype = 1;
				area = 50501;
				goal = 50504;
				grade = 132203;
				rwd = 100;
				sort = 50505;
				stype = 1;
				taid = 1;
				title = 50502;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 50507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 1351118;
			}
			CDboTSCheckLvl
			{
				maxlvl = 13;
				minlvl = 5;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 50508;
			gtype = 1;
			oklnk = 2;
			area = 50501;
			goal = 50504;
			sort = 50505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 50502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 50514;
			nextlnk = 254;
			rwdtbl = 50501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8512140;
			}
		}
	}
}

