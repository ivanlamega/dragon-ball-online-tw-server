CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 579;
	title = 57902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSSearchQuest
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
				conv = 57909;
				ctype = 1;
				idx = 4141107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 57908;
				gtype = 1;
				area = 57901;
				goal = 57904;
				grade = 132203;
				rwd = 100;
				sort = 57905;
				stype = 2;
				taid = 1;
				title = 57902;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 57914;
			nextlnk = 254;
			rwdtbl = 57901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4141107;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 57907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4141107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 10;
				minlvl = 2;
			}
			CDboTSCheckClrQst
			{
				and = "406;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 57908;
			gtype = 1;
			oklnk = 2;
			area = 57901;
			goal = 57904;
			sort = 57905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 57902;
		}
	}
}

