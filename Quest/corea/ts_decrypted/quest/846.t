CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 846;
	title = 84602;

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
			cont = 84608;
			gtype = 3;
			oklnk = 2;
			area = 84601;
			goal = 84604;
			sort = 84605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 84602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 84614;
			nextlnk = 101;
			rwdtbl = 84601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1653108;
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
			stdiag = 84607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1653107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 37;
				minlvl = 29;
			}
			CDboTSCheckClrQst
			{
				and = "845;";
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
				conv = 84609;
				ctype = 1;
				idx = 1653107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 84608;
				m1fx = "636.000000";
				m2fz = "1558.000000";
				m1fy = "0.000000";
				sort = 84605;
				m2widx = 1;
				grade = 132203;
				m0fx = "558.000000";
				m0ttip = 84615;
				m1widx = 3;
				rwd = 100;
				taid = 1;
				title = 84602;
				gtype = 3;
				area = 84601;
				goal = 84604;
				m0fz = "367.000000";
				m0widx = 3;
				m1ttip = 84616;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "369.000000";
				m2fx = "7448.000000";
				m2ttip = 84617;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 595;
				cnt0 = 2;
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
			stdiag = 84607;
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
				iidx = 595;
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
				iidx0 = 595;
				taid = 1;
				type = 1;
			}
		}
	}
}

