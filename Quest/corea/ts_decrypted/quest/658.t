CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 658;
	title = 65802;

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
			stdiag = 65807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3032105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckClrQst
			{
				and = "657;";
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 65814;
			nextlnk = 101;
			rwdtbl = 65801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3032105;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 65808;
			gtype = 2;
			oklnk = 2;
			area = 65801;
			goal = 65804;
			sort = 65805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 65802;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 65808;
				m1fx = "6308.000000";
				m2fz = "832.000000";
				m1fy = "0.000000";
				sort = 65805;
				m2widx = 1;
				grade = 132203;
				m0fx = "6326.000000";
				m0ttip = 65815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 65802;
				gtype = 2;
				area = 65801;
				goal = 65804;
				m0fz = "1011.000000";
				m0widx = 1;
				m1ttip = 65816;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "698.000000";
				m2fx = "5475.000000";
				m2ttip = 65817;
			}
			CDboTSActNPCConv
			{
				conv = 65809;
				ctype = 1;
				idx = 3032105;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 1;
				idx0 = 531;
				cnt0 = 8;
				cnt2 = 8;
				ectype = -1;
				etype = 0;
				idx1 = 532;
				taid = 3;
				esctype = 0;
				idx2 = 533;
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

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt2 = 255;
				iprob2 = "1.000000";
				icnt1 = 255;
				iidx0 = 531;
				iidx2 = 533;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
				icnt0 = 255;
				iidx1 = 532;
				iprob0 = "1.000000";
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 65807;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
	}
}

