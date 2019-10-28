CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 969;
	title = 96902;

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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 96909;
				ctype = 1;
				idx = 4041104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 96908;
				m1fx = "2716.000000";
				m2fz = "105.000000";
				m1fy = "0.000000";
				sort = 96905;
				m2widx = 1;
				grade = 132203;
				m0fx = "2700.000000";
				m0ttip = 96915;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 96902;
				gtype = 2;
				area = 96901;
				goal = 96904;
				m0fz = "45.000000";
				m0widx = 1;
				m1ttip = 96916;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "6.000000";
				m2fx = "2626.000000";
				m2ttip = 96917;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 1;
				idx0 = 736;
				cnt0 = 8;
				cnt2 = 8;
				ectype = -1;
				etype = 0;
				idx1 = 855;
				taid = 3;
				esctype = 0;
				idx2 = 856;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 96914;
			nextlnk = 101;
			rwdtbl = 96901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4041104;
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
			stdiag = 96907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4041104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 43;
				minlvl = 35;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 96908;
			gtype = 2;
			oklnk = 2;
			area = 96901;
			goal = 96904;
			sort = 96905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 96902;
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
			stdiag = 96907;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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
				iidx0 = 579;
				taid = 1;
				type = 1;
			}
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
				iidx = 736;
			}
		}
	}
}

