CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1359;
	title = 135902;

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
			stdiag = 135907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4191114;
			}
			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
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
				conv = 135909;
				ctype = 1;
				idx = 4191114;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 135908;
				m1fx = "1886.000000";
				m2fz = "5585.000000";
				m1fy = "0.000000";
				sort = 135905;
				m2widx = 1;
				grade = 132203;
				m0fx = "1704.000000";
				m0ttip = 135915;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 135902;
				gtype = 2;
				area = 135901;
				goal = 135904;
				m0fz = "5652.000000";
				m0widx = 1;
				m1ttip = 135916;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "5612.000000";
				m2fx = "1801.000000";
				m2ttip = 135917;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 16;
				eitype = 0;
				idx0 = 6613100;
				cnt0 = 16;
				cnt2 = 16;
				ectype = -1;
				etype = 0;
				idx1 = 6613200;
				taid = 3;
				esctype = 0;
				idx2 = 6613300;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 135914;
			nextlnk = 101;
			rwdtbl = 135901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4191114;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 135908;
			gtype = 2;
			oklnk = 2;
			area = 135901;
			goal = 135904;
			sort = 135905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 135902;
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

