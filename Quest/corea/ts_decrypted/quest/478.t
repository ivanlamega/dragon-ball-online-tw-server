CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 478;
	title = 47802;

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
				conv = 47809;
				ctype = 1;
				idx = 4372207;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 47808;
				gtype = 0;
				area = 47801;
				goal = 47804;
				grade = 132203;
				rwd = 100;
				sort = 47805;
				stype = 2;
				taid = 1;
				title = 47802;
			}
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
			desc = 47814;
			nextlnk = 254;
			rwdtbl = 47801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4192101;
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
			cont = 47808;
			gtype = 0;
			oklnk = 2;
			area = 47801;
			goal = 47804;
			sort = 47805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 47802;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 47807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4372207;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 21;
				minlvl = 13;
			}
		}
	}
}

