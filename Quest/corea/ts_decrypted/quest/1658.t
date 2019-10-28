CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1658;
	title = 165802;

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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 165808;
			gtype = 2;
			oklnk = 2;
			area = 165801;
			goal = 165804;
			sort = 165805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 165802;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 165809;
				ctype = 1;
				idx = 7135201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 165808;
				m1fx = "-1814.000000";
				m2fz = "-603.000000";
				m1fy = "0.000000";
				sort = 165805;
				m2widx = 1;
				grade = 132203;
				m0fx = "-1871.000000";
				m0ttip = 165815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 165802;
				gtype = 2;
				area = 165801;
				goal = 165804;
				m0fz = "-573.000000";
				m0widx = 1;
				m1ttip = 165816;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-521.000000";
				m2fx = "-1789.000000";
				m2ttip = 165817;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 0;
				idx0 = 3501109;
				cnt0 = 10;
				cnt2 = 10;
				ectype = -1;
				etype = 0;
				idx1 = 3503100;
				taid = 3;
				esctype = 0;
				idx2 = 3503105;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 165814;
			nextlnk = 101;
			rwdtbl = 165801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7135201;
			}
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
			stdiag = 165807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7135201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
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

