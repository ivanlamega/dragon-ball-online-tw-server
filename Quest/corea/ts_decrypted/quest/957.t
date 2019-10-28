CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 957;
	title = 95702;

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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 95709;
				ctype = 1;
				idx = 3172302;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 95708;
				m1fx = "3752.000000";
				m2fz = "-554.000000";
				m1fy = "0.000000";
				sort = 95705;
				m2widx = 1;
				grade = 132203;
				m0fx = "3803.000000";
				m0ttip = 95715;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 95702;
				gtype = 2;
				area = 95701;
				goal = 95704;
				m0fz = "-504.000000";
				m0widx = 1;
				m1ttip = 95715;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-495.000000";
				m2fx = "3744.000000";
				m2ttip = 95715;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 732;
				cnt0 = 3;
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
			cont = 95708;
			gtype = 2;
			oklnk = 2;
			area = 95701;
			goal = 95704;
			sort = 95705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 95702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 95714;
			nextlnk = 101;
			rwdtbl = 95701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3172302;
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
			stdiag = 95707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3172302;
			}
			CDboTSCheckLvl
			{
				maxlvl = 43;
				minlvl = 35;
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
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
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
				iidx0 = 732;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 95707;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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
				iidx = 732;
			}
		}
	}
}

