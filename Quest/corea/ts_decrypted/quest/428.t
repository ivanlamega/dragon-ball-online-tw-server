CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 428;
	title = 42802;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
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
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 42807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 3182101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 14;
				minlvl = 6;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 42814;
			nextlnk = 101;
			rwdtbl = 42801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3182101;
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
				conv = 42809;
				ctype = 1;
				idx = 3182101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 42808;
				m1fx = "5793.000000";
				area = 42801;
				goal = 42804;
				m0fz = "-3902.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 42816;
				sort = 42805;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-3476.000000";
				grade = 132203;
				m0fx = "6645.000000";
				m0ttip = 42815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 42802;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 7213100;
				cnt0 = 3;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 42808;
			gtype = 2;
			oklnk = 2;
			area = 42801;
			goal = 42804;
			sort = 42805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 42802;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

