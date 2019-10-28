CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 468;
	title = 46802;

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
				conv = 46809;
				ctype = 1;
				idx = 7153103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 46808;
				gtype = 0;
				area = 46801;
				goal = 46804;
				grade = 132203;
				rwd = 100;
				sort = 46805;
				stype = 2;
				taid = 1;
				title = 46802;
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
			desc = 46814;
			nextlnk = 254;
			rwdtbl = 46801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372207;
			}
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
			cont = 46808;
			gtype = 0;
			oklnk = 2;
			area = 46801;
			goal = 46804;
			sort = 46805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 46802;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 46807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7153103;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 12;
			}
			CDboTSCheckClrQst
			{
				and = "463;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

