CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1758;
	title = 175802;

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
			cont = 175808;
			gtype = 4;
			oklnk = 2;
			area = 175801;
			goal = 175804;
			sort = 175805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 175802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 175814;
			nextlnk = 101;
			rwdtbl = 175801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1651101;
			}
			CDboTSCheckSToCEvt
			{
				itype = 1;
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
			stdiag = 175807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1651101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 175809;
				ctype = 1;
				idx = 1651101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 175808;
				m1fx = "-132.000000";
				m2fz = "65.000000";
				m1fy = "0.000000";
				sort = 175805;
				m2widx = 10;
				grade = 132203;
				m0fx = "-145.000000";
				m0ttip = 175815;
				m1widx = 10;
				rwd = 100;
				taid = 1;
				title = 175802;
				gtype = 4;
				area = 175801;
				goal = 175804;
				m0fz = "-270.000000";
				m0widx = 10;
				m1ttip = 175816;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-46.000000";
				m2fx = "361.000000";
				m2ttip = 175817;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 1;
				idx0 = 989;
				cnt0 = 8;
				cnt2 = 8;
				ectype = -1;
				etype = 0;
				idx1 = 990;
				taid = 3;
				esctype = 0;
				idx2 = 991;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 175807;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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
				iidx0 = 989;
				iidx2 = 991;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
				icnt0 = 255;
				iidx1 = 990;
				iprob0 = "1.000000";
			}
		}
	}
}

