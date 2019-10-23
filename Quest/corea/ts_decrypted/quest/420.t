CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 420;
	title = 42002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 42008;
				gtype = 0;
				area = 42001;
				goal = 42004;
				grade = 132203;
				rwd = 100;
				sort = 42005;
				stype = 2;
				taid = 1;
				title = 42002;
			}
			CDboTSActNPCConv
			{
				conv = 42009;
				ctype = 1;
				idx = 4141107;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 42014;
			nextlnk = 254;
			rwdtbl = 42001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4261101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 42007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4141107;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 42008;
			gtype = 0;
			oklnk = 2;
			area = 42001;
			goal = 42004;
			sort = 42005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 42002;
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

