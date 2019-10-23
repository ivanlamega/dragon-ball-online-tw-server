CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 533;
	title = 53302;

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
				conv = 53309;
				ctype = 1;
				idx = 3172104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 53308;
				gtype = 1;
				area = 53301;
				goal = 53304;
				grade = 132203;
				rwd = 100;
				sort = 53305;
				stype = 2;
				taid = 1;
				title = 53302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 53307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 3172104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 26;
				minlvl = 18;
			}
			CDboTSCheckClrQst
			{
				and = "532;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 53308;
			gtype = 1;
			oklnk = 2;
			area = 53301;
			goal = 53304;
			sort = 53305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 53302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 53314;
			nextlnk = 254;
			rwdtbl = 53301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1353101;
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
	}
}

