CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 869;
	title = 86902;

	CNtlTSGroup
	{
		gid = 0;

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
			stdiag = 86907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3181202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 38;
				minlvl = 30;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 86914;
			nextlnk = 101;
			rwdtbl = 86901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3181202;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 602;
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
				conv = 86909;
				ctype = 1;
				idx = 3181202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 86908;
				m1fx = "7448.000000";
				area = 86901;
				goal = 86904;
				m0fz = "-204.000000";
				m0widx = 3;
				m1fy = "0.000000";
				m1ttip = 86916;
				sort = 86905;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "1558.000000";
				grade = 132203;
				m0fx = "446.000000";
				m0ttip = 86915;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 86902;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 602;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 86908;
			gtype = 2;
			oklnk = 2;
			area = 86901;
			goal = 86904;
			sort = 86905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 86902;
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
				iidx = 602;
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
				iidx0 = 602;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 86907;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

