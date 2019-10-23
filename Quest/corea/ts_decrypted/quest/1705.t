CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1705;
	title = 170502;

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
			stdiag = 170507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1653110;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1685;";
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 170514;
			nextlnk = 101;
			rwdtbl = 170501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1653110;
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
				conv = 170509;
				ctype = 1;
				idx = 1653110;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 1;
				idx0 = 878;
				cnt0 = 10;
				cnt2 = 10;
				ectype = -1;
				etype = 0;
				idx1 = 879;
				taid = 3;
				esctype = 0;
				idx2 = 880;
			}
			CDboTSActRegQInfo
			{
				cont = 170508;
				m1fx = "-620.000000";
				m2fz = "-37.000000";
				m1fy = "0.000000";
				sort = 170505;
				m2widx = 1;
				grade = 132203;
				m0fx = "-595.000000";
				m0ttip = 170515;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 170502;
				gtype = 2;
				area = 170501;
				goal = 170504;
				m0fz = "-9.000000";
				m0widx = 1;
				m1ttip = 170516;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-68.000000";
				m2fx = "-648.000000";
				m2ttip = 170517;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 170508;
			gtype = 2;
			oklnk = 2;
			area = 170501;
			goal = 170504;
			sort = 170505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 170502;
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
				iidx = 880;
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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 170507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

