CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 878;
	title = 87802;

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
			stdiag = 87807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3181204;
			}
			CDboTSCheckLvl
			{
				maxlvl = 33;
				minlvl = 25;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 87814;
			nextlnk = 101;
			rwdtbl = 87801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3181204;
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
				conv = 87809;
				ctype = 1;
				idx = 3181204;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 87808;
				m1fx = "5785.000000";
				area = 87801;
				goal = 87804;
				m0fz = "2344.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 87816;
				sort = 87805;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "2241.000000";
				grade = 132203;
				m0fx = "5299.000000";
				m0ttip = 87815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 87802;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 1025;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 87808;
			gtype = 2;
			oklnk = 2;
			area = 87801;
			goal = 87804;
			sort = 87805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 87802;
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
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 1025;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 87807;
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

