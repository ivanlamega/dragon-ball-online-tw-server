CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 148;
	title = 14802;

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
				conv = 14809;
				ctype = 1;
				idx = 7071101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 14808;
				gtype = 1;
				area = 14801;
				goal = 14804;
				grade = 132203;
				rwd = 100;
				sort = 14805;
				stype = 1;
				taid = 1;
				title = 14802;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 14807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 7071101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 26;
				minlvl = 18;
			}
			CDboTSCheckClrQst
			{
				and = "147;";
			}
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
			cont = 14808;
			gtype = 1;
			oklnk = 2;
			area = 14801;
			goal = 14804;
			sort = 14805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 14802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 14814;
			nextlnk = 254;
			rwdtbl = 14801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2804101;
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

