CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1578;
	title = 157802;

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
			stdiag = 157807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6204101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 157814;
			nextlnk = 101;
			rwdtbl = 157801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6204101;
			}
			CDboTSCheckSToCEvt
			{
				itype = 1;
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
				conv = 157809;
				ctype = 1;
				idx = 6204101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 157808;
				m1fx = "-1280.000000";
				m2fz = "1056.000000";
				m1fy = "0.000000";
				sort = 157805;
				m2widx = 1;
				grade = 132203;
				m0fx = "-1189.000000";
				m0ttip = 157815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 157802;
				gtype = 2;
				area = 157801;
				goal = 157804;
				m0fz = "1067.000000";
				m0widx = 1;
				m1ttip = 157816;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "1077.000000";
				m2fx = "-1245.000000";
				m2ttip = 157817;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 1;
				idx0 = 984;
				cnt0 = 8;
				cnt2 = 8;
				ectype = -1;
				etype = 0;
				idx1 = 980;
				taid = 3;
				esctype = 0;
				idx2 = 981;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 157808;
			gtype = 2;
			oklnk = 2;
			area = 157801;
			goal = 157804;
			sort = 157805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 157802;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
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
				iidx0 = 984;
				iidx2 = 981;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
				icnt0 = 255;
				iidx1 = 980;
				iprob0 = "1.000000";
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 157807;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
	}
}

