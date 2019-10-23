CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 981;
	title = 98102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 98109;
				ctype = 1;
				idx = 4041104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 98108;
				m1fx = "1742.000000";
				m2fz = "820.000000";
				m1fy = "0.000000";
				sort = 98105;
				m2widx = 1;
				grade = 132203;
				m0fx = "1794.000000";
				m0ttip = 98115;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 98102;
				gtype = 2;
				area = 98101;
				goal = 98104;
				m0fz = "887.000000";
				m0widx = 1;
				m1ttip = 98115;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "904.000000";
				m2fx = "1774.000000";
				m2ttip = 98115;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 740;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
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
				itype = 3;
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
				eitype = 3;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 98114;
			nextlnk = 101;
			rwdtbl = 98101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7131119;
			}
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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 98107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4041104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 44;
				minlvl = 36;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;252;0;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 98108;
			gtype = 2;
			oklnk = 2;
			area = 98101;
			goal = 98104;
			sort = 98105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 98102;
		}
	}
}

