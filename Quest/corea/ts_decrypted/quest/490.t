CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 490;
	title = 49002;

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
				conv = 49009;
				ctype = 1;
				idx = 4372207;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 49008;
				gtype = 0;
				area = 49001;
				goal = 49004;
				grade = 132203;
				rwd = 100;
				sort = 49005;
				stype = 2;
				taid = 1;
				title = 49002;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 49014;
			nextlnk = 254;
			rwdtbl = 49001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3171101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 49008;
			gtype = 0;
			oklnk = 2;
			area = 49001;
			goal = 49004;
			sort = 49005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 49002;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 49007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4372207;
			}
			CDboTSCheckLvl
			{
				maxlvl = 22;
				minlvl = 14;
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

