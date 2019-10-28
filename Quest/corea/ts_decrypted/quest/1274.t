CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1274;
	title = 127402;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 127407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1752103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
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
				conv = 127409;
				ctype = 1;
				idx = 1752103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 127408;
				m1fx = "1736.000000";
				m2fz = "3478.000000";
				m1fy = "0.000000";
				sort = 127405;
				m2widx = 1;
				grade = 132203;
				m0fx = "1994.000000";
				m0ttip = 127415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 127402;
				gtype = 2;
				area = 127401;
				goal = 127404;
				m0fz = "3568.000000";
				m0widx = 1;
				m1ttip = 127416;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "2794.000000";
				m2fx = "2000.000000";
				m2ttip = 127417;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 1;
				idx0 = 805;
				cnt0 = 8;
				cnt2 = 8;
				ectype = -1;
				etype = 0;
				idx1 = 806;
				taid = 3;
				esctype = 0;
				idx2 = 807;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 127414;
			nextlnk = 101;
			rwdtbl = 127401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1752103;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 15;
				iidx = 805;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 15;
				iidx = 807;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 15;
				iidx = 806;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 127408;
			gtype = 2;
			oklnk = 2;
			area = 127401;
			goal = 127404;
			sort = 127405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 127402;
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
			stdiag = 127407;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt2 = 255;
				iprob2 = "1.000000";
				icnt1 = 255;
				iidx0 = 805;
				iidx2 = 807;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
				icnt0 = 255;
				iidx1 = 806;
				iprob0 = "1.000000";
			}
		}
	}
}

