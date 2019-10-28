CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 237;
	title = 23702;

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
				cont = 23708;
				gtype = 1;
				area = 23701;
				goal = 23704;
				grade = 132203;
				rwd = 100;
				sort = 23705;
				stype = 2;
				taid = 1;
				title = 23702;
			}
			CDboTSActNPCConv
			{
				conv = 23709;
				ctype = 1;
				idx = 5533401;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 23714;
			nextlnk = 254;
			rwdtbl = 23701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142210;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 23707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5533401;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 15;
				minlvl = 7;
			}
			CDboTSCheckClrQst
			{
				or = "235;";
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
			cont = 23708;
			gtype = 1;
			oklnk = 2;
			area = 23701;
			goal = 23704;
			sort = 23705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 23702;
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

