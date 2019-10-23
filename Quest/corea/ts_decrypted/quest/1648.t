CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1648;
	title = 164802;

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
				eitype = 1;
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
			cont = 164808;
			gtype = 2;
			oklnk = 2;
			area = 164801;
			goal = 164804;
			sort = 164805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 164802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 164814;
			nextlnk = 101;
			rwdtbl = 164801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312110;
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
			stdiag = 164807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6312110;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1643;";
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
				conv = 164809;
				ctype = 1;
				idx = 6312110;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 164808;
				m1fx = "-2589.000000";
				m2fz = "-483.000000";
				m1fy = "0.000000";
				sort = 164805;
				m2widx = 1;
				grade = 132203;
				m0fx = "-2685.000000";
				m0ttip = 164815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 164802;
				gtype = 2;
				area = 164801;
				goal = 164804;
				m0fz = "-495.000000";
				m0widx = 1;
				m1ttip = 164816;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-445.000000";
				m2fx = "-2739.000000";
				m2ttip = 164817;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 1;
				idx0 = 870;
				cnt0 = 8;
				cnt2 = 8;
				ectype = -1;
				etype = 0;
				idx1 = 871;
				taid = 3;
				esctype = 0;
				idx2 = 872;
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
				itype = 1;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 164807;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 720;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 720;
				taid = 1;
				type = 1;
			}
		}
	}
}

