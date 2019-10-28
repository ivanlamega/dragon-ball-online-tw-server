CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1116;
	title = 111602;

	CNtlTSGroup
	{
		gid = 0;

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
			stdiag = 111607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3612103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 111614;
			nextlnk = 101;
			rwdtbl = 111601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3612103;
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
				conv = 111609;
				ctype = 1;
				idx = 3612103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 111608;
				m1fx = "98.000000";
				area = 111601;
				goal = 111604;
				m0fz = "2188.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 111616;
				sort = 111605;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "1550.000000";
				grade = 132203;
				m0fx = "-202.000000";
				m0ttip = 111615;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 111602;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 16;
				eitype = 0;
				idx0 = 5813202;
				cnt0 = 16;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 5813302;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 111608;
			gtype = 2;
			oklnk = 2;
			area = 111601;
			goal = 111604;
			sort = 111605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 111602;
		}
	}
}

