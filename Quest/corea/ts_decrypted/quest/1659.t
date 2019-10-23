CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1659;
	title = 165902;

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
				conv = 165909;
				ctype = 1;
				idx = 7091105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 165908;
				m1fx = "-2479.000000";
				m2fz = "161.000000";
				m1fy = "0.000000";
				sort = 165905;
				m2widx = 1;
				grade = 132203;
				m0fx = "-1989.000000";
				m0ttip = 165915;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 165902;
				gtype = 2;
				area = 165901;
				goal = 165904;
				m0fz = "80.000000";
				m0widx = 1;
				m1ttip = 165916;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "136.000000";
				m2fx = "-2482.000000";
				m2ttip = 165917;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 0;
				idx0 = 3501110;
				cnt0 = 10;
				cnt2 = 10;
				ectype = -1;
				etype = 0;
				idx1 = 3502106;
				taid = 3;
				esctype = 0;
				idx2 = 3503106;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 165908;
			gtype = 2;
			oklnk = 2;
			area = 165901;
			goal = 165904;
			sort = 165905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 165902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 165914;
			nextlnk = 101;
			rwdtbl = 165901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7091105;
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
			stdiag = 165907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7091105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
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
				itype = 0;
			}
		}
	}
}

