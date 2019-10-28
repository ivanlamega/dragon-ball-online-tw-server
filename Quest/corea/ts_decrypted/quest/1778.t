CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1778;
	title = 177802;

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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 177807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5533403;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1676;1777;";
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
				conv = 177809;
				ctype = 1;
				idx = 5533403;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 177808;
				m1fx = "-2265.000000";
				m2fz = "1986.000000";
				m1fy = "0.000000";
				sort = 177805;
				m2widx = 1;
				grade = 132203;
				m0fx = "-1392.000000";
				m0ttip = 177815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 177802;
				gtype = 2;
				area = 177801;
				goal = 177804;
				m0fz = "-1147.000000";
				m0widx = 1;
				m1ttip = 177816;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "2250.000000";
				m2fx = "-2310.000000";
				m2ttip = 177817;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 0;
				idx0 = 8471200;
				cnt0 = 1;
				cnt2 = 1;
				ectype = -1;
				etype = 0;
				idx1 = 8441200;
				taid = 3;
				esctype = 0;
				idx2 = 8441400;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 177814;
			nextlnk = 101;
			rwdtbl = 177801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5533403;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 177808;
			gtype = 2;
			oklnk = 2;
			area = 177801;
			goal = 177804;
			sort = 177805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 177802;
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

