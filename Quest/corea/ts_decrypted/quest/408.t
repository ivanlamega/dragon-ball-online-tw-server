CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 408;
	title = 40802;

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
				cont = 40808;
				gtype = 0;
				area = 40801;
				goal = 40804;
				grade = 132203;
				rwd = 100;
				sort = 40805;
				stype = 1;
				taid = 1;
				title = 40802;
			}
			CDboTSActNPCConv
			{
				conv = 40809;
				ctype = 1;
				idx = 7131104;
				taid = 2;
			}
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 40814;
			nextlnk = 254;
			rwdtbl = 40801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1111105;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 40808;
			gtype = 0;
			oklnk = 2;
			area = 40801;
			goal = 40804;
			sort = 40805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 40802;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 40807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 7131104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 11;
				minlvl = 3;
			}
			CDboTSCheckClrQst
			{
				and = "407;";
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

