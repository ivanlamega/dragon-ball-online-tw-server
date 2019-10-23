CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 146;
	title = 14602;

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
				conv = 14609;
				ctype = 1;
				idx = 3611101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 14608;
				gtype = 1;
				area = 14601;
				goal = 14604;
				grade = 132203;
				rwd = 100;
				sort = 14605;
				stype = 1;
				taid = 1;
				title = 14602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 14607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3611101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 14608;
			gtype = 1;
			oklnk = 2;
			area = 14601;
			goal = 14604;
			sort = 14605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 14602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 14614;
			nextlnk = 254;
			rwdtbl = 14601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8512126;
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

