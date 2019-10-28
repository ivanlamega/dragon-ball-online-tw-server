CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1341;
	title = 134102;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 134107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1431104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 134114;
			nextlnk = 101;
			rwdtbl = 134101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1431104;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 1;
				iidx = 838;
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
				conv = 134109;
				ctype = 1;
				idx = 1431104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 134108;
				m1fx = "0.000000";
				m2fz = "0.000000";
				m1fy = "0.000000";
				sort = 134105;
				m2widx = 1;
				grade = 132203;
				m0fx = "2849.000000";
				m0ttip = 134115;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 134102;
				gtype = 2;
				area = 134101;
				goal = 134104;
				m0fz = "4403.000000";
				m0widx = 1;
				m1ttip = 134115;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "0.000000";
				m2fx = "0.000000";
				m2ttip = 134115;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 838;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 134108;
			gtype = 2;
			oklnk = 2;
			area = 134101;
			goal = 134104;
			sort = 134105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 134102;
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
				iidx = 838;
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
				iidx0 = 838;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 134107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

