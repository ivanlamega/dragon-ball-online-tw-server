CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1916;
	title = 191602;

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
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 191607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7091111;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 5;
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
				conv = 191609;
				ctype = 1;
				idx = 7091111;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 191608;
				gtype = 2;
				area = 191601;
				goal = 191604;
				grade = 132203;
				rwd = 100;
				sort = 191605;
				stype = 1;
				taid = 1;
				title = 191602;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSParty
			{
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 191614;
			nextlnk = 254;
			rwdtbl = 191601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7091111;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 191608;
			gtype = 2;
			oklnk = 2;
			area = 191601;
			goal = 191604;
			sort = 191605;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 191602;
		}
	}
}

