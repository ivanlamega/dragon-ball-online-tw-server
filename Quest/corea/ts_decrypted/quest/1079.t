CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1079;
	title = 107902;

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
			stdiag = 107907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1655101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 107914;
			nextlnk = 101;
			rwdtbl = 107901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1655101;
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
				conv = 107909;
				ctype = 1;
				idx = 1655101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 107908;
				m1fx = "149.000000";
				m2fz = "-355.000000";
				m1fy = "0.000000";
				sort = 107905;
				m2widx = 4;
				grade = 132203;
				m0fx = "76.000000";
				m0ttip = 107915;
				m1widx = 4;
				rwd = 100;
				taid = 1;
				title = 107902;
				gtype = 3;
				area = 107901;
				goal = 107904;
				m0fz = "62.000000";
				m0widx = 4;
				m1ttip = 107916;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-155.000000";
				m2fx = "-340.000000";
				m2ttip = 107917;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 16;
				eitype = 0;
				idx0 = 6612102;
				cnt0 = 16;
				cnt2 = 1;
				ectype = -1;
				etype = 0;
				idx1 = 6612202;
				taid = 3;
				esctype = 0;
				idx2 = 6412202;
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
				eitype = 0;
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
			cont = 107908;
			gtype = 3;
			oklnk = 2;
			area = 107901;
			goal = 107904;
			sort = 107905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 107902;
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
				itype = 0;
			}
		}
	}
}

