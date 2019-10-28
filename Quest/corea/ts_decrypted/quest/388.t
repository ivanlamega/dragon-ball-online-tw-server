CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 388;
	title = 38802;

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
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 38809;
				ctype = 1;
				idx = 7131108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 38808;
				gtype = 0;
				area = 38801;
				goal = 38804;
				m0fz = "-1204.000000";
				m0widx = 1;
				sort = 38805;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "4533.000000";
				m0ttip = 38815;
				rwd = 100;
				taid = 1;
				title = 38802;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 1511101;
				cnt0 = 14;
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
			cont = 38808;
			gtype = 0;
			oklnk = 2;
			area = 38801;
			goal = 38804;
			sort = 38805;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 38802;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
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
			desc = 38814;
			nextlnk = 101;
			rwdtbl = 38801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7131108;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 38807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 7131108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 28;
				minlvl = 20;
			}
		}
	}
}

